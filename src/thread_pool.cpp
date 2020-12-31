#include "hansaduza/thread_pool.hpp"

#include <functional>
#include <utility>


using namespace hansaduza;

ThreadPool::ThreadPool(uint number_of_threads)
    : stop_all(false)
{
    if(number_of_threads == 0) {
        throw std::invalid_argument("Number of Thread on Thread Pool cannot be zero");
    }

    worker_threads.reserve(number_of_threads);
    for(uint idx(0); idx < number_of_threads; ++idx) {
        this->worker_threads.emplace_back(
            [this](){
                this->WorkThreadPool();
            }
        );
    }
}

ThreadPool::~ThreadPool() {
    this->stop_all = true;
    this->con_var.notify_all();
    for( auto& thread : worker_threads ) {
        thread.join();
    }
}

// EnqueueTask
template <typename F, typename... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::EnqueueJob(F&& f, Args... args){

    using return_type = typename std::result_of<F(Args...)>::type;
    std::packaged_task<return_type> task( std::bind(std::forward<F>(f), std::forward<Args>(args)...) );
    auto task_ptr = std::make_shared<std::packaged_task<return_type>>(task);
    std::future<return_type> task_ret_future = task.get_future();
    
    {
        std::lock_guard<std::mutex> lock(this->mtx);
        task_queue.push(task_ptr);
    }

    con_var.notify_one();

    return task_ret_future;    
}

// DequeueTask
void ThreadPool::WorkThreadPool() {
    while(true) {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->con_var.wait(lock, [this](){
            return !this->task_queue.empty() || this->stop_all;
        });

        if( this->stop_all && this->task_queue.empty() ) {
            // finish job
            return;
        }

        std::function<void()> task = std::move(this->task_queue.front());
        this->task_queue.pop();
        lock.unlock();
        task();
    }
}

bool ThreadPool::IsStop() const {
    return this->stop_all;
}

uint ThreadPool::GetCurrentTaskNumber() const {
    return this->task_queue.size();
}

uint ThreadPool::GetNumberOfThreads() const {
    return this->worker_threads.size();
}