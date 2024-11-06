#ifndef PRODUIT_FUNCTION_H_INCLUDED
#define PRODUIT_FUNCTION_H_INCLUDED

// FUNCTION USED FOR CREDIT_CARD //

void add_credit_card(char* CIN_client , char * name_client);
void  display_credit_cards(FILE  * CDM_1 ,char *name_client,char* CIN );
void Display_the_Supplier_Total_amount_sales_in_the_Day(FILE * PCM , FILE * client_choice , char * CIN , int fact_num  ); // PCM : Product Client Managment 
void Display_the_Supplier_sales_in_the_Day (FILE * supplier_amount );
#endif // FUNCTION_H_INCLUDED