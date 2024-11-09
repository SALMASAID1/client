#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "HaruPDF.h"
#include "conio.h"
#include "header_PRODUIT.h"

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
int id_product_clien ; 
char category[50];
float price;
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
    CDM = fopen("CREDIT_CARD.dat", "ab");
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
    c_textcolor(14);
    c_gotoxy(30 , 3 );printf(" %s, please enter your credit card information (typically 13-19 digits)", name_client);

    // int increment_screen = 0 ;
    int count_error = 0 ;
    do {
        c_textcolor(14);
        c_gotoxy(50 , 5+count_error  );printf("Enter your credit card number: ");
        c_textcolor(8);
        scanf("%s", A.card_number);
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
            c_textcolor(4);
            c_gotoxy(50 , 6 +count_error);printf("Please enter a valid number between 13-19 digits");
            count_error +=2;
        }
    } while (!valid);

    valid = 0;
    int month, year;
    do {
        c_textcolor(14);
        c_gotoxy(50 , 8 + count_error );
        printf("Enter the expiry date as MM/YY (e.g., 02/27): ");
        c_textcolor(8) ;
        scanf("%2s/%2s", A.expiry_date.month, A.expiry_date.year);
        // Parse and validate month and year
        if ((sscanf(A.expiry_date.month, "%2d", &month) == 1) && (sscanf(A.expiry_date.year, "%2d", &year) == 1)) {
            if (month > 0 && month <= 12  && year >= (current_year - 2000) ) {
                valid = 1;
            } 
        if (( year == current_year-2000 ) && (month <= current_mont))  valid = 0 ;
        if (valid == 0 ) {
            c_textcolor(4); 
            c_gotoxy(50 , 9 + count_error);printf("Invalid month or year!");
            count_error+=2;
            c_textcolor(7);
            }
        } else {
        c_gotoxy(50 , 9 + count_error );printf("Invalid format. Please enter MM/YY\n");
        count_error +=2 ;
        }
    } while (!valid);
 valid = 0;
 do {
    c_textcolor(14);
    count_error += 2 ;
    c_gotoxy(50 , 7 + count_error);printf("Enter your CVV code (e.g., 123): ");
    c_textcolor(8);
    c_gotoxy(83 , 7 + count_error);scanf("%s", A.CVV);

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
        c_gotoxy(50 , 9 + count_error );printf("Invalid CVV! Please enter a 3-digit number.");
        count_error += 2 ;
    }
 } while (!valid);
    c_textcolor(2);
    c_gotoxy(50 , 9 + count_error );printf("Valid CVV Code");
    c_textcolor(15);
    fwrite(&A, sizeof(CCD), 1, CDM);
    fclose(CDM);
    c_getch();
    c_clrscr();

}
void display_credit_cards(FILE  * CDM_1 ,char *name_client,char* CIN ){
    CCD CD ; // CD : CARD DETAIL 
    c_textcolor(14);
    c_gotoxy(30 , 3 );printf("------------------- Credit Card of : %s  , CIN : %s -------------------" , name_client , CIN ) ;
    while (fread(&CD , sizeof(CCD) ,1 , CDM_1) == 1 ) {
         if (strcmp(CIN , CD.client_CIN) == 0 ){
            c_textcolor(8);
            c_gotoxy(50 , 5 );printf("Card credit Number : ");
           for(int i = 0 ; i < strlen(CD.card_number) ; i++){
            if (i < 1 || (i == strlen(CD.card_number)-1 ) || (i > strlen(CD.card_number)-5 )){
            c_textcolor(14);
            c_gotoxy(71 +i, 5 );printf("%c" ,CD.card_number[i] );
            }
            else {
            c_textcolor(5);
            c_gotoxy(71 + i , 5);
            printf("*");
            }
             }
            printf("\n");
            c_textcolor(8);
            c_gotoxy(50 , 7 );printf("CIN :");
            c_textcolor(14);
            printf(" %s\n",CD.client_CIN);           
         }
    }
    c_getch();
    c_clrscr();
}

void Display_the_Supplier_sales_in_the_Day(FILE *supplier_amount) {
    // Get the current date
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;

    // Display a header with date
    c_textcolor(14);
    c_gotoxy(50, 2);
    printf("======== SUPPLIER SALES REPORT ========");
    c_gotoxy(50, 3);
    printf("DATE OF SALES : %02d-%02d-%d", day, month, year);
    c_gotoxy(50, 4);
    printf("=======================================");

    // Reset file to the beginning and set y-position
    rewind(supplier_amount);
    int y_position = 6;
    char car;

    // Display each character from supplier_amount file with alignment
    c_textcolor(15);
    while ((car = fgetc(supplier_amount)) != EOF) {
        putchar(car);
    }

    c_textcolor(15); // Reset color after displaying
}

