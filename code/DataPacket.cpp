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


// Constructor
DataPacket::DataPacket() {
    // TO DO
}
// Destructor
DataPacket::~DataPacket() {
    // TO DO
}

// Initiate a data packet object with specified attributes and return a shared pointer to that object
shared_ptr<DataPacket> DataPacket::InitDataPacket(string data, int packet_priority, int domain_ID) {
    shared_ptr<DataPacket> dataPacket(new DataPacket);  // instantiate new DataPacket object
    dataPacket->data = data;
    dataPacket->packet_priority = packet_priority;
    dataPacket->domain_ID = domain_ID;

  return dataPacket;
}

// InsertNodeData assigns a DataPacket pqIndex value and populates it's other indices
void DataPacket::InsertNodeData(int nodePqIndex) {
    pqIndex = nodePqIndex;
    leftChildIndex = (2*nodePqIndex) + 1;
    rightChildIndex = (2*nodePqIndex) + 2;

    if(nodePqIndex == 0) {
        parentIndex = NULL;  // NULL OR '-1'?
    }
    else{
        parentIndex = floor((nodePqIndex-1)/2);  // calculate parent index
    }
}

string DataPacket::GetPacketData() {
    return data;
}
 
int DataPacket::GetPacketPriority() {
    return packet_priority;
}
 
int DataPacket::GetPqIndex() {
    return pqIndex;
}

int DataPacket::GetParentIndex() {
    return parentIndex;
}

int DataPacket::GetLeftChildIndex() {
    return leftChildIndex;
}

int DataPacket::GetRightChildIndex() {
    return rightChildIndex;
}


