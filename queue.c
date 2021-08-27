#include <string.h>
#include <stdio.h>

#define SIZE 4

int front = -1;
int rear = -1;
char queue[SIZE][50];

int isFull(){
    if(rear + 1 == front || (rear == SIZE-1 && front == 0))
        return 1;
    return 0;
}

int isEmpty(){
    if(front == -1)
        return 1;
    return 0;
}

void enQueue(char* name_){
    if (isFull()){
        printf("[ERROR] Queue is Full. Error occurs while enqueueing new element %s\n", name_);
    } else {
        if (front == -1) ++front;
        rear = (rear+1)%SIZE;
        strcpy(queue[rear], name_);
    }
}

char* deQueue(){
    int temp;
    if (isEmpty()){
        printf("[ERROR] Queue is Empty.Error occurs while de-queueing the empty queue.\n");
        return NULL;
    } else {
        temp = front;
        if (rear == front) rear = front = -1;
        else front = (front + 1) % SIZE;
        return queue[temp];
    }
}

void displaySeats(){
    if (isEmpty()){
        printf("[ERROR] Queue is Full. Error occurs while printing the queue\n");
    } else {
        for (int i = front; i < rear+1; ++i) {
            printf("+----------------------------------------------+\n");
            printf("|  Seat 1  |   %s\n", queue[i]);
        }
        printf("+----------------------------------------------+\n");
    }
}
