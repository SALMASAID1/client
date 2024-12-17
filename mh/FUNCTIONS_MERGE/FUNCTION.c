#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctype.h>
#include "conio.h"
#include "FUNCTION.h"

#define KEY_RIGHT 77 // Right Arrow Key Code
#define KEY_LEFT 75  // Left Arrow Key Code
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

void c_draw_menu_f(int current_option, Options options) {
    c_clrscr();
    c_textcolor(15);
    c_gotoxy(55, 5);
    printf("%s", options.title);
    c_textcolor(14);

    for (int i = 0; i < options.len; i++) {
        if (i == current_option) {
            c_textcolor(10); // Highlight the selected option
            c_gotoxy(60, 7 + i);
            printf("> %s", options.ops[i]);
        } else {
            c_textcolor(15);
            c_gotoxy(60, 7 + i);
            printf("  %s", options.ops[i]);
        }
    }
    c_textcolor(15);  // Reset text color
}
int c_select_menu_f(Options options) {
    int current_option = 0;
    int key;
    c_draw_menu_f(current_option, options);

    while (1) {
        key = c_getch();
        switch (key) {
            case 72: // Arrow up
                current_option = (current_option == 0) ? options.len - 1 : current_option - 1;
                c_draw_menu_f(current_option, options);
                break;
            case 80: // Arrow down
                current_option = (current_option == options.len - 1) ? 0 : current_option + 1;
                c_draw_menu_f(current_option, options);
                break;
            case 13: // Enter key
                return current_option;
        }
    }
}



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

    do {
        c_gotoxy(32, 6);
        c_textattr(14);
        printf(" ===================================== Welcome M.%s =====================================",client_name);
        c_gotoxy(65, 9); printf("---------------------------");
        c_gotoxy(65, 10); printf("----- LIST OF OPTIONS -----");
        c_gotoxy(65, 11); printf("---------------------------");
        c_textattr(8);
        c_gotoxy(65, 12); printf("  1 - View Product List");
        c_gotoxy(65, 13);printf("  2 - Add Purchases");
        c_gotoxy(65, 14);printf("  3 - View Purchases ");
        c_gotoxy(65, 15);printf("  4 - Remove Purchases");
        c_gotoxy(65, 16);printf("  5 - Add A Credit Card");
        c_gotoxy(65, 17);printf("  6 - Display Credit Card");
        c_gotoxy(65, 18);printf("  7 - Confirm the purchase ");
        c_gotoxy(65, 19);printf("  8 - Back to Home Page");
        c_gotoxy(65, 20);printf("  9 - Leave Page");
        c_textattr(14);
        c_gotoxy(65, 21); printf("--------------------------");

        c_gotoxy(65, 22); printf("------->> SELECT YOUR OPTION: ");
        scanf("%d", &c);

 switch (c) {
    case 1:
        View_Product_List();
        break;
    case 2:
        Add_Purchases(Temp_cin);
        break;
    case 3:
        View_Purchases(Temp_cin);
        break;
    case 4:
        Remove_Purchases(Temp_cin);
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
            printf("FILE IS NOT EXIST !!!");
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
            printf("No credit card found for this client!");
        }
        fclose(FD);
        break;
    }
    case 7: { // Ensure the client has added a credit card
        FD = fopen("CREDIT_CARD.dat", "rb");
        if (FD == NULL) {
            c_textcolor(4);
            printf("\nError: Credit card file does not exist!\n");
            exit(0);
        }

        int card_found = 0;

        while (fread(&cd, sizeof(CCD), 1, FD) == 1) {
            if (strcmp(cd.client_CIN, Temp_cin) == 0) {
                card_found = 1;
                break;
            }
        }
        fclose(FD);

        if (!card_found) {
            c_textcolor(4);
            c_gotoxy(32,25); printf("Error: You must add a credit card before confirming your purchases!");
            c_textcolor(14);
        } else {
            confirm_purchases(Temp_cin);
        }
        break;
    }
    case 8:
        Home_LOGIN_menu();
        break;
    case 9:
        leave();
        break;
    default:
        c_textattr(4);
        printf("Incorrect choice! Your choice should be between [1 - 9]. Please retry.");
        c_textattr(14);
        c_getch();
        break;
 }

         if (c != 8) {
            c_textcolor(9);
            c_gotoxy(60 ,26); printf("Press any key to continue...\n");
            c_getch();
        }
        c_clrscr();
    } while (c != 8);
}
// french version
void liste_client_f(char *Temp_cin, char *client_name) {
    FILE *FD;
    CCD cd;
    int c;
    int check_CRD = 0;
    int check_card_exists = 0;

    do {
        c_gotoxy(32, 6);
        c_textattr(14);
        printf(" ===================================== Bienvenue M.%s =====================================", client_name); // Translated
        c_gotoxy(65, 9); printf("---------------------------");
        c_gotoxy(65, 10); printf("----- LISTE DES OPTIONS -----"); // Translated
        c_gotoxy(65, 11); printf("---------------------------");
        c_textattr(8);
        c_gotoxy(65, 12); printf("  1 - Voir la liste des produits"); // Translated
        c_gotoxy(65, 13); printf("  2 - Ajouter des achats"); // Translated
        c_gotoxy(65, 14); printf("  3 - Voir les achats "); // Translated
        c_gotoxy(65, 15); printf("  4 - Supprimer des achats"); // Translated
        c_gotoxy(65, 16); printf("  5 - Ajouter une carte de credit"); // Translated
        c_gotoxy(65, 17); printf("  6 - Afficher la carte de credit"); // Translated
        c_gotoxy(65, 18); printf("  7 - Confirmer l'achat "); // Translated
        c_gotoxy(65, 19); printf("  8 - Retour a la page d'accueil"); // Translated
        c_gotoxy(65, 20); printf("  9 - Quitter la page"); // Translated
        c_textattr(14);
        c_gotoxy(65, 21); printf("--------------------------");

        c_gotoxy(65, 22); printf("------->> SeLECTIONNEZ VOTRE OPTION: "); // Translated
        scanf("%d", &c);

        switch (c) {
            case 1:
                View_Product_List_f();
                break;
            case 2:
                Add_Purchases_f(Temp_cin);
                break;
            case 3:
                View_Purchases_f(Temp_cin);
                break;
            case 4:
                Remove_Purchases_f(Temp_cin);
                break;
            case 5: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    printf("\nLE FICHIER N'EXISTE PAS !!!\n"); // Translated
                    exit(0);
                }

                check_CRD = 0;
                check_card_exists = 0;
                while (fread(&cd, sizeof(CCD), 1, FD) == 1) {
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
                        printf("\nLa carte de credit existe deja pour ce client !\n"); // Translated
                    } else {
                        add_credit_card_f(Temp_cin, client_name);
                        c_textcolor(2);
                        printf("\nCarte de credit ajoutee avec succes !\n"); // Translated
                    }
                } else {
                    add_credit_card_f(Temp_cin, client_name);
                    c_textcolor(2);
                    printf("\nCarte de credit ajoutee avec succes !\n"); // Translated
                }
                break;
            }
            case 6: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    printf("LE FICHIER N'EXISTE PAS !!!\n"); // Translated
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
                    printf("Aucune carte de credit trouvee pour ce client !\n"); // Translated
                }
                fclose(FD);
                break;
            }
            case 7: { // Ensure the client has added a credit card
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    printf("\nErreur : Le fichier de carte de credit n'existe pas !\n"); // Translated
                    exit(0);
                }

                int card_found = 0;

                while (fread(&cd, sizeof(CCD), 1, FD) == 1) {
                    if (strcmp(cd.client_CIN, Temp_cin) == 0) {
                        card_found = 1;
                        break;
                    }
                }
                fclose(FD);

                if (!card_found) {
                    c_textcolor(4);
                    c_gotoxy(32, 25); printf("Erreur : Vous devez ajouter une carte de credit avant de confirmer vos achats !\n"); // Translated
                    c_textcolor(14);
                } else {
                    confirm_purchases_f(Temp_cin);
                }
                break;
            }
            case 8:
                Home_LOGIN_menu();
                break;
            case 9:
                leave();
                break;
            default:
                c_textattr(4);
                printf("Choix incorrect ! Votre choix doit être entre [1 - 9]. Veuillez reessayer.\n"); // Translated
                c_textattr(14);
                c_getch();
                break;
        }

        if (c != 8) {
            c_textcolor(9);
            c_gotoxy(60 ,26); printf("Appuyez sur une touche pour continuer...\n"); // Translated
            c_getch();
        }
        c_clrscr();
    } while (c != 8);
}


int is_CIN_unique(const char *cin) {
    // Check if CIN is valid: first two letters and last five digits
    size_t len = strlen(cin);
    if (len < 7 || !isalpha(cin[0]) || !isalpha(cin[1]) ||
        !isdigit(cin[len - 1]) || !isdigit(cin[len - 2]) ||
        !isdigit(cin[len - 3]) || !isdigit(cin[len - 4]) ||
        !isdigit(cin[len - 5])) {
        return 0; // Invalid CIN format
    }

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) return 1;

    char file_cin[20];
    while (fscanf(fp, "%*s %*s %s %*s", file_cin) == 1) {
        if (strcmp(file_cin, cin) == 0) {
            fclose(fp);
            return 0; // CIN is not unique
        }
    }
    fclose(fp);
    return 1; // CIN is unique
} 

int is_CIN_unique_supplier(const char *cin) {
    // Check if CIN format is valid
    int len = strlen(cin);
    if (len < 7 || !isalpha(cin[0]) || !isalpha(cin[1]) ||
        !isdigit(cin[len - 1]) || !isdigit(cin[len - 2]) ||
        !isdigit(cin[len - 3]) || !isdigit(cin[len - 4]) ||
        !isdigit(cin[len - 5])) {
        printf("Invalid CIN format for supplier. It must start with two letters and end with five digits.\n");
        return 0; // Invalid CIN format
    }

    // Check if CIN is unique
    FILE *fp = fopen("FOURNISSEUR.txt", "r");
    if (!fp) return 1;

    char file_cin[20];
    while (fscanf(fp, "%*s %*s %s %*s", file_cin) == 1) {
        if (strcmp(file_cin, cin) == 0) {
            fclose(fp);
            return 0; // CIN is not unique
        }
    }

    fclose(fp);
    return 1; // CIN is unique
}


void sign_in_client() {
    Client client;
    FILE *fp = fopen("CLIENT.txt", "a");
    if (fp == NULL) {
        c_textattr(4); // Set text color to red
        c_gotoxy(32, 8);
        printf("The file does not exist or could not be opened!");
        c_textattr(14); // Reset text color
        return;
    }

    c_clrscr();
    c_textattr(14); // Set text color to yellow
    c_gotoxy(32, 6);
    printf("Create Your Account:");

    c_textattr(8); // Set text color to gray

    c_gotoxy(32, 8);
    printf("Enter your LAST NAME: ");
    scanf("%s", client.last_name);

    c_gotoxy(32, 10);
    printf("Enter your FIRST NAME: ");
    scanf("%s", client.First_name);

    // Validate CIN (Identification Number)
    while (1) {
        c_gotoxy(32, 12);
        printf("Enter your CIN: ");
        scanf("%s", client.CIN);

        if (is_CIN_unique(client.CIN)) {
            // Clear any previous error message
            c_gotoxy(32, 13);
            printf("                                                                          "); // Clear line
            break; // CIN is valid, exit loop
        } else {
            c_textattr(4); // Set text color to red
            c_gotoxy(32, 13);
            printf("Error: The CIN already exists or Invalid Format. Please try an other one.");
            c_textattr(14); // Reset text color
        }
    }

    // Validate Password
    while (1) {
        c_gotoxy(32, 14);
        printf("Enter the NEW PASSWORD: ");
        strcpy(client.password, Pass_hide(20));

        c_gotoxy(32, 15);
        printf("Confirm your PASSWORD: ");
        strcpy(client.confirm_password, Pass_hide(20));

        if (strcmp(client.password, client.confirm_password) == 0) {
            // Clear any previous error message
            c_gotoxy(32, 16);
            printf("                                                   "); // Clear line
            break; // Passwords match, exit loop
        } else {
            c_textattr(4); // Set text color to red
            c_gotoxy(32, 16);
            printf("Error: Passwords do not match. Please try again.");
            c_textattr(14); // Reset text color
            c_gotoxy(32, 14); // Clear password fields for retry
            printf("                                                   ");
            c_gotoxy(32, 15);
            printf("                                                   ");
        }
    }

    // Save the client information
    fprintf(fp, "%s %s %s %s\n", client.last_name, client.First_name, client.CIN, client.password);
    fclose(fp);

    // Success message
    c_textattr(2); // Set text color to green
    c_gotoxy(32, 18);
    printf("Information successfully added!");
    c_textattr(14); // Reset text color
}
// french version
void sign_in_client_f() {
    Client client;
    FILE *fp = fopen("CLIENT.txt", "a");
    if (fp == NULL) {
        c_textattr(4); // Set text color to red
        c_gotoxy(32, 8);
        printf("Le fichier n'existe pas ou n'a pas pu etre ouvert !");
        c_textattr(14); // Reset text color
        return;
    }

    c_clrscr();
    c_textattr(14); // Set text color to yellow
    c_gotoxy(32, 6);
    printf("Creez votre compte :");

    c_textattr(8); // Set text color to gray

    c_gotoxy(32, 8);
    printf("Entrez votre NOM : ");
    scanf("%s", client.last_name);

    c_gotoxy(32, 10);
    printf("Entrez votre PRENOM : ");
    scanf("%s", client.First_name);

    // Validate CIN (Identification Number)
    while (1) {
        c_gotoxy(32, 12);
        printf("Entrez votre CIN : ");
        scanf("%s", client.CIN);

        if (is_CIN_unique(client.CIN)) {
            // Clear any previous error message
            c_gotoxy(32, 13);
            printf("                                                                                      "); // Clear line
            break; // CIN is valid, exit loop
        } else {
            c_textattr(4); // Set text color to red
            c_gotoxy(32, 13);
            printf("Erreur : Le CIN existe deja ou le format est invalide. Veuillez en essayer un autre.");
            c_textattr(14); // Reset text color
        }
    }

    // Validate Password
    while (1) {
        c_gotoxy(32, 14);
        printf("Entrez le NOUVEAU MOT DE PASSE : ");
        strcpy(client.password, Pass_hide(20));

        c_gotoxy(32, 15);
        printf("Confirmez votre MOT DE PASSE : ");
        strcpy(client.confirm_password, Pass_hide(20));

        if (strcmp(client.password, client.confirm_password) == 0) {
            // Clear any previous error message
            c_gotoxy(32, 16);
            printf("                                                   "); // Clear line
            break; // Passwords match, exit loop
        } else {
            c_textattr(4); // Set text color to red
            c_gotoxy(32, 16);
            printf("Erreur : Les mots de passe ne correspondent pas. Veuillez reessayer.");
            c_textattr(14); // Reset text color
            c_gotoxy(32, 14); // Clear password fields for retry
            printf("                                                   ");
            c_gotoxy(32, 15);
            printf("                                                   ");
        }
    }

    // Save the client information
    fprintf(fp, "%s %s %s %s\n", client.last_name, client.First_name, client.CIN, client.password);
    fclose(fp);

    // Success message
    c_textattr(2); // Set text color to green
    c_gotoxy(32, 18);
    printf("Informations ajoutees avec succes !");
    c_textattr(14); // Reset text color
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

void clientLogin(char *CIN) {
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
    c_textattr(8);  // Set text color to gray

    // Use gotoxy to position the cursor inside the black box
    c_gotoxy(32, 8);  // Move cursor to row 5, column 5
    printf("Let's connect to your account:");
    c_textattr(14);  // Set text color to yellow
    c_gotoxy(32, 10); 
    printf("Enter your CIN: ");
    scanf("%s", CINN);

    c_gotoxy(32, 12);  // Move cursor to row 9, column 5 for password input prompt
    printf("Enter your PASSWORD: ");
    strcpy(passw, Pass_hide(20));  // Assuming Pass_hide is a function that hides password input
    passw[strlen(passw)] = '\0';   // Ensure null termination

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        c_textattr(4);  // Set text color to red for error
        c_gotoxy(32, 14);
        printf("Error: Could not open the file.");
        c_textattr(14);  // Reset text color to default
        return;
    }

    Client client;  // Assuming Client is a struct with fields: last_name, CIN, and password
    while (fscanf(fp, "%s %*s %s %s", client.last_name, client.CIN, client.password) == 3) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {
            c_textattr(2);  // Set text color to green for success
            strcpy(CIN, CINN);  // Store the CIN of the connected client in the global variable CIN
            c_gotoxy(54, 14);
            printf("Connected successfully!");
            c_textattr(14);  // Reset text color to default
            found = 1;
            c_getch();  // Wait for user input to proceed
            c_clrscr();  // Clear the screen

            // Display client's name with a decorative frame inside the box
            
            liste_client(CIN, client.last_name);  // Assuming liste_client is a function to display client details
            break;
        }
    }

    if (!found) {
        c_textattr(4);  // Set text color to red for error
        c_gotoxy(54, 14);
        printf("You need to create an account first!");
        c_textattr(14);  // Reset text color to default
    }

    fclose(fp);
    c_getch();  // Wait for user input before closing
}
// french version
void clientLogin_f(char *CIN) {
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
    c_textattr(8);  // Set text color to gray

    // Use gotoxy to position the cursor inside the black box
    c_gotoxy(32, 8);  // Move cursor to row 8, column 32 for title
    printf("Connectez-vous a votre compte:");

    c_textattr(14);  // Set text color to yellow
    c_gotoxy(32, 10);  // Move cursor to row 10, column 32 for CIN input prompt
    printf("Entrez votre CIN : ");
    scanf("%s", CINN);

    c_gotoxy(32, 12);  // Move cursor to row 12, column 32 for password input prompt
    printf("Entrez votre MOT DE PASSE : ");
    strcpy(passw, Pass_hide(20));  // Assuming Pass_hide is a function that hides password input
    passw[strlen(passw)] = '\0';   // Ensure null termination

    FILE *fp = fopen("CLIENT.txt", "r");
    if (fp == NULL) {
        c_textattr(4);  // Set text color to red for error
        c_gotoxy(54, 14);  // Move to row 14, column 32 for error message
        printf("Erreur : Impossible d'ouvrir le fichier.");
        c_textattr(14);  // Reset text color to default
        return;
    }

    Client client;  // Assuming Client is a struct with fields: last_name, CIN, and password
    while (fscanf(fp, "%s %*s %s %s", client.last_name, client.CIN, client.password) == 3) {
        if (strcmp(client.CIN, CINN) == 0 && strcmp(client.password, passw) == 0) {
            c_textattr(2);  // Set text color to green for success
            strcpy(CIN, CINN);  // Store the CIN of the connected client in the global variable CIN
            c_gotoxy(54, 14);  // Move to row 14, column 32 for success message
            printf("Connecte avec succes !");
            c_textattr(14);  // Reset text color to default
            found = 1;
            c_getch();  // Wait for user input to proceed
            c_clrscr();  // Clear the screen
            liste_client_f(CIN, client.last_name);  // Assuming liste_client_f is a function to display client details
            break;
        }
    }

    if (!found) {
        c_textattr(4);  // Set text color to red for error
        c_gotoxy(54, 14);  // Move to row 14, column 32 for error message
        printf("Vous devez d'abord creer un compte !");
        c_textattr(14);  // Reset text color to default
    }

    fclose(fp);
    c_getch();  // Wait for user input before closing
}

