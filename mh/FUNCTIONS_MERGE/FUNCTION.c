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
// french version
void back_f() {
    c_textattr(1); 
    printf("\nRetour au menu precedent...\n");
    c_getch();      
    c_clrscr();    
    c_textattr(14);
}

void leave(){
    c_textattr(1);
    printf("Exiting the Aplication...\n\t**GOOD BYE**\t");   
    c_getch();
    c_textattr(14);
   exit(0) ;
   
}
// french version
void leave_f() {
    c_textattr(1);
    printf("Fermeture de l'application...\n\t**AU REVOIR**\t");   
    c_getch();
    c_textattr(14);
    exit(0);
    
}


void liste_client(char *Temp_cin, char *client_name) {
    FILE *FD;
    CCD cd;
    int c;
    int check_CRD = 0;
    int check_card_exists = 0;

    c_gotoxy(50, 5); printf("---------------------------");
    c_gotoxy(50, 6); printf("----- LIST OF OPTIONS -----");
    c_gotoxy(50, 7); printf("---------------------------");
    c_textattr(8);

    c_gotoxy(50, 9);  printf("---> View Product List");
    c_gotoxy(50, 10); printf("---> Add Purchases");
    c_gotoxy(50, 11); printf("---> View Purchases ");
    c_gotoxy(50, 12); printf("---> Remove Purchases");
    c_gotoxy(50, 13); printf("---> Add A Credit Card");
    c_gotoxy(50, 14); printf("---> Display Credit Card");
    c_gotoxy(50, 15); printf("---> Leave Page");
    c_textattr(14);
    c_gotoxy(50, 17); printf("--------------------------");

    do {
        c_textattr(8);
        printf("  \n1 - View Product List");
        printf("  \n2 - Add Purchases");
        printf("  \n3 - View Purchases ");
        printf("  \n4 - Remove Purchases");
        printf("  \n5 - Add A Credit Card");
        printf("  \n6 - Display Credit Card");
        printf("  \n7 - Leave Page");
        c_textattr(14);

        printf("\n\n------->> SELECT YOUR OPTION: ");
        scanf("%d", &c);
        c_clrscr();

        switch (c) {
            case 1:
                View_Product_List();
                break;

            case 2:
                Add_Purchases();
                break;

            case 3:
                View_Purchases();
                break;

            case 4:
                Remove_Purchases();
                break;

            case 5: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    printf("\nFILE IS NOT EXIST !!!");
                    exit(0);
                }

                check_CRD = 0;
                check_card_exists = 0;
                while (fread(&cd, sizeof(CCD), 1, FD) == 1) {
                    // Check if the card already exists for this client
                    if (strcmp(cd.client_CIN, Temp_cin) == 0) {
                        check_CRD = 1;
                        if (strcmp(cd.card_number, Temp_cin) == 0) {
                            check_card_exists = 1;
                            break;
                        }
                    }
                }
                fclose(FD);

                if (check_CRD) {
                    if (check_card_exists) {
                        c_textcolor(4);
                        printf("\nThe credit card already exists for this client!");
                    } else {
                        add_credit_card(Temp_cin, client_name);
                        c_textcolor(2);
                        printf("\nCredit card added successfully!");
                    }
                } else {
                    add_credit_card(Temp_cin, client_name);
                    c_textcolor(2);
                    printf("\nCredit card added successfully!");
                }
                break;
            }

            case 6: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    printf("\nFILE IS NOT EXIST !!!");
                    exit(0);
                }

                int found = 0;
                while (fread(&cd, sizeof(CCD), 1, FD) == 1) {
                    if (strcmp(cd.client_CIN, Temp_cin) == 0) {
                        display_credit_cards(client_name, Temp_cin);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    c_textcolor(4);
                    printf("\nNo credit card found for this client!");
                }
                fclose(FD);
                break;
            }

            case 7:
                leave();
                break;

            default:
                c_textattr(4);
                printf("Incorrect choice! Your choice should be between [1 - 7]. Please retry.");
                c_textattr(14);
                break;
        }
    } while (c != 7);
}
// french version
void liste_client_f(char *Temp_cin, char *client_name) {
    FILE *FD;
    CCD cd;
    int c;
    int check_CRD = 0;
    int check_card_exists = 0;

    c_gotoxy(50, 5); printf("---------------------------");
    c_gotoxy(50, 6); printf("----- LISTE DES OPTIONS -----");
    c_gotoxy(50, 7); printf("---------------------------");
    c_textattr(8);

    c_gotoxy(50, 9);  printf("---> Voir la liste des produits");
    c_gotoxy(50, 10); printf("---> Ajouter des achats");
    c_gotoxy(50, 11); printf("---> Voir les achats");
    c_gotoxy(50, 12); printf("---> Supprimer des achats");
    c_gotoxy(50, 13); printf("---> Ajouter une carte de credit");
    c_gotoxy(50, 14); printf("---> Afficher la carte de credit");
    c_gotoxy(50, 15); printf("---> Quitter la page");
    c_textattr(14);
    c_gotoxy(50, 17); printf("--------------------------");

    do {
        c_textattr(8);
        printf("  \n1 - Voir la liste des produits");
        printf("  \n2 - Ajouter des achats");
        printf("  \n3 - Voir les achats");
        printf("  \n4 - Supprimer des achats");
        printf("  \n5 - Ajouter une carte de credit");
        printf("  \n6 - Afficher la carte de credit");
        printf("  \n7 - Quitter la page");
        c_textattr(14);

        printf("\n\n------->> SeLECTIONNEZ VOTRE OPTION : ");
        scanf("%d", &c);
        c_clrscr();

        switch (c) {
            case 1:
                View_Product_List_f();
                break;

            case 2:
                Add_Purchases_f();
                break;

            case 3:
                View_Purchases_f();
                break;

            case 4:
                Remove_Purchases_f();
                break;

            case 5: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    printf("\nLE FICHIER N'EXISTE PAS !!!");
                    exit(0);
                }

                check_CRD = 0;
                check_card_exists = 0;
                while (fread(&cd, sizeof(CCD), 1, FD) == 1) {
                    // Verifiez si la carte existe deja pour ce client
                    if (strcmp(cd.client_CIN, Temp_cin) == 0) {
                        check_CRD = 1;
                        if (strcmp(cd.card_number, Temp_cin) == 0) {
                            check_card_exists = 1;
                            break;
                        }
                    }
                }
                fclose(FD);

                if (check_CRD) {
                    if (check_card_exists) {
                        c_textcolor(4);
                        printf("\nLa carte de credit existe deja pour ce client !");
                    } else {
                        add_credit_card_f(Temp_cin, client_name);
                        c_textcolor(2);
                        printf("\nCarte de credit ajoutee avec succès !");
                    }
                } else {
                    add_credit_card_f(Temp_cin, client_name);
                    c_textcolor(2);
                    printf("\nCarte de credit ajoutee avec succès !");
                }
                break;
            }

            case 6: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    printf("\nLE FICHIER N'EXISTE PAS !!!");
                    exit(0);
                }

                int found = 0;
                while (fread(&cd, sizeof(CCD), 1, FD) == 1) {
                    if (strcmp(cd.client_CIN, Temp_cin) == 0) {
                        display_credit_cards_f(client_name, Temp_cin);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    c_textcolor(4);
                    printf("\nAucune carte de credit trouvee pour ce client !");
                }
                fclose(FD);
                break;
            }

            case 7:
                leave_f();
                break;

            default:
                c_textattr(4);
                printf("Choix incorrect ! Votre choix doit être entre [1 - 7]. Veuillez reessayer.");
                c_textattr(14);
                break;
        }
    } while (c != 7);
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

