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
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ LOAD FIRST DATA CONTAINERS $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    std::array<int,50> packetPriority;
    std::array<string,50> packetData;
    std::array<int,50> packetDomainID;
// Populate the data arrays.
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

// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ CREATE DATA PACKET OBJECTS $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// CREATE ORGANIZED DATA FEED
std::stack<shared_ptr<DataPacket>> inOrderStack;  // STACK TO HOLD IN-ORDER FEED
for(int a=packetData.size()-1; a>-1; a--) {
    DataPacket curNode;
    shared_ptr<DataPacket> node = curNode.InitDataPacket(packetData[a], packetPriority[a], packetDomainID[a]);  // INITDATAPACKET
    inOrderStack.push(node);
}
// VERIFY IN-ORDER FEED
std::stack<shared_ptr<DataPacket>> tempStack = inOrderStack;  // copy the stack to check it. 
cout << "NOTE: In-order and shuffled object feeds contain the same DataPackets kept in a different order. " << endl << "verify in-order feed: ";
while(!tempStack.empty()) {
    shared_ptr<DataPacket> curPacket;
    curPacket = tempStack.top();
    tempStack.pop();
    cout << (*curPacket).GetPacketData() << " ";  // GETPACKETDATA
}
cout << endl << "  In-order stack size: " << inOrderStack.size() << endl;


// CREATE SHUFFLED DATA FEED 
std::vector<shared_ptr<DataPacket>> shuffleVec;
std::stack<shared_ptr<DataPacket>> tempStack2 = inOrderStack;  // copy stack to load shuffleVec
    // CREATE AND SHUFFLE THE VECTOR
while(!tempStack2.empty()) {
    shared_ptr<DataPacket> curPacket;
    curPacket = tempStack2.top();
    tempStack2.pop();
    shuffleVec.push_back(curPacket);
    std::random_shuffle(shuffleVec.begin(), shuffleVec.end());  // SHUFFLE shuffleVec
}
    // PUSH THE OBJECTS TO A SHUFFLED STACK
std::stack<shared_ptr<DataPacket>> shuffledStack;  // STACK TO HOLD SHUFFLED FEED
for(int c=0; c<shuffleVec.size(); ++c) {
    shared_ptr<DataPacket> curPacket;
    curPacket = shuffleVec.at(c);
    shuffledStack.push(curPacket);
}
shuffleVec.clear();
    // VERIFY SHUFFLED FEED
cout << endl << "verify shuffled feed: ";
std::stack<shared_ptr<DataPacket>> tempStack3 = shuffledStack;  // copy shuffledStack to check it. 
while(!tempStack3.empty()) {
    cout << (*tempStack3.top()).GetPacketData() << " ";
    tempStack3.pop();
}
cout << endl << "  Shuffled stack size: " << shuffledStack.size() << endl << endl << endl;

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PART TWO @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ CREATE HASHMAPS AND INSERT OBJECTS $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

cout << "~~~~~~" << endl << "Creating In-Order HashMap..." << endl;
HashMap inOrderHashMap;  // IN-ORDER HASHMAP OBJECT
inOrderHashMap.initHashMap();

if(inOrderHashMap.packetCount == 0) {
    cout << "HashMap object exists... ";
}
if((*inOrderHashMap.table[1]).domain == "uxui_interface") {
    cout << "HashMap table and PQ substructures successfully initiated.";
}

while(!inOrderStack.empty()) {
    shared_ptr<DataPacket> curPacket;
    curPacket = inOrderStack.top();
    inOrderStack.pop();
    inOrderHashMap.assignPqDomainAndInsert(curPacket);
}
cout << endl << "  Routing DataPacket objects..." << endl;
cout << endl;
cout << inOrderHashMap.packetCount << " pre-sorted DataPackets were successfully routed and inserted in the HashMapPQ data structure:" << endl;

for(int j=1; j<6; ++j) {
    cout << "  " << (*inOrderHashMap.table[j]).nodeCount << " objects in the " << (*inOrderHashMap.table[j]).domain << " domain." << endl;
}
cout << endl << endl;



cout << "~~~~~~" << endl << "Creating Shuffled HashMap..." << endl;
HashMap shuffledHashMap;  // SHUFFLED HASHMAP OBJECT
shuffledHashMap.initHashMap();

if(shuffledHashMap.packetCount == 0) {
    cout << "HashMap object exists... ";
}
if((*shuffledHashMap.table[1]).domain == "uxui_interface") {
    cout << "HashMap table and PQ substructures successfully initiated.";
}

while(!shuffledStack.empty()) {
    shared_ptr<DataPacket> curPacket;
    curPacket = shuffledStack.top();
    shuffledStack.pop();
    shuffledHashMap.assignPqDomainAndInsert(curPacket);
}

cout << endl << "  Routing DataPacket objects..." << endl;
cout << endl;
cout << shuffledHashMap.packetCount << " shuffled DataPacket objects were successfully routed and stored in the HashMapPQ data structure:" << endl;

for(int k=1; k<6; ++k) {
    cout << "  " << (*shuffledHashMap.table[k]).nodeCount << " objects in the " << (*shuffledHashMap.table[k]).domain << " domain." << endl;
}
cout << endl << endl;










    return 0;
}