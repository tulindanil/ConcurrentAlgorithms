#include <iostream>
#include <deque>
#include <condition_variable>
#include <mutex>
#include <atomic>

template <typename T>
class thread_safe_queue {

public:

    thread_safe_queue(std::size_t capacity);
    thread_safe_queue(const thread_safe_queue&) = delete;

    bool enqueue(const T& item);
    bool enqueue(T&& item);
    bool pop(T& item);

    inline void shutdown();

    inline size_t get_capacity() const;

    bool pre_push_action(std::unique_lock<std::mutex>& locker);
    void post_push_action();

private:

    std::deque<T> internal; 
    size_t capacity;

    size_t size() const;

    std::atomic_bool should_shutdown;

    std::condition_variable enq_cv, pop_cv;
    std::mutex mutex;

};
