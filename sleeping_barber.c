#include "queue.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int cust_count;
    char* name;

    do {
        printb("\t\tEnter how many customers need to send to the barber shop (Enter 0 to exit): ");
        scanf("%d", &cust_count);

        char cust_list[cust_count][100];

        // input all customer names
        for (int i = 0; i < cust_count; ++i) {
            printf("\t\tCustomer Name : ");
            scanf("%s", cust_list[i]);
        }

        // Enqueue
        for (int i = 0; i < cust_count; ++i) {
            name = cust_list[i];
            if (isFull()) {
                printf("\n\t\tNo chairs left.\n\t\t");
                printb(name);
                printf(" customer has left the barber shop...\n");
            }
            else
                enQueue(name);
        }

        printf("\n\t\tBarber woke up...\n\n");

        while (!isEmpty()) {
            char* cust = deQueue();

            printf("\t\t");
            printb(cust);
            printf(" is cutting his hair...\n");

            // Sleep - Random number between 7 and 3
            sleep(rand() % (7+1-3) + 3);

            printf("\t\t");
            printb(cust);
            printf(" left the barber shop...\n\n");

            if (!isEmpty())
                displaySeats();
            printf("\n");
        }

        printf("\t\tBarber went to sleep... z... z... z...\n\n");

    } while (cust_count != 0);
    return 0;
}
