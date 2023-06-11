#include "lci.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char** args) {
    // Initialize device and endpoint
    LCI_initialize();
    LCI_device_t device;
    LCI_endpoint_t ep;

    // Set Completion and Send matching mechanisms
    LCI_plist_t plist;
    LCI_plist_set_comp_type(plist, LCI_PORT_COMMAND, LCI_COMPLETION_SYNC);
    LCI_plist_set_comp_type(plist, LCI_PORT_MESSAGE, LCI_COMPLETION_SYNC);
    // Match by tag only to achieve results similar to MPI_ANY_SOURCE
    LCI_plist_set_match_type(plist, LCI_MATCH_TAG);
    LCI_endpoint_init(&ep, device, plist);
    LCI_plist_free(&plist);

    // Number of messages
    int nMessages = 20;
    int nProcesses = 4;
    int timeoutLimit = 50;

    // Create synchronizer
    LCI_comp_t sync;
    LCI_sync_create(device, 1, &sync);

    LCI_short_t message;
    *(uint64_t*)&message = 123;
    void* user_context = (void*)9527;

    // even rank first send then receive
    if (LCI_RANK % 2 == 0) {

        // Keep track of number of messages sent and received
        int nDests = nProcesses / 2;
        int msgSent[nDests];
        memset(msgSent, 0, nDests * sizeof(int));
        int nSources = nDests;
        int msgReceived[nSources];
        memset(msgReceived, 0, nSources * sizeof(int));

        // Send messages
        for (int i = 0; i < nMessages; i++) {

            // Create a random index to send message to
            int tempIdx = rand() % nDests;
            int dest = 2 * tempIdx + 1;

            // Use the rank of receiver as tag
            // Receiver can match any sends with tag equal to its rank
            while (LCI_sends(ep, message, dest, dest) == LCI_ERR_RETRY) {
                LCI_progress(device);
            }

            msgSent[tempIdx] = msgSent[tempIdx] + 1;
            
        }

        // Receive messages
        int failedRecvs = 0;
        while (failedRecvs < timeoutLimit) {
            LCI_request_t request;
            LCI_recvs(ep, 0, LCI_RANK, sync, user_context);
            if (LCI_sync_test(sync, &request) == LCI_ERR_RETRY) {
                failedRecvs = failedRecvs + 1;
            } else {
                int source = request.rank;
                msgReceived[source / 2] = msgReceived[source / 2] + 1;
            }
            LCI_progress(device);
            
        }

    } else {

        // Keep track of number of messages sent and received
        int nDests = nProcesses / 2 + nProcesses % 2;
        int msgSent[nDests];
        memset(msgSent, 0, nDests * sizeof(int));
        int nSources = nDests;
        int msgReceived[nSources];
        memset(msgReceived, 0, nSources * sizeof(int));

        // Receive messages
        int failedRecvs = 0;
        while (failedRecvs < timeoutLimit) {
            LCI_request_t request;
            LCI_recvs(ep, 0, LCI_RANK, sync, user_context);
            if (LCI_sync_test(sync, &request) == LCI_ERR_RETRY) {
                failedRecvs = failedRecvs + 1;
            } else {
                int source = request.rank;
                msgReceived[source / 2] = msgReceived[source / 2] + 1;
            }
            LCI_progress(device);

        }

        // Send messages
        for (int i = 0; i < nMessages; i++) {

            // Create a random index to send message to
            int tempIdx = rand() % nDests;
            int dest = 2 * tempIdx;

            // Use the rank of receiver as tag
            // Receiver can match any sends with tag equal to its rank
            while (LCI_sends(ep, message, dest, dest) == LCI_ERR_RETRY) {
                LCI_progress(device);
            }

            msgSent[tempIdx] = msgSent[tempIdx] + 1;
            
        }

        
    }
    
}
