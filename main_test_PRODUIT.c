#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "header_PRODUIT.h"
int main (){
  c_textcolor(4);
  printf("\nHello chickens\n");
  c_textcolor(15);
  add_credit_card("AM123" ,"mohamed");
  FILE * CDM = fopen("CREDIT_CARD.dat", "rb");
    if (CDM == NULL) {
        printf("File does not exist!\n");
        exit(0); 
    }
  display_credit_cards_balance(CDM ,"AM123" );
  fclose(CDM);
  c_getch();
    return 0 ;
}