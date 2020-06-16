#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

typedef struct node{
    struct node * next;
    int* client_socket;
} node_t;

void * enqueue(void*);
int * dequeue();
int create_server_socket();

#endif

