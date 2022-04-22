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
    // DO STUFF
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
    (*uxui_interface).InitPqDomain(1);  // calling InitPqDomain(1) to populate the object data members.Now, pass "uxui_interface" to the map.

    std::shared_ptr<MaxHeapPQ> db_config {new MaxHeapPQ}; 
    (*db_config).InitPqDomain(2);

    std::shared_ptr<MaxHeapPQ> launch_files {new MaxHeapPQ};
    (*launch_files).InitPqDomain(3);
    
    std::shared_ptr<MaxHeapPQ> registration {new MaxHeapPQ};
    (*registration).InitPqDomain(4);
    
    std::shared_ptr<MaxHeapPQ> exec_files {new MaxHeapPQ};
    (*exec_files).InitPqDomain(5);

    // Create the HashMap table container
    hashMap table =  {{1, uxui_interface}, {2, db_config}, {3, launch_files}, {4, registration}, {5, exec_files}};  // assign the map to the HashMap table data member
    packetCount = 0;
  //return table;
}

// Initiate a max heap with the indicated domain and capacity.(Index properties are in DataPacket class)
void MaxHeapPQ::InitPqDomain(int domain_ID) {
//shared_ptr<DataPacket> MaxHeapPQ::InitPqDomain(int domain_ID) {
    MaxHeapPQ newQueue;  // instantiate a queue.
    newQueue.domain = domain_ID;  // assign it the given domain_ID.
    newQueue.nodeCount = 0;  // zero DataPackets to start, increment counter during MaxHeapInsert().

    // initialize the pqarray with NULL pointers (replaced with DataPacket shared_ptrs during insertion).
    for(int i=0; i<PQ_SIZE; ++i) {
        newQueue.pqMaxHeapArray[i] = nullptr;  // populate the array with null pointers to start.
    }
    // create an "error node" DataPacket object with call to InitDataPacket().
    (*newQueue.pqEmptyNode).InitDataPacket("Error: the pq that was accessed is empty.", -1, domain_ID);
    newQueue.pqTopPointer = newQueue.pqMaxHeapArray[0];  // pqTop always points at index zero.
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%% INSTANTIATING FUNCTIONS (END HERE) %%%%%%%%%%%%%%%%%%%%%%%%%%%



// %%%%%%%%%%%%%%%%%%%%%%%%%%% SORT AND INSERT FUNCTION GROUP (START HERE) %%%%%%%%%%%%%%%%%%%%%%%%%%%

// assignPqDomain accepts a DataPacket shared pointer, extracts the packet domain key, iterates through the HashMap table
// until a matching key (a MaxHeapPQ shared pointer) is found, then dereferences that key and calls pqInsert(assignedPQ, packet),
// (assignedPQ is a MaxHeapPQ object pointer, and packet is a pointer to the object that will be inserted).
shared_ptr<DataPacket> HashMap::assignPqDomain(shared_ptr<DataPacket> packet) { //This function will call MaxHeapPQ::insert()
    int domainKey = packet->domain_ID;  // extract domain_ID

    map<int, shared_ptr<MaxHeapPQ>>::iterator it;
    shared_ptr<MaxHeapPQ> assignedPQ;
    for(it=(*table).begin(); it!=(*table).end(); it++) {
        if(it->first == domainKey) {
            assignedPQ = it->second;  // this is a domain specific MaxHeapPQ object pointer.
        }
    }
    (*assignedPQ).pqInsert(assignedPQ, packet);  // Pass topNode and packet pointers to pqDomainInsert.
}

// pqDomainInsert is a helper function of HashMap::assignPqDomain, that inserts packets into the corresponding domain queue.
void MaxHeapPQ::pqInsert(shared_ptr<MaxHeapPQ> pqDomain, shared_ptr<DataPacket> packet) {
    MaxHeapPQ curPQ = (*pqDomain);  // dereference the MaxHeapPQ pointer to retreive the object
    DataPacket dataPacket = (*packet);  // dereference the DataPacket pointer to retreive the object
    int packetPriority = dataPacket.GetPacketPriority();  // extract packet priority

    // If the queue is empty...
    if(curPQ.nodeCount == 0) {  
    // update DataPacket info
        dataPacket.InsertNodeData(0);  // packet will be inserted as the top node.
        curPQ.pqMaxHeapArray[0] = packet;
        curPQ.currentIndex = 1;  // Update variable to track the next insert position.
        curPQ.nodeCount++;  // nodeCount is incremented.
      return;
    }
    // For all other cases...
    else {
        dataPacket.InsertNodeData(curPQ.currentIndex);  // update packet private data members
        curPQ.pqMaxHeapArray[curPQ.currentIndex] = packet;  // insert packet at curPQ.currentIndex
        curPQ.currentIndex++;  // increment curPQ.currentIndex
        curPQ.nodeCount++;
        // Percolate up after insertion (ONLY if there are two or more objects).
        MaxHeapPercolateUp(curPQ.currentIndex-1, pqDomain);
    }
  return;
}

// 
int DataPacket::GetPacketPriority() {
    return packet_priority;
}

// 
void DataPacket::InsertNodeData(int nodePqIndex) {
    int parentidx;
    if(pqIndex == 0) {
        parentidx = -1;  // top node has no parent. (default = -1)
    }
    else{
        parentidx = floor((pqIndex-1)/2);  // calculate parent index
    }
    // update DataPacket private member variables.
    parentIndex = parentidx;
    pqIndex = nodePqIndex;
    leftChildIndex = (2*pqIndex) + 1;
    rightChildIndex = (2*pqIndex) + 2;
}

// 
void MaxHeapPQ::MaxHeapPercolateUp(int nodeIndex, shared_ptr<MaxHeapPQ> pqDomain) {
    int childIdx = nodeIndex;  // initiate local index counter.
    int parentIdx = floor((nodeIndex-1)/2);  // calculate parentIndex

    // INDEX "pqMaxHeapArray" INSIDE "pqDomain" TO RETRIEVE NODES
    shared_ptr<DataPacket> child = (*pqDomain).pqMaxHeapArray[childIdx];
    shared_ptr<DataPacket> parent = (*pqDomain).pqMaxHeapArray[parentIdx];
    int childPriority = (*child).GetPacketPriority();  // extract node priority
    int parentPriority = (*parent).GetPacketPriority();  // extract parent priority
    shared_ptr<DataPacket> temp;  // temporary variable to switch values

    while(childIdx > 0) {
        if(childPriority <= parentPriority) {
            return;
        }
        else {  
            // switch objects of nodeIndex and parentIdx
            temp = (*pqDomain).pqMaxHeapArray[childIdx];
            (*pqDomain).pqMaxHeapArray[childIdx] = (*pqDomain).pqMaxHeapArray[parentIdx];
            (*pqDomain).pqMaxHeapArray[parentIdx] = temp;
        }
    }
}
//    while (nodeIndex > 0) {
//       parentIndex = (nodeIndex - 1) / 2
//       if (heapArray[nodeIndex] <= heapArray[parentIndex])
//          return
//       else {
//          swap heapArray[nodeIndex] and heapArray[parentIndex]
//          nodeIndex = parentIndex
//       }
//    }



// %%%%%%%%%%%%%%%%%%%%%%%%%%% SORT AND INSERT FUNCTION GROUP (END HERE) %%%%%%%%%%%%%%%%%%%%%%%%%%%


// %%%%%%%%%%%%%%%%%%%%%%%%%%% INDEX AND REMOVE FUNCTION GROUP (START HERE) %%%%%%%%%%%%%%%%%%%%%%%%%%%
/* pqDomainLookUp will index a max heap structure, then remove and return the top DataPacket object within 
that queue when given a domain_ID lookup key. If the selected queue does not contain a DataPacket object, 
the function will return a pointer to the HashMap "error node", which is a real DataPacket object with a 
"data" member variable that contains an error message. (to prevent the program from crashing) */
shared_ptr<MaxHeapPQ> HashMap::pqDomainLookUp(int domain_ID) {  //This function will call MaxHeapPQ::remove()
    // DO STUFF

}
// 
shared_ptr<DataPacket> pqDomainRemove(int domain_ID){ 
   // DO STUFF

}
// %%%%%%%%%%%%%%%%%%%%%%%%%%% INDEX AND REMOVE FUNCTION GROUP (END) %%%%%%%%%%%%%%%%%%%%%%%%%%%






// returns nodeCount of the corresponding domain. 
int MaxHeapPQ::pqDomainNodeCount(int domain_ID) {
    return nodeCount;
}

// 
shared_ptr<DataPacket> MaxHeapPQ::pqDomainPeek(int domain_ID) {
    // DO STUFF
}




// DATA PACKET FUNCTIONS






