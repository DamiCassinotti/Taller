#ifndef TP2_READER_H
#define TP2_READER_H

#include <string>
#include "Thread.h"
#include "BlockingString.h"
#include "File.h"

class Reader : public Thread {
private:
    File &file;
    BlockingString &input;
public:
    Reader(File &file, BlockingString &input);
    void run();
    ~Reader();
};


#endif //TP2_READER_H
