#include "DataPacket.h"
#include "MaxHeapHashMap.h"

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


// Constructo
DataPacket::DataPacket() {
    // TO DO
}

// Destructor
DataPacket::~DataPacket() {
    // ALL GOOD
}

// Initiate a data packet object with specified attributes and return a shared pointer to that object
shared_ptr<DataPacket> DataPacket::InitDataPacket(string data, int packet_priority, int domain_ID) {
    shared_ptr<DataPacket> dataPacket(new DataPacket);  // instantiate new DataPacket object
    dataPacket->data = data;
    dataPacket->packet_priority = packet_priority;
    dataPacket->domain_ID = domain_ID;
    /*NOTE: The DataPacket member variables: pqIndex, parentIndex, leftChildIndex, and rightChildIndex 
    are all instantiated during insertion into a MaxHeapPQ data structure. see MaxHeapHashMap.cpp to see 
    how this happens. */

  return dataPacket;
}

// Return DataPacket private member var "data" (Getter function)
string DataPacket::GetPacketData() {
    return data;
}

// 
int DataPacket::GetPacketPriority() {
    return packet_priority;
}

// InsertNodeData assigns a DataPacket pqIndex value and populates it's other indices
void DataPacket::InsertNodeData(int nodePqIndex) {
    int parentidx;
    if(nodePqIndex == 0) {  // the node's
        parentidx = -1;  // top node has no parent. (default = -1)
    }
    else{
        parentidx = floor((nodePqIndex-1)/2);  // calculate parent index
    }
    // update DataPacket private member variables.
    parentIndex = parentidx;
    pqIndex = nodePqIndex;
    leftChildIndex = (2*nodePqIndex) + 1;
    rightChildIndex = (2*nodePqIndex) + 2;
}



