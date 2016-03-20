#include "thread_safe_queue.h"
#include <cassert>

template <typename T>
thread_safe_queue<T>::thread_safe_queue(size_t c): capacity(c) {

}

template <typename T>
bool thread_safe_queue<T>::enqueue(const T& item) {
    std::unique_lock<std::mutex> locker(mutex);

    enq_cv.wait(locker, [this](){return size() < capacity 
                                 || should_shutdown == true;});

    if (should_shutdown)
        return false;

    internal.push_front(item);
    if (size() == 1)
        pop_cv.notify_one();

    return true;
}

template <typename T>
bool thread_safe_queue<T>::pop(T& item) {
    std::unique_lock<std::mutex> locker(mutex);

    pop_cv.wait(locker, [this](){return size() > 0 
                                 || should_shutdown == true;});

    if (should_shutdown && size() == 0)
        return false;

    item = internal.back();
    internal.pop_back();

    if (size() == capacity - 1)
        enq_cv.notify_one();

    return true;
}

template <typename T>
size_t thread_safe_queue<T>::get_capacity() const {
    return capacity;
}
 
template <typename T>
void thread_safe_queue<T>::shutdown() {
    should_shutdown.store(true);
    pop_cv.notify_all();
    enq_cv.notify_all();
}

template <typename T>
size_t thread_safe_queue<T>::size() const {
    return internal.size();
}