#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "conio.h"
#include "FUNCTION.h"

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
    int id_product ;
    char name[20];                // Nom du produit
    float price;                 // Prix du produit
    int quantity;               // Quantite en stock
    char category[50];         // Categorie du produit
    char description[100];    // description
}product;

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


void back() {
    c_textattr(1); 
    printf("\nReturning to the previous menu...\n");
    c_getch();      
    c_clrscr();    
    c_textattr(14);
}

void chooseLanguage() {
    int choice;
    int consoleWidth = 80; // Assuming an 80-character wide console
    int yPosition = 5;     // Set a vertical starting position

    // Centered positions based on string lengths
    int englishPosition = (consoleWidth - 13) / 2; // "1. English" is 9 characters
    int frenchPosition = (consoleWidth - 12) / 2;  // "2. French" is 8 characters
    int promptPosition = (consoleWidth - 30) / 2;  // "Choose a language" prompt length

    c_gotoxy(promptPosition, yPosition);
    printf("Choose a language:\n");
    
    c_gotoxy(englishPosition, yPosition + 2);
    printf("1. English\n");

    c_gotoxy(frenchPosition, yPosition + 3);
    printf("2. French\n");

    c_gotoxy(promptPosition, yPosition + 5);
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("You selected English.\n");
            break;
        case 2:
            printf("Vous avez choisi le Français.\n");
            break;
        default:
            printf("Invalid choice. Please select 1 or 2.\n");
            break;
    }
}
void leave(){
    c_textattr(1);
    printf("Exiting the Aplication...\n\t**GOOD BYE**\t");   
    c_getch();
   exit(0) ;
   c_textattr(14);
}

void liste(char * Temp_cin) {
    int c;
         c_gotoxy(50,6);printf("---------------------------");
          c_gotoxy(50,7);printf("----- LIST OF OPTIONS -----");
           c_gotoxy(50,8);printf("---------------------------");
           c_textattr(8);

           c_gotoxy(50,9);printf("---> View Product List");
           c_gotoxy(50,10);printf("---> Add Purchases");
           c_gotoxy(50,11);printf("---> View Purchases ");
           c_gotoxy(50,12);printf("---> Remove Purchases");
           c_gotoxy(50,13);printf("---> Leave Page");
           c_textattr(14);
           c_gotoxy(50,14);printf("--------------------------");


    do {


               c_textattr(8);
               printf("  \n1 - View Product List");
               printf("  \n2 - Add Purchases");
               printf("  \n3 - View Purchases ");
               printf("  \n4 - Remove Purchases");
               printf("  \n5 - Leave Page");
               c_textattr(14);

         printf("\n\n------->> SELECT YOUR OPTION: ");scanf("%d", &c);

         c_clrscr();
        switch (c) {
            case 1: {
                View_Product_List();

                break;

            }
            case 2: {
            Add_Purchases();
                break;
            }
            case 3: {
            View_Purchases();
           break;
            }
            case 4: {
                Remove_Purchases();
                break;
            }

            case 5: {
                leave();
                break;
            }
            default:
             c_textattr(4);
                printf("Incorrect choice! Your choice should be between [1 - 8]. Please retry.");
         c_textattr(14);
        }

    } while (c != 0); // Loop until the user decides to exit
}


char pdf_header[] = 
    "%%PDF-1.4                  %% PDF header specifying version\n"
    "1 0 obj                    %% Catalog object\n"
    "<< /Type /Catalog\n"
    "   /Pages 2 0 R\n"
    ">>\n"
    "endobj\n"
    "\n"
    "2 0 obj                    %% Pages object\n"
    "<< /Type /Pages\n"
    "   /Kids [3 0 R]\n"
    "   /Count 1\n"
    ">>\n"
    "endobj\n"
    "\n"
    "3 0 obj                    %% Single Page object\n"
    "<< /Type /Page\n"
    "   /Parent 2 0 R\n"
    "   /MediaBox [0 0 612 792]\n"
    "   /Contents 4 0 R\n"
    "   /Resources << /Font << /F1 5 0 R >> >>\n"
    ">>\n"
    "endobj\n"
    "\n"
    "4 0 obj                    %% Content stream for the page\n"
    "<< /Length 330 >>          %% Length of text data\n"
    "stream\n"
    "BT                         %% Begin text block\n"
    "/F1 12 Tf                  %% Set font to F1 at 12 points\n"
    "72 750 Td                  %% Position text at (72, 750)\n";


