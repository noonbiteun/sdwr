#include "Divider.h"

Divider::Divider(int dz):divide_size(dz)
{

}

Divider::~Divider()
{}

Task_Ptr Divider::GetTask(int task_id)
{
    /* 用户自定义任务划分操作 */
    // printf("get task %d\n", task_id);
    return std::make_shared<Task>();
}
