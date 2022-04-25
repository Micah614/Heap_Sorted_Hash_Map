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

/* EACH HASHMAP INSTANTIATES AND CONTROLS FIVE SEPARATE MAXHEAPPQ DOMAINS*/
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
    nextIndex = 0;  // set currentIndex at zero.
    for(int i=0; i<PQ_SIZE; ++i) {  // initialize the array with NULL pointers
        pqMaxHeapArray[i] = nullptr;  // populate the array with null pointers to start. PQ_SIZE == 100
    }
    pqTopPointer = pqMaxHeapArray[0];  // pqTopPointer is always at index zero.
}


// use this function to insert DataPackets into instantiated MaxHeapHashMap objects.
void HashMap::assignPqDomainAndInsert(shared_ptr<DataPacket> packet) {
    int domainKey = (*packet).domain_ID;  // EXTRACT DOMAIN_ID
    shared_ptr<MaxHeapPQ> assignedPQ;  // DECLARE VARIABLE FOR ASSIGNED PQ

    map<int, shared_ptr<MaxHeapPQ>>::iterator it;  // ITERATE THROUGH "table"
    for(it=table.begin(); it!=table.end(); it++) {
        if(it->first == domainKey) {
            assignedPQ = it->second;  // COLLECT POINTER TO ASSIGNED DOMAIN PQ
        }
    }
    (*assignedPQ).pqInsert(packet);  // INSERT PACKET INTO ASSIGNED PQ
    packetCount++;  // "packetCount" INCREASES BY ONE
}


void MaxHeapPQ::pqInsert(shared_ptr<DataPacket> packet) {
    int packetPriority = (*packet).GetPacketPriority();  // COLLECT PRIORITY
    if(nextIndex == 0) {  // "pqArray" IS EMPTY
        (*packet).InsertNodeData(0);  // UPDATE DataPacket MEMBER VARIABLES
        pqMaxHeapArray[0] = packet;  // INSERT packet AT INDEX ZERO
        nextIndex++;  // INCREMENT nextIndex
        nodeCount++;  // INCREMENT nodeCount
        return;
    }
    else {
        (*packet).InsertNodeData(nextIndex);  // UPDATE DataPacket MEMBER VARIABLES
        pqMaxHeapArray[nextIndex] = packet;  // INSERT packet AT nextIndex
        nodeCount++;  // INCREMENT MAXHEAP nodeCount
        nextIndex++;  // INCREMENT MAXHEAP nextIndex
        MaxHeapPercolateUp(packet);  // PERCOLATE UP AT 
    }
  return;
}

void MaxHeapPQ::MaxHeapPercolateUp(shared_ptr<DataPacket> packet) {
    int parentIdx;
    int parentPriority;
    int percPriority;
    int percIdx = (*packet).GetPqIndex();
    shared_ptr<DataPacket> temp;

    bool isDone = false;
    while(isDone != true) {  // 

        parentIdx = (*packet).GetParentIndex();
        percPriority = (*packet).GetPacketPriority(); 
        parentPriority = (*pqMaxHeapArray[parentIdx]).GetPacketPriority();
    
        if(parentPriority > percPriority || parentIdx == NULL) {
            isDone = true;
            break;
        }
        else {
            // SWAP DATA
            (*pqMaxHeapArray[percIdx]).InsertNodeData(parentIdx);
            (*pqMaxHeapArray[parentIdx]).InsertNodeData(percIdx);
            // SWAP LOCATIONS
            temp = pqMaxHeapArray[parentIdx];
            pqMaxHeapArray[parentIdx] = pqMaxHeapArray[percIdx];
            pqMaxHeapArray[percIdx] = temp;
            percIdx = parentIdx;
        }  
    }
    return;
}

// INDEX AND REMOVAL FUNCTIONS
// 
shared_ptr<DataPacket> HashMap::indexPqAndRetrievePacket(int domain_ID) {
    shared_ptr<MaxHeapPQ> indexedPQ;  // 
    shared_ptr<DataPacket> returnPacket;  // 

    map<int, shared_ptr<MaxHeapPQ>>::iterator it;  // 
    for(it=table.begin(); it!=table.end(); it++) {
        if(it->first == domain_ID){  // 
            indexedPQ = it->second;
        }
    }
    returnPacket = (*indexedPQ).RemoveTopPriority();  // CALL RemoveTopPriority ON *indexedPQ
    packetCount--;  // HashMap packetCount DECREMENTS BY ONE.
    return returnPacket;
}

