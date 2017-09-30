#ifndef TP2_BLOCKINGSTRING_H
#define TP2_BLOCKINGSTRING_H

#include <mutex>
#include <condition_variable>
#include <string>

class BlockingString {
private:
    std::mutex mtx;
    std::condition_variable input_ready;
    std::condition_variable output_ready;
    std::string input;
public:
    BlockingString();
    ~BlockingString();
    void insert(std::string input);
    std::string getString();
};


#endif //TP2_BLOCKINGSTRING_H
