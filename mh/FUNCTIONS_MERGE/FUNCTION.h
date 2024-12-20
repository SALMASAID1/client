#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "conio.h"

        FILE * CDM;  // CRM : CREDIT CARD DETAIL MANAGEMENT
        char Temp_CIN [20];

        typedef struct {   // Date card credit information
        char year [3] ;
        char month[3] ;
        } date_card;

        typedef struct credit_card_details {     // Credit Card Information
        char client_CIN[20];
        char client_name[30];
        char card_number[50];
        char CVV [5];
        date_card expiry_date;
        } CCD ;    // CCD : CREDIT CARD DETAIL



        typedef struct {
        int id_product;          // Product ID
        char name[20];           // Product Name
        float price;             // Product Price
        int quantity;            // Quantity in stock
        char category[50];       // Product Category
        char description[100];   // Product Description
        char CINF[20];           // Supplier CIN
        } produit ;

        typedef struct {
        char nomf[30];
        char prenomf[30];
        char Cinf[30]; // CIN de fournisseur
        char mdpf[20];  // Mot de passe de fournisseur
        char cmdpf[20]; // confirm mot de pass  
        }fournisseur;

        typedef struct {
        char last_name[50];
        char First_name[50];
        char CIN[20];
        char password[20];
        char confirm_password[20];
        } Client;

        typedef struct {
        int id_product_clien ; 
        char category[50];
        float price;
        char name[20];
        int quantity ;

        }clc ; // clc : client choice 


        
        typedef struct {
        char **ops;
        int len;
        char *title;
        } Options;

        typedef struct {
                int sale_id;    
                char client_CIN[20];         // Client ID
                float total_price;          // Total price of the sale
                char sale_date[20];         // Date of the sale
        } sale;
        typedef struct {
                int sale_id;           // Client ID
                int quantity;          // Quantity sold
                int product_id;             // Product ID
        } sale_product;


        /*English Version*/
                // login page 
    char* Pass_hide(int max_length);
    int is_CIN_unique(const char *cin);
    int is_CIN_unique_supplier(const char *cin);
    void generate_histogram(const char *title, const char *data_file);      

    int date_to_days_unix(int year, int month, int day);
    void product_statis(int id_prod, int year, int month , int day);
    void clientLogin(char * CIN);
    void sign_in_client(void);
    void leave(void);
    void View_Product_List(void);
    void liste_client(char * Temp_cin , char * client_name);
    void Add_Purchases(char *CIN);
    void View_Purchases(char *CIN);
    void Remove_Purchases(char *CIN);
    void confirm_purchases(char *CIN);



    void add_credit_card(char* CIN_client , char * name_client);
    void display_credit_cards(char *name_client,char* CIN );
    void Display_the_Supplier_Total_amount_sales_in_the_Day( char * CIN  ); 
    void client_factor(char *CIN);
    void feedback_and_rate_the_product(char * name_cl , int id_product);
    int check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price);



    void login_supplier(char * CIN );
    void liste_fournisseur( char * Temp_CIN );
    void add_product(char *CINF);
    void delete_product(char *CINF);
    void modify_product(char *CINF);
    void add_supplier();
    void view_product_supplier(char * CINF);
    void delete_supplier();
    void show_supplier();
    int get_next_product_id(FILE *fp);


    /*French Version*/

// page de connexion
char* Pass_hide(int max_length);
int  is_CIN_unique(const char *cin);
void product_statis_f(int id_prod, int year, int month , int day);
void clientLogin_f(char * CIN);
void sign_in_client_f(void);
void leave_f(void);
void View_Product_List_f(void);
void liste_client_f(char * Temp_cin , char * client_name);
void Add_Purchases_f(char *CIN);
void View_Purchases_f(char *CIN);
void Remove_Purchases_f(char *CIN);
void confirm_purchases_f(char *CIN);


void add_credit_card_f(char* CIN_client , char * name_client);
void display_credit_cards_f(char *name_client,char* CIN );
void Display_the_Supplier_Total_amount_sales_in_the_Day_f(char * CIN); // PCM: Product Client Management 
void client_factor_f(char *CIN);
void feedback_and_rate_the_product_f(char * name_cl , int id_product);
int  check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price);
void login_supplier_f(char * CIN );
void liste_fournisseur_f( char * Temp_CIN );
void add_product_f(char *CINF);
void delete_product_f(char *CINF);
void modify_product_f(char *CINF);
void add_supplier_f();
void view_product_supplier_f(char * CINF);
void delete_supplier_f();
void show_supplier_f();
int  get_next_product_id(FILE *fp);




void c_print_centered(const char *text, int y, int x_offset);
void get_console_size(int *rows, int *cols);
void menu_admin();
void menu_admin_f();
void Home_OPTIONS();
void Home_LOGIN_menu();
void Home_LOGIN_menu_f();
void display_supplier_menu();
void display_supplier_menu_f();
void draw_frame(int width, int height, int start_x, int start_y);
void gradientSpinner(int duration);
void gradientSpinner_f(int duration);
void gradientSpinner_s(int duration);
void gradientSpinner_s_f(int duration);
void image(const char *filepath);
#endif // FONCTION_H_INCLUDED