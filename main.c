#include <stdio.h>
#include <malloc.h>

#define MEMORY 2560
int remaining_mem = 2560;

//void firstFit(struct Node *head_, char *process_id_, int size_);
//void showTasks(struct Node *head_);
//struct Node* getProcess(struct Node *head_, char* process_id_);

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
 * @params  : head_       - head of the linked list
 *            process_id_ - process id : example : p1, p2
 *            start_      - starting memory location of the process in the memory
 *                          example: p1 starts after the OS allocation. Start will be the end of the allocated
 *                          memory for OS. If OS is 400K, start of the p1 (only process) will be 400k.
 *            size_       - size of the process.
 */
void firstFit(struct Node *head_, char *process_id_, int size_) {
    if (remaining_mem - size_ > 0) {
        struct Node *temp = head_;
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

        new_node->process_id = process_id_;
        new_node->size = size_;
        new_node->next = NULL;

        while (temp->next != NULL) {
            if (temp->next->start - (temp->start + temp->size) > size_) {
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
        } else {
            printf("[ERROR] Ran out of memory.\n");
        }
    } else {
        printf("[ERROR] Ran out of memory.\n");
    }
}

void showTasks(struct Node *head_) {
    struct Node *temp = head_;
    printf("Process\t\tSize\t\t\n");
    while (temp->next != NULL) {
        printf("%s\n", temp->process_id);
        temp = temp->next;
    }
    printf("%s\n", temp->process_id);
//    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
//    while (temp->prev != NULL) {
//        printf("%s\n", temp->process_id);
//        temp = temp->prev;
//    }
//    printf("%s\n", temp->process_id);
}

/*
 * @function : Check a given process (node) exists
 * @return   : Given process if process exists. (a node)
 *             @type: Node pointer
 * @param    : head_       - head of the linked list
 *             process_id_ - process id : example : p1, p2
 */
struct Node* getProcess(struct Node *head_, char* process_id_){
    struct Node* temp = head_;

    if(head_->process_id == process_id_)
        return head_;

    while (temp->next != NULL){
        temp = temp->next;
        if(temp->process_id == process_id_)
            return temp;
    }

    return NULL;
}

/*
 * @function : Remove a process (Delete a node from the linked list)
 * @return   : void
 * @param    : head_       - head of the linked list
 *             process_id_ - process id : example : p1, p2
 */
void removeProcess(struct Node *head_, char* process_id_){
    struct Node* deleteNode = getProcess(head_, process_id_);

    if (deleteNode == head_) {
        printf("[ERROR] Cannot terminate the Operating System.\n");
    } else if (deleteNode != NULL && deleteNode->next !=NULL){
        deleteNode->next->prev = deleteNode->prev;
//        printf("delete node next prev: %s\n", deleteNode->next->prev->process_id);
//        printf("delete node prev: %s\n", deleteNode->prev->process_id);
//        printf("delete node : %s\n", deleteNode->process_id);
//        printf("delete node next : %s\n", deleteNode->next->process_id);
        deleteNode->prev->next = deleteNode->next;
        free(deleteNode);
    } else if(deleteNode->next == NULL){
        deleteNode->prev->next = NULL;
        free(deleteNode);
    }
}


int main() {
//    Head will be the OS.
    struct Node head;
    head.process_id = "Operating_System";
    head.start = 0;
    head.size = 400;
    head.next = NULL;
    head.prev = NULL;

    firstFit(&head, "P1", 400);
    firstFit(&head, "P2", 500);
    firstFit(&head, "P3", 600);
    removeProcess(&head, "P2");
    firstFit(&head, "P4", 200);
    firstFit(&head, "P5", 100);
    firstFit(&head, "P6", 100);
    removeProcess(&head, "P5");
    firstFit(&head, "P7", 200);
    showTasks(&head);
    printf("--------------\n");
    showTasks(&head);
    return 0;
}
