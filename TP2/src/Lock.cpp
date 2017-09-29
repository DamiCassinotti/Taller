#include "Lock.h"
#include <mutex>

Lock::Lock(std::mutex &mtx) : mtx(mtx) {
    mtx.lock();
}

Lock::~Lock() {
    mtx.unlock();
}