int is_CIN_unique_supplier(const char *cin) {
    FILE *fp = fopen("FOURNISSEUR.txt", "r");
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
    strcpy(client.password,Pass_hide(20));
    client.password[strlen(client.password)] = '\0';
    
    printf("\nConfirm your PASSWORD: ");
    strcpy(client.confirm_password,Pass_hide(20));
    client.confirm_password[strlen(client.confirm_password)] = '\0';

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
// french version
void sign_in_client_f() {
    int i, j;
    Client client;
    FILE *fp = fopen("CLIENT.txt", "a");
    if (fp == NULL) {
        printf("Le fichier n'existe pas ou n'a pas pu être ouvert !\n");
        return;
    }
    c_textattr(8);

    printf("Entrez votre NOM DE FAMILLE : ");
    scanf("%s", client.last_name);
    printf("Entrez votre PRENOM : ");
    scanf("%s", client.First_name);

    do {
        printf("Entrez votre CIN : ");
        scanf("%s", client.CIN);

        if (!is_CIN_unique(client.CIN)) {
            c_textcolor(4);  
            printf("Erreur : Le CIN existe deja. Veuillez entrer un CIN unique.\n");
            c_textattr(14);
        }
    } while (!is_CIN_unique(client.CIN));

    do {
        printf("Entrez le NOUVEAU MOT DE PASSE : ");
        strcpy(client.password, Pass_hide(20));
        client.password[strlen(client.password)] = '\0';
        
        printf("\nConfirmez votre MOT DE PASSE : ");
        strcpy(client.confirm_password, Pass_hide(20));
        client.confirm_password[strlen(client.confirm_password)] = '\0';

        if (strcmp(client.password, client.confirm_password) != 0) {
            c_textattr(4);
            printf("\nErreur : Les mots de passe ne correspondent pas. Veuillez reessayer.\n");
            c_textattr(14);
        }
    } while (strcmp(client.password, client.confirm_password) != 0);

    fprintf(fp, "%s %s %s %s\n", client.last_name, client.First_name, client.CIN, client.password);
    c_textattr(2);

    printf("\nInformations ajoutees avec succès !\n");
    c_textattr(14);

    c_clrscr();
    fclose(fp);
}


char* Pass_hide(int max_length) {
    static char PIN[256]; // Static to ensure it persists after function execution
    int i = 0;
    char ch;

    while (i < max_length - 1 && (ch = c_getch()) != '\r') {  // '\r' is Enter key in Windows
        if (ch == '\b' && i > 0) {  // Handle backspace
            i--;
            printf("\b \b");  // Move back, overwrite with space, and move back again
        } else if (ch != '\b') {
            PIN[i++] = ch;
            printf("*");
        }
    }
    PIN[i] = '\0';  // Null-terminate the PIN string
    printf("\n");
    return PIN;
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
    strcpy(passw,Pass_hide(20));
    passw[strlen(passw)] = '\0';

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        printf("\nError: Could not open the file.\n");
     c_textattr(14);
        return;
    }
    Client client;
    while (fscanf(fp, "%s %*s %s %s",client.last_name , client.CIN, client.password) == 3) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {
            c_textattr(2);
            strcpy(Temp_CIN , CINN);
            printf("\nConnected successfully!\n");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();
            liste_client(CIN , client.last_name );
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
// french version
void clientLogin_f (char * CIN){
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
    c_textattr(8);
    printf("Connectez-vous a votre compte :\n");
    c_textattr(14);
    printf("Entrez votre CIN : ");
    scanf("%s", CINN);

    printf("Entrez votre MOT DE PASSE : ");
    strcpy(passw, Pass_hide(20));
    passw[strlen(passw)] = '\0';

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        printf("\nErreur : Impossible d'ouvrir le fichier.\n");
        c_textattr(14);
        return;
    }
    Client client;
    while (fscanf(fp, "%s %*s %s %s", client.last_name, client.CIN, client.password) == 3) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {
            c_textattr(2);
            strcpy(Temp_CIN , CINN);
            printf("\nConnecte avec succès !\n");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();
            liste_client_f(CIN , client.last_name );
            break;
        }
    }
    if (!found) {
        c_textattr(4);
        printf("\nVous devez d'abord creer un compte !\n");
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
// french version
void View_Product_List_f() {

    product p;

    FILE *fk = fopen("produit.txt", "rt");
    if (fk == NULL) {
        c_textattr(4);
        printf("Le fichier n'existe pas ou n'a pas pu être ouvert !\n");

        return;
    }
    c_textattr(8);
    printf("\n====== LA LISTE DES PRODUITS ======\n\n");
    printf("%-20s %-20s %-15s %-15s %-10s %-10s\n", "ID_PRODUIT", "CATeGORIE", "NOM", "DESCRIPTION", "PRIX", "QUANTITe");
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
// french version
void Add_Purchases_f() {
    product l, p;
    Client client;
    char filename[100];

    printf("Entrez votre CIN : ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n');

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *fk = fopen("produit.txt", "rt");
    if (fk == NULL) {
        c_textattr(4);
        printf("Erreur lors de l'ouverture du fichier produit !\n");
        c_textattr(8);
        return;
    }

    int found = 0;
    printf("\nEntrez l'ID du PRODUIT : ");
    while (scanf("%d", &l.id_product) != 1) {
        c_textattr(4);
        printf("Veuillez entrer un ID de produit valide (entier) : ");
        c_textattr(8);
        while (getchar() != '\n');
    }

    // Recherche du produit dans l'inventaire
    while (fscanf(fk, "%d %49s %49s %99s %f %d", &p.id_product, p.category, p.name, p.description, &p.price, &p.quantity) == 6) {
        if (p.id_product == l.id_product) {
            found = 1;
            break;
        }
    }

    fclose(fk);

    if (!found) {
        c_textattr(4);
        printf("L'ID du produit %d n'a pas ete trouve dans l'inventaire !\n", l.id_product);
        c_textattr(8);
        return;
    }

    printf("\nEntrez la quantite (1 - %d) : ", p.quantity);
    while (scanf("%d", &l.quantity) != 1 || l.quantity < 1 || l.quantity > p.quantity) {
        c_textattr(4);
        printf("Quantite invalide. Entrez une valeur entre 1 et %d : ", p.quantity);
        c_textattr(8);
        while (getchar() != '\n');
    }

    // Lire le panier existant et verifier le produit
    FILE *ff = fopen(filename, "r+");
    if (ff == NULL) {
        ff = fopen(filename, "w");  // Creer si inexistant
        if (ff == NULL) {
            c_textattr(4);
            printf("Erreur lors de l'ouverture du fichier panier !\n");
            c_textattr(8);
            return;
        }
    }

    product cart[100];
    int cartSize = 0;
    int exists = 0;

    // Charger les articles existants du panier
    while (fscanf(ff, "%d %d", &cart[cartSize].id_product, &cart[cartSize].quantity) == 2) {
        if (cart[cartSize].id_product == l.id_product) {
            int totalQuantity = cart[cartSize].quantity + l.quantity;
            if (totalQuantity > p.quantity) {
                c_textattr(4);
                printf("Impossible d'ajouter au panier. La quantite totale (%d) depasse le stock disponible (%d).\n", totalQuantity, p.quantity);
                c_textattr(8);
                fclose(ff);
                return;
            }
            cart[cartSize].quantity = totalQuantity;  // Additionner les quantites si le produit est deja dans le panier
            exists = 1;
        }
        cartSize++;
    }

    // Si le produit est nouveau dans le panier
    if (!exists) {
        cart[cartSize] = l;
        cartSize++;
    }

    // Recrire le panier avec les quantites mises a jour
    freopen(filename, "w", ff);
    for (int i = 0; i < cartSize; i++) {
        fprintf(ff, "%d %d\n", cart[i].id_product, cart[i].quantity);
    }
    c_textattr(2);
    printf("Produit ajoute avec succès au panier.\n");
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
// french version
void View_Purchases_f() {
    Client client;
    char filename[100];
    float total_price = 0.0;

    printf("Entrez votre CIN : ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n');

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
        c_textattr(4);
        printf("Vous n'avez aucun achat dans votre panier ou le fichier du panier n'existe pas.\n");
        c_textattr(14);
        return;
    }

    printf("\n===== VOS ACHATS =====\n");
    c_textattr(8);
    printf("%-20s %-15s %-15s %-10s %-10s %-10s\n", "ID Produit", "Nom", "Categorie", "Prix", "Quantite", "Prix Total");
    printf("---------------------------------------------------------------------------------------------------------\n");
    int found = 0;
    int id_product, quantity;
    while (fscanf(ff, "%d %d", &id_product, &quantity) == 2) {

        FILE *fk = fopen("produit.txt", "rt");
        if (fk == NULL) {
            c_textattr(4);
            printf("Erreur lors de l'ouverture du fichier de la liste des produits !\n");
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
        printf("Votre panier est vide.\n");
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
// french version
void Remove_Purchases_f() {
    Client client;
    char filename[100];
    int id_product, quantity, found = 0;

    printf("Entrez votre CIN : ");
    scanf("%49s", client.CIN);
    while (getchar() != '\n'); // Clear input buffer

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN); // Construct filename based on CIN

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
        c_textattr(4);
        printf("Votre panier est vide ou le fichier du panier n'existe pas.\n");
        c_textattr(14);
        return;
    }

    // Create a temporary file to store the updated cart
    FILE *tempFile = fopen("temp_cart.txt", "w");
    if (tempFile == NULL) {
        c_textattr(4);
        printf("Erreur lors de l'ouverture du fichier temporaire.\n");
        c_textattr(14);
        fclose(ff);
        return;
    }

    product p;
    int id_product_in_cart, quantity_in_cart;

    // Display the current items in the cart
    printf("\n===== VOS ACHATS ACTUELS =====\n");
    printf("%-20s %-15s %-10s %-10s\n", "ID Produit", "Nom", "Prix", "Quantite");
    printf("--------------------------------------------------------------\n");
    c_textattr(8);

    // Read the items from the cart and print them
    while (fscanf(ff, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        FILE *fk = fopen("produit.txt", "rt");
        if (fk == NULL) {
            c_textattr(4);
            printf("Erreur lors de l'ouverture du fichier de la liste des produits !\n");
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
        printf("Aucun produit trouve dans votre panier.\n");
        c_textattr(14);
        fclose(ff);
        fclose(tempFile);
        return;
    }

    // Ask the user for the product ID and quantity to remove
    printf("\nEntrez l'ID du produit a SUPPRIMER : ");
    scanf("%d", &id_product);

    printf("Entrez la quantite a SUPPRIMER : ");
    while (scanf("%d", &quantity) != 1 || quantity < 1) {
        c_textattr(4);
        printf("Quantite invalide. Veuillez entrer un entier positif : ");
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
                    printf("Supprime %d article(s) du panier. Il en reste %d.\n", quantity, quantity_in_cart - quantity);
                } else {
                    printf("Tous les %d articles ont ete supprimes du panier.\n", quantity_in_cart);
                }
            } else {
                c_textattr(4);
                printf("Erreur : Il n'y a que %d article(s) disponible(s) dans le panier. Aucun article n'a ete supprime.\n", quantity_in_cart);
                c_textattr(14);
                fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart); // Write original data to tempFile
            }
        } else {
            fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart);
        }
    }

    if (!found) {
        c_textattr(4);
        printf("L'ID du produit %d n'a pas ete trouve dans votre panier.\n", id_product);
        c_textattr(14);
    }

    // Close the original and temporary files
    fclose(ff);
    fclose(tempFile);

    // Replace the original cart file with the updated cart
    remove(filename); // Delete the original cart file
    rename("temp_cart.txt", filename); // Rename the temporary file to the original cart filename
    c_textattr(2);

    printf("\nPanier mis a jour avec succès.\n");
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

    // Aller a la fin du fichier
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) != 0) {  // Si le fichier n'est pas vide
        rewind(fp);
        while (fscanf(fp, " %d %s %s %f %d %s", &p.id_product, p.name, p.category, &p.price, &p.quantity, p.description) == 6) {
            id = p.id_product + 1;  // Trouver le dernier ID et l'incrementer
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
    p.id_product = get_next_product_id(fp); // Definir un ID de produit unique

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
// french version
void add_product_f() {
    FILE *fp = fopen("produit.txt", "a+");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    product p;
    p.id_product = get_next_product_id(fp); // Generer un ID unique pour le produit

    // Saisie des informations du produit
    c_textcolor(14);
    c_gotoxy(30, 3);
    printf("Entrez le nom du produit : ");
    c_textcolor(8);
    scanf(" %[^\n]s", p.name);

    c_gotoxy(30, 4);
    c_textcolor(14);
    printf("Entrez la categorie du produit : ");
    c_textcolor(8);
    scanf(" %[^\n]s", p.category);

    c_gotoxy(30, 5);
    c_textcolor(14);
    printf("Entrez le prix du produit : ");
    c_textcolor(8);
    scanf("%f", &p.price);

    c_gotoxy(30, 6);
    c_textcolor(14);
    printf("Entrez la quantite du produit : ");
    c_textcolor(8);
    scanf("%d", &p.quantity);

    c_gotoxy(30, 7);
    c_textcolor(14);
    printf("Entrez la description du produit : ");
    c_textcolor(8);
    scanf(" %[^\n]s", p.description);
    c_textcolor(15);

    // Enregistrer les informations du produit dans le fichier
    fprintf(fp, " %d %s %s %s %.2f %d\n", p.id_product, p.category, p.name, p.description, p.price, p.quantity);
    fclose(fp);

    c_textcolor(2);
    printf("Produit ajoute avec succès\n");
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
// french version
void delete_product_f(){
    FILE *fp, *temp;
    fp = fopen("produit.txt", "r");
    temp = fopen("temp.txt", "w");
    int id;
    int tr = 0;
    if (fp == NULL && temp == NULL) {
        printf("Impossible d'ouvrir le fichier");
        exit(1);
    }
    c_clrscr();
    c_textcolor(1);
    c_gotoxy(30, 3);
    printf("Entrez l'ID du produit a supprimer : ");
    scanf("%d", &id);
    c_textcolor(15);
    product p;
    while (fscanf(fp, "%d %s %s %f %d %[^\n]s", &p.id_product, p.name, p.category, &p.price, &p.quantity, p.description) == 6) {
        if (p.id_product == id) {
            tr = 1; 
        } else {
            fprintf(temp, "%d %s %s %.2f %d %s\n", p.id_product, p.name, p.category, p.price, p.quantity, p.description);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt", "produit.txt");

    c_gotoxy(30, 5);
    if (tr == 0) {
        c_textcolor(4);
        printf("\nAttention, le produit n'existe pas !!");
        c_textcolor(15);
    } else {
        c_gotoxy(30, 5);
        c_textcolor(2);
        printf("\nLe produit a ete supprime avec succès !!\n");
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
// french version
void modify_product_f(){
    FILE *fp, *temp;
    fp = fopen("produit.txt", "r");
    temp = fopen("temp.txt", "w");
    int id;
    int tr = 0, r = 1;
    int c;
    if (fp == NULL && temp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }
    c_clrscr();
    c_textcolor(1);
    c_gotoxy(30, 3);
    printf("Entrez l'ID du produit a modifier : ");
    scanf("%d", &id);
    c_textcolor(15);
    product p;
    product pn;
    while (fscanf(fp, "%d %s %s %f %d %[^\n]s", &p.id_product, p.name, p.category, &p.price, &p.quantity, p.description) == 6) {
        if (p.id_product == id) {
            c_clrscr();
            printf("\n\n\n\n\n\n");
            c_textcolor(1);
            printf("\t\t\t\t\t\t\t==========================\n");
            c_textcolor(5);
            printf("\t\t\t\t\t\t\t | 1. Modifier le nom         |\n");
            printf("\t\t\t\t\t\t\t | 2. Modifier la categorie   |\n");
            printf("\t\t\t\t\t\t\t | 3. Modifier le prix        |\n");
            printf("\t\t\t\t\t\t\t | 4. Modifier la quantite    |\n");
            printf("\t\t\t\t\t\t\t | 5. Modifier la description |\n");
            c_textcolor(1);
            printf("\t\t\t\t\t\t\t=========================\n");
            c_textcolor(14);
            printf("\n\t\t\t\t\t\t\t Saisissez votre choix : ");
            scanf("%d", &c);
            c_textcolor(15);
            //-------------------------------------------clear screen------------
            c_clrscr();
            c_textcolor(1);
            c_gotoxy(30, 18);

            switch (c) {
                case 1:
                    c_gotoxy(30, 18);
                    printf("Entrez le nouveau nom : ");
                    scanf(" %[^\n]s", pn.name);
                    strcpy(p.name, pn.name);
                    break;
                case 2:
                    c_gotoxy(30, 18);
                    printf("Entrez la nouvelle categorie : ");
                    scanf(" %[^\n]s", pn.category);
                    strcpy(p.category, pn.category);
                    break;
                case 3:
                    c_gotoxy(30, 18);
                    printf("Entrez le nouveau prix : ");
                    scanf("%f", &pn.price);
                    p.price = pn.price;
                    break;
                case 4:
                    c_gotoxy(30, 10);
                    printf("Entrez la nouvelle quantite : ");
                    scanf("%d", &pn.quantity);
                    p.quantity = pn.quantity;
                    break;
                case 5:
                    c_gotoxy(30, 10);
                    printf("Entrez la nouvelle description : ");
                    scanf(" %[^\n]s", pn.description);
                    strcpy(p.description, pn.description);
                    break;
                default:
                    c_gotoxy(30, 18);
                    choixinvalid();
                    r = 0; // r pour condition
                    break;
            }
            c_textcolor(15);
            tr = 1;
        }
        fprintf(temp, "%d %s %s %.2f %d %s\n", p.id_product, p.name, p.category, p.price, p.quantity, p.description);
    }
    fclose(fp);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt", "produit.txt");

    if (tr == 0 || r == 0) {
        c_textcolor(4);
        c_gotoxy(30, 20);
        printf("\n\n\n\t\t\t\t\tAttention, le produit n'existe pas !!");
        c_textcolor(15);
    } else {
        c_textcolor(2);
        c_gotoxy(30, 20);
        printf("\n\n\n\t\t\t\t\tLe produit a ete modifie avec succès !!\n");
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

        if (!is_CIN_unique_supplier(f.Cinf)) {

              c_textcolor(4);  printf("Error: CIN already exists. Please enter a unique CIN.\n");
      c_textattr(14);

        }
    } while (!is_CIN_unique_supplier(f.Cinf));

    do {

    printf("Enter NEW PASSWORD: ");
        strcpy(f.mdpf,Pass_hide(20));
        f.mdpf[strlen(f.mdpf)] = '\0';
        printf("\nConfirm your PASSWORD: ");
        strcpy(f.cmdpf,Pass_hide(20));
        f.cmdpf[strlen(f.cmdpf)] = '\0';
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
// french version
void sign_in_supplier_f() {
    int i, j;
    fournisseur f;
    FILE *fp = fopen("FOURNISSEUR.txt", "a");
    if (fp == NULL) {
        printf("Le fichier n'existe pas ou n'a pas pu être ouvert !\n");
        return;
    }
    c_textattr(8);

    printf("Entrez votre NOM : ");
    scanf("%s", f.nomf);
    printf("Entrez votre PReNOM : ");
    scanf("%s", f.prenomf);

    do {
        printf("Entrez votre CIN : ");
        scanf("%s", f.Cinf);

        if (!is_CIN_unique_supplier(f.Cinf)) {
            c_textcolor(4);
            printf("Erreur : Ce CIN existe deja. Veuillez entrer un CIN unique.\n");
            c_textattr(14);
        }
    } while (!is_CIN_unique_supplier(f.Cinf));

    do {
        printf("Entrez un NOUVEAU MOT DE PASSE : ");
        strcpy(f.mdpf, Pass_hide(20));
        f.mdpf[strlen(f.mdpf)] = '\0';

        printf("\nConfirmez votre MOT DE PASSE : ");
        strcpy(f.cmdpf, Pass_hide(20));
        f.cmdpf[strlen(f.cmdpf)] = '\0';

        if (strcmp(f.mdpf, f.cmdpf) != 0) {
            c_textattr(4);
            printf("\nErreur : Les mots de passe ne correspondent pas. Veuillez reessayer.\n");
            c_textattr(14);
        }
    } while (strcmp(f.mdpf, f.cmdpf) != 0);

    fprintf(fp, "%s %s %s %s\n", f.nomf, f.prenomf, f.Cinf, f.mdpf);
    c_textattr(2);

    printf("\nInformations ajoutees avec succès !\n");
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
            while ((ch = c_getch()) != '\r' && i < 19) {  // Limite a 19 caractères
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
// french version
void add_supplier_f() {
    FILE *fp;
    fp = fopen("fournisseur.txt", "a+");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    fournisseur frn;
    char ch;
    int i;
    int t = 0 ;
    c_textcolor(1);
    c_gotoxy(50,6);
    printf("Prenom : ");
    scanf(" %[^\n]s", frn.prenomf);
    c_gotoxy(50,8);
    printf("Nom : ");
    scanf(" %[^\n]s", frn.nomf);
    do {
        c_gotoxy(50,10 + t );
        printf("CIN : ");
        scanf(" %s", frn.Cinf);
        if (is_CIN_unique(frn.Cinf) == 0) {
            c_gotoxy(60,11 + t );
            printf("Attention, ce CIN est deja utilise !");
            c_getch();
            t = t + 2 ;
        } else {
            c_gotoxy(50,12+t);
            printf("Saisir le mot de passe : ");
            strcpy(frn.mdpf,Pass_hide(20));
            frn.mdpf[strlen(frn.mdpf)] = '\0';
            fprintf(fp, "%s %s %s %s\n", frn.prenomf, frn.nomf, frn.Cinf, frn.mdpf);
            break;           
        }
    } while (1);
    fclose(fp);
    c_textcolor(15);
    c_textcolor(2);
    c_gotoxy(60,15+t);
    printf("Fournisseur ajoute avec succès !!");
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
            return 0; // CIN deja existant
        }
    }
    
    fclose(fr);
    return 1; // CIN n'existe pas
}

//-----------------------------------------------------------------------


void liste_fournisseur(char * Temp_CIN) {
    int choice;
    int n ;
    do {
        c_textcolor(8);
        c_clrscr();
        printf("Supplier CIN: %s\n", Temp_CIN);
        printf("\nSupplier Menu:\n");
        printf("1. Add Product\n");
        printf("2. Modify Product\n");
        printf("3. Add Supplier\n");
        printf("4. Display the Supplier Total amount sales in the Day");
        printf("5. Delete Product\n");
        printf("6. Exit\n");
        c_textcolor(14);
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
            case 4 :
            c_clrscr();
            printf("Entre number of supplier : "); 
            scanf("%d",&n);
            Display_the_Supplier_Total_amount_sales_in_the_Day(Temp_CIN,n);
            break;
            case 5:
                delete_product();
                break;
            case 6:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        if (choice !=  6) {
            printf("Press any key to continue...\n");
            c_getch();  // Pause before clearing screen again
        }
        c_getch();
        c_clrscr();
    } while (choice != 5);
}
// french version
void liste_fournisseur_f(char * Temp_CIN) {
    int choice;
    int n;
    do {
        c_textcolor(8);
        c_clrscr();
        printf("CIN du fournisseur : %s\n", Temp_CIN);
        printf("\nMenu Fournisseur :\n");
        printf("1. Ajouter un produit\n");
        printf("2. Modifier un produit\n");
        printf("3. Ajouter un fournisseur\n");
        printf("4. Afficher le montant total des ventes du fournisseur dans la journée\n");
        printf("5. Supprimer un produit\n");
        printf("6. Quitter\n");
        c_textcolor(14);
        printf("Entrez votre choix : ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_product_f();
                break;
            case 2:
                modify_product_f();
                break;
            case 3:
                add_supplier_f();
                break;
            case 4:
                c_clrscr();
                printf("Entrez le nombre de fournisseurs : "); 
                scanf("%d", &n);
                Display_the_Supplier_Total_amount_sales_in_the_Day_f(Temp_CIN, n);
                break;
            case 5:
                delete_product_f();
                break;
            case 6:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
        if (choice != 6) {
            printf("Appuyez sur une touche pour continuer...\n");
            c_getch();  // Pause avant de nettoyer l'écran à nouveau
        }
void liste_fournisseur(char * Temp_CIN) {
    int choice;
    int n;
    do {
        c_textcolor(8);
        system("cls");  // Effacer l'écran (remplacer par `clrscr();` si vous utilisez conio.h personnalisé)
        printf("CIN du fournisseur : %s\n", Temp_CIN);
        printf("\nMenu Fournisseur :\n");
        printf("1. Ajouter un produit\n");
        printf("2. Modifier un produit\n");
        printf("3. Ajouter un fournisseur\n");
        printf("4. Afficher le montant total des ventes du fournisseur dans la journée\n");
        printf("5. Supprimer un produit\n");
        printf("6. Quitter\n");
        c_textcolor(14);
        printf("Entrez votre choix : ");
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
                c_clrscr();
                printf("Entrez le nombre de fournisseurs : "); 
                scanf("%d", &n);
                Display_the_Supplier_Total_amount_sales_in_the_Day(Temp_CIN, n);
                break;
            case 5:
                delete_product();
                break;
            case 6:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
        if (choice != 6) 
            printf("Appuyez sur une touche pour continuer...\n");
        c_getch();
        c_clrscr();
    } while (choice != 5);
}

        c_clrscr();
    } while (choice != 6);
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
    strcpy(passw,Pass_hide(20));
    passw[strlen(passw)] = '\0';

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
// french version
void login_supplier_f(char *CIN) {
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
    c_textattr(8);
    printf("Connectons-nous a votre compte :\n");
    c_textattr(14);
    printf("Entrez votre CIN : ");
    scanf("%s", CINN);

    printf("Entrez votre MOT DE PASSE : ");
    strcpy(passw, Pass_hide(20));
    passw[strlen(passw)] = '\0';

    FILE *fp = fopen("FOURNISSEUR.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        printf("\nErreur : Impossible d'ouvrir le fichier.\n");
        c_textattr(14);
        return;
    }
    fournisseur f;
    while (fscanf(fp, "%*s %*s %s %s", f.Cinf, f.mdpf) == 2) {
        if (strcmp(f.Cinf, CINN) == 0 && strcmp(f.mdpf, passw) == 0) {
            c_textattr(2);
            strcpy(Temp_CIN, CINN);
            printf("\nConnexion reussie !\n");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();
            liste_fournisseur_f(Temp_CIN);
            break;
        }
    }
    if (!found) {
        c_textattr(4);
        printf("\nVous devez d'abord creer un compte!\n");
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
// french version
void client_factor_f(FILE *PCM, FILE *CDM, FILE *client_choice, char *CIN) {
    FILE *FACT = fopen("FACTEUR.pdf", "w");
    if (FACT == NULL) {
        printf("Erreur : Impossible de creer le fichier FACTEUR.pdf !\n");
        exit(1);
    }
    
    CCD client_details;
    int found = 0;
    rewind(CDM);

    // etape 1 : Rechercher les details du client dans la base de donnees des cartes de credit (CDM)
    while (fread(&client_details, sizeof(CCD), 1, CDM) == 1) {
        if (strcmp(client_details.client_CIN, CIN) == 0) {
            found = 1;
            break;
        }
    }
    if (!found) {
        fprintf(FACT, "Erreur : Client avec le CIN %s introuvable dans la base de donnees des cartes de credit !\n", CIN);
        fclose(FACT);
        return;
    }

    // etape 2 : Masquer le numero de carte de credit
    char hidden_card_number[50];
    snprintf(hidden_card_number, sizeof(hidden_card_number), "%.4s ** ** %.4s", 
             client_details.card_number, 
             client_details.card_number + strlen(client_details.card_number) - 4);

    // etape 3 : ecrire les informations du client et la date dans FACTEUR
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    fprintf(FACT, pdf_header);
    fprintf(FACT, "(================== FACTURE ==================) Tj\n0 -20 Td  ");
    fprintf(FACT, "(Nom du client : %s ) Tj\n0 -20 Td", client_details.client_name);
    fprintf(FACT, "(CIN du client : %s ) Tj\n0 -20 Td", client_details.client_CIN);
    fprintf(FACT, "(Numero de carte : %s ) Tj\n0 -20 Td", hidden_card_number);
    fprintf(FACT, "(Date d'achat : %02d-%02d-%d) Tj\n0 -30 Td " ,  
            localTime->tm_mday, 
            localTime->tm_mon + 1, 
            localTime->tm_year + 1900);
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td");
    fprintf(FACT, "(| Produit         | Quantite   | Prix Total  |) Tj\n0 -20 Td");
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td");

    // etape 4 : Traiter les choix du client et calculer le coût total
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
            case 1: // En stock
                grand_total += client_choice_entry.price * client_choice_entry.quantity;
                fprintf(FACT, "(| %-15s | %-10d | %-10.2f DH |) Tj\n0 -20 Td\n", client_choice_entry.name, client_choice_entry.quantity, client_choice_entry.price * client_choice_entry.quantity);
                break;
            case 0: // Hors stock
                fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", client_choice_entry.name, client_choice_entry.quantity, "Hors Stock");
                break;
            case -1: // Produit introuvable
                fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", client_choice_entry.name, client_choice_entry.quantity, "Introuvable");
                break;
        }
    }

    // etape 5 : Imprimer le total general et fermer le fichier FACTEUR
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Total general : %.2f DH) Tj\n0 -20 Td\n", grand_total);
    fprintf(FACT, "(=============================================) Tj\n");
    fprintf(FACT, pdf_footer);
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
    A.client_name[sizeof(A.client_name) - 1] = '\0';
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
// french version
void add_credit_card_f(char* CIN_client, char *name_client) {
    time_t t = time(NULL);   // Obtenir l'heure actuelle
    struct tm *current_time = localtime(&t); // Convertir en structure de temps local
    int current_year = current_time->tm_year + 1900; // Extraire l'annee actuelle
    int current_mont = current_time->tm_mon + 1;

    // Ouvrir le fichier en mode ajout binaire
    CDM = fopen("CREDIT_CARD.dat", "ab");
    if (CDM == NULL) {
        c_textcolor(4);
        printf("Le fichier n'existe pas !\n");
        return;  // Sortir sans terminer le programme
    }
    int valid = 0;
    CCD A;
    strncpy(A.client_CIN, CIN_client, sizeof(A.client_CIN) - 1);
    A.client_CIN[sizeof(A.client_CIN) - 1] = '\0';  // Assurer la terminaison nulle
    strncpy(A.client_name, name_client, sizeof(A.client_name) - 1);
    A.client_name[sizeof(A.client_name) - 1] = '\0';
    c_textcolor(14);
    c_gotoxy(30 , 3);
    printf(" %s, veuillez entrer les informations de votre carte de credit (generalement 13-19 chiffres)", name_client);

    int count_error = 0;
    do {
        c_textcolor(14);
        c_gotoxy(50 , 5 + count_error);
        printf("Entrez le numero de votre carte de credit : ");
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
            c_gotoxy(50 , 6 + count_error);
            printf("Veuillez entrer un numero valide entre 13 et 19 chiffres");
            count_error += 2;
        }
    } while (!valid);

    valid = 0;
    int month, year;
    do {
        c_textcolor(14);
        c_gotoxy(50 , 8 + count_error);
        printf("Entrez la date d'expiration au format MM/AA (ex. : 02/27) : ");
        c_textcolor(8);
        scanf("%2s/%2s", A.expiry_date.month, A.expiry_date.year);
        if ((sscanf(A.expiry_date.month, "%2d", &month) == 1) && (sscanf(A.expiry_date.year, "%2d", &year) == 1)) {
            if (month > 0 && month <= 12 && year >= (current_year - 2000)) {
                valid = 1;
            }
            if ((year == current_year - 2000) && (month <= current_mont)) valid = 0;
            if (!valid) {
                c_textcolor(4);
                c_gotoxy(50 , 9 + count_error);
                printf("Mois ou annee invalide !");
                count_error += 2;
                c_textcolor(7);
            }
        } else {
            c_gotoxy(50 , 9 + count_error);
            printf("Format invalide. Veuillez entrer MM/AA\n");
            count_error += 2;
        }
    } while (!valid);

    valid = 0;
    do {
        c_textcolor(14);
        count_error += 2;
        c_gotoxy(50 , 7 + count_error);
        printf("Entrez votre code CVV (ex. : 123) : ");
        c_textcolor(8);
        c_gotoxy(83 , 7 + count_error);
        scanf("%s", A.CVV);

        // Verifier si le CVV contient exactement 3 chiffres
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
            c_gotoxy(50 , 9 + count_error);
            printf("CVV invalide ! Veuillez entrer un numero a 3 chiffres.");
            count_error += 2;
        }
    } while (!valid);

    c_textcolor(2);
    c_gotoxy(50 , 9 + count_error);
    printf("Code CVV valide");
    c_textcolor(15);
    fwrite(&A, sizeof(CCD), 1, CDM);
    fclose(CDM);
    c_getch();
    c_clrscr();
}


void display_credit_cards(char *client_name, char *CIN) {
    FILE *CDM_1 = fopen("CREDIT_CARD.dat", "rb");
    if (CDM_1 == NULL) {
        c_textcolor(4);
        printf("\nERROR: The file 'CREDIT_CARD.dat' does not exist!");
        exit(0);
    }

    CCD CD; // CD: CARD DETAIL
    int found = 0;

    c_textcolor(14);
    printf("\n------------------- Credit Card Details -------------------\n");

    while (fread(&CD, sizeof(CCD), 1, CDM_1) == 1) {
        if (strcmp(CIN, CD.client_CIN) == 0) {
            found = 1;

            c_textcolor(8);
            printf("\nClient Name: ");
            c_textcolor(14);
            printf("%s\n", CD.client_name);

            c_textcolor(8);
            printf("CIN: ");
            c_textcolor(14);
            printf("%s\n", Temp_CIN);

            c_textcolor(8);
            printf("Card Number: ");
            for (int i = 0; i < strlen(CD.card_number); i++) {
                if (i < 4 || i >= strlen(CD.card_number) - 4) {
                    c_textcolor(14);
                    printf("%c", CD.card_number[i]);
                } else {
                    c_textcolor(5);
                    printf("*");
                }
            }
            printf("\n");

            c_textcolor(8);
            printf("CVV: ");
            c_textcolor(5); 
            printf("***\n");

            c_textcolor(8);
            printf("Card Expiry Date: ");
            c_textcolor(14);
            printf("%s/%s\n", CD.expiry_date.month, CD.expiry_date.year);
        }
    }

    if (!found) {
        c_textcolor(4);
        printf("\nNo credit card found for client with CIN: %s\n", CIN);
    }

    fclose(CDM_1);

    c_textattr(14);
    printf("\n----------------------------------------------------------\n");
    c_getch();
    c_clrscr();
}
// french version
void display_credit_cards_f(char *client_name, char *CIN) {
    FILE *CDM_1 = fopen("CREDIT_CARD.dat", "rb");
    if (CDM_1 == NULL) {
        c_textcolor(4);
        printf("\nERREUR : Le fichier 'CREDIT_CARD.dat' n'existe pas !");
        exit(0);
    }

    CCD CD; // CD : DeTAILS DE LA CARTE
    int found = 0;

    c_textcolor(14);
    printf("\n------------------- Details de la Carte de Credit -------------------\n");

    while (fread(&CD, sizeof(CCD), 1, CDM_1) == 1) {
        if (strcmp(CIN, CD.client_CIN) == 0) {
            found = 1;

            c_textcolor(8);
            printf("\nNom du Client : ");
            c_textcolor(14);
            printf("%s\n", CD.client_name);

            c_textcolor(8);
            printf("CIN : ");
            c_textcolor(14);
            printf("%s\n", Temp_CIN);

            c_textcolor(8);
            printf("Numero de Carte : ");
            for (int i = 0; i < strlen(CD.card_number); i++) {
                if (i < 4 || i >= strlen(CD.card_number) - 4) {
                    c_textcolor(14);
                    printf("%c", CD.card_number[i]);
                } else {
                    c_textcolor(5);
                    printf("*");
                }
            }
            printf("\n");

            c_textcolor(8);
            printf("CVV : ");
            c_textcolor(5); 
            printf("***\n");

            c_textcolor(8);
            printf("Date d'Expiration : ");
            c_textcolor(14);
            printf("%s/%s\n", CD.expiry_date.month, CD.expiry_date.year);
        }
    }

    if (!found) {
        c_textcolor(4);
        printf("\nAucune carte de credit trouvee pour le client avec le CIN : %s\n", CIN);
    }

    fclose(CDM_1);

    c_textattr(14);
    printf("\n---------------------------------------------------------------------\n");
    c_getch();
    c_clrscr();
}


void Display_the_Supplier_Total_amount_sales_in_the_Day(char *CINF, int supplier_num) {
    FILE *PCM = fopen("produit.txt", "rt");
    if (PCM == NULL) {
        printf("Error: PCM.dat does not exist!\n");
        fclose(PCM); 
        exit(0);
    }

    FILE *client_choice = fopen("client_choice.txt", "rt");
    if (client_choice == NULL) {
        printf("Error: client_choice.dat does not exist!\n");
        fclose(client_choice); 
        exit(0); 
    }

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
    FILE *supplier_amount = fopen(filename, "a+t");
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
    fclose(PCM);
    fclose(client_choice);
    c_clrscr();
}
// french version
void Display_the_Supplier_Total_amount_sales_in_the_Day_f(char *CINF, int supplier_num) {
    FILE *PCM = fopen("produit.txt", "rt");
    if (PCM == NULL) {
        printf("Error: PCM.dat does not exist!\n");
        fclose(PCM);
        exit(0);
    }
    FILE *client_choice = fopen("client_choice.txt", "rb");
    if (client_choice == NULL) {
        printf("Error: client_choice.dat does not exist!\n");
        fclose(client_choice); 
        exit(0); 
    }
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;
    c_textcolor(14);
    c_gotoxy(50, 2);
    printf("======== RAPPORT DES VENTES TOTALES DU FOURNISSEUR ========");
    c_gotoxy(50, 3);
    printf("DATE DU JOUR : %02d-%02d-%d", day, month, year);
    c_gotoxy(50, 4);
    printf("ID DU FOURNISSEUR : %s", CINF);
    c_gotoxy(50, 5);
    printf("=========================================================");

    // Creer le nom du fichier pour les donnees du fournisseur
    char filename[50];
    sprintf(filename, "fournisseur%d.txt", supplier_num);
    FILE *supplier_amount = fopen(filename, "w+t");
    if (supplier_amount == NULL) {
        c_textcolor(4);
        printf("Erreur : Impossible de creer le fichier %s !\n", filename);
        return;
    }
    int product_id, client_id;
    char product_category[30], product_name[30], client_category[30], client_name[30];
    float product_price = 0.0;
    int product_quantity = 0, client_quantity = 0;
    float total_amount = 0;
    float sale_mount = 0;

    fprintf(supplier_amount, "CIN : %s\n\n", CINF);
    c_textcolor(11);
    int y_position = 7;
    c_gotoxy(50, y_position++);
    printf("| %-15s | %-10s | %-12s |", "CATEGORIE", "QUANTITE", "MONTANT VENTE");
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
                fprintf(supplier_amount, "Categorie : %s\nQuantite : %d\nMontant Vente : %.2f\n\n", client_category, client_quantity, total_amount);
                total_amount = 0;
                break;
            }
        }
    }
    c_textcolor(14);
    c_gotoxy(50, y_position + 1);
    printf("=========================================================");
    c_gotoxy(50, y_position + 2);
    printf("MONTANT TOTAL DES VENTES : %.2f DH", sale_mount);
    c_gotoxy(50, y_position + 3);
    printf("=========================================================");
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
// french version
void feedback_and_rate_the_product_f(char *name_cl, int id_product) { // name_cl : nom du client, id_product : ID du produit
    FILE *client_opinion = fopen("feedback.txt", "a");
    if (client_opinion == NULL) {
        c_textcolor(4); 
        printf("Erreur : feedback.txt n'existe pas !\n");
        return;
    }

    char comment[256];
    c_textcolor(14);
    printf("%s, entrez votre commentaire sur le produit %d : ", name_cl, id_product);
    c_textcolor(8);
    fflush(stdin);
    fgets(comment, sizeof(comment), stdin);
    size_t len = strlen(comment);
    if (len > 0 && comment[len - 1] == '\n') 
    comment[len - 1] = '\0'; // Supprimer le caractère de nouvelle ligne
    // ecrire le commentaire dans le fichier
    fprintf(client_opinion, "Client : %s | ID Produit : %d | Commentaire : %s\n", name_cl, id_product, comment);
    puts(comment);

    int rating;
    c_textcolor(14);
    printf(" Notez le produit (1 a 5 etoiles) : ");
    c_textcolor(14);
    while (1) {
        if (scanf("%d", &rating) != 1 || rating < 1 || rating > 5) {
            // Effacer les entrees non valides dans le tampon
            while (getchar() != '\n');
            c_textcolor(4);
            printf("Note invalide. Veuillez entrer un nombre entre 1 et 5 : ");
        } else {
            break;
        }
    }

    c_textcolor(8);
    switch (rating) {
        case 1:
            printf("- Vous avez attribue 1 etoile : Nous sommes desoles d'apprendre que votre experience a ete mauvaise.\n");
            fprintf(client_opinion, "Note : 1 etoile\n");
            break;
        case 2:
            printf("-- Vous avez attribue 2 etoiles : Merci ! Nous travaillerons pour nous ameliorer.\n");
            fprintf(client_opinion, "Note : 2 etoiles\n");
            break;
        case 3:
            printf("--- Vous avez attribue 3 etoiles : Merci pour votre retour ! Nous sommes heureux que ce soit satisfaisant.\n");
            fprintf(client_opinion, "Note : 3 etoiles\n");
            break;
        case 4:
            printf("---- Vous avez attribue 4 etoiles : Super ! Merci pour ce retour positif !\n");
            fprintf(client_opinion, "Note : 4 etoiles\n");
            break;
        case 5:
            printf("----- Vous avez attribue 5 etoiles : Genial ! Nous sommes ravis que vous ayez adore !\n");
            fprintf(client_opinion, "Note : 5 etoiles\n");
            break;
    }
    c_textcolor(14);
    printf("Merci pour votre retour !");
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