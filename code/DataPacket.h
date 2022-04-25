#ifndef DATAPACKET_H__
#define DATAPACKET_H__

#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <queue>
#include <memory>
#include <string>
#include <map>
#include <stack>

// DATAPACKET DOMAIN CATEGORIES FOR PACKET ROUTING
#define UXUI_INTERFACE 1
#define DATABASE_CONFIG 2
#define LAUNCH_FILES 3
#define REGISTRATION_MATERIALS 4
#define EXECUTABLE_FILES 5

using namespace std;


class DataPacket{  
  private:
    string data;  // Primary DataPacket info
    int packet_priority;  // assigned during creation
    // Variables defined after insertion:
    int pqIndex;  // location of the pointer in the MaxHeapPQ array
    int leftChildIndex;  // index of the left child = (2 * i) + 1
    int rightChildIndex;  // index of the right child = (2 * i) + 2
    int parentIndex;  // index of the parent = floor((i-1)/2)

  public:
    int domain_ID;  // domain ID key used to route DataPackets to a PQ domain.
    DataPacket();  // Default constructor    
    ~DataPacket();  // DataPacket deconstructor.
    // InitDataPacket() returns a shared pointer to a DataPacket object 
    shared_ptr<DataPacket> InitDataPacket(string data, int packet_priority, int domain_ID);
    void InsertNodeData(int nodePqIndex);  // updates member data following add/move/remove

    // Getter functions to access private data members:
    string GetPacketData();
    int GetPacketPriority();
    int GetPqIndex();
    int GetParentIndex();
    int GetLeftChildIndex();
    int GetRightChildIndex();
};

#endif // DATAPACKET_H__