#include <iostream>
#include "../code/DataPacket.h"
#include "../code/MaxHeapHashMap.h"

#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <queue>
#include <memory>
#include <string>
#include <map>
#include <stack>
#include <random>
#include <algorithm>

using namespace std;
// SEE PROGRAM PSUEDOCODE AND DEVELOPMENT INSTRUCTIONS ARE IN README.MD


int main(){

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STAGE ONE: CREATE DATAPACKET OBJECTS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    std::array<int,50> packetPriority;  // ARRAY CONTAINING PACKET PRIORITIES
    std::array<string,50> packetData;  // ARRAY CONTAINING PACKET DATA
    // packetDomainID ARRAY DOMAIN_ID FREQUENCIES: [8, 12, 9, 7, 14] (FOR DOMAIN 1,2,3... ETC.)
    std::array<int,50> packetDomainID = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

// LOAD EACH ARRAY WITH DATA
for(int i=0; i<packetPriority.size(); ++i) {  // NUMBERED 0-50
    packetPriority[i] = i+1;
}
for(int i=0; i<packetData.size(); ++i) {  // NUMBERED 0-50
    packetData[i] = to_string(i+1);  // CONTAINS A STRING VALUE OF THE PRIORITY
}



// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STAGE TWO:LOAD SHARED POINTERS INTO STACKS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// CREATE AN IN-ORDER DATAPACKET STACK CALLED "inOrderStack"
std::stack<shared_ptr<DataPacket>> inOrderStack;  // STACK TO HOLD IN-ORDER FEED
for(int a=packetData.size()-1; a>-1; a--) {  // PUSH TO STACK IN REVERSE ORDER
    DataPacket curNode;
    shared_ptr<DataPacket> node = curNode.InitDataPacket(packetData[a], packetPriority[a], packetDomainID[a]);  // INITDATAPACKET
    inOrderStack.push(node);
}
// VERIFY THE IN-ORDER DATA FEED
std::stack<shared_ptr<DataPacket>> tempStack = inOrderStack;  // MAKE A COPY OF THE STACK TO VERIFY ITS' CONTENTS
cout << endl << "NOTE: In-order and shuffled object feeds contain the same DataPacket objects, arranged in a different order. " << endl << endl << "Verifying in-order feed: ";
while(!tempStack.empty()) {
    shared_ptr<DataPacket> curPacket;
    curPacket = tempStack.top();
    tempStack.pop();
    cout << (*curPacket).GetPacketData() << " ";  // GETPACKETDATA
}
cout << endl << "  In-order stack size: " << inOrderStack.size() << endl;



// CREATE A SHUFFLED DATA FEED 
std::vector<shared_ptr<DataPacket>> shuffleVec;
std::stack<shared_ptr<DataPacket>> tempStack2 = inOrderStack;  // COPY inOrderStack TO tempStack2
// CREATE A VECTOR WITH THE DATAPACKET OBJECTS
while(!tempStack2.empty()) {
    shared_ptr<DataPacket> curPacket;
    curPacket = tempStack2.top();
    tempStack2.pop();
    shuffleVec.push_back(curPacket);
}
std::random_shuffle(shuffleVec.begin(), shuffleVec.end());  // SHUFFLE THE VECTOR
// PUSH THE SHUFFLED OBJECTS INTO A STACK
std::stack<shared_ptr<DataPacket>> shuffledStack;  // DECLARE A STACK
for(int c=0; c<shuffleVec.size(); ++c) {
    shared_ptr<DataPacket> curPacket;
    curPacket = shuffleVec.at(c);
    shuffledStack.push(curPacket);
}
shuffleVec.clear();
// VERIFY THAT THE FEED IS SHUFFLED
cout << endl << "Verifying shuffled feed: ";
std::stack<shared_ptr<DataPacket>> tempStack3 = shuffledStack;  // COPY SHUFFLEDSTACK TO VERIFY ITS' CONTENTS
while(!tempStack3.empty()) {
    cout << (*tempStack3.top()).GetPacketData() << " ";
    tempStack3.pop();
}
cout << endl << "  Shuffled stack size: " << shuffledStack.size() << endl << endl;  // ENUMERATE THE NUMBER OF OBJECTS





// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STAGE THREE: CREATE "IN-ORDER" AND "SHUFFLED" HASHMAP OBJECTS AND INSERT THE DATAPACKETS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// INITIATE AND LOAD IN-ORDER HASHMAP:
cout << "~~~~~~" << endl << "Creating In-Order MaxHeapHashMap object..." << endl;
HashMap inOrderHashMap;  // DECLARE IN-ORDER HASHMAP OBJECT
inOrderHashMap.initHashMap();  // INITIATE IN-ORDER HASHMAP OBJECT
if(inOrderHashMap.packetCount == 0) {  // VERIFY THAT HASHMAP EXISTS
    cout << "HashMap object created successfully... " << endl;
}
if((*inOrderHashMap.table[1]).domain == "uxui_interface") {  // VERIFY HASHMAP "table" MEMBER EXISTS AND HAS THE DESIRED ATTRIBUTES
    cout << "HashMap table and PQ sub-structures successfully initiated." << endl;
}
cout << "Routing DataPacket objects..." << endl;
while(!inOrderStack.empty()) {  // INSERT THE DATA PACKETS FROM inOrderStack INTO inOrderHashMap USING assignPqDomainAndInsert MEMBER FUNCTION
    shared_ptr<DataPacket> curPacket;
    curPacket = inOrderStack.top();
    inOrderStack.pop();
    inOrderHashMap.assignPqDomainAndInsert(curPacket);  // INSERT THE PACKET INTO inOrderHashMap
}
cout << endl;
cout << inOrderHashMap.packetCount << " sorted DataPackets were successfully routed and inserted in the inOrderHashMap MaxHeapHashMap data structure." << endl;
for(int j=1; j<6; ++j) {  // DESCRIBE THE DISTRIBUTION ACCROSS DOMAINS
    cout << "  " << (*inOrderHashMap.table[j]).nodeCount << " objects in the " << (*inOrderHashMap.table[j]).domain << " domain." << endl;
}
cout << endl;



// INITIATE AND LOAD SHUFFLED HASHMAP OBJECT:
cout << "~~~~~~" << endl << "Creating Shuffled MaxHeapHashMap object..." << endl;
HashMap shuffledHashMap;  // SHUFFLED HASHMAP OBJECT
shuffledHashMap.initHashMap();  // INITIATE SHUFFLED HASHMAP OBJECT
if(shuffledHashMap.packetCount == 0) {  // VERIFY THAT HASHMAP EXISTS
    cout << "HashMap object created successfully... " << endl;
}
if((*shuffledHashMap.table[1]).domain == "uxui_interface") {  // VERIFY HASHMAP "table" MEMBER EXISTS AND HAS THE DESIRED ATTRIBUTES
    cout << "HashMap table and PQ sub-structures successfully initiated." << endl;
}
cout << "Routing DataPacket objects..." << endl;
while(!shuffledStack.empty()) {  // INSERT DATA PACKETS FROM shuffledStack INTO shuffledHashMap USING assignPqDomainAndInsert MEMBER FUNCTION
    shared_ptr<DataPacket> curPacket;
    curPacket = shuffledStack.top();
    shuffledStack.pop();
    shuffledHashMap.assignPqDomainAndInsert(curPacket);  // INSERT THE PACKET INTO shuffledHashMap
}
cout << endl;
cout << shuffledHashMap.packetCount << " shuffled DataPacket objects were successfully routed and stored in the shuffledHashMap MaxHeapHashMap data structure." << endl;
for(int k=1; k<6; ++k) {  // DESCRIBE THE DISTRIBUTION ACCROSS DOMAINS
    cout << "  " << (*shuffledHashMap.table[k]).nodeCount << " objects in the " << (*shuffledHashMap.table[k]).domain << " domain." << endl;
}
cout << endl;






cout << "The contents of the UXUI_INTERFACE domain pqMaxHeapArray of shuffledHashMap is: " << endl;
    map<int, shared_ptr<MaxHeapPQ>>::iterator it;  // ITERATE THROUGH "table"
    for(it=shuffledHashMap.table.begin(); it!=shuffledHashMap.table.end(); it++) {
        if(it->first == 1) {
            for (int i=0; i < 8; ++i) {
                shared_ptr<DataPacket> thing = (*it->second).pqMaxHeapArray[i];
                cout << (*thing).GetPacketData() << " ";
            }
            //assignedPQ = it->second;  // COLLECT POINTER TO ASSIGNED DOMAIN PQ
        }
    }
cout << endl << endl;



cout << "The contents of the UXUI_INTERFACE domain pqMaxHeapArray of inOrderHashMap is: " << endl;
    map<int, shared_ptr<MaxHeapPQ>>::iterator it1;  // ITERATE THROUGH "table"
    for(it1=inOrderHashMap.table.begin(); it1!=inOrderHashMap.table.end(); it1++) {
        if(it1->first == 1) {
            for (int i=0; i < 8; ++i) {
                shared_ptr<DataPacket> thing = (*it1->second).pqMaxHeapArray[i];
                cout << (*thing).GetPacketData() << " ";
            }
            //assignedPQ = it->second;  // COLLECT POINTER TO ASSIGNED DOMAIN PQ
        }
    }
cout << endl << endl;





// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STAGE FOUR: EMPTY THE MAXHEAPS AND POPULATE THE ARRAYS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

vector<shared_ptr<DataPacket>> InOrder_Result;  // RESULT VECTOR FOR IN-ORDER DATA
vector<shared_ptr<DataPacket>> Shuffled_Result;  // RESULT VECTOR FOR SHUFFLED DATA

// CALL indexPqAndRetrievePacket() ON "inOrderHashMap" AND "shuffledHashMap"; PLACE RETRIEVED POINTERS INTO THE ASSIGNED VECTORS

shared_ptr<DataPacket> checkPacket;
checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;

checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;

checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;

checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;

checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;

checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;

checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;

checkPacket = inOrderHashMap.indexPqAndRetrievePacket(1);
cout << (*checkPacket).GetPacketData() << endl;


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STAGE FIVE: ASSERT EQVIVALENCE OF BOTH ARRAYS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@






    return 0;
}