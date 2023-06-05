#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

// 异步写日志的日志队列
template <typename T>
class LockQueue
{
public:
    // 多个worker线程都会写日志queue
    void Push(const T &data)
    {
        std::lock_guard<std::mutex> lock(v_mutex);
        v_queue.push(data);
        v_condvariable.notify_one();
    }

    // 一个线程读日志queue，写日志文件
    T Pop()
    {
        std::unique_lock<std::mutex> lock(v_mutex);
        while (v_queue.empty())
        {
            v_condvariable.wait(lock);
        }

        T data = v_queue.front();
        v_queue.pop();
        return data;
    }

private:
    std::queue<T> v_queue;
    std::mutex v_mutex;
    std::condition_variable v_condvariable;
};