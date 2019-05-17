#include <mpi.h>
#include "Sheduler.h"

Sheduler::Sheduler(int p_id, int p_size, int xn, int yn, int zn)
{
    pro_id = p_id;
    pro_size = p_size;
    task_pool = xn*yn*zn;

    divider = std::make_shared<Divider>(xn*yn*zn);
    worker = std::make_shared<Worker>();

}

Sheduler::~Sheduler()
{
}

void Sheduler::initScatter()
{
    int *task_array = new int[pro_size-1];
    for(int i = -1; i < (pro_size-1); ++i)
    {
        task_array[i+1] = i;
    }
    MPI_Scatter(task_array, 1, MPI_INT, &current_task, 1, MPI_INT, 0, MPI_COMM_WORLD);
    delete[] task_array;
}

void Sheduler::Start()
{
    initScatter();
    int index = pro_size - 1;
    int result_num = 0;
    while(true){
        if (current_task >= 0) {
            //work process
            result_num = worker->GetResult(divider->GetTask(current_task));
            MPI_Send(&result_num, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            printf("\tworker %d send result\n", pro_id);
            MPI_Recv(&current_task, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("\tworker %d recv task %d\n", pro_id, current_task);
        } else if (current_task == -999) {
            //work process
            //reducer send
            printf("********work-reducer %d send all********\n", pro_id);
            break;
        } else {
            //shedule process
            MPI_Status status;//for sheduler
            MPI_Recv(&result_num, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
            printf("Sheduler recv result_num %d\n", result_num);
            //reducer 结果个数累加
            //........
            if (index < task_pool) {
                //send task_id
                MPI_Send(&index, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
                printf("Sheduler send task %d to worker %d\n", index, status.MPI_SOURCE);
            } else if (index < (task_pool+pro_size-1)) {
                int finish_code = -999;
                //send_finish_code
                MPI_Send(&finish_code, 1, MPI_INT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
                printf("----Sheduler send finish_code to worker %d----\n", status.MPI_SOURCE);
            }
            index++;
            if (index == (task_pool+pro_size-1)) {
                /* 已通知所有worker */
                //reducer recv
                //.................
                printf("*****Shedule-reducer recv all*****\n");
                break;
            }
        }
        
    }
}

