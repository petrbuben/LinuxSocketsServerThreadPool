#include "myqueue.hpp"

#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

node_t* head = nullptr;
node_t* tail = NULL;

void * enqueue (void * client_socket){
    node_t * newnode = (node_t*)malloc(sizeof(node_t));

    newnode->client_socket = (int*)client_socket;
    newnode->next=nullptr;

    if (tail == nullptr){ //first time
        head = newnode;
    } else {
        tail->next = newnode;
    }
    tail = newnode;

    return nullptr;
}


int * dequeue (){
    if (head == nullptr){
        return nullptr;
    } else {
        int * result = head->client_socket;
        node_t * temp = head;
        head = head->next;
        if (head == nullptr){
            tail = nullptr;
        }
        free (temp);

        return result;        
    }
}


int create_server_socket(){
  //Create the socket.
  struct sockaddr_in serverAddr;
  
  int serverSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  if(serverSocket < 0){//error = -1
    perror("server socket creation error");
    exit(-1);
  }

  // Configure settings of the server address struct
  // Address family = Internet
  serverAddr.sin_family = AF_INET;

  //Set port number, using htons function to use proper byte order
  serverAddr.sin_port = htons(7799);

  //Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  //Set all bits of the padding field to 0
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  //Bind the address struct to the socket
  int b = bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if (b< 0){
        perror("server bind error\n");
        exit(-1);
    }

  //Listen on the socket, with 50 max connection requests queued
  if( listen(serverSocket,50) == 0 )
    printf("main thread: server socket listening... \n");
  else{
    printf("main thread: server listening error\n");
    exit(-1);
  }

  return serverSocket;
}

