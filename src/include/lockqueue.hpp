#ifndef LOCKQUEUE_H_
#define LOCKQUEUE_H_
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
//异步写日志的日志队列
template<typename T>
class LockQueue{
    private:
        std::queue<T> queue_;
        std::mutex mutex_;
        std::condition_variable condition_variable_;
    public:
        void Push(const T& data);
        T& Pop();
};

#endif 