// 
shared_ptr<DataPacket> MaxHeapPQ::RemoveTopPriority() {
    shared_ptr<DataPacket> returnPacket;  // 
    int lastIdx = nextIndex - 1;  // LAST OCCUPIED pqMaxHeapArray INDEX

    // MAX PRIORITY IS AT INDEX 0
    returnPacket = pqMaxHeapArray[0];  // COLLECT THE TOP POINTER
    pqMaxHeapArray[0] = pqMaxHeapArray[lastIdx];  // SWAP TOP NODE WITH LAST NODE
    (*pqMaxHeapArray[0]).InsertNodeData(0);  // UPDATE DATAPACKET MEMBER VARIABLES
    pqMaxHeapArray[lastIdx] = nullptr;  // DELETE LAST INDEX
    nodeCount--;  // 
    nextIndex--;  // 

    // MAINTAIN HEAP INVARIANTS
    MaxHeapPercolateDown();  // CALL PERCOLATE DOWN ON CURRENT MaxHeapPQ
    pqTopPointer = pqMaxHeapArray[0];  // REASSIGN pqTopPointer AFTER PERCOLATE DOWN
    return returnPacket;
}

// FIX ME!!!!
void MaxHeapPQ::MaxHeapPercolateDown() {
    int leftChildIdx;
    int rightChildIdx;
    int percNodePriority;
    int leftChildPriority;
    int rightChildPriority;
    //
    shared_ptr<DataPacket> temp;
    int percIndex = 0;
    bool done = false;  // DECLARE WHILE-LOOP SENTINEL VALUE
    //
    while(done != true) {
        //
        leftChildIdx = (*pqMaxHeapArray[percIndex]).GetLeftChildIndex();
        rightChildIdx = (*pqMaxHeapArray[percIndex]).GetRightChildIndex();
        //
        percNodePriority = (*pqMaxHeapArray[percIndex]).GetPacketPriority();
        leftChildPriority = (*pqMaxHeapArray[leftChildIdx]).GetPacketPriority();
        rightChildPriority = (*pqMaxHeapArray[rightChildIdx]).GetPacketPriority();
        //
        if(leftChildPriority > percNodePriority && leftChildPriority > rightChildPriority) {  // SWAP LEFT CHILD AND PERCNODE
            // SWAP DATA
            (*pqMaxHeapArray[percIndex]).InsertNodeData(leftChildIdx);
            (*pqMaxHeapArray[leftChildIdx]).InsertNodeData(percIndex);
            // SWAP LOCATIONS
            temp = pqMaxHeapArray[leftChildIdx];
            pqMaxHeapArray[leftChildIdx] = pqMaxHeapArray[percIndex];
            pqMaxHeapArray[percIndex] = temp;
            percIndex = leftChildIdx;
            break;
        }
        else if(rightChildPriority > percNodePriority && rightChildPriority > leftChildPriority) {  // SWAP RIGHT CHILD AND PERCNODE
            // SWAP DATA
            (*pqMaxHeapArray[percIndex]).InsertNodeData(rightChildIdx);
            (*pqMaxHeapArray[rightChildIdx]).InsertNodeData(percIndex);
            // SWAP LOCATIONS
            temp = pqMaxHeapArray[rightChildIdx];
            pqMaxHeapArray[rightChildIdx] = pqMaxHeapArray[percIndex];
            pqMaxHeapArray[percIndex] = temp;
            percIndex = rightChildIdx; 
            break;
        }
        else {
            done = true;
        }
    }
}


// EMPTY A HASHMAP OBJECT INTO A RECEIVING VECTOR
void HashMap::FillDestinationVector(vector<shared_ptr<DataPacket>> writeToVector) {
    shared_ptr<DataPacket> curNode;
    shared_ptr<MaxHeapPQ> currentDomain;
    int domainNumber;

    map<int, shared_ptr<MaxHeapPQ>>::iterator it;  // declare iterator for the map
    for(it=table.begin(); it!=table.end(); it++) {
        currentDomain = it->second;
        domainNumber = it->first;

        while((*currentDomain).nodeCount > 0) {
            curNode = indexPqAndRetrievePacket(domainNumber);  // 
            writeToVector.push_back(curNode);  // 
        }
    }
}









