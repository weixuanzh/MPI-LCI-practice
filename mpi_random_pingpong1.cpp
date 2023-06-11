#include "/lib/x86_64-linux-gnu/openmpi/include/mpi.h"
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
using namespace std;

int main(int argc, char** argv) {

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int msg = 1234;

    // Parameters
    // Number of processes
    int nProcesses;
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    // Rate limit
    // Rate is defined as messages / second
    double rate = 1000000;
    // interval is in microsecond (1e-6)
    uint64_t interval = 1000000.0 / rate;

    // Number of messages to be sent to each process
    int numMessages = 2000;
    int lower = 100;
    int upper = 1500;

    // Determine if given lower and upper are possible
    assert(nProcesses * lower <= numMessages);
    assert(nProcesses * upper >= numMessages);

    // Number of completed recvs and recvs from each process
    int nRecv = 0;
    int msgRecved[nProcesses] = {0};
    int msgSent[nProcesses] = {0};

    srand((unsigned) (time(NULL) + rank));

    // generate random number of sends and recvs
    int sendCounts[nProcesses];
    // index of destination
    vector<int> dests;
    for (int i = 0; i < nProcesses; i++) {

        // Calculate a random number within limit
        if (i == nProcesses - 1) {
            sendCounts[i] = numMessages;
        } else {

            // Make sure the current and future random number can meet upper and lower requirements
            int remaining = nProcesses - i - 1;
            int tempLower = numMessages - upper * remaining;
            int tempUpper = numMessages - lower * remaining;
            int newLower = max(tempLower, lower);
            int newUpper = min(tempUpper, upper);
            sendCounts[i] = (rand() % (newUpper - newLower + 1)) + newLower;
            numMessages = numMessages - sendCounts[i];
        }
        dests.push_back(i);
    }
    
    // Expected number of messages received
    int totalRecvs[nProcesses] = {0};
    MPI_Allreduce(&sendCounts, &totalRecvs, nProcesses, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    
    // Send and recv
    // Post a recv request
    MPI_Request recvRequest;
    int unusedMsg;
    MPI_Irecv(&unusedMsg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &recvRequest);
    uint64_t lastSend = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    uint64_t start = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    while(dests.size() != 0) {

        // Rate limiter
        uint64_t now = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
        int withinLimit = 0;
        if (now - lastSend > interval) {
            withinLimit = 1;
        }
        // Send message
        int dest;
        if (withinLimit) {
            int idx = rand() % dests.size();
            dest = dests[idx];
            MPI_Request sendRequest;
            MPI_Isend(&msg, 1, MPI_INT, dest, 0, MPI_COMM_WORLD, &sendRequest);
            lastSend = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

            // Update number of messages sent
            msgSent[dest]++;
            sendCounts[dest]--;

            // Remove corresponding destination index when completed
            if (sendCounts[dest] == 0) {
                dests.erase(std::remove(dests.begin(), dests.end(), dest), dests.end());
            }
        }

        // Receive message, if received, post a new reqeust
        MPI_Status status;
        int received = 0;
        MPI_Test(&recvRequest, &received, &status);
        // When receive is successful, post a new request, update receive counts
        if (received == 1) {
            MPI_Irecv(&unusedMsg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &recvRequest);
            nRecv = nRecv + 1;
            msgRecved[status.MPI_SOURCE] = msgRecved[status.MPI_SOURCE] + 1;
        }
    }

    uint64_t sendDone = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    // Continue to receive until nRecv matches expected number of recvs
    while (nRecv < totalRecvs[rank]) {
        // Receive message, if received, post a new reqeust
        MPI_Status status;
        int received = 0;
        MPI_Test(&recvRequest, &received, &status);
        // When receive is successful, post a new request, update receive counts
        if (received == 1) {
            MPI_Irecv(&unusedMsg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &recvRequest);
            msgRecved[status.MPI_SOURCE] = msgRecved[status.MPI_SOURCE] + 1;
            nRecv = nRecv + 1;
        }
    }

    uint64_t recvDone = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    // Summarize send and recv results
    // Correctness
    // for (int r = 0; r < nProcesses; r++) {
    //     printf("process %d sent to process %d: %d \n", rank, r, msgSent[r]);
    //     printf("process %d received from process %d: %d \n", rank, r, msgRecved[r]);
    // }

    // Send and recv time
    printf("Send takes %f ms\n", (sendDone - start) / 1000.0);
    printf("Total time: %f ms \n", (recvDone - start) / 1000.0);

    // Finalize the MPI environment.
    MPI_Finalize();
}