void View_Product_List() {
    c_clrscr(); // Clear the screen
    produit p;

    // Open the binary file "produit.dat" for reading
    FILE *fk = fopen("produit.dat", "rb");
    if (fk == NULL) {
        c_textattr(4); // Set text color to red
        printf("Error: The file does not exist or could not be opened!\n");
        return;
    }

    // Print the table header
    c_textattr(8); // Set text color to gray
    c_gotoxy(50, 4);
    printf("====== PRODUCT LIST ======");
    c_gotoxy(18, 8);
    printf(" %-10s %-20s %-20s %-10s %-10s %-30s", 
           "ID", "NAME", "CATEGORY", "PRICE", "QUANTITY", "DESCRIPTION");
    c_gotoxy(18, 10);
    printf("-----------------------------------------------------------------------------------------------------------");

    // Read and display each product
    c_textattr(14); // Set text color to yellow
    int row = 12; // Start displaying from row 12
    int productFound = 0; // To track if any products are found

    while (fread(&p, sizeof(produit), 1, fk) == 1) {
        c_gotoxy(18, row);
        printf("%-10d %-20s %-20s %-10.2f %-10d %-30s", 
               p.id_product, p.name, p.category, p.price, p.quantity, p.description);
        row++;
        productFound = 1; // Mark that at least one product was found
    }

    // If no products were found, print a message
    if (!productFound) {
        c_textattr(4); // Set text color to red
        printf("\nNo products found in the file.\n");
    }

    fclose(fk); // Close the file
    c_textattr(8); // Reset text color to gray
}
// french version
void View_Product_List_f() {
    c_clrscr(); // Clear the screen
    produit p;

    // Open the binary file "produit.dat" for reading
    FILE *fk = fopen("produit.dat", "rb");
    if (fk == NULL) {
        c_textattr(4); // Set text color to red
        printf("Erreur : Le fichier n'existe pas ou n'a pas pu être ouvert !\n");
        return;
    }

    // Print the table header
    c_textattr(8); // Set text color to gray
    c_gotoxy(50, 4);
    printf("====== LISTE DES PRODUITS ======");
    c_gotoxy(18, 8);
    printf(" %-10s %-20s %-20s %-10s %-10s %-30s", 
           "ID", "NOM", "CATeGORIE", "PRIX", "QUANTITe", "DESCRIPTION");
    c_gotoxy(18, 10);
    printf("-----------------------------------------------------------------------------------------------------------");

    // Read and display each product
    c_textattr(14); // Set text color to yellow
    int row = 12; // Start displaying from row 12
    int productFound = 0; // To track if any products are found

    while (fread(&p, sizeof(produit), 1, fk) == 1) {
        c_gotoxy(18, row);
        printf("%-10d %-20s %-20s %-10.2f %-10d %-30s", 
               p.id_product, p.name, p.category, p.price, p.quantity, p.description);
        row++;
        productFound = 1; // Mark that at least one product was found
    }

    // If no products were found, print a message
    if (!productFound) {
        c_textattr(4); // Set text color to red
        printf("\nAucun produit trouve dans le fichier.\n");
    }

    fclose(fk); // Close the file
    c_textattr(8); // Reset text color to gray
}

void Add_Purchases(char *CIN) {
    c_clrscr();
    produit l, p;           // 'l' for input product, 'p' for checking inventory
    Client client;
    char filename[100];
    strcpy(client.CIN, CIN);

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    // Open the product file for reading
    FILE *fk = fopen("produit.dat", "rb");
    if (fk == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("Error: Unable to open the product file!");
        c_textattr(8);
        return;
    }

    int found = 0;
    c_gotoxy(32, 8);
    printf("Enter PRODUCT ID: ");

    // Input validation for product ID
    while (scanf("%d", &l.id_product) != 1) {
        c_textattr(4);
        c_gotoxy(32, 9);
        printf("Invalid input! Please enter a valid product ID (integer): ");
        c_textattr(8);
        while (getchar() != '\n'); // Clear invalid input buffer
    }

    // Search for the product in the inventory file
    while (fread(&p, sizeof(produit), 1, fk) == 1) {
        if (p.id_product == l.id_product) {
            found = 1;
            break;
        }
    }
    fclose(fk);

    if (!found) {
        c_textattr(4);
        c_gotoxy(32, 10);
        printf("Error: Product ID %d not found in inventory!", l.id_product);
        c_textattr(8);
        c_clrscr();
        return;
    }

    // Check if the product's quantity is 0
    if (p.quantity == 0) {
        c_textattr(4);
        c_gotoxy(32, 11);
        printf("Error: Product ID %d is out of stock!", l.id_product);
        c_textattr(8);
        return;
    }

    // Input for quantity with validation
    c_gotoxy(32, 12);
    printf("Enter quantity (1 - %d): ", p.quantity);
    while (scanf("%d", &l.quantity) != 1 || l.quantity < 1 || l.quantity > p.quantity) {
        c_textattr(4);
        c_gotoxy(32, 13);
        printf("Invalid quantity! Enter a value between 1 and %d: ", p.quantity);
        c_textattr(8);
        while (getchar() != '\n'); // Clear invalid input buffer
    }

    // Open the user's cart file
    FILE *ff = fopen(filename, "r+");
    if (ff == NULL) {
        ff = fopen(filename, "w");  // Create the file if it doesn't exist
        if (ff == NULL) {
            c_textattr(4);
            c_gotoxy(32, 14);
            printf("Error: Unable to open or create the cart file!");
            c_textattr(8);
            c_clrscr();
            return;
        }
    }

    // Read existing cart contents and update if product already exists
    produit cart[100];
    int cartSize = 0;
    int exists = 0;

    while (fscanf(ff, "%d %d", &cart[cartSize].id_product, &cart[cartSize].quantity) == 2) {
        if (cart[cartSize].id_product == l.id_product) {
            int totalQuantity = cart[cartSize].quantity + l.quantity;
            if (totalQuantity > p.quantity) {
                c_textattr(4);
                c_gotoxy(32, 15);
                printf("Error: Total quantity (%d) exceeds available stock (%d)!", totalQuantity, p.quantity);
                c_textattr(8);
                fclose(ff);
                c_clrscr();
                return;
            }
            cart[cartSize].quantity = totalQuantity; // Update quantity
            exists = 1;
        }
        cartSize++;
    }

    // Add new product to the cart if it doesn't exist
    if (!exists) {
        cart[cartSize] = l;
        cartSize++;
    }

    // Rewrite the updated cart back to the file
    freopen(filename, "w", ff); // Reopen file in write mode
    for (int i = 0; i < cartSize; i++) {
        fprintf(ff, "%d %d\n", cart[i].id_product, cart[i].quantity);
    }

    c_textattr(2);
    c_gotoxy(32, 16);
    printf("Success: Product added to the cart!");
    c_textattr(14);

    fclose(ff);
}

// french version
void Add_Purchases_f(char *CIN) {
    c_clrscr();
    produit l, p;           // 'l' for input product, 'p' for checking inventory
    Client client;
    char filename[100];
    strcpy(client.CIN, CIN);

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    // Open the product file for reading
    FILE *fk = fopen("produit.dat", "rb");
    if (fk == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("Erreur : Impossible d'ouvrir le fichier des produits !");
        c_textattr(8);
        return;
    }

    int found = 0;
    c_gotoxy(32, 8);
    printf("Entrez l'ID du PRODUIT : ");

    // Input validation for product ID
    while (scanf("%d", &l.id_product) != 1) {
        c_textattr(4);
        c_gotoxy(32, 9);
        printf("Entree invalide ! Veuillez entrer un ID de produit valide (entier) : ");
        c_textattr(8);
        while (getchar() != '\n'); // Clear invalid input buffer
    }

    // Search for the product in the inventory file
    while (fread(&p, sizeof(produit), 1, fk) == 1) {
        if (p.id_product == l.id_product) {
            found = 1;
            break;
        }
    }
    fclose(fk);

    if (!found) {
        c_textattr(4);
        c_gotoxy(32, 10);
        printf("Erreur : L'ID du produit %d n'a pas ete trouve dans l'inventaire !", l.id_product);
        c_textattr(8);
        return;
    }

    // Input for quantity with validation
    c_gotoxy(32, 11);
    printf("Entrez la quantite (1 - %d) : ", p.quantity);
    while (scanf("%d", &l.quantity) != 1 || l.quantity < 1 || l.quantity > p.quantity) {
        c_textattr(4);
        c_gotoxy(32, 12);
        printf("Quantite invalide ! Entrez une valeur entre 1 et %d : ", p.quantity);
        c_textattr(8);
        while (getchar() != '\n'); // Clear invalid input buffer
    }

    // Open the user's cart file
    FILE *ff = fopen(filename, "r+");
    if (ff == NULL) {
        ff = fopen(filename, "w");  // Create the file if it doesn't exist
        if (ff == NULL) {
            c_textattr(4);
            c_gotoxy(32, 13);
            printf("Erreur : Impossible d'ouvrir ou de creer le fichier du panier !");
            c_textattr(8);
            c_clrscr();
            return;
        }
    }

    // Read existing cart contents and update if product already exists
    produit cart[100];
    int cartSize = 0;
    int exists = 0;

    while (fscanf(ff, "%d %d", &cart[cartSize].id_product, &cart[cartSize].quantity) == 2) {
        if (cart[cartSize].id_product == l.id_product) {
            int totalQuantity = cart[cartSize].quantity + l.quantity;
            if (totalQuantity > p.quantity) {
                c_textattr(4);
                c_gotoxy(32, 14);
                printf("Erreur : La quantite totale (%d) depasse le stock disponible (%d) !", totalQuantity, p.quantity);
                c_textattr(8);
                fclose(ff);
                c_clrscr();
                return;
            }
            cart[cartSize].quantity = totalQuantity; // Update quantity
            exists = 1;
        }
        cartSize++;
    }

    // Add new product to the cart if it doesn't exist
    if (!exists) {
        cart[cartSize] = l;
        cartSize++;
    }

    // Rewrite the updated cart back to the file
    freopen(filename, "w", ff); // Reopen file in write mode
    for (int i = 0; i < cartSize; i++) {
        fprintf(ff, "%d %d\n", cart[i].id_product, cart[i].quantity);
    }

    c_textattr(2);
    c_gotoxy(32, 15);
    printf("Succes : Produit ajoute au panier !");
    c_textattr(14);

    fclose(ff);
}

