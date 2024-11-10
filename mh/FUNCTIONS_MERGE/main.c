#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "conio.h"
#include "FUNCTION.h"

int choice;

int main() {
    char* Client_CIN = (char*)malloc(20 * sizeof(char));
    char* Supplier_CIN = (char*)malloc(20 * sizeof(char));

    chooseLanguage();
    do {
        c_clrscr();
        displayMenu();
        c_gotoxy(40, 12);
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            // Handle invalid input and clear the buffer
            while (getchar() != '\n'); // Clear the buffer
            c_textattr(4);
            c_gotoxy(40, 14);
            printf("Invalid input. Please enter a number.\n");
            c_textattr(14);
            c_getch();
            continue;
        }
        
        switch (choice) {
            case 1:  // Supplier options
                do {
                    c_clrscr();
                    c_textattr(8);
                    c_gotoxy(50, 6); printf("1 - Login");
                    c_gotoxy(50, 7); printf("2 - Sign In");
                    c_gotoxy(50, 8); printf("3 - Leave page");
                    c_textattr(14);
                    c_gotoxy(50, 9); printf(" ---->> GIVE CHOICE : ");
                    
                    if (scanf("%d", &choice) != 1) {
                        // Handle invalid input and clear the buffer
                        while (getchar() != '\n');
                        c_textattr(4);
                        c_gotoxy(50, 11); printf("Invalid input. Please enter a number.\n");
                        c_textattr(14);
                        c_getch();
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            login_supplier(Supplier_CIN);
                            break;
                        case 2:
                            sign_in_supplier();
                            break;
                        case 3:
                            leave();
                            break;
                        default:
                            c_textattr(4);
                            c_gotoxy(50, 11); printf("Please choose a valid option.\n");
                            c_textattr(14);
                            c_getch();
                            break;
                    }
                } while (choice != 3);
                break;
            
            case 2:  // Client options
                do {
                    c_clrscr();
                    c_textattr(8);
                    c_gotoxy(50, 6); printf("1 - Login");
                    c_gotoxy(50, 7); printf("2 - Sign In");
                    c_gotoxy(50, 8); printf("3 - Leave page");
                    c_textattr(14);
                    c_gotoxy(50, 9); printf(" ---->> GIVE CHOICE : ");
                    
                    if (scanf("%d", &choice) != 1) {
                        // Handle invalid input and clear the buffer
                        while (getchar() != '\n');
                        c_textattr(4);
                        c_gotoxy(50, 11); printf("Invalid input. Please enter a number.\n");
                        c_textattr(14);
                        c_getch();
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            clientLogin(Client_CIN);
                            break;
                        case 2:
                            sign_in_client();
                            break;
                        case 3:
                            leave();
                            break;
                        default:
                            c_textattr(4);
                            c_gotoxy(50, 11); printf("Please choose a valid option.\n");
                            c_textattr(14);
                            c_getch();
                            break;
                    }
                } while (choice != 3);
                break;
            
            case 4:  // Back to previous menu or exit
                back();
                break;
            
            case 5:  // Leave application
                leave();
                break;

            default:
                c_textattr(4);
                c_gotoxy(40, 14);
                printf("Invalid choice. Please try again.");
                c_textattr(14);
                c_getch();
                break;
        }
    } while (choice != 5);

    free(Client_CIN);  // Free allocated memory before exit
    free(Supplier_CIN);
    return 0;
}
