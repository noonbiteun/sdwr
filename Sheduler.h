#ifndef SHEDULER_H_INCLUDE
#define SHEDULER_H_INCLUDE

#include <memory>
#include <iostream>
#include "Divider.h"
#include "Worker.h"
#include "Reducer.h"

class Sheduler
{
private:
    int pro_id;//current process id
    int pro_size;//running process size
    int task_pool;
    int current_task = -1;
    std::shared_ptr<Divider> divider;
    std::shared_ptr<Worker> worker;
    std::shared_ptr<Reducer> reducer;

    void initScatter();
public:
    Sheduler(int, int, int, int, int);
    ~Sheduler();

    void Start();
};

#endif