void View_Purchases(char *CIN) {
    c_clrscr();
    Client client;
    char filename[100];
    float total_price = 0.0;
    strcpy(client.CIN, CIN);

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("You have no purchases in your cart, or the cart file does not exist.");
        c_textattr(14);
        return;
    }

    c_gotoxy(52, 8);
    printf("===== YOUR PURCHASES =====");
    c_textattr(8);
    c_gotoxy(20, 10);
    printf("%-20s %-15s %-15s %-10s %-10s %-10s", 
           "Product ID", "Name", "Category", "Price", "Quantity", "Total Price");
    c_gotoxy(20, 11);
    printf("-------------------------------------------------------------------------------------------------");

    int found = 0;
    int id_product, quantity;
    int current_line = 12;

    while (fscanf(ff, "%d %d", &id_product, &quantity) == 2) {
        FILE *fk = fopen("produit.dat", "rb");
        if (fk == NULL) {
            c_textattr(4);
            c_gotoxy(20, current_line);
            printf("Error opening the product list file!");
            c_textattr(14);
            fclose(ff);
            return;
        }

        produit p;
        while (fread(&p, sizeof(produit), 1, fk) == 1) {
            if (p.id_product == id_product) {
                c_textattr(14);
                float item_total_price = p.price * quantity;
                c_gotoxy(20, current_line);
                printf("%-20d %-15s %-15s %-10.2f %-10d %-10.2f", 
                       p.id_product, p.name, p.category, p.price, quantity, item_total_price);
                total_price += item_total_price;
                found = 1;
                current_line++;
                break;
            }
        }
        fclose(fk);
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(20, current_line + 1);
        printf("Your cart is empty.");
        c_textattr(14);
    } else {
        c_gotoxy(20, current_line + 1);
        printf("-------------------------------------------------------------------------------------------------");
        c_gotoxy(20, current_line + 2);
        printf("%-20s %-15s %-15s %-10s %-10s %-10.2f", 
               "Total", "", "", "", "", total_price);
    }

    fclose(ff);
}
// french version
void View_Purchases_f(char *CIN) {
    c_clrscr();
    Client client;
    char filename[100];
    float total_price = 0.0;
    strcpy(client.CIN, CIN);

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *ff = fopen(filename, "r");
    if (ff == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("Vous n'avez aucun achat dans votre panier, ou le fichier du panier n'existe pas.");
        c_textattr(14);
        return;
    }

    c_gotoxy(52, 8);
    printf("===== VOS ACHATS =====");
    c_textattr(8);
    c_gotoxy(20, 10);
    printf("%-20s %-15s %-15s %-10s %-10s %-10s", 
           "ID Produit", "Nom", "Categorie", "Prix", "Quantite", "Prix Total");
    c_gotoxy(20, 11);
    printf("-------------------------------------------------------------------------------------------------");

    int found = 0;
    int id_product, quantity;
    int current_line = 12;

    while (fscanf(ff, "%d %d", &id_product, &quantity) == 2) {
        FILE *fk = fopen("produit.dat", "rb");
        if (fk == NULL) {
            c_textattr(4);
            c_gotoxy(20, current_line);
            printf("Erreur lors de l'ouverture du fichier des produits !");
            c_textattr(14);
            fclose(ff);
            return;
        }

        produit p;
        while (fread(&p, sizeof(produit), 1, fk) == 1) {
            if (p.id_product == id_product) {
                c_textattr(14);
                float item_total_price = p.price * quantity;
                c_gotoxy(20, current_line);
                printf("%-20d %-15s %-15s %-10.2f %-10d %-10.2f", 
                       p.id_product, p.name, p.category, p.price, quantity, item_total_price);
                total_price += item_total_price;
                found = 1;
                current_line++;
                break;
            }
        }
        fclose(fk);
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(20, current_line + 1);
        printf("Votre panier est vide.");
        c_textattr(14);
    } else {
        c_gotoxy(20, current_line + 1);
        printf("-------------------------------------------------------------------------------------------------");
        c_gotoxy(20, current_line + 2);
        printf("%-20s %-15s %-15s %-10s %-10s %-10.2f", 
               "Total", "", "", "", "", total_price);
    }

    fclose(ff);
}

void Remove_Purchases(char *CIN) {
    c_clrscr();
    char filename[100];
    int id_product_in_cart, quantity_in_cart;
    produit p;
    int found = 0;

    // Construct the filename based on CIN
    snprintf(filename, sizeof(filename), "%s_Cart.txt", CIN);

    // Open the cart file
    FILE *cartFile = fopen(filename, "r");
    if (cartFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("Your cart is empty or the cart file doesn't exist.\n");
        c_textattr(14);
        return;
    }

    // Display the header for the purchases
    c_gotoxy(50, 8);
    printf("===== YOUR CURRENT PURCHASES =====");
    c_gotoxy(32, 10);
    printf("%-10s %-20s %-15s %-10s %-10s %-20s", "ID", "Name", "Category", "Price", "Quantity", "Description");
    c_gotoxy(32, 11);
    printf("-----------------------------------------------------------------------------------------");

    // Iterate through the cart file
    while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        FILE *productFile = fopen("produit.dat", "rb");
        if (productFile == NULL) {
            c_textattr(4);
            c_gotoxy(32, 13);
            printf("Error opening product list file!\n");
            c_textattr(14);
            fclose(cartFile);
            return;
        }

        // Search for the product in produit.dat
        while (fread(&p, sizeof(produit), 1, productFile) == 1) {
            if (p.id_product == id_product_in_cart) {
                // Display the product information along with the quantity from the cart
                c_textattr(8);
                c_gotoxy(32, 12 + found); // Adjust position for each product
                printf("%-10d %-20s %-15s %-10.2f %-10d %-20s", 
                    p.id_product, p.name, p.category, p.price, quantity_in_cart, p.description);
                found = 1;
                break;
            }
        }
        fclose(productFile);
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(32, 16);
        printf("No products found in your cart.");
        c_textattr(14);
    }

    // Close the cart file
    fclose(cartFile);

    if (found) {
        c_textattr(2);
        c_gotoxy(32, 18);
        printf("End of cart display");
        c_textattr(14);
        c_getch();
    }
}

// french version
void Remove_Purchases_f(char *CIN) {
    c_clrscr();
    char filename[100];
    int id_product_in_cart, quantity_in_cart;
    produit p;
    int found = 0;

    // Construire le nom du fichier basé sur le CIN
    snprintf(filename, sizeof(filename), "%s_Cart.txt", CIN);

    // Ouvrir le fichier du panier
    FILE *cartFile = fopen(filename, "r");
    if (cartFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("Votre panier est vide ou le fichier du panier n'existe pas.\n");
        c_textattr(14);
        return;
    }

    // Afficher l'en-tête pour les achats
    c_gotoxy(50, 8);
    printf("===== VOS ACHATS ACTUELS =====");
    c_gotoxy(32, 10);
    printf("%-10s %-20s %-15s %-10s %-10s %-20s", "ID", "Nom", "Catégorie", "Prix", "Quantité", "Description");
    c_gotoxy(32, 11);
    printf("-----------------------------------------------------------------------------------------");

    // Parcourir le fichier du panier
    while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        FILE *productFile = fopen("produit.dat", "rb");
        if (productFile == NULL) {
            c_textattr(4);
            c_gotoxy(32, 13);
            printf("Erreur lors de l'ouverture du fichier de la liste des produits !\n");
            c_textattr(14);
            fclose(cartFile);
            return;
        }

        // Rechercher le produit dans produit.dat
        while (fread(&p, sizeof(produit), 1, productFile) == 1) {
            if (p.id_product == id_product_in_cart) {
                // Afficher les informations sur le produit avec la quantité du panier
                c_textattr(8);
                c_gotoxy(32, 12 + found); // Ajuster la position pour chaque produit
                printf("%-10d %-20s %-15s %-10.2f %-10d %-20s", 
                    p.id_product, p.name, p.category, p.price, quantity_in_cart, p.description);
                found = 1;
                break;
            }
        }
        fclose(productFile);
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(32, 16);
        printf("Aucun produit trouvé dans votre panier.");
        c_textattr(14);
    }

    // Fermer le fichier du panier
    fclose(cartFile);

    if (found) {
        c_textattr(2);
        c_gotoxy(32, 18);
        printf("Fin de l'affichage du panier");
        c_textattr(14);
        c_getch();
    }
}

void confirm_purchases(char *Temp_cin) {
    FILE *cartFile, *productFile;
    produit p;
    int id_product_in_cart, quantity_in_cart;
    char filename[100];
    int confirm_choice;

    // Construct the cart filename
    snprintf(filename, sizeof(filename), "%s_Cart.txt", Temp_cin);

    // Open the cart file
    cartFile = fopen(filename, "r");
    if (cartFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8); 
        printf("Your cart is empty or the cart file does not exist.\n");
        c_textattr(14);
        return;
    }

    // Ask for purchase confirmation using the menu
    Options options = { 
        .ops = (char *[]){"Yes", "No"},
        .len = 2,
        .title = "Do you want to confirm your purchase?"
    };

    int selection = c_select_menu_f(options);

    if (selection != 0) { // User selects "No"
        c_textattr(4);
        c_gotoxy(32, 10);
        printf("Purchase not confirmed.\n");
        c_textattr(14);
        fclose(cartFile);
        return;
    }

    // Open the product file
    productFile = fopen("produit.dat", "r+b");
    if (productFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 12);
        printf("Error opening the product file!\n");
        c_textattr(14);
        fclose(cartFile);
        return;
    }

    // Process each product in the cart
    while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        int found = 0;

        // Search for the product in produit.dat
        while (fread(&p, sizeof(produit), 1, productFile) == 1) {
            if (p.id_product == id_product_in_cart) {
                found = 1;

                // Check stock availability
                if (p.quantity >= quantity_in_cart) {
                    p.quantity -= quantity_in_cart;

                    // Move the file pointer to update the product
                    fseek(productFile, -sizeof(produit), SEEK_CUR);
                    fwrite(&p, sizeof(produit), 1, productFile);

                    c_textattr(2);
                    c_gotoxy(32, 14);
                    printf("Product ID %d updated. Remaining quantity: %d\n", p.id_product, p.quantity);
                    c_textattr(14);
                } else {
                    c_textattr(4);
                    c_gotoxy(32, 15);
                    printf("Error: Insufficient stock for product ID %d. Purchase canceled.\n", p.id_product);
                    c_textattr(14);

                    fclose(cartFile);
                    fclose(productFile);
                    return; // Exit cleanly
                }
                break;
            }
        }

        if (!found) {
            c_textattr(4);
            c_gotoxy(32, 16);
            printf("Product ID %d not found in the product list.\n", id_product_in_cart);
            c_textattr(14);
        }

        // Reset the file pointer to search for the next product
        rewind(productFile);
    }

    // Close the files
    fclose(cartFile);
    fclose(productFile);

    // Purchase confirmed, call client_factor function
    client_factor(Temp_cin);

    // Show loading spinner before the final message
    gradientSpinner(5); // Adjust duration for the spinner

    // Remove the cart file after confirmation
    char cart_file_name[100];
    snprintf(cart_file_name, sizeof(cart_file_name), "%s_Cart.txt", Temp_cin);
    if (remove(cart_file_name) == 0) {
        // Adding a delay using usleep (500000 microseconds = 0.5 seconds)
        usleep(500000);  // Sleep for 0.5 seconds before printing the message

        // Display success message
        c_textattr(2);
        c_gotoxy(32, 18);
        printf("Your factor is ready to print.\n");
    } else {
        c_textattr(4);
        c_gotoxy(32, 18);
        printf("Error removing the cart file.\n");
    }

    c_textattr(14);
    c_getch();
    c_clrscr();
}
// french version
void confirm_purchases_f(char *Temp_cin) {
    FILE *cartFile, *productFile;
    produit p;
    int id_product_in_cart, quantity_in_cart;
    char filename[100];
    int confirm_choice;

    // Construct the cart filename
    snprintf(filename, sizeof(filename), "%s_Cart.txt", Temp_cin);

    // Open the cart file
    cartFile = fopen(filename, "r");
    if (cartFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8); 
        printf("Votre panier est vide ou le fichier du panier n'existe pas.\n"); // Translated
        c_textattr(14);
        return;
    }

    // Ask for purchase confirmation using the menu
    Options options = { 
        .ops = (char *[]){"Oui", "Non"}, // Translated
        .len = 2,
        .title = "Voulez-vous confirmer votre achat ?" // Translated
    };

    int selection = c_select_menu_f(options);

    if (selection != 0) { // User selects "Non" // Translated
        c_textattr(4);
        c_gotoxy(32, 10);
        printf("Achat non confirme.\n"); // Translated
        c_textattr(14);
        fclose(cartFile);
        return;
    }

    // Open the product file
    productFile = fopen("produit.dat", "r+b");
    if (productFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 12);
        printf("Erreur d'ouverture du fichier produit !\n"); // Translated
        c_textattr(14);
        fclose(cartFile);
        return;
    }

    // Process each product in the cart
    while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        int found = 0;

        // Search for the product in produit.dat
        while (fread(&p, sizeof(produit), 1, productFile) == 1) {
            if (p.id_product == id_product_in_cart) {
                found = 1;

                // Check stock availability
                if (p.quantity >= quantity_in_cart) {
                    p.quantity -= quantity_in_cart;

                    // Move the file pointer to update the product
                    fseek(productFile, -sizeof(produit), SEEK_CUR);
                    fwrite(&p, sizeof(produit), 1, productFile);

                    c_textattr(2);
                    c_gotoxy(32, 14);
                    printf("Produit ID %d mis a jour. Quantite restante : %d\n", p.id_product, p.quantity); // Translated
                    c_textattr(14);
                } else {
                    c_textattr(4);
                    c_gotoxy(32, 15);
                    printf("Erreur : Stock insuffisant pour le produit ID %d. Achat annule.\n", p.id_product); // Translated
                    c_textattr(14);

                    fclose(cartFile);
                    fclose(productFile);
                    return; // Exit cleanly
                }
                break;
            }
        }

        if (!found) {
            c_textattr(4);
            c_gotoxy(32, 16);
            printf("Produit ID %d introuvable dans la liste des produits.\n", id_product_in_cart); // Translated
            c_textattr(14);
        }

        // Reset the file pointer to search for the next product
        rewind(productFile);
    }

    // Close the files
    fclose(cartFile);
    fclose(productFile);

    // Purchase confirmed, call client_factor function
    client_factor(Temp_cin);

    // Show loading spinner before the final message
    gradientSpinner(5); // Adjust duration for the spinner

    // Remove the cart file after confirmation
    char cart_file_name[100];
    snprintf(cart_file_name, sizeof(cart_file_name), "%s_Cart.txt", Temp_cin);
    if (remove(cart_file_name) == 0) {
        // Adding a delay using usleep (500000 microseconds = 0.5 seconds)
        usleep(500000);  // Sleep for 0.5 seconds before printing the message

        // Display success message
        c_textattr(2);
        c_gotoxy(32, 18);
        printf("Votre facture est prête a être imprimee.\n"); // Translated
    } else {
        c_textattr(4);
        c_gotoxy(32, 18);
        printf("Erreur lors de la suppression du fichier du panier.\n"); // Translated
    }

    c_textattr(14);
    c_getch();
    c_clrscr();
}



