<strong>Purpose</strong><br>
The purpose of this project is to determine if multiple max heap priority queue structures can simultaneously route, sort, store, and retrieve a jumbled list containing domain labeled of nodes (data packets).

<strong>Abstract</strong><br>
The routing and storage of data packet objects using max heap priority queues proved highly efficient in terms of packet sorting but emptying the static BST arrays without provoking a segmentation fault proved more challenging. This problem is easily resolved using a try-except when probing the second and third layers of an unbalanced BST. Heapifying these structures using either bubble-up or bubble down improves the issue but does not resolve it.  

<strong>Description</strong><br>
This hybrid data structure contains five max heap priority queues that are controlled by a central key index routing table [an index dictionary]. The table contains integer keys that represent the domain of each data packet, the shared pointer value is the address of the object’s assigned queue. This table also contains data members and class functions belonging to two semantic categories: "routing and storage" and "indexing and removal". 

Data packets are developed using object-oriented design principles and contain class member data and functions that define the basic node structure of the BSTs. These nodes are collected from a combined list of such objects. The packets are then sorted and inserted into the appropriate priority queue by referencing the routing table. A separate script is used to remove each node from its’ assigned priority queue individually, to assess the performance of the hybrid data structure. 

<strong>Discussion<strong><br>
The design works exceptionally well for packet sorting but suffers certain performance issues associated with removing the final (c.a., 3) nodes from the queue. Percolate up and percolate down priority queue algorithms are implemented throughout the assignment to organize the underlying maxheap based priority queues. However, it is impossible to know if the BST remains balanced at the end of the packet collection. 

  <strong>Instructions to compile and run the program:</strong><br>
  1.) Clone the repository from github <br>
  2.) Navigate to the build folder in the terminal's command line <br>
  3.) Run cmake commands to create the executable files <br>
  4.) Run the make command to compile the project <br>
  5.) Clear the screen and enter: "./run_app" to run the main.cpp file <br>

The script in the main.cpp file will execute the commands for the project. You may follow along by reading the main.cpp file and reading the terminal print statements. 
This program repository contains two cpp files and two header files, all kept in the "code" folder. Datapacket objects and member functions are kept in "datapacket.h" and 
"datapacket.cpp", while the maxheappq and hashmap declarations and definitions are kept in "maxheaphashmap.h" and "maxheaphashmap.cpp" files respectively. 


Enjoy the project.
Thank you.
