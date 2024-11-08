#include <stdio.h>
#include <stdlib.h>
#include "conio.c"
#include"fonction.h"
int main() {
    int choice;
    c_textattr(5);

    do {
        printf("1 - Login\n");
        printf("2 - Sign In\n");
        printf("3 - Leave page\n");
        printf(" ---->> GIVE CHOICE : ");

        if (scanf("%d", &choice) != 1) {
            // Clear invalid input from the buffer
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;  // Restart the loop
        }

        switch (choice) {
            case 1:
                Login();
                break;
            case 2:
                sign_in();
                break;
            case 3:
                leave();
                break;
            default:
                printf("Please choose a valid option.\n");
                break;
        }

    } while (choice != 3);  // Exit the loop if choice is 3

    return 0;
}
