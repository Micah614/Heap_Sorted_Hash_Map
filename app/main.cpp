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

using namespace std;
// SEE PROGRAM PSUEDOCODE AND DEVELOPMENT INSTRUCTIONS ARE IN README.MD


int main(){

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PART ONE @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    std::array<int,50> packetPriority;
    std::array<string,50> packetData;
    std::array<int,50> packetDomainID;

// Populate the data arrays.
for(int i=0; i<packetPriority.size(); ++i) {
    int j;
    if(i<14) {          // 0-13
        j = i;
        packetDomainID[i] = UXUI_INTERFACE; }
    else if(i<21) {     // 14-20
        j = (i-13);
        packetDomainID[i] = DATABASE_CONFIG; }
    else if(i<36) {     // 21-35
        j = (i-20);
        packetDomainID[i] = LAUNCH_FILES; }
    else if(i<41) {     // 36-40
        j = (i-35);
        packetDomainID[i] = REGISTRATION_MATERIALS; }
    else {              // 41-50
        j = (i-40);
        packetDomainID[i] = EXECUTABLE_FILES; }

    packetPriority[i] = j;
    packetData[i] = "dataPacket" + to_string(i+1);
}

//CREATE 50 DATAPACKET SHARED POINTER OBJECTS & PUSH THEM TO A STACK
std::stack<shared_ptr<DataPacket>> dataPacketStack1;  // declare a stack to push DataPackets into.
for(int a=0; a<packetData.size(); ++a) {
    DataPacket curNode;
    shared_ptr<DataPacket> node = curNode.InitDataPacket(packetData[a], packetPriority[a], packetDomainID[a]);
    dataPacketStack1.push(node);
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ PART TWO @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

while(!dataPacketStack1.empty()) {
    shared_ptr<DataPacket>> curPacket = dataPacketStack1.top();
    dataPacketStack1.pop();
    cout << "Data packet: " << curPacket.GetPacketData() << " inserting int MaxHeapHash..." << endl;
}




    return 0;
}