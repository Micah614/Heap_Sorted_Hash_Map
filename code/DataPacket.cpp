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
int GetPacketData() {
    // DO STUFF
}

// Return DataPacket private member var "packet_priority" (Getter function)
int GetPacketPriority() {
    // DO STUFF
}





