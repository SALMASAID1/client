#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"
        /*English Version*/
                // login page 
    char* Pass_hide(int max_length);
    void displayMenu();
    int is_CIN_unique(const char *cin);
    int is_CIN_unique_supplier(const char *cin);
    void back();
               // SAID -------- SALMA //
    void clientLogin(char * CIN);
    void sign_in_client(void);
    void leave(void);
    void View_Product_List(void);
    void liste_client(char * Temp_cin , char * client_name);
    void Add_Purchases(void);
    void View_Purchases(void);
    void Remove_Purchases(void);

                // TAMZIRT -------- MOHAMED //
    void add_credit_card(char* CIN_client , char * name_client);
    void display_credit_cards(char *name_client,char* CIN );
//     FILE * PCM , FILE * client_choice ,
    void Display_the_Supplier_Total_amount_sales_in_the_Day( char * CIN , int fact_num  ); // PCM : Product Client Managment 
    void client_factor(FILE *PCM, FILE *CDM, FILE *client_choice, char *CIN);
    void feedback_and_rate_the_product(char * name_cl , int id_product);
    int check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price);

                // Alaoui -------- TAHA //
    void sign_in_supplier();
    void login_supplier(char * CIN );
    void liste_fournisseur( char * Temp_CIN );
    void add_product();
    void delete_product();
    void modify_product();
    void add_supplier();
    void delete_supplier();
    void show_supplier();
    int get_next_product_id(FILE *fp);
    void choixinvalid();


    /*French Version*/

// page de connexion
char* Pass_hide(int max_length);
void displayMenu_f();
int is_CIN_unique(const char *cin);
void back();

// SAID -------- SALMA //
void clientLogin_f(char * CIN);
void sign_in_client_f(void);
void leave_f(void);
void View_Product_List_f(void);
void liste_client_f(char * Temp_cin , char * client_name);
void Add_Purchases_f(void);
void View_Purchases_f(void);
void Remove_Purchases_f(void);

// TAMZIRT -------- MOHAMED //
void add_credit_card_f(char* CIN_client , char * name_client);
void display_credit_cards_f(char *name_client,char* CIN );
void Display_the_Supplier_Total_amount_sales_in_the_Day_f(char * CIN , int fact_num); // PCM: Product Client Management 
void client_factor_f(FILE *PCM, FILE *CDM, FILE *client_choice, char *CIN);
void feedback_and_rate_the_product_f(char * name_cl , int id_product);
int check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price);

// Alaoui -------- TAHA //
void sign_in_supplier_f();
void login_supplier_f(char * CIN );
void liste_fournisseur_f( char * Temp_CIN );
void add_product_f();
void delete_product_f();
void modify_product_f();
void add_supplier_f();
void delete_supplier_f();
void show_supplier_f();
int get_next_product_id(FILE *fp);
void choixinvalid();


void menu_admin();
void menu_admin_f();
void Home_OPTIONS();
void Home_LOGIN_menu();
void Home_LOGIN_menu_f();
#endif // FONCTION_H_INCLUDED