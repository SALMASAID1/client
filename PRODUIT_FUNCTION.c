#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "conio.h"
#include "header_PRODUIT.h"

// typedef struct Purchase {
//     char creditCardNumber[20];
//     char purchaseDate[11];
//     char merchantName[50];
//     double rest_amount;
// }; // Amount spent on the purchase using a credit card



FILE *CDM;  // CRM : CREDIT CARD DETAIL MANAGEMENT

typedef struct {     // Date card credit information
    char year[3];
    char month[3];
} date_card;

typedef struct credit_card_details {     // Credit Card Information
    char client_CIN[20];
    char client_name[30];
    char card_number[50];
    char CVV [5];
    date_card expiry_date;
    double Amount ;
} CCD;    // CCD : CREDIT CARD DETAIL

void add_credit_card(char* CIN_client, char *name_client) {
    time_t t = time(NULL);   // Get the current time
    struct tm *current_time = localtime(&t); // Convert to local time structure
    int current_year = current_time->tm_year + 1900; // Extract the current year
    int current_mont = current_time->tm_mon + 1 ;

    // Open the file in append binary mode
    CDM = fopen("CREDIT_CARD.dat", "wb");
    if (CDM == NULL) {
        printf("File does not exist!\n");
        return;  // Exit without terminating the program
    }
   int valid = 0;
    CCD A;
    strncpy(A.client_CIN, CIN_client, sizeof(A.client_CIN) - 1);
    A.client_CIN[sizeof(A.client_CIN) - 1] = '\0';  // Ensure null termination
    strncpy(A.client_name, name_client, sizeof(A.client_name) - 1);
    A.client_name[sizeof(A.client_name) - 1] = '\0';  // Ensure null termination

    c_gotoxy(18 , -1 );printf(" %s, please enter your credit card information (typically 13-19 digits):", name_client);

    int increment_screen = 0 ;
    do {
        c_gotoxy(19 , 4  );printf("Enter your credit card number: ");
        c_gotoxy(19  , 31);scanf("%s", A.card_number);

        // Check if card number contains only digits and has valid length
        valid = 1;
        for (int i = 0; i < strlen(A.card_number); i++) {
            if (!isdigit(A.card_number[i])) {
                valid = 0;
                break;
            }
        }
        if (strlen(A.card_number) < 13 || strlen(A.card_number) > 16) {
            valid = 0;
        }

        if (!valid) {
            c_clrscr();
           c_textcolor(4);
           printf("\n\nPlease enter a valid number between 13-19 digits\n\n");
           c_textcolor(15);
        }
    } while (!valid);

    c_gotoxy(23 , 31 );printf("\n************** Enter The Expiry Date **************\n");

    valid = 0;
    int month, year;
    do {
        printf("\nEnter the expiry date as MM/YY (e.g., 02/27): ");
        scanf("%2s/%2s", A.expiry_date.month, A.expiry_date.year);
        // Parse and validate month and year
        if ((sscanf(A.expiry_date.month, "%2d", &month) == 1) && (sscanf(A.expiry_date.year, "%2d", &year) == 1)) {
            if (month > 0 && month <= 12  && year >= (current_year - 2000) ) {
                valid = 1;
            } 
        if (( year == current_year-2000 ) && (month <= current_mont))  valid = 0 ;
        if (valid == 0 ) {
                c_textcolor(4); 
                printf("Invalid month or year!");
                c_textcolor(7);
            }
        } else {
           printf("\nInvalid format. Please enter MM/YY\n");
        }
    } while (!valid);
 valid = 0;
 do {
    printf("Enter your CVV code (e.g., 123): ");
    scanf("%s", A.CVV);

    // Check if CVV is exactly 3 digits
    valid = 1;  
    if (strlen(A.CVV) != 3) {
        valid = 0;
    } else {
        for (int i = 0; i < 3; i++) {
            if (!isdigit(A.CVV[i])) {
                valid = 0;
                break;
            }
        }
    }

    if (!valid) {
        c_textcolor(4);
        printf("Invalid CVV! Please enter a 3-digit number.\n");
        c_textcolor(7);
    }
 } while (!valid);
    c_textcolor(4);
   printf("Valid CVV Code");
   c_textcolor(15);
   A.Amount= ADD_spent_money_to_credit_cards();
    fwrite(&A, sizeof(CCD), 1, CDM);
    fclose(CDM);


}
 double  ADD_spent_money_to_credit_cards(){
   c_textcolor(2);
    printf("\nPlease enter the amount of money you want to spend using your credit card in DH : ");
    c_textcolor(15);
    double s_m; // spent money
    do{
    scanf("%lf" ,&s_m);
    if (s_m >= 0 ){
      c_textcolor(2);
      printf("Secces Validition !!");
      c_textcolor(15);
      break;
    }
    }while (1);
    return  s_m ;
}
void  display_credit_cards_balance(FILE  * CDM_1 , char* CIN ){
    CCD CD ; // CD : CARD DETAIL 
    while (fread(&CD , sizeof(CCD) ,1 , CDM_1) == 1 ) {
         if (strcmp(CIN , CD.client_CIN) == 0 ){
            c_textcolor(4);
            printf("\nCard credit Number : ");
           for(int i = 0 ; i < strlen(CD.card_number) ; i++){
            if (i < 2 || (i == strlen(CD.card_number)-1 ) || (i == strlen(CD.card_number)-2 ))printf("%c" ,CD.card_number[i] );
            else printf("*");
             }
            printf("\n");
            printf("CIN : %s\n",CD.client_CIN);
            printf("Balance : %.2lf DH\n" , CD.Amount);
            
         }
    }
}