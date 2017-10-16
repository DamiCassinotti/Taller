#ifndef TP2_WRITER_H
#define TP2_WRITER_H

#include <string>
#include "Thread.h"
#include "File.h"
#include "BlockingString.h"

// Thread para escritura en archivo
class Writer : public Thread {
private:
    File &file;
    BlockingString &input;
public:
    Writer(File &file, BlockingString &input);
    void run();
    ~Writer();
};


#endif //TP2_WRITER_H
