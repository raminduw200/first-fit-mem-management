#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MEM_SPACE 2560

// 
struct Node {
    char* process_id;
    int start;
    int size;
    bool free;
    struct Node* next;
};

void insertNode(struct Node* head_, char* process_id_, int start_, int size_){
    struct Node* temp = head_;
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node -> process_id = process_id_;
    new_node -> start = start_;
    new_node -> size = size_;
    new_node -> free = false;
    new_node -> next = NULL;

    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    temp -> next = new_node;
}

void showTasks(struct Node* head_){
    struct Node* temp = head_;
    printf("Process\t\tSize\t\t");
    while (temp -> next != NULL) {
        printf("%d\n", temp->start);
        temp = temp -> next;
    }
    printf("%d\n", temp->start);
}

int main() {
    struct Node head;
    head.process_id = "Operating System";
    head.start = 0;
    head.size = 400;
    head.free = false;
    head.next = NULL;

    insertNode(&head, "P1", 400, 400);
    insertNode(&head, "P2", 500, 400);
    insertNode(&head, "P3", 600, 400);
    showTasks(&head);
    return 0;
}
