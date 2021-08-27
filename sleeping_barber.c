#include "queue.c"
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>


int main(){
    int cust_count;
    char* name;

    do {
        printf("Enter how many customers need to send to the barber shop (Enter 0 to exit): ");
        scanf("%d", &cust_count);

        char cust_list[cust_count][100];

        for (int i = 0; i < cust_count; ++i) {
            printf("Customer Name : ");
            scanf("%s", &cust_list[i]);
        }
        for (int i = 0; i < cust_count; ++i) {
            printf("Customer Name : %s\n", cust_list[i]);
        }

        for (int i = 0; i < cust_count; ++i) {
            name = cust_list[i];
            if (isFull())
                printf("No chairs left.\n"
                       "%s customer has left the barber shop...\n", name);
            else
                enQueue(name);
        }

        while (!isEmpty()) {
            char* cust = deQueue();
            printf("%s is cutting his hair...\n", cust);
            sleep(5);
            printf("%s left the barber shop...\n", cust);
        }

    } while (cust_count != 0);
    return 0;
}
