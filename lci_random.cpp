#include "/home/weixuan/library/lci/include/lci.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

// Assumes little endian
void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main(int argc, char** args) {
    // Initialize device and endpoint
    LCI_initialize();

    LCI_device_t device;

    LCI_device_init(&device);

    LCI_endpoint_t ep;
    
    // Initialize completion queue
    LCI_comp_t cq;
    LCI_queue_create(device, &cq);

    // Set Completion and Send matching mechanisms
    LCI_plist_t plist;

    LCI_plist_create(&plist);

    LCI_plist_set_comp_type(plist, LCI_PORT_COMMAND, LCI_COMPLETION_QUEUE);

    LCI_plist_set_comp_type(plist, LCI_PORT_MESSAGE, LCI_COMPLETION_QUEUE);

    LCI_plist_set_match_type(plist, LCI_MATCH_RANKTAG);

    LCI_plist_set_default_comp(plist, cq);

    LCI_endpoint_init(&ep, device, plist);

    LCI_plist_free(&plist);

    // Number of messages
    int numMessages = 2000;
    int lower = 100;
    int upper = 1500;
    const int nProcesses = LCI_NUM_PROCESSES;

    // Determine if given lower and upper are possible
    assert(nProcesses * lower <= numMessages);
    assert(nProcesses * upper >= numMessages);

    // Rate limit
    // Rate is defined as messages / second
    double rate = 1000000;
    // interval is in microsecond (1e-6)
    uint64_t interval = 1000000.0 / rate;
    
    // Number of message to send to each process
    srand((unsigned) (time(NULL) + LCI_RANK));
    int sendCounts[nProcesses];
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

    // Keep track of messages sent and recved
    int msgSent[nProcesses];
    int msgRecved[nProcesses];
    memset(msgSent, 0, nProcesses * sizeof(int));
    memset(msgRecved, 0, nProcesses * sizeof(int));

    // Send expected message counts to all processes
    // Message count is sent in the tag of the message (corrupted memory when sending with data)
    LCI_short_t src;
    for (int i = LCI_RANK; i < LCI_RANK + nProcesses; i++) {
        
        *(uint32_t*)&src = (uint32_t) sendCounts[i % nProcesses];
        while (LCI_puts(ep, src, i % nProcesses, sendCounts[i % nProcesses], LCI_DEFAULT_COMP_REMOTE) == LCI_ERR_RETRY) {
            LCI_progress(device);
        }

    }

    // Recv expected message counts
    int nRecved = 0;
    // Expected total recv
    int expectedRecv = 0;

    while (nRecved < nProcesses) {
        LCI_request_t request;
        while (LCI_queue_pop(cq, &request) == LCI_ERR_RETRY) {
            LCI_progress(device);
            
        }
        nRecved++;

        // Write expected number of recved message

        // if (*(uint32_t*)&request.data.immediate != request.tag) {
        //     printf("src is: %d\n", *(uint32_t*)&request.data.immediate );
        //     printf("tag is: %d\n", request.tag );
        // }
        expectedRecv = expectedRecv + request.tag;
    }

    // Send and receive messages
    int sendCompleted = 0;
    int nRecv = 0;

    // Timer to limit rate
    uint64_t lastSend = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    LCI_short_t unused;
    *(uint64_t*)&unused = 1;

    uint64_t sendStart = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    while (dests.size() != 0) {

        // Generate a random destination
        // rand_r()
        int dest = dests[rand() % dests.size()];
        
        uint64_t now = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
        // Send messages if within rate limit

        if (now - lastSend > interval) {

            while (LCI_puts(ep, unused, dest, 0, LCI_DEFAULT_COMP_REMOTE) == LCI_ERR_RETRY) {
                LCI_progress(device);
            }
            lastSend = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
            // Update send counts
            sendCounts[dest]--;
            msgSent[dest]++;
            if (sendCounts[dest] == 0) {
                dests.erase(std::remove(dests.begin(), dests.end(), dest), dests.end());
            }
            
        } else {
            LCI_progress(device);
        }

        // Receive message
        if (nRecv < expectedRecv) {
            LCI_request_t request;
            if (LCI_queue_pop(cq, &request) == LCI_OK) {
                nRecv++;
                msgRecved[request.rank]++;
            }
            LCI_progress(device);
        }

    }
    uint64_t sendFinish = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    // Wait for recv to complete
    while (nRecv < expectedRecv) {

        LCI_request_t request;
        while (LCI_queue_pop(cq, &request) == LCI_ERR_RETRY) {
            LCI_progress(device);
        }
        nRecv++;
        msgRecved[request.rank]++;
    }

    uint64_t recvFinish = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();

    // for (int r = 0; r < nProcesses; r++) {
    //     printf("process %d sent to process %d: %d \n", LCI_RANK, r, msgSent[r]);
    //     printf("process %d received from process %d: %d \n", LCI_RANK, r, msgRecved[r]);
    // }
    printf("Send takes %f ms\n", (sendFinish - sendStart) / 1000.0);
    printf("Total time: %f ms \n", (recvFinish - sendStart) / 1000.0);

    // Finalize LCI environment
    LCI_finalize();
}
