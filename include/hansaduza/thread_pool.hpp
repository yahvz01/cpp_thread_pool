#pragma once;


#include <type_traits>
#include <mutex>
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <functional>

#include <future>

namespace hansaduza {
    class ThreadPool {
    public :
        ThreadPool(uint number_of_threads);
        ~ThreadPool();

        template <typename F, typename... Args>
        std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(F, Args... args);

        bool Stop();
        bool IsStop() const;
        uint GetCurrentTaskNumber() const;
        uint GetNumberOfThreads() const;
        
    private:
        void WorkThreadPool();
        bool stop_all;
        
        std::mutex mtx;

        std::vector<std::thread> worker_threads;

        std::condition_variable con_var;
        std::queue<std::function<void()>> task_queue;
    };
}