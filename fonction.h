#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
void Login(void);
void sign_in(void);
void leave(void);

void View_Product_List(void);
void Add_To_Cart(void);
void View_Cart(void);
void Remove_From_Cart(void);
void Checkout(void);
void Track_Order(void);
void Rate_Product(void);

// Function to get the console width
int getConsoleWidth() {
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1; // Width of the console
}

// Function to print centered text
void printCentered(const char *text) {
    int consoleWidth = getConsoleWidth();
    int len = strlen(text);
    int padding = (consoleWidth - len) / 2; // Calculate padding for centering
    if (padding > 0) {
        // Print spaces for padding
        for (int i = 0; i < padding; i++) {
            printf(" ");
        }
    }
    printf("%s\n", text); // Print the text
}


void setConsoleColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor | (bgColor << 4));
}
void resetConsoleColor() {
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
}

typedef struct {
    char last_name[50];
    char First_name[50];
    char CIN[20];
    char password[20];
    char confirm_password[20];
} Client;

typedef struct {
    char category[50];
    char name[20];
    char description[100];
    float price;

}product;


void leave(){
setConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY, 0);
printf("Exiting the Aplication...\n\t**GOOD BYE**\t");
resetConsoleColor();
 exit(0);

}

int is_CIN_unique(const char *cin) {
    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) return 1;

    char file_cin[20];
    while (fscanf(fp, "%*s %*s %s %*s", file_cin) == 1) {
        if (strcmp(file_cin, cin) == 0) {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void sign_in() {
    int i,j;
    Client client;
    FILE *fp = fopen("CLIENT.txt", "a");
    if (fp == NULL) {
        printf("The file does not exist or could not be opened!\n");
        return;
    }

    printf("Enter your LAST NAME: ");
    scanf("%s", client.last_name);
    printf("Enter your FIRST NAME: ");
    scanf("%s", client.First_name);

    do {
        printf("Enter your CIN: ");
        scanf("%s", client.CIN);
        if (!is_CIN_unique(client.CIN)) {
                setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
                printf("Error: CIN already exists. Please enter a unique CIN.\n");
               resetConsoleColor();

        }
    } while (!is_CIN_unique(client.CIN));

    do {

    printf("Enter NEW PASSWORD: ");
    for (i = 0; i < 19; i++) {
        client.password[i] = getch();  // Read character without displaying it

        if (client.password[i] == '\r') {  // Stop if Enter is pressed
            break;
        }

        printf("*");  // Display an asterisk for each character
    }

    client.password[i] = '\0';  // Null-terminate the string


        printf("\nConfirm your PASSWORD: ");
           for (j = 0; j < 19; j++) {
        client.confirm_password[j] = getch();

        if (client.confirm_password[j] == '\r') {
            break;
        }

        printf("*");
    }

    client.confirm_password[j] = '\0';

        if (strcmp(client.password, client.confirm_password) != 0) {
                setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
                printf("\nError: Passwords do not match. Please try again.\n");
               resetConsoleColor();

        }
    } while (strcmp(client.password, client.confirm_password) != 0);

    fprintf(fp, "%s %s %s %s\n", client.last_name, client.First_name, client.CIN, client.password);
        setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0);
                 printf("\nInformation added successfully!\n");
               resetConsoleColor();


    fclose(fp);
}


void liste() {
    int c;
    do {
        // Displaying the menu with color and better formatting
        setConsoleColor(FOREGROUND_RED|FOREGROUND_BLUE| FOREGROUND_INTENSITY,0); // Green text
        printCentered("     ---------------------------");
        printCentered("     ----- LIST OF OPTIONS -----");
          printCentered("      ---------------------------");
                  resetConsoleColor();
         setConsoleColor(FOREGROUND_BLUE|  FOREGROUND_INTENSITY,0);
          printCentered("          1 - View Product List");
          printCentered("    2 - Add To Cart");
          printCentered("  3 - View Cart");
          printCentered("        4 - Remove From Cart");
          printCentered("5 - Checkout");
          printCentered("    6 - Track Order");
          printCentered("    7 - Rate Product");
          setConsoleColor(FOREGROUND_RED|FOREGROUND_BLUE|  FOREGROUND_INTENSITY,0);
          printCentered("  8 - Leave Page");
          printCentered("      ---------------------------");
        resetConsoleColor(); // Reset color before getting input

        // Prompt for user input
        printf("------->> SELECT YOUR OPTION: ");scanf("%d", &c);
        system("cls");

        switch (c) {
            case 1: {
                View_Product_List();

                break;

            }
            case 2: {
                // Code for adding to cart
                printCentered("Adding to cart...");
                break;
            }
            case 3: {
                // Code for viewing cart
                printCentered("Viewing cart...");
                break;
            }
            case 4: {
                // Code for removing from cart
                printCentered("Removing from cart...");
                break;
            }
            case 5: {
                // Code for checkout
                printCentered("Checking out...");
                break;
            }
            case 6: {
                // Code for tracking order
                printCentered("Tracking order...");
                break;
            }
            case 7: {
                // Code for rating product
                printCentered("Rating product...");
                break;
            }
            case 8: {
                leave(); // Call the leave function
                break;
            }
            default:
                setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY,0); // Red text for error
                printCentered("Incorrect choice! Your choice should be between [1 - 8]. Please retry.");
                resetConsoleColor(); // Reset color after error message
        }

    } while (c != 0); // Loop until the user decides to exit
}
void Login() {

    char passw[20];
    int found = 0;
    char CINN[20];
    int k;

    printf("Let's connect to your account:\n");
    printf("Enter your CIN: ");
    scanf("%s", CINN);

    printf("Enter your PASSWORD: ");
        for (k = 0; k < 19; k++) {
        passw[k] = getch();

        if (passw[k] == '\r') {
            break;
        }

        printf("*");
    }
    passw[k] = '\0';

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        printf("\nError: Could not open the file.\n");
        return;
    }

    Client client;
    while (fscanf(fp, "%*s %*s %s %s", client.CIN, client.password) == 2) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {
            setConsoleColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY, 0);
            printf("\nConnected successfully!\n");
            resetConsoleColor();
            found = 1;
            system("cls");
            liste();

            break;
        }
    }

    if (!found) {
        setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
        printf("\nYou need to create an account first!\n");
        resetConsoleColor();
    }

    fclose(fp);
}
void View_Product_List(){
     product p;

    FILE *fk = fopen("products.dat", "rb");
    if (fk == NULL) {
          printf("The file does not exist or could not be opened!\n");
        return 0 ;
    }

    printf("\n======THE PRODUCTS LIST====== :\n\n");

    printf("CATEGORY\tNAME\t\tDESCRIPTION\t\tPRICE\n");
    printf("-------------------------------------------------------\n");

    while (fread(&p, sizeof(product), 1, fk) == 1) {
        printf("%s\t\t%s\t\t%s\t\t%.2f\n",
               p.category, p.name, p.description, p.price);
    }

    fclose(fk);
    printf("\n\n\n\n\n");

}





#endif // FONCTION_H_INCLUDED