// -----------------------------

char pdf_footer[] = 
    "ET                         %% End text block\n"
    "endstream\n"
    "endobj\n"
    "\n"
    "5 0 obj                    %% Font object\n"
    "<< /Type /Font\n"
    "   /Subtype /Type1\n"
    "   /BaseFont /Helvetica\n"
    ">>\n"
    "endobj\n"
    "\n"
    "xref                       %% Cross-reference table\n"
    "0 6\n"
    "0000000000 65535 f\n"
    "0000000010 00000 n\n"
    "0000000079 00000 n\n"
    "0000000178 00000 n\n"
    "0000000307 00000 n\n"
    "0000000403 00000 n\n"
    "\n"
    "trailer\n"
    "<< /Root 1 0 R\n"
    "   /Size 6\n"
    ">>\n"
    "startxref\n"
    "482                        %% Offset to start of xref\n"
    "%%%%EOF\n";



// -----------------------------

int is_CIN_unique(const char *cin) {
    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) return 1;

    char file_cin[20];
    while (fscanf(fp, "%*s %*s %s %*s", file_cin) == 1) {
        if (strcmp(file_cin, cin) == 0) {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void sign_in_client() {
    int i,j;
    Client client;
    FILE *fp = fopen("CLIENT.txt", "a");
    if (fp == NULL) {
        printf("The file does not exist or could not be opened!\n");
        return;
    }
      c_textattr(8);

    printf("Enter your LAST NAME: ");
    scanf("%s", client.last_name);
    printf("Enter your FIRST NAME: ");
    scanf("%s", client.First_name);

    do {
        printf("Enter your CIN: ");
        scanf("%s", client.CIN);

        if (!is_CIN_unique(client.CIN)) {

              c_textcolor(4);  printf("Error: CIN already exists. Please enter a unique CIN.\n");
      c_textattr(14);

        }
    } while (!is_CIN_unique(client.CIN));

    do {

    printf("Enter NEW PASSWORD: ");
    for (i = 0; i < 19; i++) {
        client.password[i] = c_getch();  // Read character without displaying it

        if (client.password[i] == '\r') {  // Stop if Enter is pressed
            break;
        }

        printf("*");
    }

    client.password[i] = '\0';


        printf("\nConfirm your PASSWORD: ");
           for (j = 0; j < 19; j++) {
        client.confirm_password[j] = c_getch();

        if (client.confirm_password[j] == '\r') {
            break;
        }

        printf("*");
    }

    client.confirm_password[j] = '\0';

        if (strcmp(client.password, client.confirm_password) != 0) {
                 c_textattr(4);

                printf("\nError: Passwords do not match. Please try again.\n");
                 c_textattr(14);

        }
    } while (strcmp(client.password, client.confirm_password) != 0);

    fprintf(fp, "%s %s %s %s\n", client.last_name, client.First_name, client.CIN, client.password);
     c_textattr(2);

                 printf("\nInformation added successfully!\n");
 c_textattr(14);

 c_clrscr();
    fclose(fp);

}

void displayMenu() {
    c_gotoxy(40, 5);  // Centered coordinates (adjust as needed)
    printf("Welcome to the Login Page\n");
    c_gotoxy(40, 7);
    printf("1. Supplier \n");
    c_gotoxy(40, 8);
    printf("2. Client\n");
    c_gotoxy(40, 9);
    printf("3. Leave\n");
}

void clientLogin (char * CIN){
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
    c_textattr(8);
    printf("Let's connect to your account:\n");
    c_textattr(14);
    printf("Enter your CIN: ");
    scanf("%s", CINN);

    printf("Enter your PASSWORD: ");
        for (k = 0; k < 19; k++) {
        passw[k] = c_getch();

        if (passw[k] == '\r') {
            break;
        }

        printf("*");
    }
    passw[k] = '\0';

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        printf("\nError: Could not open the file.\n");
     c_textattr(14);
        return;
    }
    Client client;
    while (fscanf(fp, "%*s %*s %s %s", client.CIN, client.password) == 2) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {
            c_textattr(2);
            strcpy(Temp_CIN , CINN);
            printf("\nConnected successfully!\n");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();
            liste(Temp_CIN);
            break;
        }
    }
    if (!found) {
        c_textattr(4);
        printf("\nYou need to create an account first!\n");
        c_textattr(14);
    }
    fclose(fp);
    c_getch();
}