//----------------------------------------add product--------------------------------------

int get_next_product_id(FILE *fp) {
    produit temp;
    int last_id = 0;

    // Read all records to find the last product ID
    rewind(fp);
    while (fread(&temp, sizeof(produit), 1, fp) == 1) {
        last_id = temp.id_product;
    }
    return last_id + 1;
}


void add_product(char *CINF) {
    FILE *fp = fopen("produit.dat", "ab+");  // Open binary file in append mode
    if (fp == NULL) {
        perror("Error opening file"); // Provide detailed error message
        exit(EXIT_FAILURE);
    }

    int frame_width = 60;
    int frame_height = 15;
    int frame_x = 55;
    int frame_y = 11;

    c_clrscr();
    draw_frame(frame_width, frame_height, frame_x, frame_y);

    // Product structure
    produit p;
    p.id_product = get_next_product_id(fp);  // Generate next product ID

    // Input validation for Name
    do {
        c_textcolor(14);
        c_gotoxy(70, 14); 
        printf("Enter the product name: ");
        c_textcolor(8);
        c_gotoxy(94, 14);
        fflush(stdin); // Clear input buffer
        gets(p.name);
        if (strlen(p.name) == 0) {
            c_textcolor(12);
            c_gotoxy(70, 20); 
            printf("The name cannot be empty. Try again!");
            c_getch();
            draw_frame(frame_width, frame_height, frame_x, frame_y);
        } else break;
    } while (1);

    // Input validation for Category
    do {
        c_textcolor(14);
        c_gotoxy(70, 15); 
        printf("Enter the product category: ");
        c_textcolor(8);
        c_gotoxy(98, 15);
        fflush(stdin); // Clear input buffer
        gets(p.category);
        if (strlen(p.category) == 0) {
            c_textcolor(12);
            c_gotoxy(70, 21); 
            printf("The category cannot be empty. Try again!");
            c_getch();
            draw_frame(frame_width, frame_height, frame_x, frame_y);
        } else break;
    } while (1);

    // Input validation for Price and Quantity
    do {
        c_textcolor(14);
        c_gotoxy(70, 16); 
        printf("Enter the product price: ");
        c_textcolor(8);
        c_gotoxy(95, 16);
        if (scanf("%f", &p.price) != 1 || p.price <= 0) {
            p.price = 0;  // Reset price if invalid
        }

        c_textcolor(14);
        c_gotoxy(70, 17); 
        printf("Enter the product quantity: ");
        c_textcolor(8);
        c_gotoxy(98, 17);
        if (scanf("%d", &p.quantity) != 1 || p.quantity <= 0) {
            p.quantity = 0;  // Reset quantity if invalid
        }
        if (p.price <= 0 || p.quantity <= 0) {
            c_textcolor(12);
            c_gotoxy(70, 21); 
            printf("Price and quantity must be > 0. Try again!");
            c_getch();
            draw_frame(frame_width, frame_height, frame_x, frame_y);
        } else {
            break;
        }
    } while (1);

    // Product description (optional, can be empty)
    c_textcolor(14);
    c_gotoxy(70, 18); 
    printf("Enter the product description: ");
    c_textcolor(8);
    c_gotoxy(101, 18);
    fflush(stdin); // Clear input buffer
    gets(p.description);
    if (strlen(p.description) == 0) {
        p.description[0] = '\0';  // Default to empty if invalid
    }

    // Set CINF
    strncpy(p.CINF, CINF, sizeof(p.CINF) - 1);
    p.CINF[sizeof(p.CINF) - 1] = '\0';  // Ensure null termination

    // Show the gradient spinner during product addition process
    gradientSpinner_s(50);  // Call spinner with 50ms duration (speed adjust as needed)

    // Write product details to the binary file
    size_t write_count = fwrite(&p, sizeof(produit), 1, fp);
    if (write_count != 1) {
        c_textcolor(12);
        c_gotoxy(70, 21); 
        printf("Failed to write product data to file!");
        c_getch();
    }

    fclose(fp);
    // Confirmation message
    c_textcolor(2);
    c_gotoxy(70, 20); 
    printf("Product added successfully!");
    c_textcolor(15);
}
// french version
void add_product_f(char *CINF) {
    FILE *fp = fopen("produit.dat", "ab+");  // Open binary file in append mode
    if (fp == NULL) {
        perror("Erreur d'ouverture du fichier"); // Provide detailed error message
        exit(EXIT_FAILURE);
    }

    int frame_width = 60;
    int frame_height = 15;
    int frame_x = 55;
    int frame_y = 11;

    c_clrscr();
    draw_frame(frame_width, frame_height, frame_x, frame_y);

    // Product structure
    produit p;
    p.id_product = get_next_product_id(fp);  // Generate next product ID

    // Input validation for Name
    do {
        c_textcolor(14);
        c_gotoxy(70, 14); 
        printf("Entrez le nom du produit : ");
        c_textcolor(8);
        c_gotoxy(94, 14);
        fflush(stdin); // Clear input buffer
        gets(p.name);
        if (strlen(p.name) == 0) {
            c_textcolor(12);
            c_gotoxy(70, 20); 
            printf("Le nom ne peut pas etre vide. Reessayez !");
            c_getch();
            draw_frame(frame_width, frame_height, frame_x, frame_y);
        } else break;
    } while (1);

    // Input validation for Category
    do {
        c_textcolor(14);
        c_gotoxy(70, 15); 
        printf("Entrez la categorie du produit : ");
        c_textcolor(8);
        c_gotoxy(98, 15);
        fflush(stdin); // Clear input buffer
        gets(p.category);
        if (strlen(p.category) == 0) {
            c_textcolor(12);
            c_gotoxy(70, 21); 
            printf("La categorie ne peut pas etre vide. Reessayez !");
            c_getch();
            draw_frame(frame_width, frame_height, frame_x, frame_y);
        } else break;
    } while (1);

    // Input validation for Price and Quantity
    do {
        c_textcolor(14);
        c_gotoxy(70, 16); 
        printf("Entrez le prix du produit : ");
        c_textcolor(8);
        c_gotoxy(95, 16);
        if (scanf("%f", &p.price) != 1 || p.price <= 0) {
            p.price = 0;  // Reset price if invalid
        }

        c_textcolor(14);
        c_gotoxy(70, 17); 
        printf("Entrez la quantite du produit : ");
        c_textcolor(8);
        c_gotoxy(98, 17);
        if (scanf("%d", &p.quantity) != 1 || p.quantity <= 0) {
            p.quantity = 0;  // Reset quantity if invalid
        }
        if (p.price <= 0 || p.quantity <= 0) {
            c_textcolor(12);
            c_gotoxy(70, 21); 
            printf("Le prix et la quantite doivent etre > 0. Reessayez !");
            c_getch();
            draw_frame(frame_width, frame_height, frame_x, frame_y);
        } else {
            break;
        }
    } while (1);

    // Product description (optional, can be empty)
    c_textcolor(14);
    c_gotoxy(70, 18); 
    printf("Entrez la description du produit : ");
    c_textcolor(8);
    c_gotoxy(101, 18);
    fflush(stdin); // Clear input buffer
    gets(p.description);
    if (strlen(p.description) == 0) {
        p.description[0] = '\0';  // Default to empty if invalid
    }

    // Set CINF
    strncpy(p.CINF, CINF, sizeof(p.CINF) - 1);
    p.CINF[sizeof(p.CINF) - 1] = '\0';  // Ensure null termination

    // Show the gradient spinner during product addition process
    gradientSpinner_s_f(50);  // Call spinner with 50ms duration (speed adjust as needed)

    // Write product details to the binary file
    size_t write_count = fwrite(&p, sizeof(produit), 1, fp);
    if (write_count != 1) {
        c_textcolor(12);
        c_gotoxy(70, 21); 
        printf("echec de l'enregistrement des donnees du produit dans le fichier !");
        c_getch();
    }

    fclose(fp);

    // Confirmation message
    c_textcolor(2);
    c_gotoxy(70, 20); 
    printf("Produit ajoute avec succes !");
    c_textcolor(15);
}
//----------------------------------------delete product--------------------------------------

