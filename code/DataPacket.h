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
    
    // The following member variables are declared during pq insertion
    int pqIndex;  // location of the pointer in the MaxHeapPQ array
    int parentIndex;  // index of the parent = floor((i-1)/2)
    int leftChildIndex;  // index of the left child = (2 * i) + 1
    int rightChildIndex;  // index of the right child = (2 * i) + 2

  public:
    string domain_ID;  // software domain ID used to route DataPackets to an appropriated hash bucket.
      // Default constructor
      DataPacket();
      // DataPacket deconstructor.
      ~DataPacket();
      // InitDataPacket() returns a shared pointer to a DataPacket object 
      shared_ptr<DataPacket> InitDataPacket(string data, int packet_priority, int domain_ID);
      // 
      void InsertNodeData(int nodePqIndex);
      // Getter function to access private data member: "data".
      string GetPacketData();
      // Getter function to access private data member: "packet_priority".
      int GetPacketPriority();
};

#endif // DATAPACKET_H__