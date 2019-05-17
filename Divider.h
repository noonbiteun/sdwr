#ifndef DIVIDER_H_INCLUDE
#define DIVIDER_H_INCLUDE

#include <memory>
#include <iostream>

struct Task
{
    /* 用户自定义任务数据结构 */

};

typedef std::shared_ptr<Task> Task_Ptr;

class Divider
{
private:
    const int divide_size;

public:
    Divider(int);
    ~Divider();
    
    Task_Ptr GetTask(int);
};

#endif