void Display_the_Supplier_Total_amount_sales_in_the_Day(FILE *PCM, FILE *client_choice, char *CINF, int supplier_num) {
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;
    c_textcolor(14);
    c_gotoxy(50, 2);
    printf("======== SUPPLIER TOTAL SALES REPORT ========");
    c_gotoxy(50, 3);
    printf("TODAY'S DATE: %02d-%02d-%d", day, month, year);
    c_gotoxy(50, 4);
    printf("SUPPLIER ID: %s", CINF);
    c_gotoxy(50, 5);
    printf("============================================");

    // Create the filename for supplier data
    char filename[50];
    sprintf(filename, "supplier%d.txt", supplier_num);
    FILE *supplier_amount = fopen(filename, "w+t");
    if (supplier_amount == NULL) {
        c_textcolor(4);
        printf("Error: Unable to create file %s!\n", filename);
        return;
    }
    int product_id, client_id;
    char product_category[30], product_name[30], client_category[30], client_name[30];
    float product_price = 0.0;
    int product_quantity = 0, client_quantity = 0;
    float total_amount = 0;
    float sale_mount = 0;

    fprintf(supplier_amount, "CIN: %s\n\n", CINF);
    c_textcolor(11);
    int y_position = 7;
    c_gotoxy(50, y_position++);
    printf("| %-15s | %-10s | %-12s |", "CATEGORY", "QUANTITY", "SALE AMOUNT");
    c_gotoxy(50, y_position++);
    printf("|-----------------|------------|--------------|");

    c_textcolor(8);
    while (fscanf(client_choice, "%d %s %s %d", &client_id, client_category, client_name, &client_quantity) == 4) {
        rewind(PCM);  
        while (fscanf(PCM, "%d %s %s %*s %f %d", &product_id, product_category, product_name, &product_price, &product_quantity) == 5) {
            if (product_id == client_id && strcmp(product_category, client_category) == 0 && strcmp(product_name, client_name) == 0) {
                total_amount = product_price * client_quantity;
                sale_mount += total_amount;
                c_gotoxy(50, y_position++);
                printf("| %-15s | %-10d | %-12.2f DH |", client_category, client_quantity, total_amount);
                fprintf(supplier_amount, "Category: %s\nQuantity: %d\nSale Amount: %.2f\n\n", client_category, client_quantity, total_amount);
                total_amount = 0;
                break;
            }
        }
    }
    c_textcolor(14);
    c_gotoxy(50, y_position + 1);
    printf("============================================");
    c_gotoxy(50, y_position + 2);
    printf("TOTAL SALES AMOUNT: %.2f DH", sale_mount);
    c_gotoxy(50, y_position + 3);
    printf("============================================");
    fclose(supplier_amount);
    c_textcolor(15);
}

void feedback_and_rate_the_product(char *name_cl, int id_product) { // name_cl: client name, id_product: product id
    FILE *client_opinion = fopen("feedback.txt", "a");
    if (client_opinion == NULL) {
        c_textcolor(4); 
        printf("Error: feedback.txt does not exist!\n");
        return;
    }

    char comment[256];
    c_textcolor(14);
    printf("%s, enter your comment about Product %d: ", name_cl, id_product);
    c_textcolor(8);
    fflush(stdin);
    fgets(comment, sizeof(comment), stdin);
    size_t len = strlen(comment);
    if (len > 0 && comment[len - 1] == '\n') 
    comment[len - 1] = '\0'; // Remove the newline character
    // Write the comment to the file
    fprintf(client_opinion, "Client: %s | Product ID: %d | Comment: %s\n", name_cl, id_product, comment);
    puts(comment);

    int rating;
    c_textcolor(14);
    printf(" Rate the product (1 to 5 stars): ");
    c_textcolor(14);
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

    c_textcolor(8);
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
    printf("Thank you for your feedback!");
    c_textcolor(15);
    fclose(client_opinion);
}

int check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price) {
    product prod;
    rewind(PCM);
    while (fscanf(PCM, "%d %s %s %s %f %d", &prod.id_product, prod.category, prod.name, prod.description, &prod.price, &prod.quantity) == 6) {
        if (strcmp(prod.category, category) == 0 && strcmp(prod.name, name) == 0) {
            *price = prod.price; 
            if (quantity <= prod.quantity) {
                return 1; // In stock
            } else {
                return 0; // Out of stock
            }
        }
    }
    return -1; // Product not found
}

