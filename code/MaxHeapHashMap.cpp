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
    std::shared_ptr<MaxHeapPQ> uxui_interface {new MaxHeapPQ};  // create a new MaxHeapPQ object
    (*uxui_interface).InitPqDomain("uxui_interface");  // initialize the domain
    //
    std::shared_ptr<MaxHeapPQ> db_config {new MaxHeapPQ};  // create a new MaxHeapPQ object
    (*db_config).InitPqDomain("db_config");  // initialize the domain
    //
    std::shared_ptr<MaxHeapPQ> launch_files {new MaxHeapPQ};  // create a new MaxHeapPQ object
    (*launch_files).InitPqDomain("launch_files");  // initialize the domain
    //
    std::shared_ptr<MaxHeapPQ> registration {new MaxHeapPQ};  // create a new MaxHeapPQ object
    (*registration).InitPqDomain("registration");  // initialize the domain
    //
    std::shared_ptr<MaxHeapPQ> exec_files {new MaxHeapPQ};  // create a new MaxHeapPQ object
    (*exec_files).InitPqDomain("exec_files");  // initialize the domain
    // Create HashMap table container
    table = { {1, uxui_interface}, {2, db_config}, {3, launch_files}, {4, registration}, {5, exec_files} };
    packetCount = 0;
}

// Initiate a max heap with the indicated domain and capacity.(Index properties are in DataPacket class)
void MaxHeapPQ::InitPqDomain(string domain_ID) {
    domain = domain_ID;  // update domain_ID.
    nodeCount = 0;  // set node count at zero
    currentIndex = 0;  // set currentIndex at zero.
    for(int i=0; i<PQ_SIZE; ++i) {  // initialize the array with NULL pointers
        pqMaxHeapArray[i] = nullptr;  // populate the array with null pointers to start. PQ_SIZE == 100
    }
    pqTopPointer = pqMaxHeapArray[0];  // pqTopPointer is always at index zero.
}

// use this function to insert DataPackets into instantiated MaxHeapHashMap objects.
void HashMap::assignPqDomainAndInsert(shared_ptr<DataPacket> packet) {
    int domainKey = (*packet).domain_ID;  // extract domain_ID from DataPacket (public)
    map<int, shared_ptr<MaxHeapPQ>>::iterator it;  // declare iterator for the map
    shared_ptr<MaxHeapPQ> assignedPQ;  // declare a variable for collecting the MaxHeapPQ pointer
    for(it=table.begin(); it!=table.end(); it++) {
        if(it->first == domainKey) {
            assignedPQ = it->second;
        }
    }
    (*assignedPQ).pqInsert(packet);  // access the underlying MaxHeapPQ and insert the packet pointer.
    packetCount++;  // HashMap's packetCounter is incremented.
}

void MaxHeapPQ::pqInsert(shared_ptr<DataPacket> packet) {
    int packetPriority = (*packet).GetPacketPriority();  // extract the packet priority
    int insertionIndex = currentIndex;  // member variables are accessible inside MaxHeapPQ member functions 
    // If the array is empty...
    if(nodeCount == 0) {  
        (*packet).InsertNodeData(0);  // 
        pqMaxHeapArray[insertionIndex] = packet;  // 
        currentIndex++;  // 
        nodeCount++;  // 
        return;
    }
    else {
        (*packet).InsertNodeData(insertionIndex);  // 
        pqMaxHeapArray[insertionIndex] = packet;  // 
        nodeCount++;  // 
        currentIndex++;  // 
        MaxHeapPercolateUp(currentIndex-1, packetPriority);
    }
  return;
}

void MaxHeapPQ::MaxHeapPercolateUp(int nodeIndex, int packetPriority) {
    shared_ptr<DataPacket> temp;  // temporary pointer variable to switch node pqArray indices
    int percolateIndex = nodeIndex;
    while(percolateIndex > 0) {
        int parentIdx = floor((percolateIndex - 1) / 2);
        if( (*pqMaxHeapArray[percolateIndex]).GetPacketPriority() < (*pqMaxHeapArray[parentIdx]).GetPacketPriority()) {
            return;  // Done
        }
        else {  // otherwise, swap 
            temp = pqMaxHeapArray[percolateIndex];  // temp variable holds child pointer
            pqMaxHeapArray[percolateIndex] = pqMaxHeapArray[parentIdx];  // child index holds parent pointer
            pqMaxHeapArray[parentIdx] = temp;  // parent index holds previous child pointer
            percolateIndex = parentIdx;  // update percolateIndex for next iteration.
        }
    }
}


// INDEXING AND REMOVAL FUNCTIONS
// 
shared_ptr<DataPacket> indexPqAndRetrievePacket(int domain_ID) {
    // DO STUFF
}










