# CSE434Project1

Authors
========
Patrick O'Connor - paoconno@asu.edu    
Andrew Moawad - amoawad@asu.edu

What is this Project?
===============
Use Sockets to create a dead simple P2P network that will share txt files. There will be a single server used to track what clients offer what files that will communicate over UDP packets. Packets sent this way will have a high probability to be dropped, which means a timeout logic on both the clients and servers will need to be implemented. Communication between clients will be done over TCP to ensure packets are received.

Requirements
===========
 - Create clients and servers that communicate over UDP.
 - Clients should send messages to the server in order to UPDATE the server
 or QUERY it for data.
 - Once a client receives the information it needs, it can create a TCP connection to another client to download the file it is looking for or allow other clients to download from it.
 - When a client wants to exit the peer network, it can send an EXIT to the server.
 - The client and server should implement a stop-and-wait timeout for UDP packets that do not arrive successfully.


 Our Packet/Message Structure
 ================
 Our basic block of data is called a Packet. This Packet includes a header and message field. The header is composed of the hostname, IP address, and the action this Packet is meant for. An action is defined as an UPDATE, QUERY, EXIT, ACK, or QUERYRESULT. The data field is an arbitrary message to be sent. An example of a Packet looks like this:    
 ```
 UPDATE|WF11806.local|192.168.2.8
text.txt|128
text2.txt|256```

 Above we can see the action, hostname, and IP Address delimited by a `|`. On the next line we have the message which in this case is the name of the files that this client is offering as well as their size in bytes.

 What we completed
 =================
 - [x] Create clients and servers that communicate over UDP.
 - [x] Clients should send messages to the server in order to UPDATE the server
 or QUERY it for data.
 - [ ] Once a client receives the information it needs, it can create a TCP connection to another client to download the file it is looking for or allow other clients to download from it.
 - [ ] When a client wants to exit the peer network, it can send an EXIT to the server.
 - [ ] The client and server should implement a stop-and-wait timeout for UDP packets that do not arrive successfully.
 - [x] Multi-threaded server

 How to Run the Server and Client
 ============
 A Makefile is included to allow easy building and running of the client and Server. The Makefile uses clang++ to compile the source files. g++ can be used instead but is not supported in the Makefile.

 <h4>Run the Server</h4>
 To run the server, simply run `make run_server`. This will build the server and start running it on the server designated port.

 <h4>Run the Client</h4>
 To run the server, simply run `make run_client`. This will build the client and start running. The client will start up, UPDATE the server on what files it has available and then make a QUERY for 2 text files called text.txt and text2.txt. The client will receive a packet with information detailing where to find the files it is looking for. This information includes the client if it has these files.