void client_factor(FILE *PCM, FILE *CDM, FILE *client_choice, char *CIN) {
    FILE *FACT = fopen("FACTEUR.txt", "w");
    if (FACT == NULL) {
        printf("Error: Unable to create FACTEUR.txt file!\n");
        exit(1);
    }
    
    CCD client_details;
    int found = 0;
    rewind(CDM);

    // Step 1: Search for client details in the credit card database (CDM)
    while (fread(&client_details, sizeof(CCD), 1, CDM) == 1) {
        if (strcmp(client_details.client_CIN, CIN) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        fprintf(FACT, "Error: Client with CIN %s not found in credit card database!\n", CIN);
        fclose(FACT);
        return;
    }

    // Step 2: Mask credit card number
    char hidden_card_number[50];
    snprintf(hidden_card_number, sizeof(hidden_card_number), "%.4s **** **** %.4s", 
             client_details.card_number, 
             client_details.card_number + strlen(client_details.card_number) - 4);

    // Step 3: Write Client Information and Date to FACTEUR
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    fprintf(FACT, "================== FACTURE ==================\n");
    fprintf(FACT, "Client Name: %s\n", client_details.client_name);
    fprintf(FACT, "Client CIN: %s\n", client_details.client_CIN);
    fprintf(FACT, "Card Number: %s\n", hidden_card_number);
    fprintf(FACT, "Date of Purchase: %02d-%02d-%d\n\n",  
            localTime->tm_mday, 
            localTime->tm_mon + 1, 
            localTime->tm_year + 1900);
    fprintf(FACT, "---------------------------------------------\n");
    fprintf(FACT, "| %-15s | %-10s | %-10s |\n", "Product", "Quantity", "Total Price");
    fprintf(FACT, "---------------------------------------------\n");

    // Step 4: Process Client's Choices and Calculate Total Cost
    clc client_choice_entry;
    float grand_total = 0.0;
    rewind(client_choice);
    while (fscanf(client_choice, "%d %s %s %f %d", 
                  &client_choice_entry.id_product_clien,
                  client_choice_entry.category, 
                  client_choice_entry.name, 
                  &client_choice_entry.price, 
                  &client_choice_entry.quantity) == 5) {
        
        float product_price;
        int stock_status = check_stock_and_get_price(PCM, client_choice_entry.category, client_choice_entry.name, client_choice_entry.quantity, &product_price);

        switch (stock_status) {
            case 1: // In stock
                grand_total += client_choice_entry.price * client_choice_entry.quantity;
                fprintf(FACT, "| %-15s | %-10d | %-10.2f DH |\n", client_choice_entry.name, client_choice_entry.quantity, client_choice_entry.price * client_choice_entry.quantity);
                break;
            case 0: // Out of stock
                fprintf(FACT, "| %-15s | %-10d | %-10s |\n", client_choice_entry.name, client_choice_entry.quantity, "Out of Stock");
                break;
            case -1: // Product not found
                fprintf(FACT, "| %-15s | %-10d | %-10s |\n", client_choice_entry.name, client_choice_entry.quantity, "Not Found");
                break;
        }
    }

    // Step 5: Print Grand Total and Close FACTEUR File
    fprintf(FACT, "---------------------------------------------\n");
    fprintf(FACT, "Grand Total: %.2f DH\n", grand_total);
    fprintf(FACT, "=============================================\n");
    fclose(FACT);
    convert_txt_to_pdf("FACTEUR.txt" ,"FACTEUR_1.pdf");
}

void convert_txt_to_pdf(const char *txt_file, const char *pdf_file) {
    // Create a new PDF document
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf) {
        printf("Error creating PDF document.\n");
        return;
    }

    // Create a new page
    HPDF_Page page = HPDF_AddPage(pdf);
    if (!page) {
        printf("Error creating PDF page.\n");
        HPDF_Free(pdf);
        return;
    }

    // Set the page size to A4
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // Set font and size
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(page, font, 12);

    // Open the .txt file
    FILE *file = fopen(txt_file, "r");
    if (!file) {
        printf("Error opening text file.\n");
        HPDF_Free(pdf);
        return;
    }

    // Read the text file and write it to the PDF page
    char buffer[1024];
    float y_position = 800; // starting position for text (top of the page)
    while (fgets(buffer, sizeof(buffer), file)) {
        if (y_position < 50) {
            // If we reach the bottom of the page, add a new page
            page = HPDF_AddPage(pdf);
            HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
            HPDF_Page_SetFontAndSize(page, font, 12);
            y_position = 800; // reset y position for new page
        }

        // Write the text to the page
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 50, y_position, buffer);
        HPDF_Page_EndText(page);

        // Move down for next line
        y_position -= 15; // line height
    }

    // Close the text file
    fclose(file);

    // Save the PDF document to the specified file
    if (HPDF_SaveToFile(pdf, pdf_file) != HPDF_OK) {
        printf("Error saving PDF file.\n");
    }

    // Free the PDF document
    HPDF_Free(pdf);

    printf("Conversion successful! PDF saved as %s\n", pdf_file);
}
