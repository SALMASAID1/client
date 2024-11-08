#include <stdio.h>
#include <stdlib.h>
#include "conio.c"
#include"fonction.h"
int main() {
    int choice;


    do {    c_textattr(8);
       c_gotoxy(50,6); printf("1 - Login");
        c_gotoxy(50,7);printf("2 - Sign In");
        c_gotoxy(50,8);printf("3 - Leave page");
        c_textattr(14);
        c_gotoxy(50,9); printf(" ---->> GIVE CHOICE : ");
         if (scanf("%d", &choice) != 1) {
            // Clear invalid input from the buffer
            while (getchar() != '\n');
                 c_textattr(4);
           c_gotoxy(50,11); printf("Invalid input. Please enter a number.\n");
           c_clrscr();
                 c_textattr(14);
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
                 c_textattr(4);
                printf("Please choose a valid option.\n");
                 c_textattr(14);
                break;
        }

    } while (choice != 3);  // Exit the loop if choice is 3

    return 0;
}
