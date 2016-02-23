#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <thread>       /* for thread shenanigans */
#include <unistd.h>     /* for close() */
#include <vector>
#include <algorithm>
#include "../Constants/actions.h" /* Contains UPDATE, QUERY, EXIT constants */
#include "../Packet/packet.h"
#include "../Ports/ports.h"
#include "../Utils/file_utils.h"
#include "../ClientList/ClientList.h"


/* Project Imports */
#include "../Constants/actions.h"
#include "../Packet/packet.h"

#define ECHOMAX 255     /* Longest string to echo */
std::vector<ClientList> clients;

void exitWithError(const char *errorMessage) /* External error handling function */
{
    perror(errorMessage);
    exit(1);
}
std::string getClientsByFileName (const char *fileName){
  std::string message = "";
  for(std::vector<ClientList>::iterator iter = clients.begin(); iter != clients.end(); iter++) {
      if(iter->fileFoundInClient(fileName))
      {
        std::cout << iter->getHostName();
        //message += message + iter->getHostName();
      }
  }
      return message.c_str();
}
void handleClient(char *buffer, int sock, int msgSize, struct sockaddr_in addr) {

  Packet *recvPacket = Packet::deserialize(buffer);
  char *action = recvPacket->getAction();
  if (strcmp(action, UPDATE) == 0) {
    printf("Got UPDATE\n");
    // TODO: Implement data table logic
    char* Files = recvPacket->getMessage();
    ClientList *clientList = new ClientList::ClientList(recvPacket->getHostName(), recvPacket->getIpAddress());
    // if(!clients.empty())
    // {
    //   if(std::find(clients.begin(), clients.end(), clientList) != clients.end()) {
    //
    //   }
    //   else {
    //     clients.push_back(*clientList);
    //   }
    // }
    // else
    // {
    //   clients.push_back(*clientList);
    // }
   char* Status = clientList->formatFilesList(Files);

    Packet *sendPacket = new Packet::Packet(ACK, ACK);
    if (sendto(sock,
               sendPacket->serialize(),
               strlen(sendPacket->serialize()),
               0,
               (struct sockaddr *) &addr,
               sizeof(addr)) != strlen(sendPacket->serialize()))
                exitWithError("sendto() sent a different number of bytes than expected");

  } else if (strcmp(action, QUERY) == 0) {
    printf("Got QUERY\n");
    // TODO: Implement logic to find all clints with requested file(s)
    char *files = recvPacket->getMessage();
    std::string packetMessage = getClientsByFileName(files);
    Packet *sendPacket = new Packet::Packet(QUERYRESULT, packetMessage.c_str()); // <- Dummy data
    if (sendto(sock,
               sendPacket->serialize(),
               strlen(sendPacket->serialize()),
               0,
               (struct sockaddr *) &addr,
               sizeof(addr)) != strlen(sendPacket->serialize()))
                exitWithError("sendto() sent a different number of bytes than expected");

  } else if (strcmp(action, EXIT) == 0) {
    printf("Got EXIT\n");
    // TODO: Handle client wanting to exit and delete it from data table
    Packet *sendPacket = new Packet::Packet(ACK, "Client has been disconnected");
    if (sendto(sock,
               sendPacket->serialize(),
               strlen(sendPacket->serialize()),
               0,
               (struct sockaddr *) &addr,
               sizeof(addr)) != strlen(sendPacket->serialize()))
                exitWithError("sendto() sent a different number of bytes than expected");

  } else {
    /* Send received datagram back to the client */
    // TODO: If a non-valid action is recieved, should the packet be ignored?
    printf("%s\n", "Client sent invalid action. Ignoring...");
    }
}

int main(int argc, char *argv[])
{
    int sock;                        /* Socket */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned int cliAddrLen;         /* Length of incoming message */
    char echoBuffer[ECHOMAX];        /* Buffer for echo string */
    unsigned short echoServPort;     /* Server port */
    int recvMsgSize;                 /* Size of received message */

    if (argc != 2)         /* Test for correct number of parameters */
    {
        fprintf(stderr,"Usage:  %s <UDP SERVER PORT>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);  /* First arg:  local port */

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        exitWithError("socket() failed");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        exitWithError("bind() failed");

    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        cliAddrLen = sizeof(echoClntAddr);

        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock,
                                    echoBuffer,
                                    ECHOMAX,
                                    0,
                                    (struct sockaddr *) &echoClntAddr,
                                    &cliAddrLen)
                                  ) < 0)
            exitWithError("recvfrom() failed");

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        // Create thread to handle client
        std::thread clientThread(handleClient, echoBuffer, sock, recvMsgSize, echoClntAddr);
        // Let the thread run independently
        clientThread.detach();

        }

    /* NOT REACHED */
}
