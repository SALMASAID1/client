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





#endif // FONCTION_H_INCLUDED
