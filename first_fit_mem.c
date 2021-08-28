#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
 * Name     : Ramindu Walgama
 * Index    : 201177
 * Email    : raminduw200@gmail.com
 */

#define MEMORY 2560
int remaining_mem = 2560;

void printb(char* string_);

// Node = Process/ Job
struct Node {
    char *process_id;
    int start;
    int size;
    struct Node *next;
    struct Node *prev;
};

/*
 * @function: Insert a new process into the memory according to the first-fit
 *            algorithm. (Insert a node to the linked list)
 * @return  : void
 * @args    : head_       - head of the linked list
 *            process_id_ - process id : example : p1, p2
 *            start_      - starting memory location of the process in the memory
 *                          example: p1 starts after the OS allocation. Start will be the end of the allocated
 *                          memory for OS. If OS is 400K, start of the p1 (only process) will be 400k.
 *            size_       - size of the process.
 */
void firstFit(struct Node *head_, char *process_id__, int size_) {
    char *process_id_ = malloc(strlen(process_id__) + 1);
    strcpy(process_id_, process_id__);

//    Check the memory is full or not.
    if (remaining_mem - size_ >= 0) {
        struct Node *temp = head_;
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

        new_node->process_id = process_id_;
        new_node->size = size_;
        new_node->next = NULL;

/*      Check place where the new_node should be(where the process should be in the memory)
 *      let new_node = P2 and goes between P1 and P3
 *      OS ------> P1 ------> P3
 *      while loop assign the P1 to the temp since its the place where new node belongs
 *                                  4.temp -> next = new_node               1.new_node -> next = temp -> next
 *                                |--------------------------->|            |--------------------------->|
 *      OS -------------> P1 (temp)                             P2 (new_node)                             P3
 *                                |<---------------------------|            |<---------------------------|
 *                                  2.new_node -> prev = temp               3.temp -> next -> prev = new_node
 */
        while (temp->next != NULL) {
            if (temp->next->start - (temp->start + temp->size) >= size_) {
                new_node->start = temp->start + temp->size;
                new_node->next = temp->next;
                new_node->prev = temp;
                temp->next->prev = new_node;
                temp->next = new_node;
                remaining_mem -= size_;
                break;
            }
            temp = temp->next;
        }

//        If only the OS exists as a process in the memory, add new process next to OS.
        if (head_->next == NULL) {
            new_node->start = head_->start + head_->size;
            head_->next = new_node;
            new_node->prev = head_;
            remaining_mem -= size_;
        }
//        If the available memory is in the last space, add new process to the last
        else if (MEMORY - (temp->start + temp->size) > size_) {
            new_node->start = temp->start + temp->size;
            temp->next = new_node;
            new_node->prev = temp;
        }
        else {
            printb("\n\t\t[ERROR] Ran out of memory.\n");
        }
    } else {
        printb("\n\t\t[ERROR] Ran out of memory.\n");
    }
}


/*
 * @function : Print a snapshot of the memory
 * @return   : void
 *             print the snapshot
 * @args     : head_       - head of the linked list
 */
void showTasks(struct Node *head_) {
    struct Node *temp = head_;
    printf("+---------------------------------------------------------------------------------------+\n");
    printb("|\tStart Address\t|\t\tProcess\t\t|\t\tSize\t\t|\t\t\n");
    printf("+---------------------------------------------------------------------------------------+\n");
    printf("|\t%dK\t\t|\t%s\t|\t\t%dK\t\t|\t\t\n", head_->start, head_->process_id, head_->size);
    printf("+---------------------------------------------------------------------------------------+\n");

    while (temp->next != NULL) {
        temp = temp->next;
        printf("|\t%dK\t\t|\t\t%s\t\t|\t\t%dK\t\t|\t\t\n", temp->start, temp->process_id, temp->size);
        printf("+---------------------------------------------------------------------------------------+\n");
    }
}


/*
 * @function : Check a given process (node) exists
 * @return   : Given process if process exists. (a node)
 *             @type: Node pointer
 * @args    : head_       - head of the linked list
 *             process_id_ - process id : example : p1, p2
 */
struct Node* getProcess(struct Node *head_, char *process_id_){
    struct Node* temp = head_;

    if(head_->process_id == process_id_)
        return head_;

    while (temp->next != NULL){
        temp = temp->next;
        if(strcmp(temp->process_id, process_id_) == 0) // temp->process_id == process_id_
            return temp;
    }

    return NULL;
}


/*
 * @function : Remove a process (Delete a node from the linked list)
 * @return   : void
 * @args    : head_       - head of the linked list
 *             process_id_ - process id : example : p1, p2
 */
void removeProcess(struct Node *head_, char* process_id_) {
    struct Node* deleteNode = getProcess(head_, process_id_);

    if (deleteNode == head_){
        printb("\n\t\t[ERROR] Cannot terminate the Operating System.\n");
    } else if (deleteNode->next !=NULL){
        deleteNode->next->prev = deleteNode->prev;
        deleteNode->prev->next = deleteNode->next;
        free(deleteNode);
    } else if(deleteNode->next == NULL){
        deleteNode->prev->next = NULL;
        free(deleteNode);
    }
}


// main thread
int main() {
    int option;
    int process_size;

    //    Head will be the OS.
    struct Node head;
    head.process_id = "Operating_System";
    head.start = 0;
    head.size = 400;
    head.next = NULL;
    head.prev = NULL;

    printf("\n+---------------------------------------------------------------------------------------+\n");
    printb("+-----------------------------First Fit Memory Management-------------------------------+\n");
    printf("+---------------------------------------------------------------------------------------+\n");

    do {
        char process_id[20];

        printf("\n\n\t\tStart a New process : 1\n");
        printf("\t\tTerminate a process : 2\n");
        printf("\t\tShow process stack  : 3\n");
        printf("\t\tExit : -1\n");
        printf("\t\t+-----------------------+\n");
        printf("\t\tSelect an option : ");
        scanf("%d", &option);


        switch (option) {
            case 1: // Start a New process
                printf("\t\tEnter the ProcessID : ");
                scanf("%s", process_id);
//                check the process is already running
                if (getProcess(&head, process_id) == NULL) {
                    printf("\t\tEnter the size of the Process : ");
                    scanf("%d", &process_size);
                    if (process_size > 0)
                        firstFit(&head, process_id, process_size);
                    else{
                        printb("\n\t\t[ERROR] Memory allocation cannot be negative or 0");
                        continue;
                    }
                } else {
                    printb("\n\t\t[WARNING] Process is already running.\n");
                }
                break;
            case 2: // Terminate a process
                printf("\t\tEnter the ProcessID : ");
                scanf("%s", process_id);
                if (getProcess(&head, process_id) == NULL)
                    printb("\n\t\t[ERROR] Process does not exists. Termination failed");
                else
                    removeProcess(&head, process_id);
                break;
            case 3: // Show process stack
                showTasks(&head);
                break;
            default:
                printb("\t\tPlease enter a valid input\n");
                break;
        }
    } while (option != -1);

    return 0;
}

// Method to bold text, errors
void printb(char* string_){
    printf("\e[1m%s\e[0m", string_);
};