#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        void * tempPtrs[10];
        sleep(5);
        int msg = 114514;
        int sendCompleted = 0;
        int sendCompleted2;
        MPI_Request request;
        MPI_Request nullRequest = MPI_REQUEST_NULL;
        void * reqPtr = &request;
        MPI_Isend(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        while (sendCompleted == 0) {
            MPI_Test(reqPtr, &sendCompleted, MPI_STATUS_IGNORE);
            printf("%d", sendCompleted);
        }
        //MPI_Test(reqPtr, &sendCompleted, MPI_STATUS_IGNORE);
        MPI_Test(&nullRequest, &sendCompleted2, MPI_STATUS_IGNORE);
        printf("%d", sendCompleted2);
    } else {
        sleep(1);
    }
    MPI_Finalize();
}