#pragma once
#include <mutex>
#include <condition_variable>
#include <chrono>
class MyEvent
{
public:

    MyEvent(bool initial, bool manual) :
        state(initial), manual(manual)
    {
    }
    void set()
    {
        std::unique_lock<std::mutex> lock(mutex);

        if (state)
            return;

        state = true;
        if (manual)
            condition.notify_all();
        else
            condition.notify_one();
    }
    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex);

        condition.wait(lock, [this] { return state; });

        if (!manual)
            state = false;
    }
private:
    std::mutex mutex;
    std::condition_variable condition;
    bool state, manual;
};

