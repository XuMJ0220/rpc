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
        T Pop();
};

template<typename T>
void LockQueue<T>::Push(const T& data){
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(data);
    condition_variable_.notify_one();
}

template<typename T>
T LockQueue<T>::Pop(){
    std::unique_lock<std::mutex> lock(mutex_);
    while(queue_.empty()){
        condition_variable_.wait(lock);
    }
    T data = queue_.front();
    queue_.pop();
    return data;
}

#endif 