void View_Product_List() {

    product p;

    FILE *fk = fopen("produit.txt", "rt");
    if (fk == NULL) {
             c_textattr(4);
        printf("The file does not exist or could not be opened!\n");

        return;
    }
     c_textattr(8);
    printf("\n====== THE PRODUCTS LIST ======\n\n");
    printf("%-20s %-20s %-15s %-15s %-10s %-10s\n", "ID_PRODUCT", "CATEGORY", "NAME", "DESCRIPTION", "PRICE", "QUANTITY");
    printf("-----------------------------------------------------------------------------------------------------\n");
     c_textattr(14);
    while (fscanf(fk, "%d %19s %19s %19s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
        printf("%-20d %-20s %-15s %-15s %-10.2f %-10d\n", p.id_product, p.category, p.name, p.description, p.price, p.quantity);
    }

    fclose(fk);
    printf("\n\n\n\n\n");
     c_textattr(8);


}

void Add_Purchases() {
    product l, p;
    Client client;
    char filename[100];

    printf("Enter your CIN: ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n');

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *fk = fopen("produit.txt", "rt");
    if (fk == NULL) {
             c_textattr(4);
        printf("Error opening the product file!\n");
     c_textattr(8);
        return;
    }

    int found = 0;
    printf("\nEnter PRODUCT ID: ");
    while (scanf("%d", &l.id_product) != 1) {
             c_textattr(4);
        printf("Please enter a valid product ID (integer): ");
     c_textattr(8);
        while (getchar() != '\n');
    }

    // Search for product in the inventory
    while (fscanf(fk, "%d %49s %49s %99s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
        if (p.id_product == l.id_product) {
            found = 1;
            break;
        }
    }

    fclose(fk);

    if (!found) {
             c_textattr(4);
        printf("Product ID %d not found in inventory!\n", l.id_product);
     c_textattr(8);
        return;
    }

    printf("\nEnter quantity (1 - %d): ", p.quantity);
    while (scanf("%d", &l.quantity) != 1 || l.quantity < 1 || l.quantity > p.quantity) {
             c_textattr(4);
        printf("Invalid quantity. Enter a value between 1 and %d: ", p.quantity);
     c_textattr(8);
        while (getchar() != '\n');
    }

    // Read the existing cart and check for the product
    FILE *ff = fopen(filename, "r+");
    if (ff == NULL) {
        ff = fopen(filename, "w");  // Create if not exists
        if (ff == NULL) {
                 c_textattr(4);
            printf("Error opening the cart file!\n");
         c_textattr(8);
            return;
        }
    }

    product cart[100];
    int cartSize = 0;
    int exists = 0;

    // Load existing cart items
    while (fscanf(ff, "%d %d", &cart[cartSize].id_product, &cart[cartSize].quantity) == 2) {
        if (cart[cartSize].id_product == l.id_product) {
            int totalQuantity = cart[cartSize].quantity + l.quantity;
            if (totalQuantity > p.quantity) {
                     c_textattr(4);
            printf("Cannot add to cart. The total quantity (%d) exceeds stock available (%d).\n", totalQuantity, p.quantity);
             c_textattr(8);
                fclose(ff);
                return;
            }
            cart[cartSize].quantity = totalQuantity;  // Sum quantities if product already in cart
            exists = 1;
        }
        cartSize++;
    }

    // If product is new to the cart
    if (!exists) {
        cart[cartSize] = l;
        cartSize++;
    }

    // Rewrite cart with updated quantities
    freopen(filename, "w", ff);
    for (int i = 0; i < cartSize; i++) {
        fprintf(ff, "%d %d\n", cart[i].id_product, cart[i].quantity);
    }
     c_textattr(2);
    printf("Product successfully added to cart.\n");
     c_textattr(14);


    fclose(ff);
    c_clrscr();
}
void View_Purchases() {
    Client client;
    char filename[100];
    float total_price = 0.0;

    printf("Enter your CIN: ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n');

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
             c_textattr(4);
        printf("You have no purchases in your cart or the cart file doesn't exist.\n");
     c_textattr(14);
        return;
    }

    printf("\n===== YOUR PURCHASES =====\n");
      c_textattr(8);
    printf("%-20s %-15s %-15s %-10s %-10s %-10s\n", "Product ID", "Name", "Category", "Price", "Quantity", "Total Price");
    printf("---------------------------------------------------------------------------------------------------------\n");
    int found = 0;
    int id_product, quantity;
    while (fscanf(ff, "%d %d", &id_product, &quantity) == 2) {

        FILE *fk = fopen("produit.txt", "rt");
        if (fk == NULL) {
                 c_textattr(4);
            printf("Error opening the product list file!\n");
         c_textattr(14);
            fclose(ff);
            return;
        }

        product p;
        while (fscanf(fk, "%d %49s %49s %99s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
            if (p.id_product == id_product) {
                      c_textattr(14);
                float item_total_price = p.price * quantity;
                printf("%-20d %-15s %-15s %-10.2f %-10d %-10.2f\n", p.id_product, p.name, p.category, p.price, quantity, item_total_price);
                total_price += item_total_price;
                found = 1;
                break;
            }
        }
        fclose(fk);
    }

    if (!found) {
             c_textattr(4);
        printf("Your cart is empty.\n");
     c_textattr(14);
    } else {

        printf("\n---------------------------------------------------------------------------------------------------------\n");
        printf("%-20s %-15s %-15s %-10s %-10s %-10.2f\n", "Total", "", "", "", "", total_price);
    }

    fclose(ff);

}

void Remove_Purchases() {
    Client client;
    char filename[100];
    int id_product, quantity, found = 0;

    printf("Enter your CIN: ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n'); // Clear input buffer

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN); // Construct filename based on CIN

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
            c_textattr(4);
        printf("Your cart is empty or the cart file doesn't exist.\n");
    c_textattr(14);
        return;
    }

    // Create a temporary file to store the updated cart
    FILE *tempFile = fopen("temp_cart.txt", "w");
    if (tempFile == NULL) {
            c_textattr(4);
        printf("Error opening temporary file.\n");
    c_textattr(14);
        fclose(ff);
        return;
    }

    product p;
    int id_product_in_cart, quantity_in_cart;

    // Display the current items in the cart
    printf("\n===== YOUR CURRENT PURCHASES =====\n");
    printf("%-20s %-15s %-10s %-10s\n", "Product ID", "Name", "Price", "Quantity");
    printf("--------------------------------------------------------------\n");
    c_textattr(8);

    // Read the items from the cart and print them
    while (fscanf(ff, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        FILE *fk = fopen("produit.txt", "rt");
        if (fk == NULL) {
                c_textattr(4);
            printf("Error opening product list file!\n");
        c_textattr(8);
            fclose(ff);
            fclose(tempFile);
            return;
        }

        while (fscanf(fk, "%d %49s %49s %99s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
            if (p.id_product == id_product_in_cart) {
                printf("%-20d %-15s %-10.2f %-10d\n", p.id_product, p.name, p.price, quantity_in_cart);
                found = 1;
                break;
            }
        }
        fclose(fk);
    }

    if (!found) {
            c_textattr(4);
        printf("No products found in your cart.\n");
    c_textattr(14);
        fclose(ff);
        fclose(tempFile);
        return;
    }

    // Ask the user for the product ID and quantity to remove
    printf("\nEnter the Product ID to REMOVE: ");
    scanf("%d", &id_product);

    printf("Enter the quantity to REMOVE: ");
    while (scanf("%d", &quantity) != 1 || quantity < 1) {
            c_textattr(4);
        printf("Invalid quantity. Please enter a positive integer: ");
    c_textattr(14);
        while (getchar() != '\n'); // Clear invalid input
    }

    // Rewind the cart file and copy all items to the temporary file except the one to be removed
    rewind(ff);
    found = 0;

    while (fscanf(ff, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        if (id_product_in_cart == id_product) {
            found = 1;
            if (quantity_in_cart >= quantity) {
                if (quantity_in_cart > quantity) {
                    fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart - quantity);
                    printf("Removed %d items from cart. %d items remain.\n", quantity, quantity_in_cart - quantity);
                } else {
                    printf("Removed all %d items from cart.\n", quantity_in_cart);
                }
            } else {
                c_textattr(4);
                printf("Error: Only %d items are available in the cart. No items removed.\n", quantity_in_cart);c_textattr(14);
                fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart); // Write original data to tempFile
            }
        } else {
            fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart);
        }
    }

    if (!found) {
            c_textattr(4);
        printf("Product ID %d not found in your cart.\n", id_product);
    c_textattr(14);
    }

    // Close the original and temporary files
    fclose(ff);
    fclose(tempFile);

    // Replace the original cart file with the updated cart
    remove(filename); // Delete the original cart file
    rename("temp_cart.txt", filename); // Rename the temporary file to the original cart filename
    c_textattr(2);

    printf("\nCart updated successfully.\n");
    c_textattr(14);
}

//*******************__________________*********************/

void tap(){
	getchar();
    getchar();
    system("cls");
}

void choixinvalid(){
    system("cls");
    c_textcolor(4);
    printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tchoix invalide .");
    tap();
    c_textcolor(15);
}
//----------------------------------------add product--------------------------------------
int get_next_product_id(FILE *fp) {
    product p;
    int id = 1;

    // Aller à la fin du fichier
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) != 0) {  // Si le fichier n'est pas vide
        rewind(fp);
        while (fscanf(fp, " %d %s %s %f %d %s", &p.id_product, p.name, p.category, &p.price, &p.quantity, p.description) == 6) {
            id = p.id_product + 1;  // Trouver le dernier ID et l'incrémenter
        }
    }
    return id;
}

// Fonction pour ajouter un produit

void add_product() {
    FILE *fp = fopen("produit.txt", "a+");
    if (fp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    product p;
    p.id_product = get_next_product_id(fp); // Définir un ID de produit unique

    // Lecture des informations sur le produit
    // set_color(1);
    c_textcolor(14);
    c_gotoxy(30 , 3 );
    printf("Enter product name: ");
     c_textcolor(8);
    scanf(" %[^\n]s",p.name);
    c_gotoxy(30 , 4 );
     c_textcolor(14);
    printf("Enter product category: ");
     c_textcolor(8);
    scanf(" %[^\n]s",p.category);
    c_gotoxy(30 , 5 );
     c_textcolor(14);
    printf("Enter product price: ");
     c_textcolor(8);
    scanf("%f", &p.price);
    c_gotoxy(30 , 6 );
     c_textcolor(14);
    printf("Enter product quantity: ");
     c_textcolor(8);
    scanf("%d", &p.quantity);
    c_gotoxy(30 , 7 );
     c_textcolor(14);
    printf("Enter product description: ");
     c_textcolor(8);
    scanf(" %[^\n]s",p.description);
    c_textcolor(15);
    //set_color(7);

    // Enregistrement du produit dans le fichier
    fprintf(fp, " %d %s %s %s %.2f %d\n", p.id_product,p.category ,p.name , p.description,p.price , p.quantity);
    fclose(fp);

    c_textcolor(2);
    printf("Product added successfully\n");
    c_textcolor(15);
    c_getch();
    c_clrscr();
}

//----------------------------------------delete product--------------------------------------
void delete_product(){
    FILE *fp,*temp;
    fp=fopen("produit.txt","r");
    temp=fopen("temp.txt","w");
    int id;
    int tr=0;
    if(fp==NULL && temp==NULL){
        printf("unable to open file");
        exit(1);
    }
    c_clrscr();
    c_textcolor(1);
    c_gotoxy(30,3);
    printf("enter the product id to delete:");
    scanf("%d",&id);
    c_textcolor(15);
    product p;
    while(fscanf(fp,"%d %s %s %f %d %[^\n]s",&p.id_product,p.name,p.category,&p.price,&p.quantity,p.description)==6){
    
        if(p.id_product==id){
            tr=1; 
        }
        else{
            fprintf(temp,"%d %s %s %.2f %d %s\n",p.id_product,p.name,p.category,p.price,p.quantity,p.description);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt","produit.txt");
  
    c_gotoxy(30,5);
    if(tr==0){
          c_textcolor(4);
        printf("\nbe careful the product does not exist !!"); 
    c_textcolor(15);
    }
    else{
        c_gotoxy(30,5);
      c_textcolor(2);
      printf("\nthe product is successfully deleted!!\n");
      c_textcolor(15);
      }
      }
//----------------------------------------modify product--------------------------------------
  
void modify_product(){
        FILE*fp,*temp;
        fp=fopen("produit.txt","r");
        temp=fopen("temp.txt","w");
        int id;
        int tr=0,r=1;
        int c;
        if(fp==NULL && temp==NULL){
           printf("unable to open file");
           exit(1);
         }
         c_clrscr();
          c_textcolor(1);
          c_gotoxy(30,3);
        printf("enter the product id to modify:");
        scanf("%d",&id);
        c_textcolor(15);
        product p;
        product pn;
    while(fscanf(fp,"%d %s %s %f %d %[^\n]s",&p.id_product,p.name,p.category,&p.price,&p.quantity,p.description)==6){
        if(p.id_product==id){
              c_clrscr();
             printf("\n\n\n\n\n\n");
             c_textcolor(1);
             printf("\t\t\t\t\t\t\t==========================\n");
             c_textcolor(5);
             printf("\t\t\t\t\t\t\t | 1. modify name               |\n");
             printf("\t\t\t\t\t\t\t | 2. modify category           |\n");
             printf("\t\t\t\t\t\t\t | 3. modify price              |\n");
             printf("\t\t\t\t\t\t\t | 4. modify quantity           |\n");
             printf("\t\t\t\t\t\t\t | 5. modify description        |\n");
               c_textcolor(1);
             printf("\t\t\t\t\t\t\t=========================\n");
             c_textcolor(14);
            printf("\n\t\t\t\t\t\t\t Saisissez votre choix : ");
            scanf("%d",&c);
            c_textcolor(15);
            //-------------------------------------------clear screen------------
            c_clrscr();
          c_textcolor(1);
          c_gotoxy(30,18);
    
            switch(c){
                case 1:
                  c_gotoxy(30,18);
                  printf(" enter the new name:");scanf(" %[^\n]s",pn.name);
                  strcpy(p.name,pn.name);

                break;
                case 2:
                c_gotoxy(30,18);
                  printf(" enter the new category:");scanf(" %[^\n]s",pn.category);
                  strcpy(p.category,pn.category);
                 break;
                case 3:
                c_gotoxy(30,18);
                   printf("       enter the new price :");scanf("%f",&pn.price);
                   p.price=pn.price;
                 break;
                case 4:
                
                  c_gotoxy(30,10);
                  printf("    enter the new quantity : ");
                  scanf("%d",&pn.quantity);
                  p.quantity=pn.quantity;
                 break;
                case 5:
                c_gotoxy(30,10);
                  printf(" enter the new description :");scanf(" %[^\n]s",pn.description);
                  strcpy(p.description,pn.description);
                 break;
                 default:
                 c_gotoxy(30,18);
                 choixinvalid();
                  r=0; // r pour condition 
                 break;
               
            }
            c_textcolor(15);
              tr=1;
            }
         fprintf(temp,"%d %s %s %.2f %d %s\n",p.id_product,p.name,p.category,p.price,p.quantity,p.description);
       
        
           
        
    }
    fclose(fp);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt","produit.txt");
    //c_clrscr();
    
    if(tr==0 || r==0){
        c_textcolor(4);
        c_gotoxy(30,20);  
        printf("\n\n\n\t\t\t\t\tbe careful the product does not exist !!"); 
    c_textcolor(15);
    }
    else{
        
      c_textcolor(2);
       c_gotoxy(30,20); 
      printf("\n\n\n\t\t\t\t\tthe product is successfully modified !!\n");
      c_textcolor(15);
      }
     
     }
//-------------------------------------------sign fournisseur-------------------------------

void sign_in_supplier() {
    int i,j;
    fournisseur f;
    FILE *fp = fopen("FOURNISSEUR.txt", "a");
    if (fp == NULL) {
        printf("The file does not exist or could not be opened!\n");
        return;
    }
      c_textattr(8);

    printf("Enter your LAST NAME: ");
    scanf("%s", f.nomf   );
    printf("Enter your FIRST NAME: ");
    scanf("%s", f.prenomf);

    do {
        printf("Enter your CIN: ");
        scanf("%s", f.Cinf);

        if (!is_CIN_unique(f.Cinf)) {

              c_textcolor(4);  printf("Error: CIN already exists. Please enter a unique CIN.\n");
      c_textattr(14);

        }
    } while (!is_CIN_unique(f.Cinf));

    do {

    printf("Enter NEW PASSWORD: ");
    for (i = 0; i < 19; i++) {
        f.mdpf[i] = c_getch();  // Read character without displaying it

        if (f.mdpf[i] == '\r') {  // Stop if Enter is pressed
            break;
        }

        printf("*");
    }

    f.mdpf[i] = '\0';


        printf("\nConfirm your PASSWORD: ");
           for (j = 0; j < 19; j++) {
        f.cmdpf[j] = c_getch();

        if (f.cmdpf[j] == '\r') {
            break;
        }

        printf("*");
    }

    f.cmdpf[j] = '\0';

        if (strcmp(f.mdpf, f.cmdpf) != 0) {
                 c_textattr(4);

                printf("\nError: Passwords do not match. Please try again.\n");
                 c_textattr(14);

        }
    } while (strcmp(f.mdpf, f.cmdpf) != 0);

    fprintf(fp, "%s %s %s %s\n", f.nomf, f.prenomf,f.Cinf, f.mdpf);
     c_textattr(2);

                 printf("\nInformation added successfully!\n");
 c_textattr(14);

 c_clrscr();
    fclose(fp);

}

void add_supplier() {
    FILE *fp;
    fp = fopen("fournisseur.txt", "a+");
    if (fp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    fournisseur frn;
   char ch;
   int i;
   c_textcolor(1);
    c_gotoxy(50,6);
    printf("first name : ");
    scanf(" %[^\n]s", frn.prenomf);
    c_gotoxy(50,8);
    printf("second name  : ");
    scanf(" %[^\n]s", frn.nomf);

    do {
         c_gotoxy(50,10);
        printf("    CIN  : ");
        scanf(" %s", frn.Cinf);
        // c_gotoxy(60,12);
        if (is_CIN_unique(frn.Cinf) == 0) {
            c_gotoxy(60,12);
            printf("Be careful, the CIN is already used!\n");
            c_getch();
            c_clrscr();
        } else {
            c_gotoxy(50,12);
            printf("Saisir le mot de passe : ");
            i = 0;
            // Saisie et masquage du mot de passe avec '*'
            while ((ch = c_getch()) != '\r' && i < 19) {  // Limite à 19 caractères
                frn.mdpf[i++] = ch;
                printf("*");
            }
            frn.mdpf[i] = '\0';  // Ajouter le caractère de fin de chaîne
            printf("\n");

            fprintf(fp, "%s %s %s %s\n", frn.prenomf, frn.nomf, frn.Cinf, frn.mdpf);
            break;           
        }
    } while (1);
    fclose(fp);
      c_textcolor(15);
         c_textcolor(2);
         c_gotoxy(60,15);
    printf("supplier adds successfully!!");
    c_textcolor(15);
 c_getch();
 c_clrscr();
}

//------------------------------------verification cin---------------------
int veri_cin(char *cin) {
    FILE *fr = fopen("fournisseur.txt", "r");
    if (fr == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }
    
    fournisseur four;
    while (fscanf(fr, "%s %s %s %s", four.prenomf, four.nomf, four.Cinf, four.mdpf) == 4) {
        if (strcmp(cin, four.Cinf) == 0) {  
            fclose(fr);
            return 0; // CIN déjà existant
        }
    }
    
    fclose(fr);
    return 1; // CIN n'existe pas
}

//-----------------------------------------------------------------------


void liste_fournisseur(char * Temp_CIN) {
    int choice;
    
    do {
        system("cls");  // Clear screen (replace with `clrscr();` if using custom conio.h)
        printf("Supplier CIN: %s\n", Temp_CIN);
        printf("\nSupplier Menu:\n");
        printf("1. Add Product\n");
        printf("2. Modify Product\n");
        printf("3. Add Supplier\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_product();
                break;
            case 2:
                modify_product();
                break;
            case 3:
                add_supplier();
                break;
            case 4:
                delete_product();
                break;
            case 5:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        if (choice != 5) {
            printf("Press any key to continue...\n");
            c_getch();  // Pause before clearing screen again
        }
        c_getch();
        c_clrscr();
    } while (choice != 5);
}


//------------------------------------add supplier-----------------------------


void login_supplier (char * CIN){
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
    c_textattr(8);
    printf("Let's connect to your account:\n");
    c_textattr(14);
    printf("Enter your CIN: ");
    scanf("%s", CINN);

    printf("Enter your PASSWORD: ");
        for (k = 0; k < 19; k++) {
        passw[k] = c_getch();

        if (passw[k] == '\r') {
            break;
        }

        printf("*");
    }
    passw[k] = '\0';

    FILE *fp = fopen("FOURNISSEUR.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        printf("\nError: Could not open the file.\n");
     c_textattr(14);
        return;
    }
    fournisseur f;
    while (fscanf(fp, "%*s %*s %s %s", f.Cinf, f.mdpf) == 2) {
        if (strcmp(f.Cinf, CINN) == 0 && strcmp(f.mdpf, passw) == 0) {
            c_textattr(2);
            strcpy(Temp_CIN , CINN);
            printf("\nConnected successfully!\n");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();
            liste_fournisseur(Temp_CIN);
            break;
        }
    }
    if (!found) {
        c_textattr(4);
        printf("\nYou need to create an account first!\n");
        c_textattr(14);
    }
    fclose(fp);
    c_getch();
}

//-----------------------------------------------------------------------

void client_factor(FILE *PCM, FILE *CDM, FILE *client_choice, char *CIN) {
    FILE *FACT = fopen("FACTEUR.pdf", "w");
    if (FACT == NULL) {
        printf("Error: Unable to create FACTEUR.pdf file!\n");
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
    snprintf(hidden_card_number, sizeof(hidden_card_number), "%.4s ** ** %.4s", 
             client_details.card_number, 
             client_details.card_number + strlen(client_details.card_number) - 4);

    // Step 3: Write Client Information and Date to FACTEUR
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    fprintf(FACT, pdf_header);
    fprintf(FACT, "(================== FACTURE ==================) Tj\n0 -20 Td  ");
    fprintf(FACT, "(Client Name: %s ) Tj\n0 -20 Td", client_details.client_name);
    fprintf(FACT, "(Client CIN: %s ) Tj\n0 -20 Td", client_details.client_CIN);
    fprintf(FACT, "(Card Number: %s ) Tj\n0 -20 Td", hidden_card_number);
    fprintf(FACT, "(Date of Purchase: %02d-%02d-%d) Tj\n0 -30 Td " ,  
            localTime->tm_mday, 
            localTime->tm_mon + 1, 
            localTime->tm_year + 1900);
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td");
    fprintf(FACT, "(| Product         | Quantity   | Total Price |) Tj\n0 -20 Td");
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td");

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
                fprintf(FACT, "(| %-15s | %-10d | %-10.2f DH |) Tj\n0 -20 Td\n", client_choice_entry.name, client_choice_entry.quantity, client_choice_entry.price * client_choice_entry.quantity);
                break;
            case 0: // Out of stock
                fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", client_choice_entry.name, client_choice_entry.quantity, "Out of Stock");
                break;
            case -1: // Product not found
                fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", client_choice_entry.name, client_choice_entry.quantity, "Not Found");
                break;
        }
    }

    // Step 5: Print Grand Total and Close FACTEUR File
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Grand Total: %.2f DH) Tj\n0 -20 Td\n", grand_total);
    fprintf(FACT, "(=============================================) Tj\n");
    fprintf(FACT,pdf_footer);
    fclose(FACT);
}

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
    c_getch();
    c_clrscr();
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
