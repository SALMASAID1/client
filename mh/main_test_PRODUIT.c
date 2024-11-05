#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "header_PRODUIT.h"
      

      helllo 
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
    display_credit_cards(CDM, "AM123");
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

    // Display total amount of client sales
    Display_the_total_amount_of_client_sales(PCM, C, "AM123", 1); // Ensure the correct CIN is passed

    // Close files
    fclose(C);
    fclose(PCM);

    c_getch(); // Wait for user input before closing
    return 0;
}
