#ifndef WORKER_H_INCLUDE
#define WORKER_H_INCLUDE

#include <memory>
#include "Divider.h"

struct Result
{
    /* data */
};

typedef std::shared_ptr<Result> Result_Ptr;

class Worker
{
private:
    /* data */
public:
    Worker(/* args */);
    ~Worker();

    int GetResult(Task_Ptr);
};

#endif