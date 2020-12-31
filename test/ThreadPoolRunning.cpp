//#include "hansaduza/thread_pool.hpp"

#include <gtest/gtest.h>

//#include <mutex>

//using namespace hansaduza;

TEST(ThreadPoolRunning, CheckingDeadlock) {
    int data = 0;
    int count = 40000;
    //std::mutex mtx;
    //{
    //    ThreadPool pool(4);
    //    for(uint idx(0); idx < count; ++idx)
    //        pool.EnqueueJob([&data, &mtx](){
    //            std::lock_guard<std::mutex> lck(mtx);
    //            ++data;
    //        });
    //}
    EXPECT_EQ(data, count);
}