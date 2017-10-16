#ifndef TP2_THREAD_H
#define TP2_THREAD_H

#include <thread>

// Clase abstracta para generalizar los threads
class Thread {
private:
    std::thread thread;
public:
    Thread();
    void start();
    void join();
    virtual void run() = 0;
    virtual ~Thread();
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread(Thread&& other);
    Thread& operator=(Thread&& other);
};


#endif //TP2_THREAD_H