void delete_product(char *CINF) {
    FILE *fp, *temp;
    fp = fopen("produit.dat", "rb");
    temp = fopen("temp.dat", "wb");
    int id, tr = 0;

    if (fp == NULL || temp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    c_clrscr();
    c_textcolor(1);
    c_gotoxy(30, 3);
    printf("Enter the product ID to delete: ");
    scanf("%d", &id);
    c_textcolor(15);

    produit p;
    int product_count = 0;
    while (fread(&p, sizeof(produit), 1, fp)) {
        if (p.id_product == id && strcmp(p.CINF, CINF) == 0) {
            tr = 1; // Mark as found if ID and supplier match
        } else {
            fwrite(&p, sizeof(produit), 1, temp);
            product_count++;
        }
    }
    fclose(fp);
    fclose(temp);

    if (tr == 0) {
        c_gotoxy(30, 5);
        c_textcolor(4);
        printf("\nWarning: The product does not exist or does not belong to the specified supplier!\n");
        c_textcolor(15);
    } else {
        // Reorder IDs for remaining products
        fp = fopen("produit.dat", "wb");
        temp = fopen("temp.dat", "rb");
        int new_id = 1;

        while (fread(&p, sizeof(produit), 1, temp)) {
            p.id_product = new_id++; // Update the ID to maintain order
            fwrite(&p, sizeof(produit), 1, fp);
            usleep(100000); // Pause to switch right and left visually
        }

        fclose(fp);
        fclose(temp);

        remove("temp.dat");

        c_gotoxy(30, 5);
        c_textcolor(2);
        printf("\nThe product has been successfully deleted and IDs have been reordered!\n");
        c_textcolor(15);
    }
}

// french version
void delete_product_f(char *CINF) {
    FILE *fp, *temp;
    fp = fopen("produit.dat", "rb");
    temp = fopen("temp.dat", "wb");
    int id, tr = 0;

    if (fp == NULL || temp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    c_clrscr();
    c_textcolor(1);
    c_gotoxy(30, 3);
    printf("Entrez l'ID du produit a supprimer : ");
    scanf("%d", &id);
    c_textcolor(15);

    produit p;
    int product_count = 0;
    while (fread(&p, sizeof(produit), 1, fp)) {
        if (p.id_product == id && strcmp(p.CINF, CINF) == 0) {
            tr = 1; // Marquer comme trouve si l'ID et le fournisseur correspondent
        } else {
            fwrite(&p, sizeof(produit), 1, temp);
            product_count++;
        }
    }
    fclose(fp);
    fclose(temp);

    if (tr == 0) {
        c_gotoxy(30, 5);
        c_textcolor(4);
        printf("\nAttention : Le produit n'existe pas ou n'appartient pas au fournisseur specifie !\n");
        c_textcolor(15);
    } else {
        // Reorganiser les IDs des produits restants
        fp = fopen("produit.dat", "wb");
        temp = fopen("temp.dat", "rb");
        int new_id = 1;

        while (fread(&p, sizeof(produit), 1, temp)) {
            p.id_product = new_id++; // Mettre a jour l'ID pour maintenir l'ordre
            fwrite(&p, sizeof(produit), 1, fp);
            usleep(100000); // Pause pour l'effet visuel de basculement
        }

        fclose(fp);
        fclose(temp);

        remove("temp.dat");

        c_gotoxy(30, 5);
        c_textcolor(2);
        printf("\nLe produit a ete supprime avec succes et les IDs ont ete reorganises !\n");
        c_textcolor(15);
    }
}


//----------------------------------------modify product--------------------------------------

void modify_product(char *CINF) {
    FILE *fp, *temp;
    fp = fopen("produit.dat", "rb+"); // Open binary file for read/write
    temp = fopen("temp.dat", "wb");   // Temporary file to store modifications

    if (fp == NULL || temp == NULL) {
        c_textcolor(4); // Set text color to red
        printf("Unable to open the file!\n");
        exit(1);
    }

    int id, choice;
    int productFound = 0;
    produit p, pn; // Product structures
    int frame_width = 60, frame_height = 15, frame_x = 55, frame_y = 11;

    c_clrscr();
    draw_frame(frame_width, frame_height, frame_x, frame_y); // Draw the frame for UI

    // Ask user for product ID to modify
    c_textcolor(1);
    c_gotoxy(70, 14);
    printf("Enter the product ID to modify: ");
    scanf("%d", &id);
    c_textcolor(15);

    // Search for the product to modify (filter by CINF)
    while (fread(&p, sizeof(produit), 1, fp) == 1) {
        if (p.id_product == id && strcmp(p.CINF, CINF) == 0) {
            productFound = 1;
            c_clrscr();
            draw_frame(frame_width, frame_height, frame_x, frame_y); // Redraw frame

            // Display modification options
            c_textcolor(1);
            Options options;
            char *modify_options[] = {
                "Modify Name",
                "Modify Category",
                "Modify Price",
                "Modify Quantity",
                "Modify Description",
                "Back"
            };
            options.ops = modify_options;
            options.len = sizeof(modify_options) / sizeof(modify_options[0]);
            options.title = "================== Modify Product ==================";

            int selected = c_select_menu_f(options);

            // Switch to modify the appropriate field
            c_clrscr();
            draw_frame(frame_width, frame_height, frame_x, frame_y); // Redraw frame

            switch (selected) {
                case 0:  // Modify Name
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Enter the new name: ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    fflush(stdin);
                    gets(pn.name);
                    strcpy(p.name, pn.name);
                    break;

                case 1:  // Modify Category
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Enter the new category: ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    fflush(stdin);
                    gets(pn.category);
                    strcpy(p.category, pn.category);
                    break;

                case 2:  // Modify Price
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Enter the new price: ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    scanf("%f", &pn.price);
                    p.price = pn.price;
                    break;

                case 3:  // Modify Quantity
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Enter the new quantity: ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    scanf("%d", &pn.quantity);
                    p.quantity = pn.quantity;
                    break;

                case 4:  // Modify Description
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Enter the new description: ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    fflush(stdin);
                    gets(pn.description);
                    strcpy(p.description, pn.description);
                    break;

                case 5:  // Back
                    fclose(fp);
                    fclose(temp);
                    return; // Exit the modify function
            }
        }

        // Write the (modified or unchanged) product back to the temp file
        fwrite(&p, sizeof(produit), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (!productFound) {
        c_textcolor(4);
        c_gotoxy(70, 20);
        printf("The product does not exist or is not associated with this supplier.");
    } else {
        remove("produit.dat");
        rename("temp.dat", "produit.dat");
        c_textcolor(2);
        c_gotoxy(70, 20);
        printf("Product successfully modified.");
    }

    c_textcolor(15);
}
// french version
void modify_product_f(char *CINF) {
    FILE *fp, *temp;
    fp = fopen("produit.dat", "rb+"); // Open binary file for read/write
    temp = fopen("temp.dat", "wb");   // Temporary file to store modifications

    if (fp == NULL || temp == NULL) {
        c_textcolor(4); // Set text color to red
        printf("Impossible d'ouvrir le fichier !\n");
        exit(1);
    }

    int id, choice;
    int productFound = 0;
    produit p, pn; // Product structures
    int frame_width = 60, frame_height = 15, frame_x = 55, frame_y = 11;

    c_clrscr();
    draw_frame(frame_width, frame_height, frame_x, frame_y); // Draw the frame for UI

    // Ask user for product ID to modify
    c_textcolor(1);
    c_gotoxy(70, 14);
    printf("Entrez l'ID du produit a modifier : ");
    scanf("%d", &id);
    c_textcolor(15);

    // Search for the product to modify (filter by CINF)
    while (fread(&p, sizeof(produit), 1, fp) == 1) {
        if (p.id_product == id && strcmp(p.CINF, CINF) == 0) {
            productFound = 1;
            c_clrscr();
            draw_frame(frame_width, frame_height, frame_x, frame_y); // Redraw frame

            // Display modification options
            c_textcolor(1);
            Options options;
            char *modify_options[] = {
                "Modifier le nom",
                "Modifier la categorie",
                "Modifier le prix",
                "Modifier la quantite",
                "Modifier la description",
                "Retour"
            };
            options.ops = modify_options;
            options.len = sizeof(modify_options) / sizeof(modify_options[0]);
            options.title = "================== Modifier le produit ==================";

            int selected = c_select_menu_f(options);

            // Switch to modify the appropriate field
            c_clrscr();
            draw_frame(frame_width, frame_height, frame_x, frame_y); // Redraw frame

            switch (selected) {
                case 0:  // Modify Name
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Entrez le nouveau nom : ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    fflush(stdin);
                    gets(pn.name);
                    strcpy(p.name, pn.name);
                    break;

                case 1:  // Modify Category
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Entrez la nouvelle categorie : ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    fflush(stdin);
                    gets(pn.category);
                    strcpy(p.category, pn.category);
                    break;

                case 2:  // Modify Price
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Entrez le nouveau prix : ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    scanf("%f", &pn.price);
                    p.price = pn.price;
                    break;

                case 3:  // Modify Quantity
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Entrez la nouvelle quantite : ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    scanf("%d", &pn.quantity);
                    p.quantity = pn.quantity;
                    break;

                case 4:  // Modify Description
                    c_textcolor(14);
                    c_gotoxy(70, 14);
                    printf("Entrez la nouvelle description : ");
                    c_textcolor(8);
                    c_gotoxy(94, 14);
                    fflush(stdin);
                    gets(pn.description);
                    strcpy(p.description, pn.description);
                    break;

                case 5:  // Back
                    fclose(fp);
                    fclose(temp);
                    return; // Exit the modify function
            }
        }

        // Write the (modified or unchanged) product back to the temp file
        fwrite(&p, sizeof(produit), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (!productFound) {
        c_textcolor(4);
        c_gotoxy(70, 20);
        printf("Le produit n'existe pas ou n'est pas associe a ce fournisseur.");
    } else {
        remove("produit.dat");
        rename("temp.dat", "produit.dat");
        c_textcolor(2);
        c_gotoxy(70, 20);
        printf("Produit modifie avec succes.");
    }

    c_textcolor(15);
}

void gradientSpinner_s(int duration) {
    char spinner[] = "|/-\\";
    int spinnerIndex = 0;
    c_textcolor(2);
    c_gotoxy(70 , 6);("Back...");
    int j = 1 ;
    for (int i = 0; i < 100; i++) {
        c_textcolor(j);
        c_gotoxy(70 , 7);printf("Loding... %c %d%%", spinner[spinnerIndex], i + 1);
        fflush(stdout);
        spinnerIndex = (spinnerIndex + 1) % 4;
        usleep(duration * 100); // Ajuster la vitesse
        j++;
        if(j == 10 ) j = 1 ;
    }
    c_textcolor(2);
    c_gotoxy(70 , 8);printf("Done!");
}
void add_supplier() {
    FILE *fp;
    fp = fopen("fournisseur.txt", "a+");
    if (fp == NULL) {
        printf("Unable to open the file\n");
        exit(1);
    }

    fournisseur frn;
    char ch;
    int i = 0, j = 0, l = 0;

    c_textcolor(1);
    c_gotoxy(50, 27);
    c_textcolor(14);
    printf("First Name   : ");
    c_textcolor(8);
    c_gotoxy(64, 27);
    scanf(" %[^\n]s", frn.prenomf);
    c_gotoxy(50, 28);
    c_textcolor(14);
    printf("Last Name    : ");
    c_textcolor(8);
    c_gotoxy(64, 28);
    scanf(" %[^\n]s", frn.nomf);

    do {
        c_gotoxy(50, 29 + j);
        c_textcolor(14);
        printf("CIN          : ");
        c_textcolor(8);
        c_gotoxy(64, 29 + j);
        scanf(" %s", frn.Cinf);

        if (is_CIN_unique_supplier(frn.Cinf) == 0) {
            c_gotoxy(50, 32 + i - 2);
            c_textcolor(4);
            printf("Warning, the CIN is already in use!\n");
            c_getch();
            c_textcolor(15);
            i += 4;
            j += 2;
            l++;
            if (l == 2) break;
        } else {
            do {
                c_gotoxy(50, 31 + i);
                c_textcolor(14);
                printf("Enter the password : ");
                c_textcolor(8);
                strcpy(frn.mdpf, Pass_hide(20));

                c_gotoxy(50, 32 + i);
                c_textcolor(14);
                printf("Confirm the password : ");
                c_textcolor(8);
                strcpy(frn.cmdpf, Pass_hide(20));

                if (strcmp(frn.mdpf, frn.cmdpf) != 0) {
                    c_gotoxy(50, 33 + i);
                    c_textcolor(4);
                    printf("Passwords do not match! Please try again.");
                    c_getch();
                    i += 2;
                } else {
                    fprintf(fp, "%s %s %s %s\n", frn.prenomf, frn.nomf, frn.Cinf, frn.mdpf);
                    break;
                }
            } while (1);
            break;
        }
    } while (1);

    if (l != 2) {
        fclose(fp);
        c_textcolor(15);
        c_textcolor(2);
        c_gotoxy(50, 34 + i);
        printf("Supplier successfully added!!");
        gradientSpinner_s(20);
        c_textcolor(15);
        c_getch();
    }
}
// french version
void gradientSpinner_s_f(int duration) {
    char spinner[] = "|/-\\";
    int spinnerIndex = 0;
    c_textcolor(2);
    c_gotoxy(70 , 6);("Retour...");
    int j = 1 ;
    for (int i = 0; i < 100; i++) {
        c_textcolor(j);
        c_gotoxy(70 , 7);printf("Chargement... %c %d%%", spinner[spinnerIndex], i + 1);
        fflush(stdout);
        spinnerIndex = (spinnerIndex + 1) % 4;
        usleep(duration * 100); // Ajuster la vitesse
        j++;
        if(j == 10 ) j = 1 ;
    }
    c_textcolor(2);
    c_gotoxy(70 , 8);printf("Termine!");
}

void add_supplier_f() {
    FILE *fp;
    fp = fopen("fournisseur.txt", "a+");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }

    fournisseur frn;
    char ch;
    int i = 0, j = 0, l = 0;

    c_textcolor(1);
    c_gotoxy(50, 27);
    c_textcolor(14);
    printf("Prenom      : ");
    c_textcolor(8);
    c_gotoxy(64, 27);
    scanf(" %[^\n]s", frn.prenomf);
    c_gotoxy(50, 28);
    c_textcolor(14);
    printf("Nom         : ");
    c_textcolor(8);
    c_gotoxy(64, 28);
    scanf(" %[^\n]s", frn.nomf);

    do {
        c_gotoxy(50, 29 + j);
        c_textcolor(14);
        printf("CIN         : ");
        c_textcolor(8);
        c_gotoxy(64, 29 + j);
        scanf(" %s", frn.Cinf);

        if (is_CIN_unique_supplier(frn.Cinf) == 0) {
            c_gotoxy(50, 32 + i - 2);
            c_textcolor(4);
            printf("Attention, le CIN est deja utilise!\n");
            c_getch();
            c_textcolor(15);
            i += 4;
            j += 2;
            l++;
            if (l == 2) break;
        } else {
            do {
                c_gotoxy(50, 31 + i);
                c_textcolor(14);
                printf("Entrez le mot de passe : ");
                c_textcolor(8);
                strcpy(frn.mdpf, Pass_hide(20));

                c_gotoxy(50, 32 + i);
                c_textcolor(14);
                printf("Confirmez le mot de passe : ");
                c_textcolor(8);
                strcpy(frn.cmdpf, Pass_hide(20));

                if (strcmp(frn.mdpf, frn.cmdpf) != 0) {
                    c_gotoxy(50, 33 + i);
                    c_textcolor(4);
                    printf("Les mots de passe ne correspondent pas! Reessayez.");
                    c_getch();
                    i += 2;
                } else {
                    fprintf(fp, "%s %s %s %s\n", frn.prenomf, frn.nomf, frn.Cinf, frn.mdpf);
                    break;
                }
            } while (1);
            break;
        }
    } while (1);

    if (l != 2) {
        fclose(fp);
        c_textcolor(15);
        c_textcolor(2);
        c_gotoxy(50, 34 + i);
        printf("Fournisseur ajoute avec succes!!");
        gradientSpinner_s_f(20);
        c_textcolor(15);
        c_getch();
    }
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

void liste_fournisseur(char *Temp_CIN) {
    int choice;
    do {
        c_textcolor(14);
        c_clrscr();
        c_gotoxy(32, 3);  printf("---------------------------------------------------------------------------------------------------");
        c_gotoxy(32, 5);  printf("------------------------------------------ Supplier Menu ------------------------------------------");
        c_gotoxy(32, 7);  printf("---------------------------------------------------------------------------------------------------");
        c_textcolor(8);
        c_gotoxy(64, 14); printf("1. Add Product");
        c_gotoxy(64, 15); printf("2. Modify Product");
        c_gotoxy(64, 16); printf("3. View Product List");
        c_gotoxy(64, 17); printf("4. Display the Supplier's Total Sales for the Day");
        c_gotoxy(64, 18); printf("5. Delete Product");
        c_gotoxy(64, 19); printf("6. Exit");
        c_textcolor(14);
        c_gotoxy(32, 28); printf("------------------------------------------ Supplier CIN: %s -----------------------------------------", Temp_CIN);
        c_gotoxy(64, 21); printf("Enter your choice: ");
        c_textcolor(8);
        c_gotoxy(83, 21); scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_product(Temp_CIN);
                break;

            case 2:
                modify_product(Temp_CIN);
                break;

            case 3:
                view_product_supplier(Temp_CIN);
                break;

            case 4:
                Display_the_Supplier_Total_amount_sales_in_the_Day(Temp_CIN);
                break;

            case 5:
                delete_product(Temp_CIN);
                break;

            case 6:
                c_textcolor(1);
                c_gotoxy(64, 22);
                printf("Returning to main menu...");
                c_getch();
                Home_LOGIN_menu();
                break;

            default:
                c_textcolor(4);
                c_gotoxy(64, 23);
                printf("Invalid choice. Please try again.");
                c_getch();
                break;
        }

        if (choice != 6) {
            c_textcolor(1);
            c_gotoxy(64, 24);
            printf("Press any key to continue...");
            c_getch();
            c_clrscr();
        }

    } while (choice != 6);
}
// french version
void liste_fournisseur_f(char *Temp_CIN) {
    int choice;
    do {
        c_textcolor(14);
        c_clrscr();
        c_gotoxy(32, 3);  
        printf("---------------------------------------------------------------------------------------------------");
        c_gotoxy(32, 5);  
        printf("------------------------------------------ Menu Fournisseur ------------------------------------------");
        c_gotoxy(32, 7);  
        printf("---------------------------------------------------------------------------------------------------");
        c_textcolor(8);
        c_gotoxy(64, 14); 
        printf("1. Ajouter un produit");
        c_gotoxy(64, 15); 
        printf("2. Modifier un produit");
        c_gotoxy(64, 16); 
        printf("3. Voir la liste des produits");
        c_gotoxy(64, 17); 
        printf("4. Afficher les ventes totales du fournisseur pour la journee");
        c_gotoxy(64, 18); 
        printf("5. Supprimer un produit");
        c_gotoxy(64, 19); 
        printf("6. Quitter");
        c_textcolor(14);
        c_gotoxy(32, 28); 
        printf("------------------------------------------ CIN Fournisseur: %s ----------------------------------------", Temp_CIN);
        c_gotoxy(64, 21); 
        printf("Entrez votre choix : ");
        c_textcolor(8);
        c_gotoxy(83, 21); 
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_product_f(Temp_CIN);
                break;

            case 2:
                modify_product_f(Temp_CIN);
                break;

            case 3:
                view_product_supplier_f(Temp_CIN);
                break;

            case 4:
                Display_the_Supplier_Total_amount_sales_in_the_Day_f(Temp_CIN);
                break;

            case 5:
                delete_product_f(Temp_CIN);
                break;

            case 6:
                c_textcolor(1);
                c_gotoxy(64, 22);
                printf("Retour au menu principal...");
                c_getch();
                Home_LOGIN_menu();
                break;

            default:
                c_textcolor(4);
                c_gotoxy(64, 23);
                printf("Choix invalide. Veuillez reessayer.");
                c_getch();
                break;
        }

        if (choice != 6) {
            c_textcolor(1);
            c_gotoxy(64, 24);
            printf("Appuyez sur une touche pour continuer...");
            c_getch();
            c_clrscr();
        }

    } while (choice != 6);
}

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
            printf("\nConnexion reussie !\n");
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

void client_factor(char *CIN) {
    FILE *FACT = fopen("FACTEUR.pdf", "w");
    if (FACT == NULL) {
        printf("Error: Unable to create FACTEUR.pdf file!\n");
        exit(1);
    }
    
    CCD client_details;
    int found = 0;

    // Read credit card details from CREDIT_CARD.dat
    FILE *CDM = fopen("CREDIT_CARD.dat", "rb");
    if (CDM == NULL) {
        printf("Error: Unable to open CREDIT_CARD.dat!\n");
        exit(1);
    }
    while (fread(&client_details, sizeof(CCD), 1, CDM) == 1) {
        if (strcmp(client_details.client_CIN, CIN) == 0) {
            found = 1;
            break;
        }
    }
    fclose(CDM);

    if (!found) {
        fprintf(FACT, "Error: Client with CIN %s not found in credit card database!\n", CIN);
        fclose(FACT);
        return;
    }

    // Mask credit card number
    char hidden_card_number[50];
    snprintf(hidden_card_number, sizeof(hidden_card_number), "%.4s ** ** %.4s", 
             client_details.card_number, 
             client_details.card_number + strlen(client_details.card_number) - 4);

    // Write Client Information and Date to FACTEUR
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

    // Dynamically create the file name based on CIN
    char client_choice_filename[100];
    snprintf(client_choice_filename, sizeof(client_choice_filename), "%s_Cart.txt", CIN);

    // Open the dynamically generated file
    FILE *client_choice_file = fopen(client_choice_filename, "r");
    if (client_choice_file == NULL) {
        printf("Error: Unable to open %s_Cart.txt!\n", CIN);
        exit(1);
    }

    // Step 4: Process Client's Choices and Calculate Total Cost
    clc client_choice_entry;
    float grand_total = 0.0;
    while (fscanf(client_choice_file, "%d %d", &client_choice_entry.id_product_clien, &client_choice_entry.quantity) == 2) {
        
        produit product;
        int product_found = 0;

        // Read product details from produit.dat
        FILE *produit_file = fopen("produit.dat", "rb");
        if (produit_file == NULL) {
            printf("Error: Unable to open produit.dat!\n");
            exit(1);
        }

        // Search for the product based on ID
        while (fread(&product, sizeof(produit), 1, produit_file) == 1) {
            if (product.id_product == client_choice_entry.id_product_clien) {
                product_found = 1;
                break;
            }
        }
        fclose(produit_file);

        if (product_found) {
            if (client_choice_entry.quantity <= product.quantity) {
                float total_price = product.price * client_choice_entry.quantity;
                grand_total += total_price;
                fprintf(FACT, "(| %-15s | %-10d | %-10.2f DH |) Tj\n0 -20 Td\n", product.name, client_choice_entry.quantity, total_price);
            } else {
                fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", product.name, client_choice_entry.quantity, "Out of Stock");
            }
        } else {
            fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", "Product Not Found", client_choice_entry.quantity, "Not Found");
        }
    }
    fclose(client_choice_file);

    // Step 5: Print Grand Total and Close FACTEUR File
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Grand Total: %.2f DH) Tj\n0 -20 Td\n", grand_total);
    fprintf(FACT, "(=============================================) Tj\n");
    fprintf(FACT, pdf_footer);
    fclose(FACT);
}

// french version
void client_factor_f(char *CIN) {
    FILE *FACT = fopen("FACTEUR.pdf", "w");
    if (FACT == NULL) {
        printf("Erreur : Impossible de creer le fichier FACTEUR.pdf !\n");
        exit(1);
    }
    
    CCD client_details;
    int found = 0;

    // Lire les details de la carte de credit depuis CREDIT_CARD.dat
    FILE *CDM = fopen("CREDIT_CARD.dat", "rb");
    if (CDM == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier CREDIT_CARD.dat !\n");
        exit(1);
    }
    while (fread(&client_details, sizeof(CCD), 1, CDM) == 1) {
        if (strcmp(client_details.client_CIN, CIN) == 0) {
            found = 1;
            break;
        }
    }
    fclose(CDM);

    if (!found) {
        fprintf(FACT, "Erreur : Client avec CIN %s non trouve dans la base de donnees des cartes de credit !\n", CIN);
        fclose(FACT);
        return;
    }

    // Masquer le numero de carte de credit
    char hidden_card_number[50];
    snprintf(hidden_card_number, sizeof(hidden_card_number), "%.4s ** ** %.4s", 
             client_details.card_number, 
             client_details.card_number + strlen(client_details.card_number) - 4);

    // ecrire les informations du client et la date dans FACTEUR
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
    fprintf(FACT, "(| Produit         | Quantite   | Prix total   |) Tj\n0 -20 Td");
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td");

    // Dynamically create the file name based on CIN
    char client_choice_filename[100];
    snprintf(client_choice_filename, sizeof(client_choice_filename), "%s_Cart.txt", CIN);

    // Open the dynamically generated file
    FILE *client_choice_file = fopen(client_choice_filename, "r");
    if (client_choice_file == NULL) {
        printf("Erreur : Impossible d'ouvrir %s_Cart.txt !\n", CIN);
        exit(1);
    }

    // Step 4: Process Client's Choices and Calculate Total Cost
    clc client_choice_entry;
    float grand_total = 0.0;
    while (fscanf(client_choice_file, "%d %d", &client_choice_entry.id_product_clien, &client_choice_entry.quantity) == 2) {
        
        produit product;
        int product_found = 0;

        // Read product details from produit.dat
        FILE *produit_file = fopen("produit.dat", "rb");
        if (produit_file == NULL) {
            printf("Erreur : Impossible d'ouvrir produit.dat !\n");
            exit(1);
        }

        // Search for the product based on ID
        while (fread(&product, sizeof(produit), 1, produit_file) == 1) {
            if (product.id_product == client_choice_entry.id_product_clien) {
                product_found = 1;
                break;
            }
        }
        fclose(produit_file);

        if (product_found) {
            if (client_choice_entry.quantity <= product.quantity) {
                float total_price = product.price * client_choice_entry.quantity;
                grand_total += total_price;
                fprintf(FACT, "(| %-15s | %-10d | %-10.2f DH |) Tj\n0 -20 Td\n", product.name, client_choice_entry.quantity, total_price);
            } else {
                fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", product.name, client_choice_entry.quantity, "En rupture de stock");
            }
        } else {
            fprintf(FACT, "(| %-15s | %-10d | %-10s DH |) Tj\n0 -20 Td\n", "Produit non trouve", client_choice_entry.quantity, "Non trouve");
        }
    }
    fclose(client_choice_file);

    // Step 5: Print Grand Total and Close FACTEUR File
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Total general : %.2f DH) Tj\n0 -20 Td\n", grand_total);
    fprintf(FACT, "(=============================================) Tj\n");
    fprintf(FACT, pdf_footer);
    fclose(FACT);
}



void add_credit_card(char* CIN_client, char *name_client) {
    c_clrscr();
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
    c_clrscr();
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
    c_clrscr();
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
    c_clrscr();
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


void Display_the_Supplier_Total_amount_sales_in_the_Day(char *CINF) {
    c_clrscr();
    FILE *produit_file = fopen("produit.dat", "rb");
    if (produit_file == NULL) {
        printf("Error: 'produit.dat' does not exist!\n");
        exit(0);
    }

    FILE *client_file = fopen("client.txt", "rt");
    if (client_file == NULL) {
        printf("Error: 'client.txt' does not exist!\n");
        fclose(produit_file);
        exit(0);
    }

    // Get today's date
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;

    // Dynamically create the filename for the supplier report
    char report_filename[50];
    sprintf(report_filename, "supplier%s.txt", CINF);
    FILE *supplier_report_file = fopen(report_filename, "w+t");
    if (supplier_report_file == NULL) {
        printf("Error: Unable to create the report file '%s'!\n", report_filename);
        fclose(produit_file);
        fclose(client_file);
        return;
    }

    // Display report header on console
    system("clear"); // Clear the screen
    printf("======== SUPPLIER TOTAL SALES REPORT ========\n");
    printf("DATE: %02d-%02d-%d\n", day, month, year);
    printf("SUPPLIER CIN: %s\n", CINF);
    printf("============================================\n");
    printf("| %-15s | %-10s | %-12s |\n", "CATEGORY", "QUANTITY", "SALE AMOUNT (DH)");
    printf("|-----------------|------------|-----------------|\n");

    fprintf(supplier_report_file, "SUPPLIER CIN: %s\nDATE: %02d-%02d-%d\n\n", CINF, day, month, year);
    fprintf(supplier_report_file, "Category           Quantity    Sale Amount (DH)\n");
    fprintf(supplier_report_file, "----------------------------------------------\n");

    // Variables
    produit p;
    int cart_product_id, cart_quantity;
    float total_sales_amount = 0.0;

    // Process each client
    char client_name[30], client_lastname[30], client_cinc[30], client_motpass[30];
    while (fscanf(client_file, "%s %s %s %s", client_name, client_lastname, client_cinc, client_motpass) == 4) {
        // Build the client's cart filename
        char cart_filename[50];
        sprintf(cart_filename, "%s_Cart.txt", client_cinc);
        FILE *cart_file = fopen(cart_filename, "rt");
        if (cart_file == NULL) {
            continue; // Skip to next client if the cart file doesn't exist
        }

        // Process each product in the client's cart file
        while (fscanf(cart_file, "%d %d", &cart_product_id, &cart_quantity) == 2) {
            rewind(produit_file);
            // Search for the product in produit.dat
            while (fread(&p, sizeof(produit), 1, produit_file)) {
                if (p.id_product == cart_product_id && strcmp(p.CINF, CINF) == 0) {
                    // Calculate total amount
                    float total_amount = p.price * cart_quantity;
                    total_sales_amount += total_amount;

                    // Display on console
                    printf("| %-15s | %-10d | %-15.2f |\n", p.category, cart_quantity, total_amount);
                    fprintf(supplier_report_file, "%-18s %-10d %-15.2f\n", p.category, cart_quantity, total_amount);

                    usleep(100000); // Visual pause
                    break;
                }
            }
        }
        fclose(cart_file);
    }

    // Display total sales amount
    printf("============================================\n");
    printf("TOTAL SALES AMOUNT: %.2f DH\n", total_sales_amount);
    printf("============================================\n");

    fprintf(supplier_report_file, "----------------------------------------------\n");
    fprintf(supplier_report_file, "TOTAL SALES AMOUNT: %.2f DH\n\n", total_sales_amount);

    // Cleanup
    fclose(supplier_report_file);
    fclose(produit_file);
    fclose(client_file);
}
// french version

void Display_the_Supplier_Total_amount_sales_in_the_Day_f(char *CINF) {
    FILE *produit_file = fopen("produit.dat", "rb");
    if (produit_file == NULL) {
        printf("Error: 'produit.dat' does not exist!\n");
        exit(0);
    }

    FILE *client_file = fopen("client.txt", "rt");
    if (client_file == NULL) {
        printf("Error: 'client.txt' does not exist!\n");
        fclose(produit_file);
        exit(0);
    }

    // Get today's date
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;

    // Dynamically create the filename for the supplier report
    char report_filename[50];
    sprintf(report_filename, "supplier%s.txt", CINF);
    FILE *supplier_report_file = fopen(report_filename, "a+t");
    if (supplier_report_file == NULL) {
        printf("Error: Unable to create the report file '%s'!\n", report_filename);
        fclose(produit_file);
        fclose(client_file);
        return;
    }

    // Display report header on console
    system("clear"); // Clear the screen
    printf("======== SUPPLIER TOTAL SALES REPORT ========\n");
    printf("DATE: %02d-%02d-%d\n", day, month, year);
    printf("SUPPLIER CIN: %s\n", CINF);
    printf("============================================\n");
    printf("| %-15s | %-10s | %-12s |\n", "CATEGORY", "QUANTITY", "SALE AMOUNT (DH)");
    printf("|-----------------|------------|-----------------|\n");

    fprintf(supplier_report_file, "SUPPLIER CIN: %s\nDATE: %02d-%02d-%d\n\n", CINF, day, month, year);
    fprintf(supplier_report_file, "Category           Quantity    Sale Amount (DH)\n");
    fprintf(supplier_report_file, "----------------------------------------------\n");

    // Variables
    produit p;
    int cart_product_id, cart_quantity;
    float total_sales_amount = 0.0;

    // Process each client
    char client_name[30], client_lastname[30], client_cinc[30], client_motpass[30];
    while (fscanf(client_file, "%s %s %s %s", client_name, client_lastname, client_cinc, client_motpass) == 4) {
        // Build the client's cart filename
        char cart_filename[50];
        sprintf(cart_filename, "%s_Cart.txt", client_cinc);
        FILE *cart_file = fopen(cart_filename, "rt");
        if (cart_file == NULL) {
            continue; // Skip to next client if the cart file doesn't exist
        }

        // Process each product in the client's cart file
        while (fscanf(cart_file, "%d %d", &cart_product_id, &cart_quantity) == 2) {
            rewind(produit_file);
            // Search for the product in produit.dat
            while (fread(&p, sizeof(produit), 1, produit_file)) {
                if (p.id_product == cart_product_id && strcmp(p.CINF, CINF) == 0) {
                    // Calculate total amount
                    float total_amount = p.price * cart_quantity;
                    total_sales_amount += total_amount;

                    // Display on console
                    printf("| %-15s | %-10d | %-15.2f |\n", p.category, cart_quantity, total_amount);
                    fprintf(supplier_report_file, "%-18s %-10d %-15.2f\n", p.category, cart_quantity, total_amount);

                    usleep(100000); // Visual pause
                    break;
                }
            }
        }
        fclose(cart_file);
    }

    // Display total sales amount
    printf("============================================\n");
    printf("TOTAL SALES AMOUNT: %.2f DH\n", total_sales_amount);
    printf("============================================\n");

    fprintf(supplier_report_file, "----------------------------------------------\n");
    fprintf(supplier_report_file, "TOTAL SALES AMOUNT: %.2f DH\n\n", total_sales_amount);

    // Cleanup
    fclose(supplier_report_file);
    fclose(produit_file);
    fclose(client_file);
}

void feedback_and_rate_the_product(char *name_cl, int id_product) { 
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
    comment[len - 1] = '\0'; 
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
    comment[len - 1] = '\0'; // Supprimer le caractere de nouvelle ligne
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

void draw_frame(int width, int height, int start_x, int start_y) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            c_gotoxy(start_x + x, start_y + y);
            if (y == 0 || y == height - 1) {
                // Top and bottom borders
                printf("=");
            } else if (x == 0 || x == width - 1) {
                // Left and right borders
                printf("|");
            } else {
                // Fill inside the frame with spaces
                printf(" ");
            }
        }
    }
}

void menu_admin() {
    int choix;
    int i ;
    int frame_width = 60;
    int frame_height = 15;
    int frame_x = 55; 
    int frame_y = 11;  
    do {
        i = 0;
        c_textattr(14);
        c_clrscr();

        // Draw the menu frame
        draw_frame(frame_width, frame_height, frame_x, frame_y);

        // Print menu title and options inside the frame
        c_textattr(14);
        c_gotoxy(28 , 5 ); printf("---------------------------------  Administrator Menu - Supplier Management  ---------------------------------");

        c_textattr(8);
        c_gotoxy(70 , 15 ); printf("1. Add a Supplier");
        c_gotoxy(70 , 16 ); printf("2. Delete a Supplier");
        c_gotoxy(70 , 17 ); printf("3. View Supplier List");
        c_gotoxy(70 , 18 ); printf("4. Exit");
        c_textattr(14);
        c_gotoxy(70 , 19  );printf("Enter your choice:  ");
        c_textattr(8);
        c_gotoxy(70 , 44 );
        scanf("%d", &choix);

        c_textattr(7);
        switch (choix) {
            case 1:
                add_supplier();
                break;
            case 2:
                delete_supplier();
                i = 10 ;
                break;
            case 3:
                c_clrscr();
                show_supplier();
                i = 10 ;
                break;
            case 4:
                c_gotoxy(65,23);
                c_textcolor(1);
                printf("Exiting administrator menu...(tap any word)");
                c_getch();
                Home_LOGIN_menu();
                break;
            default:
                c_textattr(12);
                c_gotoxy(65,22);
                printf("Invalid choice. Please try again.");
                break;
        }
        if (choix != 4) {
            c_textattr(9);
            c_gotoxy(60,23 + i);
            printf("Press any key to continue...");
            c_getch();
        }
        c_clrscr();
    } while (choix != 4);
}

void menu_admin_f() {
    int j ;
    int choix;
    int frame_width = 60;
    int frame_height = 15;
    int frame_x = 55; 
    int frame_y = 11;  
    do {
        j = 0 ;
        c_textattr(14);
        c_clrscr();

        // Draw the menu frame
        draw_frame(frame_width, frame_height, frame_x, frame_y);

        // Print menu title and options inside the frame
        c_textattr(14);
        c_gotoxy(32 , 5 ); printf("---------------------------- Menu Administrateur - Gestion des Fournisseurs ----------------------------");

        c_textattr(8);
        c_gotoxy(70 , 15 ); printf("1. Ajouter un Fournisseur");
        c_gotoxy(70 , 16 ); printf("2. Supprimer un Fournisseur");
        c_gotoxy(70 , 17 ); printf("3. Voir la Liste des Fournisseurs");
        c_gotoxy(70 , 18 ); printf("4. Quitter");
        c_textattr(14);
        c_gotoxy(70 , 19  );printf("Entrez votre choix :  ");
        c_textattr(8);
        c_gotoxy(70 , 44 );
        scanf("%d", &choix);

        c_textattr(7);
        switch (choix) {
            case 1:
                add_supplier_f();
                break;
            case 2:
                delete_supplier_f();
                j = 10 ;
                break;
            case 3:
                show_supplier_f();
                j = 10 ;
                break;
            case 4:
                c_gotoxy(60,23);
                c_textcolor(1);
                printf("Quitter le menu... (appuyez sur une touche)");
                c_getch();
                Home_LOGIN_menu();
                break;
            default:
                c_textattr(12);
                c_gotoxy(65,22);
                printf("Choix invalide. Veuillez reessayer.");
                break;
        }
        if (choix != 4) {
            c_textattr(9);
            c_gotoxy(60,24 + j );
            printf("Appuyez sur une touche pour continuer...");
            c_getch();
        }
        c_clrscr();
    } while (choix != 4);
}



// Function to get console dimensions
void get_console_size(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}
void c_print_centered(const char *text, int y, int console_width) {
    int x = (console_width - strlen(text)) / 2;
    c_gotoxy(x, y);
    printf("%s", text);
}

// Function to draw the menu frame
void draw_menu_frame(int x, int y, int width, int height) {
    c_textcolor(14);
    c_gotoxy(x, y);
    for (int i = 0; i < width; i++) printf("=");
    for (int i = 1; i <= height; i++) {
        c_textcolor(14);
        c_gotoxy(x, y + i);
        printf("|");
        c_gotoxy(x + width - 1, y + i);
        printf("|");
    }
    // c_textcolor(14);
    c_textcolor(14);
    c_gotoxy(x, y + height + 1);
    for (int i = 0; i < width; i++) printf("=");
}

// Function to display the menu
void c_draw_menu(int op, Options options) {
    c_clrscr();

    int console_rows, console_cols;
    get_console_size(&console_rows, &console_cols);

    int frame_width = 50;
    int frame_height = options.len + 4;
    int frame_x = 55;
    int frame_y = 15;
    c_textattr(14); 
    c_gotoxy(28, 6);
    printf("--------------------------------------------- Gestion des Achat ----------------------------------------------");
    // Display the title at specific coordinates
    c_textattr(14); 
    c_gotoxy(28, 10);
    printf("%s", options.title);
    c_textattr(7); 
    // Draw the menu frame
    draw_menu_frame(frame_x, frame_y, frame_width, frame_height);

    // Display menu options
    for (int i = 0; i < options.len; i++) {
        c_textattr(op == i ? 14 : 8); // Highlight the current option
        c_gotoxy(frame_x + (frame_width - strlen(options.ops[i])) / 2, frame_y + 2 + i);
        printf("%s", options.ops[i]);
    }

    // Footer instructions
    c_textattr(8);
    c_gotoxy(57, 26);
    printf("Use UP/DOWN arrows to navigate, ENTER to select");
    c_textattr(7); // Reset text color
}

// Function to handle menu selection
int c_select_menu(Options options) {
    int current_option = 0;
    int key;
    c_draw_menu(current_option, options);

    while (1) {
        key = c_getch();
        switch (key) {
            case 72: // Arrow up
                current_option = (current_option == 0) ? options.len - 1 : current_option - 1;
                c_draw_menu(current_option, options);
                break;
            case 80: // Arrow down
                current_option = (current_option == options.len - 1) ? 0 : current_option + 1;
                c_draw_menu(current_option, options);
                break;
            case 13: // Enter key
                return current_option;
        }
    }
}

// Global Variables
Options options;
char *Home_LOGIN[] = {
    "[- Admin -]",
    "[- Supplier -]",
    "[- Client -]",
    "[- Exit -]"
};

char *Accueil_CONNEXION[] = {
    "[- Admin -]",
    "[- Fournisseur -]",
    "[- Client -]",
    "[- Quitter -]"
};

char *choose_language[] = {
    "[- English -]",
    "[- French  -]",
    "[- Leave   -]"
};

// Main Menu Function
void Home_OPTIONS() {
    options.title = "---------------------------------------------    HOME -- PAGE    ---------------------------------------------";
    options.ops = choose_language;
    options.len = sizeof(choose_language) / sizeof(choose_language[0]);

    int selected = c_select_menu(options);
    if (selected == options.len - 1) {
        exit(0); 
    } else if (selected == 1) { 
        Home_LOGIN_menu_f();
    } else { 
        Home_LOGIN_menu();
    }
}
void Home_LOGIN_menu()  {
    c_textcolor(14);
    options.title = "---------------------------------------------     HOME -- PAGE    ---------------------------------------------";
    options.ops = Home_LOGIN;
    options.len = sizeof(Home_LOGIN) / sizeof(Home_LOGIN[0]);

    int selected = c_select_menu(options);
    if (selected == 3) { // Option "Exit"
        Home_OPTIONS();
    } else {
        char *Client_CIN = (char *)malloc(20 * sizeof(char));
        char *Supplier_CIN = (char *)malloc(20 * sizeof(char));
        if(selected == 0 ) menu_admin();
        if (selected == 1 ) { // Fournisseur
            int choice;
            do {
                c_clrscr();
                c_textattr(8);
                c_gotoxy(50, 6); printf("1 - Login");
                c_gotoxy(50, 8); printf("2 - Back to Main Menu");
                c_gotoxy(50, 9); printf("3 - Leave Program");
                c_textattr(14);
                c_gotoxy(50, 10); printf(" ---->> GIVE CHOICE : ");
                
                if (scanf("%d", &choice) != 1) {
                    while (getchar() != '\n');
                    c_textattr(4);
                    c_gotoxy(50, 12); printf("Invalid input. Please enter a number.\n");
                    c_textattr(14);
                    c_getch();
                    continue;
                }

                switch (choice) {
                    case 1:
                        login_supplier(Supplier_CIN);
                        break;
                    case 2:
                        Home_OPTIONS();
                        break;
                    case 3:
                        free(Client_CIN);
                        free(Supplier_CIN);
                        c_textcolor(15);
                        exit(0);
                    default:
                        c_textattr(4);
                        c_gotoxy(50, 12); printf("Please choose a valid option.\n");
                        c_textattr(14);
                        c_getch();
                        break;
                }
            } while (choice != 3 && choice != 2);
        } else if (selected == 2){ 
            int choice;
            do {
                c_clrscr();
                c_textattr(8);
                c_gotoxy(50, 6); printf("1 - Login");
                c_gotoxy(50, 7); printf("2 - Sign In");
                c_gotoxy(50, 8); printf("3 - Back to Main Menu");
                c_gotoxy(50, 9); printf("4 - Leave Program");
                c_textattr(14);
                c_gotoxy(50, 10); printf(" ---->> GIVE CHOICE : ");
                
                if (scanf("%d", &choice) != 1) {
                    while (getchar() != '\n');
                    c_textattr(4);
                    c_gotoxy(50, 12); printf("Invalid input. Please enter a number.\n");
                    c_textattr(14);
                    c_getch();
                    continue;
                }

                switch (choice) {
                    case 1:
                        clientLogin(Client_CIN);
                        break;
                    case 2:
                        sign_in_client();
                        break;
                    case 3:
                        Home_OPTIONS();
                        break;
                    case 4:
                        free(Client_CIN);
                        free(Supplier_CIN);
                        c_textcolor(15);
                        exit(0);
                    default:
                        c_textattr(4);
                        c_gotoxy(50, 12); printf("Please choose a valid option.\n");
                        c_textattr(14);
                        c_getch();
                        break;
                }
            } while (choice != 3 && choice != 4);

                    }else Home_OPTIONS();

                    free(Client_CIN);
                    free(Supplier_CIN);
                }
                c_getch();
}

void Home_LOGIN_menu_f() {
    c_textcolor(14);
    options.title = "---------------------------------------------     PAGE D'ACCUEIL     -----------------------------------------";
    options.ops = Accueil_CONNEXION;
    options.len = sizeof(Accueil_CONNEXION) / sizeof(Accueil_CONNEXION[0]);

    int selected = c_select_menu(options);
    if (selected == 3) { // Quitter
        Home_OPTIONS();
    } else {
        char *Client_CIN = (char *)malloc(20 * sizeof(char));
        char *Supplier_CIN = (char *)malloc(20 * sizeof(char));
        if(selected == 0 ) menu_admin_f();
        if (selected == 1) { // Fournisseur
            int choice;
            do {
                
                c_clrscr();
                c_textattr(8);
                c_gotoxy(50, 7); printf("1 - Se connecter");
                c_gotoxy(50, 8); printf("2 - Retour au menu principal");
                c_gotoxy(50, 9); printf("3 - Quitter le programme");
                c_textattr(14);
                c_gotoxy(50, 10); printf(" ---->> VOTRE CHOIX : ");
                
                if (scanf("%d", &choice) != 1) {
                    while (getchar() != '\n');
                    c_textattr(4);
                    c_gotoxy(50, 12); printf("Entree invalide. Veuillez entrer un numero.\n");
                    c_textattr(14);
                    c_getch();
                    continue;
                }

                switch (choice) {
                    case 1:
                        login_supplier_f(Supplier_CIN);
                        break;
                    case 2:
                        Home_OPTIONS();
                        break;
                    case 3:
                        free(Client_CIN);
                        free(Supplier_CIN);
                        c_textcolor(15);
                        exit(0);
                    default:
                        c_textattr(4);
                        c_gotoxy(50, 12); printf("Veuillez choisir une option valide.\n");
                        c_textattr(14);
                        c_getch();
                        break;
                }
            } while (choice != 3 && choice != 2);
            } else if(selected == 2 ) {
                    int choice;
                do {
                    int choice;
                    c_clrscr();
                    c_textattr(8);
                    c_gotoxy(50, 6); printf("1 - Se connecter");
                    c_gotoxy(50, 7); printf("2 - S'inscrire");
                    c_gotoxy(50, 8); printf("3 - Retour au menu principal");
                    c_gotoxy(50, 9); printf("4 - Quitter le programme");
                    c_textattr(14);
                    c_gotoxy(50, 10); printf(" ---->> VOTRE CHOIX : ");
                    
                    if (scanf("%d", &choice) != 1) {
                        while (getchar() != '\n');
                        c_textattr(4);
                        c_gotoxy(50, 12); printf("Entree invalide. Veuillez entrer un numero.\n");
                        c_textattr(14);
                        c_getch();
                        continue;
                    }

                    switch (choice) {
                        case 1:
                            clientLogin_f(Client_CIN);
                            break;
                        case 2:
                            sign_in_client_f();
                            break;
                        case 3:
                            Home_OPTIONS();
                            break;
                        case 4:
                            free(Client_CIN);
                            free(Supplier_CIN);
                            c_textcolor(15);
                            exit(0);
                        default:
                            c_textattr(4);
                            c_gotoxy(50, 12); printf("Veuillez choisir une option valide.\n");
                            c_textattr(14);
                            c_getch();
                            break;
                    }
                } while (choice != 3 && choice != 4);

        }else Home_OPTIONS();

        free(Client_CIN);
        free(Supplier_CIN);
    }
    c_getch();
}


//-----------------------function delete supplier--------------

void delete_supplier() {
    FILE *fp, *temp;
    fp = fopen("fournisseur.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        c_gotoxy(50, 25);
        printf("Unable to open this file");
        exit(1);
    }

    fseek(fp, 0, SEEK_END); // Check if file is empty
    if (ftell(fp) == 0) {
        c_gotoxy(50, 26);
        printf("The file fournisseur.txt is empty.");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }
    rewind(fp); // Reset file pointer to start

    char CIN[30];
    c_gotoxy(60, 27);
    printf("Enter the supplier's CIN: ");
    c_gotoxy(86, 27);
    scanf("%s", CIN);
    int tr = 0;
    fournisseur f, fs;
    int y = 29; // Starting y-coordinate for output

    while (fscanf(fp, "%s %s %s %s\n", f.prenomf, f.nomf, f.Cinf, f.mdpf) == 4) {
        if (strcmp(f.Cinf, CIN) == 0) {
            tr = 1;
            strcpy(fs.prenomf, f.prenomf);
            strcpy(fs.Cinf, f.Cinf);
            strcpy(fs.nomf, f.nomf);
            strcpy(fs.mdpf, f.mdpf);
        } else {
            fprintf(temp, "%s %s %s %s\n", f.prenomf, f.nomf, f.Cinf, f.mdpf);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("fournisseur.txt");
    rename("temp.txt", "fournisseur.txt");

    if (tr == 0) {
        c_gotoxy(60, y);
        c_textcolor(4);
        printf("Warning, the supplier does not exist!!");
        c_textcolor(15);
    } else {
        gradientSpinner_s(20); // Show the spinner first
        c_gotoxy(60, y); // Set position after the spinner
        c_textcolor(2);
        printf("Mr. %s %s successfully deleted", fs.nomf, fs.prenomf); // Show the success message after spinner
        c_textcolor(15);
    }
}
// version french
void delete_supplier_f() {
    FILE *fp, *temp;
    fp = fopen("fournisseur.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        c_gotoxy(50, 25);
        printf("Impossible d'ouvrir ce fichier");
        exit(1);
    }

    fseek(fp, 0, SEEK_END); // Verifier si le fichier est vide
    if (ftell(fp) == 0) {
        c_gotoxy(50, 26);
        printf("Le fichier fournisseur.txt est vide.");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }
    rewind(fp); // Reinitialiser le pointeur de fichier au debut

    char CIN[30];
    c_gotoxy(60, 27);
    printf("Entrez le CIN du fournisseur : ");
    c_gotoxy(91, 27);
    scanf("%s", CIN);
    int tr = 0;
    fournisseur f, fs;
    int y = 29; // Coordonnee de depart pour l'affichage

    while (fscanf(fp, "%s %s %s %s\n", f.prenomf, f.nomf, f.Cinf, f.mdpf) == 4) {
        if (strcmp(f.Cinf, CIN) == 0) {
            tr = 1;
            strcpy(fs.prenomf, f.prenomf);
            strcpy(fs.Cinf, f.Cinf);
            strcpy(fs.nomf, f.nomf);
            strcpy(fs.mdpf, f.mdpf);
        } else {
            fprintf(temp, "%s %s %s %s\n", f.prenomf, f.nomf, f.Cinf, f.mdpf);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("fournisseur.txt");
    rename("temp.txt", "fournisseur.txt");

    if (tr == 0) {
        c_gotoxy(60, y);
        c_textcolor(4);
        printf("Attention, le fournisseur n'existe pas !!");
        c_textcolor(15);
    } else {
        gradientSpinner_s_f(20); // Afficher le spinner d'abord
        c_gotoxy(60, y); // Positionner apres le spinner
        c_textcolor(2);
        printf("M. %s %s supprime avec succes", fs.nomf, fs.prenomf); // Afficher le message de succes apres le spinner
        c_textcolor(15);
    } 
}


//----------------------show supplier-----------------------
void gradientSpinner_f(int duration) {
    char spinner[] = "|/-\\";
    int spinnerIndex = 0;
    c_textcolor(2);
    c_gotoxy(70 , 4);("Retour...");
    int j = 1 ;
    for (int i = 0; i < 100; i++) {
        c_textcolor(j);
        c_gotoxy(70 , 5);printf("Chargement... %c %d%%", spinner[spinnerIndex], i + 1);
        fflush(stdout);
        spinnerIndex = (spinnerIndex + 1) % 4;
        usleep(duration * 100); // Ajuster la vitesse
        j++;
        if(j == 10 ) j = 1 ;
    }
    c_textcolor(2);
    c_gotoxy(70 , 6);printf("Termine!");
}

void gradientSpinner(int duration) {
    char spinner[] = "|/-\\";
    int spinnerIndex = 0;
    c_textcolor(2);
    c_gotoxy(70 , 4);("Go back...");
    int j = 1 ;
    for (int i = 0; i < 100; i++) {
        c_textcolor(j);
        c_gotoxy(70 , 5);printf("Loading... %c %d%%", spinner[spinnerIndex], i + 1);
        fflush(stdout);
        spinnerIndex = (spinnerIndex + 1) % 4;
        usleep(duration * 100); // Adjust speed
        j++;
        if(j == 10 ) j = 1 ;
    }
    c_textcolor(2);
    c_gotoxy(70 , 6);printf("Done!");
}

void show_supplier() {
    FILE *fp;
    fp = fopen("fournisseur.txt", "r");
    if (fp == NULL) {
        printf("Unable to open the file fournisseur.txt.");
        return;
    }

    fournisseur f;
    fseek(fp, 0, SEEK_END); // Check if the file is empty
    if (ftell(fp) == 0) {
        printf("The file fournisseur.txt is empty.");
        fclose(fp);
        return;
    }
    rewind(fp); // Reset file pointer to the start

    int tableWidth = 51; // Width of the table
    int x = 55, y = 9;   // Starting coordinates
    int page = 0, linesPerPage = 15; // Pagination variables
    int totalRecords = 0;            // Total records counter

    // Count the total number of records in the file
    while (fscanf(fp, "%s %s %s %s", f.nomf, f.prenomf, f.Cinf, f.mdpf) == 4) {
        totalRecords++;
    }

    rewind(fp); // Go back to the start of the file
    
    int totalPages = (totalRecords + linesPerPage - 1) / linesPerPage; // Calculate total pages
    
    while (1) {
        c_clrscr();
        rewind(fp);

        // Skip records for previous pages
        int skip = page * linesPerPage;
        for (int i = 0; i < skip; i++) {
            fscanf(fp, "%s %s %s %s", f.nomf, f.prenomf, f.Cinf, f.mdpf);
        }

        // Draw Table Header
        c_textcolor(14);
        c_gotoxy(x, y - 2);
        for (int i = 0; i < tableWidth; i++) printf("_");
        c_gotoxy(x, y - 1);
        c_textcolor(8); printf("| %-15s | %-15s | %-10s |", "Name", "Surname", "CIN");
        c_gotoxy(x, y);
        c_textcolor(14);
        for (int i = 0; i < tableWidth; i++) printf("-");
        
        // Display current page data
        int count = 0;
        while (count < linesPerPage && fscanf(fp, "%s %s %s %s", f.nomf, f.prenomf, f.Cinf, f.mdpf) == 4) {
            c_gotoxy(x, y + 1 + count);
            c_textcolor(14);
            printf("| %-15s | %-15s | %-10s |", f.nomf, f.prenomf, f.Cinf);
            count++;
        }
        
        // Draw closing line
        c_gotoxy(x, y + 1 + count);
        for (int i = 0; i < tableWidth; i++) printf("-");
        
        // Show page information
        c_gotoxy(x, y + 3 + count);
        printf("Page %d of %d - Use LEFT/RIGHT arrows to navigate, ESC to quit.", page + 1, totalPages);

        // Wait for user input
        int ch = c_getch();
        if (ch == 27) { // ESC Key to exit
            gradientSpinner(20); // Add the spinner animation on quit
            break;
        } else if (ch == 0 || ch == 224) { // Special keys (arrows)
            ch = c_getch();
            if (ch == KEY_RIGHT && page < totalPages - 1) {
                page++; // Go to next page
            } else if (ch == KEY_LEFT && page > 0) {
                page--; // Go to previous page
            }
        }
    }

    fclose(fp);
    c_textcolor(14);
    c_gotoxy(x, y*3 + 2);
    printf("End of the list. Returning to the menu...");
}
void show_supplier_f() {
    FILE *fp;
    fp = fopen("fournisseur.txt", "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier fournisseur.txt.");
        return;
    }

    fournisseur f;
    fseek(fp, 0, SEEK_END); // Verifier si le fichier est vide
    if (ftell(fp) == 0) {
        printf("Le fichier fournisseur.txt est vide.");
        fclose(fp);
        return;
    }
    rewind(fp); // Reinitialiser le pointeur de fichier au debut

    int tableWidth = 51; // Largeur du tableau
    int x = 50, y = 9;   // Coordonnees de depart
    int page = 0, linesPerPage = 15; // Variables de pagination
    int totalRecords = 0;            // Compteur du nombre total d'enregistrements

    // Compter le nombre total d'enregistrements dans le fichier
    while (fscanf(fp, "%s %s %s %s", f.nomf, f.prenomf, f.Cinf, f.mdpf) == 4) {
        totalRecords++;
    }

    rewind(fp); // Retourner au debut du fichier
    
    int totalPages = (totalRecords + linesPerPage - 1) / linesPerPage; // Calculer le nombre total de pages
    
    while (1) {
        c_clrscr();
        rewind(fp);

        // Sauter les enregistrements pour les pages precedentes
        int skip = page * linesPerPage;
        for (int i = 0; i < skip; i++) {
            fscanf(fp, "%s %s %s %s", f.nomf, f.prenomf, f.Cinf, f.mdpf);
        }

        // En-tete du tableau
        c_textcolor(14);
        c_gotoxy(x, y - 2);
        for (int i = 0; i < tableWidth; i++) printf("_");
        c_gotoxy(x, y - 1);
        c_textcolor(8); printf("| %-15s | %-15s | %-10s |", "Nom", "Prenom", "CIN");
        c_gotoxy(x, y);
        c_textcolor(14);
        for (int i = 0; i < tableWidth; i++) printf("-");
        
        // Afficher les donnees de la page actuelle
        int count = 0;
        while (count < linesPerPage && fscanf(fp, "%s %s %s %s", f.nomf, f.prenomf, f.Cinf, f.mdpf) == 4) {
            c_gotoxy(x, y + 1 + count);
            c_textcolor(14);
            printf("| %-15s | %-15s | %-10s |", f.nomf, f.prenomf, f.Cinf);
            count++;
        }
        
        // Ligne de fermeture
        c_gotoxy(x, y + 1 + count);
        for (int i = 0; i < tableWidth; i++) printf("-");
        
        // Afficher les informations de la page
        c_gotoxy(x, y + 3 + count);
        printf("Page %d de %d - Utilisez les fleches GAUCHE/DROITE pour naviguer, ESC pour quitter.", page + 1, totalPages);

        // Attendre l'entree de l'utilisateur
        int ch = c_getch();
        if (ch == 27) { // Touche ESC pour quitter
            gradientSpinner_f(20); // Ajouter l'animation de chargement lors de la sortie
            break;
        } else if (ch == 0 || ch == 224) { // Touches speciales (fleches)
            ch = c_getch();
            if (ch == KEY_RIGHT && page < totalPages - 1) {
                page++; // Aller a la page suivante
            } else if (ch == KEY_LEFT && page > 0) {
                page--; // Retourner a la page precedente
            }
        }
    }

    fclose(fp);
    c_textcolor(14);
    c_gotoxy(x, y*3 + 2);
    printf("Fin de la liste. Retour au menu...");
}


void view_product_supplier(char *CINF) {
    FILE *fp = fopen("produit.dat", "rb");
    if (fp == NULL) {
        printf("Error: Unable to open the file produit.dat\n");
        return;
    }

    produit p;
    int tableWidth = 90;  
    int x = 40, y = 8;    
    int count = 0;

    c_clrscr();
    c_gotoxy(x, y - 2);
    for (int i = 0; i < tableWidth; i++) printf("_");
    c_gotoxy(x, y - 1);
    printf("| %-5s | %-10s | %-10s | %-8s | %-8s | %-15s | %-15s |", 
           "ID", "Name", "Category", "Price", "Quantity", "Description", "CINF");
    c_gotoxy(x, y);
    for (int i = 0; i < tableWidth; i++) printf("-");

    y++;  // Move to the next row after the header

    // Pagination: Variables to keep track of page
    int page = 0;
    int productsPerPage = 15;
    fseek(fp, page * productsPerPage * sizeof(produit), SEEK_SET);  // Start at the correct page

    while (fread(&p, sizeof(produit), 1, fp) == 1) {
        if (strcmp(p.CINF, CINF) == 0) {  // Check if the product matches the provided CIN
            c_gotoxy(x, y);
            printf("| %-5d | %-10s | %-10s | %-8.2f | %-8d | %-15s | %-15s |", 
                   p.id_product, p.name, p.category, p.price, p.quantity, p.description, p.CINF);
            count++;
            y++;

            if (count % productsPerPage == 0) {  // Pagination after every 15 products
                c_gotoxy(x, y + 2);
                printf("Press any key to continue or 'q' to quit...");
                char ch = c_getch();  // Get user input

                if (ch == 'q') break; // Exit if 'q' is pressed

                // Go to the next page (right)
                page++;
                fseek(fp, page * productsPerPage * sizeof(produit), SEEK_SET);
                c_clrscr();
                y = 8;  // Reset Y to the start of the screen

                // Re-print the header and the table for the next page
                c_gotoxy(x, y - 2);
                for (int i = 0; i < tableWidth; i++) printf("_");
                c_gotoxy(x, y - 1);
                printf("| %-5s | %-10s | %-10s | %-8s | %-8s | %-15s | %-15s |", 
                       "ID", "Name", "Category", "Price", "Quantity", "Description", "CINF");
                c_gotoxy(x, y);
                for (int i = 0; i < tableWidth; i++) printf("-");

                y++;  // Move to the row under the header after clearing
            }
            usleep(100000);  // Sleep for 500ms for a smoother user experience
        }
    }

    if (count == 0) {
        c_gotoxy(x, y);
        printf("No products found for the supplier with CIN: %s", CINF);
    } else {
        c_gotoxy(x, y);
        for (int i = 0; i < tableWidth; i++) printf("-");  // Draw a line after the last product
    }

    fclose(fp);
    c_gotoxy(x, y + 2);
    printf("End of list. Press any key to return to the menu.");
}

void view_product_supplier_f(char *CINF) {
    FILE *fp = fopen("produit.dat", "rb");
    if (fp == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier produit.dat\n");
        return;
    }

    produit p;
    int tableWidth = 90;  
    int x = 40, y = 8;    
    int count = 0;

    c_clrscr();
    c_gotoxy(x, y - 2);
    for (int i = 0; i < tableWidth; i++) printf("_");
    c_gotoxy(x, y - 1);
    printf("| %-5s | %-10s | %-10s | %-8s | %-8s | %-15s | %-15s |", 
           "ID", "Nom", "Categorie", "Prix", "Quantite", "Description", "CINF");
    c_gotoxy(x, y);
    for (int i = 0; i < tableWidth; i++) printf("-");

    y++;  // Move to the next row after the header

    // Pagination: Variables to keep track of page
    int page = 0;
    int productsPerPage = 15;
    fseek(fp, page * productsPerPage * sizeof(produit), SEEK_SET);  // Start at the correct page

    while (fread(&p, sizeof(produit), 1, fp) == 1) {
        if (strcmp(p.CINF, CINF) == 0) {  // Check if the product matches the provided CIN
            c_gotoxy(x, y);
            printf("| %-5d | %-10s | %-10s | %-8.2f | %-8d | %-15s | %-15s |", 
                   p.id_product, p.name, p.category, p.price, p.quantity, p.description, p.CINF);
            count++;
            y++;

            if (count % productsPerPage == 0) {  // Pagination after every 15 products
                c_gotoxy(x, y + 2);
                printf("Appuyez sur une touche pour continuer ou 'q' pour quitter...");
                char ch = c_getch();  // Get user input

                if (ch == 'q') break; // Exit if 'q' is pressed

                // Go to the next page (right)
                page++;
                fseek(fp, page * productsPerPage * sizeof(produit), SEEK_SET);
                c_clrscr();
                y = 8;  // Reset Y to the start of the screen

                // Re-print the header and the table for the next page
                c_gotoxy(x, y - 2);
                for (int i = 0; i < tableWidth; i++) printf("_");
                c_gotoxy(x, y - 1);
                printf("| %-5s | %-10s | %-10s | %-8s | %-8s | %-15s | %-15s |", 
                       "ID", "Nom", "Categorie", "Prix", "Quantite", "Description", "CINF");
                c_gotoxy(x, y);
                for (int i = 0; i < tableWidth; i++) printf("-");

                y++;  // Move to the row under the header after clearing
            }
            usleep(100000);  // Sleep for 500ms for a smoother user experience
        }
    }

    if (count == 0) {
        c_gotoxy(x, y);
        printf("Aucun produit trouve pour le fournisseur avec CIN : %s", CINF);
    } else {
        c_gotoxy(x, y);
        for (int i = 0; i < tableWidth; i++) printf("-");  // Draw a line after the last product
    }

    fclose(fp);
    c_gotoxy(x, y + 2);
    printf("Fin de la liste. Appuyez sur une touche pour revenir au menu.");
}

