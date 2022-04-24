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

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STEP ONE: CREATE THE DATAPACKET OBJECTS AND LOAD SHARED POINTERS INTO STACKS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    std::array<int,50> packetPriority;  // ARRAY CONTAINING PACKET PRIORITIES
    std::array<string,50> packetData;  // ARRAY CONTAINING PACKET DATA
    std::array<int,50> packetDomainID;  // ARRAY CONTAINING PACKET DOMAIN_IDs

// LOAD THE ARRAYS WITH NODE DATA
for(int i=0; i<packetPriority.size(); ++i) {
    int j;
    if(i<14) {          // 0-13
        j = i;
        // packetDomainID[i] = "uxui_interface"; }
        packetDomainID[i] = 1; }
    else if(i<21) {     // 14-20
        j = (i-13);
        // packetDomainID[i] = "db_config"; }
        packetDomainID[i] = 2; }
    else if(i<36) {     // 21-35
        j = (i-20);
        // packetDomainID[i] = "launch_files"; }
        packetDomainID[i] = 3; }
    else if(i<41) {     // 36-40
        j = (i-35);
        // packetDomainID[i] = "registration"; }
        packetDomainID[i] = 4; }
    else {              // 41-50
        j = (i-40);
        // packetDomainID[i] = "exec_files"; }
        packetDomainID[i] = 5; }

    packetPriority[i] = j;
    packetData[i] = to_string(i+1);
}

// CREATE AN IN-ORDER DATA FEED STACK "inOrderStack"
std::stack<shared_ptr<DataPacket>> inOrderStack;  // STACK TO HOLD IN-ORDER FEED
for(int a=packetData.size()-1; a>-1; a--) {
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



// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STEP TWO: CREATE TWO MAX-HEAP-HASHMAP OBJECTS AND INSERT DATAPACKETS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// CREATE IN-ORDER HASHMAP OBJECT
cout << "~~~~~~" << endl << "Creating In-Order MaxHeapHashMap object..." << endl;
HashMap inOrderHashMap;  // IN-ORDER HASHMAP OBJECT
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
cout << inOrderHashMap.packetCount << " pre-sorted DataPackets were successfully routed and inserted in the inOrderHashMap MaxHeapHashMap data structure." << endl;
for(int j=1; j<6; ++j) {  // DESCRIBE THE DISTRIBUTION ACCROSS DOMAINS
    cout << "  " << (*inOrderHashMap.table[j]).nodeCount << " objects in the " << (*inOrderHashMap.table[j]).domain << " domain." << endl;
}
cout << endl;


// CREATE SHUFFLED HASHMAP OBJECT
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


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STEP THREE: SCRIPT-GOVERNED TABLE INDEXING AND POPULATION OF ARRAYS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

vector<shared_ptr<DataPacket>> InOrder_Result;  // RESULT VECTOR FOR IN-ORDER DATA
vector<shared_ptr<DataPacket>> Shuffled_Result;  // RESULT VECTOR FOR SHUFFLED DATA

// CREATE A WHILE-LOOP ISSUING DOMAIN ID REQUESTS TO inOrderHashMap AND shuffledHashMap
    // STORE THE RETRIEVED POINTERS IN THE ASSIGNED VECTORS

// VERIFY THAT THE CONTENTS OF EACH VECTOR ARE SORTED AND IDENTICAL







// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ STEP FOUR: ASSERT EQVIVALENCE OF BOTH ARRAYS @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@




    return 0;
}