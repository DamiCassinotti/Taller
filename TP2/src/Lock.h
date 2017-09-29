#ifndef TP2_LOCK_H
#define TP2_LOCK_H

#include <mutex>


class Lock {
private:
    std::mutex& mtx;
public:
    Lock(std::mutex &mtx);
    ~Lock();
    Lock(const Lock&) = delete;
    Lock& operator=(const Lock&) = delete;
    Lock(Lock&&) = delete;
    Lock& operator=(Lock&&) = delete;
};


#endif //TP2_LOCK_H
