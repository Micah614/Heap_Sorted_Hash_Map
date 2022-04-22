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
  MaxHeapPQ();  // PQ default constructor. Create one heap for each domain
  ~MaxHeapPQ();  // Destructor
  int domain;  // the PQ domain identity
  int nodeCount;  // keeps track of how populated a heap is.
  int currentIndex;  // first open index in the pointer array.

  // IS THIS ARRAY DECLARED CORRECTLY??
  shared_ptr<DataPacket> pqMaxHeapArray[PQ_SIZE];  // variable size-allocated array of DataPacket shared pointers
  // IS THIS ARRAY DECLARED CORRECTLY??
  
  shared_ptr<DataPacket> pqTopPointer;  // always found at maxHeapArray[0]
  shared_ptr<DataPacket> pqEmptyNode;  // DataPacket object containing an error message, returned by pqDomainLookUp when an accessed queue is empty. 

  //shared_ptr<DataPacket> InitPqDomain(int domain);  // Allocates max heap PQ, returns a shared pointer to the top node.
  void InitPqDomain(int domain_ID);
  void pqInsert(shared_ptr<MaxHeapPQ> pqDomain, shared_ptr<DataPacket> packet);  // inserts a DataPacket pointer object into appropriate max heap PQ
  void MaxHeapPercolateUp(int nodeIndex, shared_ptr<MaxHeapPQ> pqDomain);

  shared_ptr<DataPacket> pqDomainRemove(int domain_ID);  // removes and returns the highest priority element in the PQ with a matching hash bucket ID
  int pqDomainNodeCount(int domain_ID);  // retrieves the node_count for a selected PQ heap domain
  shared_ptr<DataPacket> pqDomainPeek(int domain_ID);
};

typedef std::map<int, shared_ptr<MaxHeapPQ>> hashMap;  // typedef vector<shared_ptr<MaxHeapPQ>> hashTable;

// UXUI_INTERFACE 1 || DATABASE_CONFIG 2 || LAUNCH_FILES 3 || REGISTRATION_MATERIALS 4 || EXECUTABLE_FILES 5
struct HashMap {  // HashMap contains a five key map of domain ID's leading to shared pointer MaxHeapPQ top node pointers
  int packetCount; // DataPacket count accross all five domains
  shared_ptr<hashMap> table;  // points to a map with key:value pairs domain_ID : shared_ptr<MaxHeapPQ>;
  HashMap();  // Default constructor for PerfectHashTable objects
  ~HashMap();  // Destructor for PerfectHashTable objects

  // InitHashMap initializes five (5) imbedded domain-labeled priority queues and returns a shared pointer to the hashMap typedef object
  void initHashMap();
  // assignHashBucket() extracts domain_ID from DataPacket and returns a top node pointer to the appropriate max heap priority queue
  shared_ptr<DataPacket> assignPqDomain(shared_ptr<DataPacket> packet);  // pointer will be passed to MaxHeapPQ::MaxHeapInsert() function
  shared_ptr<MaxHeapPQ> pqDomainLookUp(int domain_ID);  // returns a PQ top node pointer when handed a domain_ID number
};



#endif // EMPTY_H__