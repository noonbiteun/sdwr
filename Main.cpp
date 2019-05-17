#include <iostream>
#include <mpi.h>
#include "Sheduler.h"

int main(int argc, char const *argv[])
{
    MPI_Init(NULL, NULL);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    Sheduler s(rank, size, 5, 3, 2);
    s.Start();
    MPI_Finalize();
    return 0;
}
