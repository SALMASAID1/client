#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "conio.h"
#include "header_PRODUIT.h"


FILE * FACT ; // Client's Factor

FILE * CDM;  // CRM : CREDIT CARD DETAIL MANAGEMENT

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
} CCD ;    // CCD : CREDIT CARD DETAIL

typedef struct {
    int id_product ;
    char name[20];
    char category[50];
    float price;
    char description[100];
    int quantity ;
}product;

// choice of client 

typedef struct {
char category[50];
char name[20];
int quantity ;

}clc ; // clc : client choice 

// functions of chickens


void add_credit_card(char* CIN_client, char *name_client) {
    time_t t = time(NULL);   // Get the current time
    struct tm *current_time = localtime(&t); // Convert to local time structure
    int current_year = current_time->tm_year + 1900; // Extract the current year
    int current_mont = current_time->tm_mon + 1 ;

    // Open the file in append binary mode
    CDM = fopen("CREDIT_CARD.dat", "wb");
    if (CDM == NULL) {
        c_textcolor(4);
        printf("File does not exist!\n");
        return;  // Exit without terminating the program
    }
   int valid = 0;
    CCD A;
    strncpy(A.client_CIN, CIN_client, sizeof(A.client_CIN) - 1);
    A.client_CIN[sizeof(A.client_CIN) - 1] = '\0';  // Ensure null termination
    strncpy(A.client_name, name_client, sizeof(A.client_name) - 1);
    A.client_name[sizeof(A.client_name) - 1] = '\0';  // Ensure null termination
    c_textcolor(5);
    c_gotoxy(18 , -1 );printf(" %s, please enter your credit card information (typically 13-19 digits):", name_client);

    int increment_screen = 0 ;
    do {
        c_textcolor(1);
        c_gotoxy(19 , 4  );printf("Enter your credit card number: ");
        c_textcolor(15);
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
           c_gotoxy(18 , -1 );printf("\n\nPlease enter a valid number between 13-19 digits\n\n");
        }
    } while (!valid);
    c_gotoxy(23 , 31 );printf("\n************** Enter The Expiry Date **************\n");

    valid = 0;
    int month, year;
    do {
        c_textcolor(5);
        printf("\nEnter the expiry date as MM/YY (e.g., 02/27): ");
        c_textcolor(1) ;
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
    c_textcolor(1);
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
    }
 } while (!valid);
    c_textcolor(2);
   printf("Valid CVV Code");
   c_textcolor(15);
    fwrite(&A, sizeof(CCD), 1, CDM);
    fclose(CDM);
    c_getch();
    c_clrscr();

}
void display_credit_cards(FILE  * CDM_1 ,char *name_client,char* CIN ){
    CCD CD ; // CD : CARD DETAIL 
    c_textcolor(5);
    printf("------------------- Credit Card of : %s  , CIN : %s -------------------" , name_client , CIN ) ;
    while (fread(&CD , sizeof(CCD) ,1 , CDM_1) == 1 ) {
         if (strcmp(CIN , CD.client_CIN) == 0 ){
            c_textcolor(1);
            printf("\nCard credit Number : ");
           for(int i = 0 ; i < strlen(CD.card_number) ; i++){
            if (i < 2 || (i == strlen(CD.card_number)-1 ) || (i == strlen(CD.card_number)-2 )){
            c_textcolor(5);
            printf("%c" ,CD.card_number[i] );
            }
            else {
            c_textcolor(5);
            printf("*");
            }
             }
            printf("\n");
            c_textcolor(1);
            printf("CIN :");
            c_textcolor(5);
            printf(" %s\n",CD.client_CIN);           
         }
    }
    c_getch();
    c_clrscr();
}
void Display_the_Supplier_sales_in_the_Day (FILE * supplier_amount){
    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1; // Months are 0-11, so add 1
    int year = localTime->tm_year + 1900; // Years since 1900, so add 1900
    c_textcolor(5);
    printf("\ndate of sales : %02d-%02d-%d\n", day, month, year);
    char car ;
    rewind(supplier_amount);
    while((car = fgetc(supplier_amount))!=EOF)
    {
        putchar(car );
    }
    c_textcolor(15);


}
void Display_the_Supplier_Total_amount_sales_in_the_Day(FILE *PCM, FILE *client_choice, char *CINF, int supplier_num) { // PCM : PRODUCT CLIEN MANGMENT
    time_t currentTime;
    time(&currentTime);

    struct tm *localTime = localtime(&currentTime);

    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1 ;     // Months are 0-11, so add 1
    int year = localTime->tm_year + 1900 ; // Years since 1900, so add 1900
    c_textcolor(1);
    printf("\nToday's date: %02d-%02d-%d\n", day, month, year);    
    char filename[50];
    sprintf(filename, "supplier%d.txt", supplier_num);
    FILE * supplier_amount = fopen(filename, "w+t");
    if (supplier_amount == NULL) {
        printf("Error: Unable to create file %s!\n", filename);
        return;
    }
    product A;
    clc B;
    float total_amount = 0;
    float sale_mount = 0  ;
    c_textcolor(5);
    c_gotoxy(15, 30);
    printf("----------------The total amount of your sale, %s ----------------\n", CINF);
    c_textcolor(1);
    fprintf(supplier_amount ,"CIN: %s \n", CINF );
    while (fread(&B, sizeof(clc), 1, client_choice) == 1) {
        rewind(PCM); // Ensure we read PCM from the start for each choice
        while (fread(&A, sizeof(product), 1, PCM) == 1) {
            if ((strcmp(A.category, B.category) == 0 ) && strcmp (A.name , B.name ) == 0  ) {
                total_amount += A.price * B.quantity;
                sale_mount += total_amount ;
            }
        }
        fprintf(supplier_amount, "Category: %s \nQuantity: %d \nSale Amount: %.2f\n", B.category, B.quantity, total_amount);
        total_amount = 0; // Reset for the next client choice
    }
    c_textcolor(1);
    printf("                --------- %.2f DH ---------", sale_mount );
    sale_mount = 0 ;
    fclose(supplier_amount);
}
void feedback_and_rate_the_product(char *name_cl, int id_product) { // name_cl: client name, id_product: product id
    FILE *client_opinion = fopen("feedback.txt", "a");
    if (client_opinion == NULL) {
        c_textcolor(4); 
        printf("Error: feedback.txt does not exist!\n");
        return;
    }

    char comment[256];
    c_textcolor(5);
    printf("%s, enter your comment about Product %d: ", name_cl, id_product);
    c_textcolor(1);
    fflush(stdin);
    fgets(comment, sizeof(comment), stdin);
    size_t len = strlen(comment);
    if (len > 0 && comment[len - 1] == '\n') 
    comment[len - 1] = '\0'; // Remove the newline character
    // Write the comment to the file
    fprintf(client_opinion, "Client: %s | Product ID: %d | Comment: %s\n", name_cl, id_product, comment);
    puts(comment);

    int rating;
    c_textcolor(5);
    printf(" Rate the product (1 to 5 stars): ");
    c_textcolor(15);

    // Input loop for rating with validation
    while (1) {
        if (scanf("%d", &rating) != 1 || rating < 1 || rating > 5) {
            // Clear invalid input from buffer
            while (getchar() != '\n');
            c_textcolor(4);
            printf("Invalid rating. Please enter a number between 1 and 5: ");
        } else {
            break;
        }
    }

    c_textcolor(1);
    switch (rating) {
        case 1:
            printf("- You rated this product 1 star: We're sorry to hear that you had a poor experience.\n");
            fprintf(client_opinion, "Rating: 1 star\n");
            break;
        case 2:
            printf("-- You rated this product 2 stars: Thank you! We'll work on improving.\n");
            fprintf(client_opinion, "Rating: 2 stars\n");
            break;
        case 3:
            printf("--- You rated this product 3 stars: Thanks for the feedback! We're glad it was satisfactory.\n");
            fprintf(client_opinion, "Rating: 3 stars\n");
            break;
        case 4:
            printf("---- You rated this product 4 stars: Great! Thank you for the positive feedback!\n");
            fprintf(client_opinion, "Rating: 4 stars\n");
            break;
        case 5:
            printf("----- You rated this product 5 stars: Awesome! We're thrilled you loved it!\n");
            fprintf(client_opinion, "Rating: 5 stars\n");
            break;
    }
    c_textcolor(14);
    printf("\nThank you for your feedback!\n");
    c_textcolor(15);
    fclose(client_opinion);
}
