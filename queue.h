#include <string.h>
#include <stdio.h>

#define SIZE 4

int front = -1;
int rear = -1;
char queue[SIZE][50];
void printb(char* string_);

/*
 * @function : to check the queue is full
 * @return   : boolean - 1 or 0
 * @args     : -
 */
int isFull(){
    if(rear + 1 == front || (rear == SIZE-1 && front == 0))
        return 1;
    return 0;
}

/*
 * @function : to check queue is empty
 * @return   : boolean - 1 or 0
 * @args     : -
 */
int isEmpty(){
    if(front == -1)
        return 1;
    return 0;
}

/*
 * @function : Add an element to the queue
 * @return   : void
 * @args     : name_ - string
 */
void enQueue(char* name_){
    if (isFull()){
        printb("\t\t[ERROR] Queue is Full. Error occurs while enqueueing new element");
        printf("%s\n", name_);
    } else {
        if (front == -1) ++front;
        rear = (rear+1)%SIZE;
        strcpy(queue[rear], name_);
    }
}

/*
 * @function : remove an element from the queue
 * @return   : string - removed value from the queue
 * @args     : -
 */
char* deQueue(){
    int temp;
    if (isEmpty()){
        printb("\t\t[ERROR] Queue is Empty.Error occurs while de-queueing the empty queue.\n");
        return NULL;
    } else {
        temp = front;
        if (rear == front) rear = front = -1;
        else front = (front + 1) % SIZE;
        return queue[temp];
    }
}


/*
 * @function : display a snapshot of the queue (chairs)
 * @return   : void - print the queue
 * @args     : -
 */
void displaySeats(){
    int count=0;
    if (isEmpty()){
        printb("\t\t[ERROR] Queue is Full. Error occurs while printing the queue\n");
    } else {
        for (int i = front; i < rear+1; ++i) {
            printf("\t\t+----------------------------------------------+\n");
            printf("\t\t|  Seat %d  |   %s\n", ++count, queue[i]);
        }
        printf("\t\t+----------------------------------------------+\n");
    }
}

// Method to bold text, errors
void printb(char* string_){
    printf("\e[1m%s\e[0m", string_);
};