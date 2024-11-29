#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conio.h"
#include "FUNCTION.h"

typedef struct Options {
    char **ops;
    int len;
    char *title;
} Options;

void c_print_centered(const char *text, int y) {
    int x = (80 - strlen(text)) / 2;
    c_gotoxy(x, y*2);
    printf("%s", text);
}

void c_draw_menu(int op, Options options) {
    c_clrscr();
    c_textattr(14);
    c_print_centered(options.title, 3);
    c_textattr(7);

    for (int i = 0; i < options.len; i++) {
        c_textattr(op == i ? 14 : 8);
        c_print_centered(options.ops[i], 5 + i);
    }
    c_textattr(7);
}

int c_select_menu(Options options) {
    int current_option = 0;
    int key;
    c_draw_menu(current_option, options);

    while (1) {
        key = c_getch();
        switch (key) {
            case 72: // Arrow Up
                if (current_option > 0) {
                    current_option--;
                    c_draw_menu(current_option, options);
                }
                break;
            case 80: // Arrow Down
                if (current_option < options.len - 1) {
                    current_option++;
                    c_draw_menu(current_option, options);
                }
                break;
            case 13: // Enter
                return current_option;
        }
    }
}

Options options;
char *Home_LOGIN[] = {
    "[- Supplier -]",
    "[- Client-]   ",
    "[- Exit-]     "
};

char *choose_language[] = {
    "[-English-]" ,
    "[-French -]"  ,
    "[-Leave  -]"
};

void Home_OPTIONS();
void Home_LOGIN_menu();

void Home_OPTIONS() {
    c_textcolor(14);
    options.title = "----- HOME -- PAGE -----";
    options.ops = choose_language;
    options.len = sizeof(choose_language) / sizeof(choose_language[0]);
    c_textcolor(8);

    int selected = c_select_menu(options);
    if (selected == options.len - 1) { // Last option = Leave
        exit(0); // Exit program
    } else {
        Home_LOGIN_menu(); // Navigate to Home Login if another option is selected
    }
    c_getch();
}

void Home_LOGIN_menu() {
    c_textcolor(14);
    options.title = "----- HOME -- PAGE -----";
    options.ops = Home_LOGIN;
    options.len = sizeof(Home_LOGIN) / sizeof(Home_LOGIN[0]);

    int selected = c_select_menu(options);
    int choice;  // Declare the choice variable
    if (selected == 2) { // Exit option selected
        Home_OPTIONS(); // Exit program
    } else {
    char* Client_CIN = (char*)malloc(20 * sizeof(char));
    char* Supplier_CIN = (char*)malloc(20 * sizeof(char));
    
        if (selected == 0) {
            do {
                c_clrscr();
                c_textattr(8);
                c_gotoxy(50, 6); printf("1 - Login");
                c_gotoxy(50, 7); printf("2 - Sign In");
                c_gotoxy(50, 8); printf("3 - Back to Main Menu");
                c_gotoxy(50, 9); printf("4 - Leave Program");
                c_textattr(14);
                c_gotoxy(50, 10); printf(" ---->> GIVE CHOICE : ");
                
                if (scanf("%d", &choice) != 1) {
                    // Handle invalid input and clear the buffer
                    while (getchar() != '\n');
                    c_textattr(4);
                    c_gotoxy(50, 12); printf("Invalid input. Please enter a number.\n");
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
                        Home_LOGIN_menu(); // Go back to the Home menu
                    case 4:
                        exit(0); // Leave program
                    default:
                        c_textattr(4);
                        c_gotoxy(50, 12); printf("Please choose a valid option.\n");
                        c_textattr(14);
                        c_getch();
                        break;
                }
            } while (choice != 3 && choice != 4); // Keep looping until Back or Leave is selected
        } else {
            do {
                c_clrscr();
                c_textattr(8);
                c_gotoxy(50, 6); printf("1 - Login");
                c_gotoxy(50, 7); printf("2 - Sign In");
                c_gotoxy(50, 8); printf("3 - Back to Main Menu");
                c_gotoxy(50, 9); printf("4 - Leave Program");
                c_textattr(14);
                c_gotoxy(50, 10); printf(" ---->> GIVE CHOICE : ");
                
                if (scanf("%d", &choice) != 1) {
                    // Handle invalid input and clear the buffer
                    while (getchar() != '\n');
                    c_textattr(4);
                    c_gotoxy(50, 12); printf("Invalid input. Please enter a number.\n");
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
                        Home_LOGIN_menu(); // Go back to the Home menu
                    case 4:
                        exit(0); // Leave program
                    default:
                        c_textattr(4);
                        c_gotoxy(50, 12); printf("Please choose a valid option.\n");
                        c_textattr(14);
                        c_getch();
                        break;
                }
            } while (choice != 3 && choice != 4); // Keep looping until Back or Leave is selected
        }
    }
    c_getch();
}

int main() {
    Home_OPTIONS();
    return 0;
}

