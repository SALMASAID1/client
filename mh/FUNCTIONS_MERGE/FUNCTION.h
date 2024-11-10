#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
                // login page 

    void Login();
    void  sign_in(void);
    void  leave(void);

               // SAID -------- SALMA //
    void View_Product_List(void);
    void liste(char * Temp_cin);
    void Add_Purchases(void);
    void View_Purchases(void);
    void Remove_Purchases(void);

                // TAMZIRT -------- MOHAMED //
    void add_credit_card(char* CIN_client , char * name_client);
    void display_credit_cards(FILE  * CDM_1 ,char *name_client,char* CIN );
    void Display_the_Supplier_Total_amount_sales_in_the_Day(FILE * PCM , FILE * client_choice , char * CIN , int fact_num  ); // PCM : Product Client Managment 
    void client_factor(FILE *PCM, FILE *CDM, FILE *client_choice, char *CIN);
    void feedback_and_rate_the_product(char * name_cl , int id_product);
    int check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price);

                // Alaoui -------- TAHA //
    void add_product();
    void delete_product();
    void modify_product();
    void add_supplier();
    int get_next_product_id(FILE *fp);
    void choixinvalid();


#endif // FONCTION_H_INCLUDED