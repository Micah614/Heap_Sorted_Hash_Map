#ifndef MAXHEAPHASHMAP_H__
#define MAXHEAPHASHMAP_H__
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

using namespace std;
#define PQ_SIZE 100

// UXUI_INTERFACE 1 || DATABASE_CONFIG 2 || LAUNCH_FILES 3 || REGISTRATION_MATERIALS 4 || EXECUTABLE_FILES 5
struct MaxHeapPQ {  // Five MaxHeapPQ's are instantiated in every HashMap object
  string domain;  // the PQ domain identity
  int nodeCount;  // keeps track of how populated a heap is.
  int nextIndex;  // first open index in the pointer array.
  shared_ptr<DataPacket> pqMaxHeapArray[PQ_SIZE];  // variable size-allocated array of DataPacket shared pointers
  shared_ptr<DataPacket> pqTopPointer;  // always found at maxHeapArray[0]

  // INITIATION FUNCTIONS
  void InitPqDomain(string domain_ID);
  MaxHeapPQ();  // PQ default constructor. Create one heap for each domain
  ~MaxHeapPQ();  // Destructor

  // STORAGE FUNCTIONS
  void pqInsert(shared_ptr<DataPacket> packet);  // inserts a DataPacket pointer object into appropriate max heap PQ
  void MaxHeapPercolateUp(shared_ptr<DataPacket> packet);

  // RETRIEVAL FUNCTIONS
  shared_ptr<DataPacket> RemoveTopPriority();  // 
  void MaxHeapPercolateDown(int index);  // 
};


typedef std::map<int, shared_ptr<MaxHeapPQ>> hashMap;  // typedef vector<shared_ptr<MaxHeapPQ>> hashTable;
// UXUI_INTERFACE 1 || DATABASE_CONFIG 2 || LAUNCH_FILES 3 || REGISTRATION_MATERIALS 4 || EXECUTABLE_FILES 5


struct HashMap {  // HashMap contains a five key map of domain ID's leading to shared pointer MaxHeapPQ top node pointers
  int packetCount; // DataPacket count accross all five domains
  hashMap table;  // points to a map with key:value pairs domain_ID : shared_ptr<MaxHeapPQ>;

  // INITIATION FUNCTIONS
  HashMap();  // Default constructor for PerfectHashTable objects
  ~HashMap();  // Destructor for PerfectHashTable objects
  void initHashMap();  // initializes five (5) imbedded domain priority queues and a hashMap table routing object

  // STORAGE FUNCTIONS
  void assignPqDomainAndInsert(shared_ptr<DataPacket> packet);  // accepts a DataPacket shared_ptr, then categorizes and inserts it by domain_ID

  // RETRIEVAL FUNCTIONS
  shared_ptr<DataPacket> indexPqAndRetrievePacket(int domain_ID);  // accepts an integer domain_ID, indexes MaxHeapPQ objects and extracts the top pointer
  void FillDestinationVector(vector<shared_ptr<DataPacket>> writeToVector);  // fill a destination vector with DataPacket object
};



#endif // EMPTY_H__