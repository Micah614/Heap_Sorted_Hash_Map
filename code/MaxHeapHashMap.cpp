#include "MaxHeapHashMap.h"
#include "DataPacket.h"

#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <queue>
#include <memory>
#include <string>
#include <map>
#include <stack>
#include <cmath>

using namespace std;


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@ HASHMAP FUNCTIONS (START) @@@@@@@@@@@@@@@@@@@@@@@@@@@@

/* EACH HASHMAP INSTANTIATES AND CONTROLS FIVE MAXHEAPPQ DOMAINS*/
// 
HashMap::HashMap() {

}
// 
HashMap::~HashMap() {
    // DO STUFF
}

// 
MaxHeapPQ::MaxHeapPQ() {
    // DO STUFF
}
// 
MaxHeapPQ::~MaxHeapPQ() {
    // DO STUFF
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%% INSTANTIATING FUNCTIONS (START HERE) %%%%%%%%%%%%%%%%%%%%%%%%%%%
// collects five pointers for MaxHeap PQ top nodes, instantiates a map and returns a pointer.
void HashMap::initHashMap() {
    std::shared_ptr<MaxHeapPQ> uxui_interface {new MaxHeapPQ};  // uxui_interface is now a shared pointer to a MaxHeapPQ object.
    (*uxui_interface).InitPqDomain("uxui_interface");  // calling InitPqDomain(1) to populate the object data members.Now, pass "uxui_interface" to the map.

    std::shared_ptr<MaxHeapPQ> db_config {new MaxHeapPQ}; 
    (*db_config).InitPqDomain("db_config");

    std::shared_ptr<MaxHeapPQ> launch_files {new MaxHeapPQ};
    (*launch_files).InitPqDomain("launch_files");
    
    std::shared_ptr<MaxHeapPQ> registration {new MaxHeapPQ};
    (*registration).InitPqDomain("registration");
    
    std::shared_ptr<MaxHeapPQ> exec_files {new MaxHeapPQ};
    (*exec_files).InitPqDomain("exec_files");

    // Create the HashMap table container
    table = { {1, uxui_interface}, {2, db_config}, {3, launch_files}, {4, registration}, {5, exec_files} };  // ass
    //table = std::map<int, shared_ptr<MaxHeapPQ>> newTable { {1, uxui_interface}, {2, db_config}, {3, launch_files}, {4, registration}, {5, exec_files} };  // assign the map to the HashMap table data member
    packetCount = 0;
    //return table;
}

// Initiate a max heap with the indicated domain and capacity.(Index properties are in DataPacket class)
void MaxHeapPQ::InitPqDomain(string domain_ID) {
    // MaxHeapPQ newQueue;  // instantiate a queue.
    domain = domain_ID;  // assign it the given domain_ID.
    nodeCount = 0;  // zero DataPackets to start, increment counter during MaxHeapInsert().

    // initialize the pqarray with NULL pointers (replaced with DataPacket shared_ptrs during insertion).
    for(int i=0; i<PQ_SIZE; ++i) {
        pqMaxHeapArray[i] = nullptr;  // populate the array with null pointers to start.
    }
    // create an "error node" DataPacket object with call to InitDataPacket().
    //pqEmptyNode.InitDataPacket("Error: the pq you accessed was empty.", -1, domain_ID);
    pqTopPointer = pqMaxHeapArray[0];  // pqTop always points at index zero.
}










