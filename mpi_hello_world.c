#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int msg = 1234;

    // Parameters
    // Number of processes
    int nProcesses = 4;
    // Number of messages to send in total
    int maxMsg = 99;
    // Number of failed tests before timeout
    int timeoutLimit = 5;
    // Maximum number of sends in progress
    int windowSize = 50;

    // Number of messages to be sent to each process
    int lower = 5;
    int upper = 50;

    // Flags of total send and receive completion
    int sendCompleted = 0;
    int recvCompleted = 0;

    // Keep track of number of messages sent
    int msgSent[nProcesses - 1];
    memset(msgSent, 0, (nProcesses - 1) * sizeof(int) );
    int totalSent = 0;

    // Keep track of sends in progress
    MPI_Request requestPtrs[windowSize];
    int isWorking[windowSize];
    memset(isWorking, 0, windowSize * sizeof(int) );
    int sendInProgress = 0;

    // Keep track of received messages
    int messagesReceived[nProcesses - 1];
    memset(messagesReceived, 0, (nProcesses - 1) * sizeof(int) );

    // Attempt to send messages
    while (sendCompleted != 1) {

        if (rank == 0) printf("%d", totalSent);
        // Check for sends in progress
        for (int i = 0; i < windowSize; i++) {

            // Send in progress, need to check completion
            if (isWorking[i] == 1) {
                int completed;
                MPI_Test(&requestPtrs[i], &completed, MPI_STATUS_IGNORE);

                // Send is completed, remove it from working list, update numbers in progress
                if (completed == 1) {
                    isWorking[i] = 0;
                    sendInProgress = sendInProgress - 1;
                }

                // Otherwise do nothing
            }
        }

        // Attempt to send one message
        if (sendInProgress < windowSize && sendCompleted == 0) {

            int currIdx = rand() % (nProcesses - 1);
            // Adjust destination index
            int dest;
            if (currIdx < rank) {
                dest = currIdx;
            } else {
                dest = currIdx + 1;
            }
            //printf("process %d sends to process %d \n", rank, dest);
            // Send message
            MPI_Request request;
            MPI_Isend(&msg, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &request);

            // Update send counts
            msgSent[currIdx] = msgSent[currIdx] + 1;
            totalSent = totalSent + 1;

            // Add request to requests in progress
            sendInProgress = sendInProgress + 1;
            for (int i = 0; i < windowSize; i++) {

                // Find empty spot in request array
                if (isWorking[i] == 0) {

                    // Insert current request
                    isWorking[i] = 1;
                    requestPtrs[i] = request;
                    break;
                }
            }
        }
        

        // The last send is done, mark as completed
        if (totalSent >= maxMsg) {
            sendCompleted = 1;
        }

        

    }

    MPI_Barrier(MPI_COMM_WORLD);

    // Receive messages
    while (recvCompleted != 1) {
        // Attempt to receive one message
        if (recvCompleted != 1) {

            // Receive message and source
            int unusedMsg;
            int received = 0;
            MPI_Request receiveRequest;
            MPI_Status status;
            MPI_Irecv(&unusedMsg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &receiveRequest);

            // Test for receive request completion, with a timeout mechanism
            int nTests = 0;
            //printf("process %d start Testing, %d \n", rank, receiveRequest == MPI_REQUEST_NULL);
            //printf("request info on process %d:, %p", rank, receiveRequest);
            while (nTests < timeoutLimit && received == 0) {
                MPI_Test(&receiveRequest, &received, &status);
                nTests = nTests + 1;
            }
            //printf("process %d end Testing \n", rank);
            // Successfully received a message
            if (received == 1) {
                int source = status.MPI_SOURCE;

                // Translate source index to index in counter array
                if (source < rank) {
                    messagesReceived[source] = messagesReceived[source] + 1;
                } else {
                    messagesReceived[source - 1] = messagesReceived[source - 1] + 1;
                }
            }

            // Timeout, assume that no more message is incoming, mark receive completed
            if (nTests == timeoutLimit) {
                MPI_Cancel(&receiveRequest);
                recvCompleted = 1;
            }
            
        }
    }

    // Summarize send and receive results
    for (int r = 0; r < nProcesses - 1; r++) {
        int temp = 0;
        if (r < rank) {
            temp = r;
        } else {
            temp = r + 1;
        }
        printf("process %d sent to process %d: %d \n", rank, temp, msgSent[r]);
        printf("process %d received from process %d: %d \n", rank, temp, messagesReceived[r]);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}