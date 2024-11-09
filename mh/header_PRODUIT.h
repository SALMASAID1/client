#ifndef PRODUIT_FUNCTION_H_INCLUDED
#define PRODUIT_FUNCTION_H_INCLUDED

// FUNCTION USED FOR CREDIT_CARD //

void add_credit_card(char* CIN_client , char * name_client);
void  display_credit_cards(FILE  * CDM_1 ,char *name_client,char* CIN );
void Display_the_Supplier_Total_amount_sales_in_the_Day(FILE * PCM , FILE * client_choice , char * CIN , int fact_num  ); // PCM : Product Client Managment 
void Display_the_Supplier_sales_in_the_Day (FILE * supplier_amount );
void client_factor(FILE *PCM, FILE *CDM, FILE *client_choice, char *CIN);
void feedback_and_rate_the_product(char * name_cl , int id_product);
int check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price);
#endif // FUNCTION_H_INCLUDED