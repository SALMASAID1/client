#ifndef PRODUIT_FUNCTION_H_INCLUDED
#define PRODUIT_FUNCTION_H_INCLUDED

// FUNCTION USED FOR CREDIT_CARD //

void add_credit_card(char* CIN_client , char * name_client);
void  display_credit_cards(FILE  * CDM_1 , char* CIN);

/********************************************************/

// FUNCTION USED FOR PRODUCT_MANAGMENT //

void Display_the_total_amount_of_client_sales (FILE * PCM , FILE * client_choice , char * CIN , int fact_num  ); // PCM : Product Client Managment 
#endif // FUNCTION_H_INCLUDED