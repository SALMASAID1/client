#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "header_PRODUIT.h"

int main() {
    // Set text color and print greeting
    c_textcolor(4);
    printf("\nHello chickens  hhhhh !!!\n");
    c_textcolor(15);

    // Add a credit card for the client
    add_credit_card("AM123", "mohamed");

    // Open credit card file
    FILE *CDM = fopen("CREDIT_CARD.dat", "rb");
    if (CDM == NULL) {
        printf("Error: CREDIT_CARD.dat does not exist!\n");
        return 1; // Return a non-zero value for error
    }

    // Display credit card details
    display_credit_cards(CDM, "mohamed","AM123");
    fclose(CDM);

    // Open PCM file
    FILE *PCM = fopen("PCM.dat", "rb");
    if (PCM == NULL) {
        printf("Error: PCM.dat does not exist!\n");
        return 1; // Return a non-zero value for error
    }

    // Open client choice file
    FILE *C = fopen("client_choice.dat", "rb");
    if (C == NULL) {
        printf("Error: client_choice.dat does not exist!\n");
        fclose(PCM); // Close PCM before exiting
        return 1; // Return a non-zero value for error
    }

    Display_the_Supplier_Total_amount_sales_in_the_Day(PCM, C, "AM123", 1); // Ensure the correct CIN is passed

    fclose(C);
    fclose(PCM);

    FILE *kk = fopen("supplier1.txt", "rb");
    if (kk == NULL) {
        printf("Error: supplier1.txt does not exist!\n");
        return 1; // Return a non-zero value for error
    }

    Display_the_Supplier_sales_in_the_Day(kk);
    fclose(kk);
    c_getch();
    c_clrscr();
    feedback_and_rate_the_product("mohamed" , 1 );
    c_getch();
    return 0;
}
