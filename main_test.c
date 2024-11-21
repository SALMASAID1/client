#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "conio.h"

// typedef struct Options {
//     char **ops;  // Array of option strings
//     int len;     // Number of options
//     char *title; // Menu title
// } Options;

// void c_print_centered(const char *text, int y) {
//     int x = (80 - strlen(text)) / 2; 
//     c_gotoxy(x, y);
//     printf("%s", text);
// }

// // Function to draw the menu
// void c_draw_menu(int op, Options options) {
//     c_clrscr();
//     c_textattr(13); // Magenta for the title
//     c_print_centered(options.title, 3);
//     c_textattr(7); // Reset to default

//     for (int i = 0; i < options.len; i++) {
//         c_textattr(op == i ? 10 : 7); // Highlight selected option
//         c_print_centered(options.ops[i], 5 + i);
//     }
//     c_textattr(7); // Reset to default
// }

// // Function to handle menu navigation
// int c_select_menu(Options options) {
//     int current_option = 0;
//     int key;
//     c_draw_menu(current_option, options);

//     while (1) {
//         key = c_getch();
//         switch (key) {
//             case 72: // Arrow Up
//                 if (current_option > 0) {
//                     current_option--;
//                     c_draw_menu(current_option, options);
//                 }
//                 break;
//             case 80: // Arrow Down
//                 if (current_option < options.len - 1) {
//                     current_option++;
//                     c_draw_menu(current_option, options);
//                 }
//                 break;
//             case 13: // Enter
//                 return current_option;
//         }
//     }
// }

// // Menu data
// Options options;
// char *MAIN_OPTIONS[] = {
//     "Settings",
//     "Exit"
// };

// char *SETTINGS_OPTIONS[] = {
//     "Brightness",
//     "Volume",
//     "Back to Main Menu"
// };

// // Function prototypes
// void settings();
// void main_menu();

// // Settings menu
// void settings() {
//     options.title = "SETTINGS MENU";
//     options.ops = SETTINGS_OPTIONS;
//     options.len = sizeof(SETTINGS_OPTIONS) / sizeof(SETTINGS_OPTIONS[0]);

//     if (c_select_menu(options) == options.len - 1) { // Last option = Back
//         main_menu();
//     }
// }

// // Main menu
// void main_menu() {
//     options.title = "MAIN MENU";
//     options.ops = MAIN_OPTIONS;
//     options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

//     if (c_select_menu(options) == 0) { // First option = Settings
//         settings();
//     }
// }


void * PIN_hide(char *PIN, int max_length)
    {
    int i = 0;
    char ch;

    while (i < max_length - 1 && (ch = _getch()) != '\r')  // '\r' is Enter key in Windows
    { 
        if (ch == '\b' && i > 0)  // Handle backspace
        { 
            i--;
            printf("\b \b");  // Move back, overwrite with space, and move back again
        }
        else if (ch != '\b')
        {
            PIN[i++] = ch;
            printf("*");
        }
    }
    PIN[i] = '\0'; // Null-terminate the PIN string
    printf("\n"); 
}

void clientLogin (char * CIN){
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
    c_textattr(8);
    printf("Let's connect to your account:\n");
    c_textattr(14);
    printf("Enter your CIN: ");
    scanf("%s", CINN);

    printf("Enter your PASSWORD: ");
        for (k = 0; k < 19; k++) {
        passw[k] = c_getch();
        if (passw[k] == '\r') {
            break;
        }

        printf("*");
    }
    passw[k] = '\0';

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        printf("\nError: Could not open the file.\n");
     c_textattr(14);
        return;
    }
    Client client;
    while (fscanf(fp, "%*s %*s %s %s", client.CIN, client.password) == 2) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {
            c_textattr(2);
            strcpy(Temp_CIN , CINN);
            printf("\nConnected successfully!\n");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();
            liste(Temp_CIN);
            break;
        }
    }
    if (!found) {
        c_textattr(4);
        printf("\nYou need to create an account first!\n");
        c_textattr(14);
    }
    fclose(fp);
    c_getch();
}

int main() {
    // main_menu();
    char * Pass[20] ;
    PIN_hide(Pass , 20);
    clientLogin("abcd");
    printf("PIN : %s " ,Pass);
    return 0;
}
