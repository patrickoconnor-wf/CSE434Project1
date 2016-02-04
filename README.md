# CSE434Project1

What is this Project?
===============
Use Sockets to create a dead simple P2P network that will share txt files. There will be a single server used to track what clients offer what files that will communicate over UDP packets. Packets sent this way will have a high probability to be dropped, which means a timeout logic on both the clients and servers will need to be implemented. Communication between clients will be done over TCP to ensure packets are received.

Requirements
===========
<h5>Support for 3 different commands</h5>
- "Inform and Update"
- "Query For Content"
- "Exit"

<h5>At Least 2 Status Codes Need to be Implemented</h5>
- 200 (OK)
- 400 (Error)

<h5>For  messages  exchanged  between  the  directory  server  and  a  P2P  client,  we  assume  that  the  maximum
transmission unit (MTU) is 128 bytes.  I need to decide how to deal with messages longer than 128 bytes. Two options are:</h5>
- Throw an error.
- Implement a fragmentation and reassembly of packets.
