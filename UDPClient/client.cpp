#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <iostream>
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

/* Project Imports */
#include "../Constants/actions.h" /* Contains UPDATE, QUERY, EXIT constants */
#include "../Packet/packet.h"
#include "../Ports/ports.h"
#include "../Utils/file_utils.h"

#define ECHOMAX 255     /* Longest string to echo */
#define SERVERPORT 4923 /* Server should always be on this port */

void exitWithError(const char *errorMessage) /* External error handling function */
{
    perror(errorMessage);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    struct sockaddr_in fromAddr;     /* Source address of echo */
    unsigned int fromSize;           /* In-out of address size for recvfrom() */
    char *servIP;                    /* IP address of server */
    char *echoString;                /* String to send to echo server */
    char echoBuffer[ECHOMAX+1];      /* Buffer for receiving echoed string */
    int echoStringLen;               /* Length of string to echo */
    int respStringLen;               /* Length of received response */
    Packet *sendPacket;              /* A created Packet that will be sent */
    Packet *recvPacket;              /* A created Packet that was received */

    if ((argc < 1) || (argc > 3))    /* Test for correct number of arguments */
    {
        fprintf(stderr,"Usage: %s <Server IP>\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];           /* First arg: server IP address (dotted quad) */
    echoString = argv[2];       /* Second arg: string to echo */

    if ((echoStringLen = strlen(echoString)) > ECHOMAX)  /* Check input length */
        exitWithError("Echo word too long");

    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        exitWithError("socket() failed");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));    /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                 /* Internet addr family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);  /* Server IP address */
    echoServAddr.sin_port   = htons(SERVERPORT);     /* Server port */

    sendPacket = new Packet::Packet(UPDATE, getFileSystemContents());

    /* Send the string to the server */
    // TODO: Determine the number of packets to send so that the serialize is less than ECHOMAX
    if (sendto(sock,
        sendPacket->serialize(),
        strlen(sendPacket->serialize()),
        0,
        (struct sockaddr *) &echoServAddr,
        sizeof(echoServAddr)) != strlen(sendPacket->serialize()))
          exitWithError("sendto() sent a different number of bytes than expected");

    /* Recv a response */
    fromSize = sizeof(fromAddr);
    if ((respStringLen = recvfrom(sock,
                                  echoBuffer,
                                  ECHOMAX,
                                  0,
                                  (struct sockaddr *) &fromAddr,
                                  &fromSize)) != strlen(echoBuffer))
        exitWithError("recvfrom() failed");

    if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        fprintf(stderr,"Error: received a packet from unknown source.\n");
        exit(1);
    }

    // Confirm that the packet that was recieved is an ACK.
    recvPacket = Packet::deserialize(echoBuffer);
    memset(echoBuffer, 0, strlen(echoBuffer));
    if (strcmp(recvPacket->getAction(), ACK) != 0) {
      exitWithError("Recieved invalid response from server. Expected ACK.");
    }

    sendPacket = new Packet::Packet(QUERY, "text.txt\ntext2.txt");
    if (sendto(sock,
        sendPacket->serialize(),
        strlen(sendPacket->serialize()),
        0,
        (struct sockaddr *) &echoServAddr,
        sizeof(echoServAddr)) != strlen(sendPacket->serialize()))
          exitWithError("sendto() sent a different number of bytes than expected");

    // Hopefully recieve a QUERYRESULT packet
    fromSize = sizeof(fromAddr);
    if ((respStringLen = recvfrom(sock,
                                  echoBuffer,
                                  ECHOMAX,
                                  0,
                                  (struct sockaddr *) &fromAddr,
                                  &fromSize)) != strlen(echoBuffer))
        exitWithError("recvfrom() failed");

    if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        fprintf(stderr,"Error: received a packet from unknown source.\n");
        exit(1);
    }

    // Confirm that the packet that was recieved is a QUERYRESULT.
    recvPacket = Packet::deserialize(echoBuffer);
    memset(echoBuffer, 0, strlen(echoBuffer));
    if (strcmp(recvPacket->getAction(), QUERYRESULT) != 0) {
      exitWithError("Recieved invalid response from server. Expected ACK.");
    }



    /* null-terminate the received data */
    //echoBuffer[respStringLen] = '\0';
    printf("Received: %s\n", recvPacket->serialize());    /* Print the echoed arg */

    // printf("%s\n", "Deserializing char * into Packet ...\n");
    // recvPacket = Packet::deserialize(echoBuffer);
    // printf("%s\n", "Serialized Packet output:");
    // printf("%s\n", recvPacket->serialize());

    close(sock);
    exit(0);
}
