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

void image(const char *filepath) {
    char commandI[512];

    // Format the command to open the .png image
    snprintf(commandI, sizeof(commandI), "start \"\" \"%s\"", filepath);

    // Execute the command
    int result = system(commandI);

    if (result != 0) {
        printf("Failed to open the image: %s\n", filepath);
    }
}

void openPDFInBrave(const char *filePath) {
    char command[512]; // Buffer to hold the PowerShell command

    // Format the command to open the PDF in Brave
    snprintf(command, sizeof(command), "powershell -Command \"Start-Process 'brave.exe' -ArgumentList '%s'\"", filePath);

    // Execute the command
    int result = system(command);

    // Check if the command was executed successfully
    if (result != 0) {
        printf("Failed to open the PDF in Brave browser.\n");
    } 
}

void c_draw_menu_f(int current_option, Options options) {
    c_clrscr();
    c_textcolor(15);
    c_gotoxy(65, 13);
    printf("%s", options.title);
    c_textcolor(14);

    for (int i = 0; i < options.len; i++) {
        if (i == current_option) {
            c_textcolor(10); // Highlight the selected option
            c_gotoxy(65, 15 + i);
            printf("> %s", options.ops[i]);
        } else {
            c_textcolor(15);
            c_gotoxy(65, 15 + i);
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
    int check_CRD = 0;
    int check_card_exists = 0;

    Options menu_options = {
        .ops = (char*[]) {
            "View Product List",
            "Add Purchases", 
            "View Purchases",
            "Remove Purchases",
            "Add A Credit Card",
            "Display Credit Card",
            "Confirm the purchase",
            "Rate Products",
            "Back to Home Page",
            "Leave Page"
        },
        .len = 10,
        .title = "----- LIST OF OPTIONS -----"
    };

    int choice;
    do {
        choice = c_select_menu_f(menu_options);

        switch (choice) {
            case 0:
                View_Product_List();
                break;

            case 1:
                Add_Purchases(Temp_cin);
                break;

            case 2:
                View_Purchases(Temp_cin);
                break;

            case 3:
                Remove_Purchases(Temp_cin);
                break;

            case 4: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("FILE DOES NOT EXIST !!!");
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
                        c_gotoxy(45, 27);
                        printf("The credit card already exists for this client!");
                    } else {
                        add_credit_card(Temp_cin, client_name);
                        c_textcolor(2);
                        c_gotoxy(45, 27);
                        printf("Credit card added successfully!");
                    }
                } else {
                    add_credit_card(Temp_cin, client_name);
                    c_textcolor(2);
                    c_gotoxy(45, 27);
                    printf("Credit card added successfully!");
                }
                break;
            }

            case 5: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("FILE DOES NOT EXIST !!!");
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
                    c_gotoxy(45, 27);
                    printf("No credit card found for this client!");
                }
                fclose(FD);
                break;
            }

            case 6: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("Error: Credit card file does not exist!\n");
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
                    c_gotoxy(45, 27);
                    printf("You must add a credit card before confirming your purchases!");
                } else {
                    confirm_purchases(Temp_cin);
                }
                break;
            }

            case 7: {
                char cart_filename[100];
                snprintf(cart_filename, sizeof(cart_filename), "%s_Cart.txt", Temp_cin);
                FILE *cart_file = fopen(cart_filename, "r");
                
                if (cart_file == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("No purchases found to rate!\n");
                    break;
                }

                int product_id, quantity;
                while (fscanf(cart_file, "%d %d", &product_id, &quantity) == 2) {
                    c_textcolor(15);
                    printf("Rating product ID : %d", product_id);
                    feedback_and_rate_the_product(client_name, product_id);
                }
                fclose(cart_file);
                break;
            }

            case 8:
                Home_LOGIN_menu();
                break;

            case 9:
                leave();
                break;

            default:
                c_textcolor(4);
                c_gotoxy(45, 27);
                printf("Invalid choice! Please retry.");
                break;
        }

        if (choice != 8 && choice != 9) {
            c_textcolor(9);
            c_gotoxy(60, 30);
            printf("Press any key to continue...");
            c_getch();
        }
        c_clrscr();
    } while (choice != 8 && choice != 9);
}
// french version
void liste_client_f(char *Temp_cin, char *client_name) {
    FILE *FD;
    CCD cd;
    int check_CRD = 0;
    int check_card_exists = 0;

    Options menu_options = {
        .ops = (char*[]) {
            "Afficher la liste des produits",
            "Ajouter des achats", 
            "Afficher les achats",
            "Supprimer des achats",
            "Ajouter une carte de credit",
            "Afficher la carte de credit",
            "Confirmer l'achat",
            "Evaluer les produits",
            "Retour a la page d'accueil",
            "Quitter la page"
        },
        .len = 10,
        .title = "----- LISTE DES OPTIONS -----"
    };

    int choice;
    do {
        choice = c_select_menu_f(menu_options);

        switch (choice) {
            case 0:
                View_Product_List_f();
                break;

            case 1:
                Add_Purchases_f(Temp_cin);
                break;

            case 2:
                View_Purchases_f(Temp_cin);
                break;

            case 3:
                Remove_Purchases_f(Temp_cin);
                break;

            case 4: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("LE FICHIER N'EXISTE PAS !!!");
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
                        c_gotoxy(45, 27);
                        printf("La carte de credit existe deja pour ce client !");
                    } else {
                        add_credit_card_f(Temp_cin, client_name);
                        c_textcolor(2);
                        c_gotoxy(45, 27);
                        printf("Carte de credit ajoutee avec succes !");
                    }
                } else {
                    add_credit_card_f(Temp_cin, client_name);
                    c_textcolor(2);
                    c_gotoxy(45, 27);
                    printf("Carte de credit ajoutee avec succes !");
                }
                break;
            }

            case 5: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("LE FICHIER N'EXISTE PAS !!!");
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
                    c_gotoxy(45, 27);
                    printf("Aucune carte de credit trouvee pour ce client !");
                }
                fclose(FD);
                break;
            }

            case 6: {
                FD = fopen("CREDIT_CARD.dat", "rb");
                if (FD == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("Erreur : Le fichier des cartes de credit n'existe pas !");
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
                    c_gotoxy(45, 27);
                    printf("Vous devez ajouter une carte de credit avant de confirmer vos achats !");
                } else {
                    confirm_purchases_f(Temp_cin);
                }
                break;
            }

            case 7: {
                char cart_filename[100];
                snprintf(cart_filename, sizeof(cart_filename), "%s_Cart.txt", Temp_cin);
                FILE *cart_file = fopen(cart_filename, "r");
                
                if (cart_file == NULL) {
                    c_textcolor(4);
                    c_gotoxy(45, 27);
                    printf("Aucun achat trouve a evaluer !");
                    break;
                }

                int product_id, quantity;
                while (fscanf(cart_file, "%d %d", &product_id, &quantity) == 2) {
                    c_textcolor(15);
                    printf("Evaluation du produit ID : %d\n", product_id);
                    feedback_and_rate_the_product_f(client_name, product_id);
                }
                fclose(cart_file);
                break;
            }

            case 8:
                Home_LOGIN_menu_f();
                break;

            case 9:
                leave_f();
                break;

            default:
                c_textcolor(4);
                c_gotoxy(45, 27);
                printf("Choix invalide ! Veuillez reessayer.");
                break;
        }

        if (choice != 8 && choice != 9) {
            c_textcolor(9);
            c_gotoxy(60, 30);
            printf("Appuyez sur une touche pour continuer...");
            c_getch();
        }
        c_clrscr();
    } while (choice != 8 && choice != 9);
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


void sign_up_client() {
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
    c_textattr(2); 
    c_gotoxy(32, 6);
    printf("Create Your Account:");
    c_textattr(2);
    c_gotoxy(32, 8);
    printf("Enter your LAST NAME: ");
    c_textattr(15);
    scanf("%s", client.last_name);
    c_textattr(2); 
    c_gotoxy(32, 10);
    printf("Enter your FIRST NAME: ");
    c_textattr(15);
    scanf("%s", client.First_name);

    // Validate CIN (Identification Number)
    while (1) {
        c_gotoxy(32, 12);
        c_textattr(2);
        printf("Enter your CIN: ");
        c_textattr(15);
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
        c_textattr(2);
        c_gotoxy(32, 14);
        printf("Enter the NEW PASSWORD: ");
        c_textattr(15);
        strcpy(client.password, Pass_hide(20));

        c_gotoxy(32, 15);
        c_textattr(2);
        printf("Confirm your PASSWORD: ");
        c_textattr(15);
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
void sign_up_client_f() {
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
    c_textattr(2); 
    c_gotoxy(32, 6);
    printf("Creer votre compte :");
    c_textattr(2);
    c_gotoxy(32, 8);
    printf("Entrez votre NOM : ");
    c_textattr(15);
    scanf("%s", client.last_name);
    c_textattr(2); 
    c_gotoxy(32, 10);
    printf("Entrez votre PReNOM : ");
    c_textattr(15);
    scanf("%s", client.First_name);

    // Validate CIN (Identification Number)
    while (1) {
        c_gotoxy(32, 12);
        c_textattr(2);
        printf("Entrez votre CIN : ");
        c_textattr(15);
        scanf("%s", client.CIN);

        if (is_CIN_unique(client.CIN)) {
            // Clear any previous error message
            c_gotoxy(32, 13);
            printf("                                                                          "); // Clear line
            break; // CIN is valid, exit loop
        } else {
            c_textattr(4); // Set text color to red
            c_gotoxy(32, 13);
            printf("Erreur : Le CIN existe deja ou est invalide. Veuillez reessayer.");
            c_textattr(14); // Reset text color
        }
    }

    // Validate Password
    while (1) {
        c_textattr(2);
        c_gotoxy(32, 14);
        printf("Entrez un NOUVEAU MOT DE PASSE : ");
        c_textattr(15);
        strcpy(client.password, Pass_hide(20));

        c_gotoxy(32, 15);
        c_textattr(2);
        printf("Confirmez votre MOT DE PASSE : ");
        c_textattr(15);
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
    c_textcolor(14);
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
    c_textattr(2);  // Set text color to gray

    // Use gotoxy to position the cursor inside the black box
    c_gotoxy(32, 8);  // Move cursor to row 5, column 5
    printf("Let's connect to your account:");
    c_textattr(15);  // Set text color to yellow
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
    c_textattr(2);  // Set text color to gray

    // Use gotoxy to position the cursor inside the black box
    c_gotoxy(32, 8);  // Move cursor to row 8, column 32 for title
    printf("Connectez-vous a votre compte:");

    c_textattr(15);  // Set text color to yellow
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
    c_gotoxy(32, 8);
    printf(" %-10s %-20s %-20s %-10s %-10s %-30s", 
           "ID", "NAME", "CATEGORY", "PRICE", "QUANTITY", "DESCRIPTION");
    c_gotoxy(32, 10);
    printf("-----------------------------------------------------------------------------------------------------------");

    // Read and display each product
    c_textattr(2); // Set text color to yellow
    int row = 12; // Start displaying from row 12
    int productFound = 0; // To track if any products are found

    while (fread(&p, sizeof(produit), 1, fk) == 1) {
        c_gotoxy(32, row);
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
        printf("Erreur : Le fichier n'existe pas ou n'a pas pu etre ouvert !\n");
        return;
    }

    // Print the table header
    c_textattr(8); // Set text color to gray
    c_gotoxy(50, 4);
    printf("====== LISTE DES PRODUITS ======");
    c_gotoxy(32, 8);
    printf(" %-10s %-20s %-20s %-10s %-10s %-30s", 
           "ID", "NOM", "CATEGORIE", "PRIX", "QUANTITE", "DESCRIPTION");
    c_gotoxy(32, 10);
    printf("-----------------------------------------------------------------------------------------------------------");

    // Read and display each product
    c_textattr(2); // Set text color to yellow
    int row = 12; // Start displaying from row 12
    int productFound = 0; // To track if any products are found

    while (fread(&p, sizeof(produit), 1, fk) == 1) {
        c_gotoxy(32, row);
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
        c_textattr(15);
        c_gotoxy(32, 9);
        printf("Invalid input! Please enter a valid product ID (integer): ");
        c_textattr(2);
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
    int attempts = 0;
    do {
        c_textattr(2);
        printf(" Enter quantity (1 - %d): ", p.quantity);
        c_textattr(15);
        while (scanf("%d", &l.quantity) != 1) {
            c_textattr(4);
            c_gotoxy(32, 13+attempts);
            printf("Invalid input! Please enter a number.");
            c_textattr(8);
            while (getchar() != '\n'); // Clear invalid input buffer
        }

        if (l.quantity < 1 || l.quantity > p.quantity) {
            attempts++;
            if (attempts >= 3) {
                c_textattr(4);
                c_gotoxy(32, 13+attempts);
                printf("Maximum attempts reached. Returning to menu.");
                c_textattr(8);
                c_getch();
                return;
            }
            c_textattr(4);
            c_gotoxy(32, 13+attempts);
            printf("Invalid quantity! Enter a value between 1 and %d (Attempt %d/3)", p.quantity, attempts);
            c_textattr(8);
            while (getchar() != '\n'); // Clear invalid input buffer
        } else {
            break;
        }
    } while (attempts < 3);

    // Open the user's cart file
    FILE *ff = fopen(filename, "r+");
    if (ff == NULL) {
        ff = fopen(filename, "w");  // Create the file if it doesn't exist
        if (ff == NULL) {
            c_textattr(4);
            c_gotoxy(32, 14);
            printf("Error: Unable to open or create the cart file!");
            c_textattr(8);
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
    produit l, p;           
    Client client;
    char filename[100];
    strcpy(client.CIN, CIN);

    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

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
    printf("Entrez l'ID DU PRODUIT : ");

    while (scanf("%d", &l.id_product) != 1) {
        c_textattr(15);
        c_gotoxy(32, 9);
        printf("Entree invalide ! Veuillez entrer un ID de produit valide (entier) : ");
        c_textattr(2);
        while (getchar() != '\n');
    }

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

    if (p.quantity == 0) {
        c_textattr(4);
        c_gotoxy(32, 11);
        printf("Erreur : Le produit ID %d est en rupture de stock !", l.id_product);
        c_textattr(8);
        return;
    }

    c_gotoxy(32, 12);
    int attempts = 0;
    do {
        c_textattr(2);
        printf(" Entrez la quantite (1 - %d) : ", p.quantity);
        c_textattr(15);
        while (scanf("%d", &l.quantity) != 1) {
            c_textattr(4);
            c_gotoxy(32, 13+attempts);
            printf("Entree invalide ! Veuillez entrer un nombre.");
            c_textattr(8);
            while (getchar() != '\n');
        }

        if (l.quantity < 1 || l.quantity > p.quantity) {
            attempts++;
            if (attempts >= 3) {
                c_textattr(4);
                c_gotoxy(32, 13+attempts);
                printf("Nombre maximum de tentatives atteint. Retour au menu.");
                c_textattr(8);
                c_getch();
                return;
            }
            c_textattr(4);
            c_gotoxy(32, 13+attempts);
            printf("Quantite invalide ! Entrez une valeur entre 1 et %d (Tentative %d/3)", p.quantity, attempts);
            c_textattr(8);
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (attempts < 3);

    FILE *ff = fopen(filename, "r+");
    if (ff == NULL) {
        ff = fopen(filename, "w");
        if (ff == NULL) {
            c_textattr(4);
            c_gotoxy(32, 14);
            printf("Erreur : Impossible d'ouvrir ou de creer le fichier du panier !");
            c_textattr(8);
            return;
        }
    }

    produit cart[100];
    int cartSize = 0;
    int exists = 0;

    while (fscanf(ff, "%d %d", &cart[cartSize].id_product, &cart[cartSize].quantity) == 2) {
        if (cart[cartSize].id_product == l.id_product) {
            int totalQuantity = cart[cartSize].quantity + l.quantity;
            if (totalQuantity > p.quantity) {
                c_textattr(4);
                c_gotoxy(32, 15);
                printf("Erreur : La quantite totale (%d) depasse le stock disponible (%d) !", totalQuantity, p.quantity);
                c_textattr(8);
                fclose(ff);
                return;
            }
            cart[cartSize].quantity = totalQuantity;
            exists = 1;
        }
        cartSize++;
    }

    if (!exists) {
        cart[cartSize] = l;
        cartSize++;
    }

    freopen(filename, "w", ff);
    for (int i = 0; i < cartSize; i++) {
        fprintf(ff, "%d %d\n", cart[i].id_product, cart[i].quantity);
    }

    c_textattr(2);
    c_gotoxy(32, 16);
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
    c_gotoxy(32, 10);
    printf("%-20s %-15s %-15s %-10s %-10s %-10s", 
           "Product ID", "Name", "Category", "Price", "Quantity", "Total Price");
    c_gotoxy(32, 11);
    printf("-------------------------------------------------------------------------------------------------");

    int found = 0;
    int id_product, quantity;
    int current_line = 12;

    while (fscanf(ff, "%d %d", &id_product, &quantity) == 2) {
        FILE *fk = fopen("produit.dat", "rb");
        if (fk == NULL) {
            c_textattr(4);
            c_gotoxy(32, current_line);
            printf("Error opening the product list file!");
            c_textattr(14);
            fclose(ff);
            return;
        }

        produit p;
        while (fread(&p, sizeof(produit), 1, fk) == 1) {
            if (p.id_product == id_product) {
                c_textattr(2);
                float item_total_price = p.price * quantity;
                c_gotoxy(32, current_line);
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
        c_gotoxy(32, current_line + 1);
        printf("Your cart is empty.");
        c_textattr(14);
    } else {
        c_gotoxy(32, current_line + 1);
         c_textattr(15);
        printf("-------------------------------------------------------------------------------------------------");
        c_gotoxy(32, current_line + 2);
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
    c_gotoxy(32, 10);
    printf("%-32s %-15s %-15s %-10s %-10s %-10s", 
           "ID Produit", "Nom", "Categorie", "Prix", "Quantite", "Prix Total");
    c_gotoxy(32, 11);
    printf("-------------------------------------------------------------------------------------------------");

    int found = 0;
    int id_product, quantity;
    int current_line = 12;

    while (fscanf(ff, "%d %d", &id_product, &quantity) == 2) {
        FILE *fk = fopen("produit.dat", "rb");
        if (fk == NULL) {
            c_textattr(4);
            c_gotoxy(32, current_line);
            printf("Erreur lors de l'ouverture du fichier des produits !");
            c_textattr(14);
            fclose(ff);
            return;
        }

        produit p;
        while (fread(&p, sizeof(produit), 1, fk) == 1) {
            if (p.id_product == id_product) {
                c_textattr(2);
                float item_total_price = p.price * quantity;
                c_gotoxy(45, current_line);
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
        c_gotoxy(32, current_line + 1);
        printf("Votre panier est vide.");
        c_textattr(14);
    } else {
        c_gotoxy(32, current_line + 1);
         c_textattr(15);
        printf("-------------------------------------------------------------------------------------------------");
        c_gotoxy(32, current_line + 2);
        printf("%-20s %-15s %-15s %-10s %-10s %-10.2f", 
               "Total", "", "", "", "", total_price);
    }

    fclose(ff);
}

void Remove_Purchases(char *CIN) {
    c_clrscr();
    int i = 0 , j = 0;
    Client client;
    char filename[100];
    int id_product, quantity, found = 0;
    strcpy(client.CIN, CIN);

    // Construct the filename based on CIN
    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *cartFile = fopen(filename, "r");
    if (cartFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("Your cart is empty or the cart file doesn't exist.\n");
        c_textattr(14);
        return;
    }

    produit product;
    int id_product_in_cart, quantity_in_cart;

    // Display the current items in the cart
    c_gotoxy(52, 8);
    printf("===== YOUR CURRENT PURCHASES =====");
    c_gotoxy(32, 10);
    printf("%-10s %-20s %-15s %-10s %-10s", "Product ID", "Name", "Category", "Price", "Quantity");
    c_gotoxy(32, 11);
    printf("--------------------------------------------------------------");

    FILE *productFile;

    c_textattr(2);
    int row = 12;
    while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        productFile = fopen("produit.dat", "rb");
        if (productFile == NULL) {
            c_textattr(4);
            c_gotoxy(32, row);
            printf("Error opening product list file!\n");
            c_textattr(14);
            fclose(cartFile);
            return;
        }

        while (fread(&product, sizeof(produit), 1, productFile) == 1) {
            if (product.id_product == id_product_in_cart) {
                c_gotoxy(32, row);
                printf("%-10d %-20s %-15s %-10.2f %-10d", 
                       product.id_product, product.name, product.category, product.price, quantity_in_cart);
                row++;
                found = 1;
                i = -1;
            }
        }
        fclose(productFile);
    }

    fclose(cartFile);

    if (!found) {
        c_textattr(4);
        c_gotoxy(32, row);
        printf("No products found in your cart.\n");
        c_textattr(14);
        return;
    }

    // Ask the user to modify or remove products
    do {
        c_gotoxy(32, row + 1);
        c_textattr(15);
        printf("Enter the Product ID to modify/remove (or -1 to exit): ");
        scanf("%d", &id_product);

        if (id_product == -1) {
            j = -1;
            break;}

        // Reopen the cart file for reading and create a temporary file
        cartFile = fopen(filename, "r");
        FILE *tempFile = fopen("temp_cart.txt", "w");
        if (cartFile == NULL || tempFile == NULL) {
            c_textattr(4);
            printf("Error opening files!\n");
            c_textattr(14);
            return;
        }

        found = 0;
        while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
            if (id_product_in_cart == id_product) {
                found = 1;
                int modify_option;

                c_gotoxy(32, row + 2);
                printf("1. Modify Quantity\n");
                c_gotoxy(32, row + 3);
                printf("2. Remove Product\n");
                c_gotoxy(32, row + 4);
                printf("Choose an option: ");
                scanf("%d", &modify_option);

                if (modify_option == 1) {
                    c_gotoxy(32, row + 5);
                    printf("Enter new quantity: ");
                    scanf("%d", &quantity);

                    if (quantity > 0) {
                        fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity);
                        c_gotoxy(32, row + 6);
                        c_textattr(2);
                        printf("Quantity updated successfully.\n");
                        i = -1;
                    } else {
                        c_textattr(4);
                        c_gotoxy(32, row + 6);
                        printf("Invalid quantity!\n");
                        c_textattr(14);
                    }
                } else if (modify_option == 2) {
                    c_gotoxy(32, row + 6);
                    c_textattr(2);
                    printf("Product removed successfully.\n");
                    i = -1;
                } else {
                    c_textattr(4);
                    c_gotoxy(32, row + 6);
                    printf("Invalid option!\n");
                    c_textattr(14);
                    fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart);
                }
            } else {
                fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart);
            }
        }

        fclose(cartFile);
        fclose(tempFile);

        if (!found) {
            c_textattr(4);
            c_gotoxy(32, row + 7);
            printf("Product ID %d not found in your cart.\n", id_product);
            c_textattr(14);
        } else {
            remove(filename);
            rename("temp_cart.txt", filename);
        }
    } while ( i != -1);

    c_textattr(2);
    c_gotoxy(32, row + 8);
    if( j != -1 ){
    printf("Cart updated successfully.");
    c_getch();}
    c_textattr(14);

}
// french version
void Remove_Purchases_f(char *CIN) {
    c_clrscr();
    Client client;
    char filename[100];
    int id_product, quantity, found = 0;
    strcpy(client.CIN, CIN);

    // Construire le nom du fichier base sur le CIN
    snprintf(filename, sizeof(filename), "%s_Cart.txt", client.CIN);

    FILE *cartFile = fopen(filename, "r");
    if (cartFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8);
        printf("Votre panier est vide ou le fichier du panier n'existe pas.\n");
        c_textattr(14);
        return;
    }

    produit product;
    int id_product_in_cart, quantity_in_cart;

    // Afficher les articles actuels dans le panier
    c_gotoxy(52, 8);
    printf("===== VOS ACHATS ACTUELS =====");
    c_gotoxy(32, 10);
    printf("%-10s %-20s %-15s %-10s %-10s", "ID Produit", "Nom", "Categorie", "Prix", "Quantite");
    c_gotoxy(32, 11);
    printf("--------------------------------------------------------------");

    FILE *productFile;
    
    c_textattr(2);
    while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
        productFile = fopen("produit.dat", "rb");
        if (productFile == NULL) {
            c_textattr(4);
            c_gotoxy(32, 13);
            printf("Erreur lors de l'ouverture du fichier de la liste des produits !\n");
            c_textattr(14);
            fclose(cartFile);
            return;
        }

        while (fread(&product, sizeof(produit), 1, productFile) == 1) {
            if (product.id_product == id_product_in_cart) {
                c_gotoxy(32, 12 + found);
                printf("%-10d %-20s %-15s %-10.2f %-10d", 
                       product.id_product, product.name, product.category, product.price, quantity_in_cart);
                found++;
                break;
            }
        }
        fclose(productFile);
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(32, 15);
        printf("Aucun produit trouve dans votre panier.\n");
        c_textattr(14);
        fclose(cartFile);
        return;
    }

    fclose(cartFile);

    // Demander a l'utilisateur de modifier ou supprimer des produits
    int option;
    do {
        c_gotoxy(32, 16 + found);
        c_textattr(15);
        printf("Entrez l'ID du produit a modifier/supprimer (ou -1 pour quitter) : ");
        scanf("%d", &id_product);

        if (id_product == -1) break;

        // Reouvrir le fichier du panier pour la lecture et creer un fichier temporaire
        cartFile = fopen(filename, "r");
        FILE *tempFile = fopen("temp_cart.txt", "w");
        if (cartFile == NULL || tempFile == NULL) {
            c_textattr(4);
            printf("Erreur lors de l'ouverture des fichiers !\n");
            c_textattr(14);
            return;
        }

        found = 0;
        while (fscanf(cartFile, "%d %d", &id_product_in_cart, &quantity_in_cart) == 2) {
            if (id_product_in_cart == id_product) {
                found = 1;
                int modify_option;

                c_gotoxy(32, 17 + found);
                printf("1. Modifier la quantite\n");
                c_gotoxy(32, 18 + found);
                printf("2. Supprimer le produit\n");
                c_gotoxy(32, 19 + found);
                printf("Choisissez une option : ");
                scanf("%d", &modify_option);

                if (modify_option == 1) {
                    c_gotoxy(32, 20 + found);
                    printf("Entrez la nouvelle quantite : ");
                    scanf("%d", &quantity);

                    if (quantity > 0) {
                        fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity);
                        c_gotoxy(32, 21 + found);
                        c_textattr(2);
                        printf("Quantite mise a jour avec succes.\n");
                    } else {
                        c_textattr(4);
                        c_gotoxy(32, 21 + found);
                        printf("Quantite invalide !\n");
                        c_textattr(14);
                    }
                } else if (modify_option == 2) {
                    c_gotoxy(32, 21 + found);
                    c_textattr(2);
                    printf("Produit supprime avec succes.\n");
                } else {
                    c_textattr(4);
                    c_gotoxy(32, 21 + found);
                    printf("Option invalide !\n");
                    c_textattr(14);
                    fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart);
                }
            } else {
                fprintf(tempFile, "%d %d\n", id_product_in_cart, quantity_in_cart);
            }
        }

        fclose(cartFile);
        fclose(tempFile);

        if (!found) {
            c_textattr(4);
            c_gotoxy(32, 22 + found);
            printf("ID du produit %d non trouve dans votre panier.\n", id_product);
            c_textattr(14);
        } else {
            remove(filename);
            rename("temp_cart.txt", filename);
        }
    } while (id_product != -1);

    c_textattr(2);
    c_gotoxy(32, 23 + found);
    printf("Panier mis a jour avec succes.\n");
    c_textattr(14);
    c_getch();
}

void confirm_purchases(char *Temp_cin) {
    FILE *cartFile, *productFile;
    produit p;
    int id_product_in_cart, quantity_in_cart;
    char filename[100];
    int confirm_choice;

    snprintf(filename, sizeof(filename), "%s_Cart.txt", Temp_cin);
    cartFile = fopen(filename, "r");

    if (cartFile == NULL) {
        c_textattr(4);
        c_gotoxy(32, 8); 
        printf("Your cart is empty or the cart file does not exist.\n");
        c_textattr(14);
        return;
    }
    Options options = { 
        .ops = (char *[]){"Yes", "No"},
        .len = 2,
        .title = "Do you want to confirm your purchase?"
    };

    int selection = c_select_menu_f(options);

    if (selection != 0) { // User selects "No"
        c_textattr(4);
        c_gotoxy(55, 27);
        printf("Purchase not confirmed.");
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
                    c_gotoxy(55, 21);
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
        c_gotoxy(65, 25);
        printf("Your factor is ready to print.");
    } else {
        c_textattr(4);
        c_gotoxy(32, 18);
        printf("Error removing the cart file.");
    }

    c_textattr(14);
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
        c_gotoxy(55, 27);
        printf("Achat non confirme."); // Translated
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
        c_gotoxy(65, 26);
        printf("Votre facture est prete a etre imprimee.\n"); // Translated
    } else {
        c_textattr(4);
        c_gotoxy(32, 18);
        printf("Erreur lors de la suppression du fichier du panier.\n"); // Translated
    }

    c_textattr(14);
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
        c_textcolor(4);
        c_gotoxy(50, 8);
        printf("Unable to open file");
        exit(1);
    }

    c_clrscr();
    c_textcolor(2);
    c_gotoxy(50, 10);
    printf("Enter the product ID to delete: ");
    c_textcolor(15);
    c_gotoxy(82, 10);
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
        c_textcolor(4);
        c_gotoxy(50, 12);
        printf("Warning: The product does not exist or does not belong to the specified supplier!");
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

        c_textcolor(2);
        c_gotoxy(50, 12);
        printf("The product has been successfully deleted and IDs have been reordered!");
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
        c_textcolor(4);
        c_gotoxy(50, 8);
        printf("Impossible d'ouvrir le fichier");
        exit(1);
    }

    c_clrscr();
    c_textcolor(2);
    c_gotoxy(50, 10);
    printf("Entrez l'ID du produit à supprimer : ");
    c_textcolor(15);
    c_gotoxy(82, 10);
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
        c_textcolor(4);
        c_gotoxy(50, 12);
        printf("Attention : Le produit n'existe pas ou n'appartient pas au fournisseur specifie !");
        c_textcolor(15);
    } else {
        // Reorganiser les IDs pour les produits restants
        fp = fopen("produit.dat", "wb");
        temp = fopen("temp.dat", "rb");
        int new_id = 1;

        while (fread(&p, sizeof(produit), 1, temp)) {
            p.id_product = new_id++; // Mettre à jour l'ID pour maintenir l'ordre
            fwrite(&p, sizeof(produit), 1, fp);
            usleep(100000); // Pause pour un affichage visuel fluide
        }

        fclose(fp);
        fclose(temp);

        remove("temp.dat");

        c_textcolor(2);
        c_gotoxy(50, 12);
        printf("Le produit a ete supprime avec succès et les IDs ont ete reorganises !");
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
    c_textcolor(15);
    c_gotoxy(66, 18);
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
                    liste_fournisseur(CINF);
            }
        }

        // Write the (modified or unchanged) product back to the temp file
        fwrite(&p, sizeof(produit), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (!productFound) {
        c_textcolor(4);
        c_gotoxy(65, 29);
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
    c_textcolor(15);
    c_gotoxy(66, 18);
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
                    liste_fournisseur_f(CINF);
            }
        }

        // Write the (modified or unchanged) product back to the temp file
        fwrite(&p, sizeof(produit), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (!productFound) {
        c_textcolor(4);
        c_gotoxy(65, 29);
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
    int i , j , w , l ;

    c_textcolor(1);
    c_gotoxy(64, 23);
    c_textcolor(14);
    printf("First Name   : ");
    c_textcolor(8);
    c_gotoxy(79, 23);
    scanf(" %[^\n]s", frn.prenomf);
    c_gotoxy(64, 24);
    c_textcolor(14);
    printf("Last Name    : ");
    c_textcolor(8);
    c_gotoxy(79, 24);
    scanf(" %[^\n]s", frn.nomf);
    l = w = 0 ;
    do {
        j = i = 0 ;
        c_gotoxy(64, 25 + j);
        c_textcolor(14);
        printf("CIN          : ");
        c_textcolor(8);
        c_gotoxy(79, 25 + j);
        scanf(" %s", frn.Cinf);

        if (is_CIN_unique_supplier(frn.Cinf) == 0) {
            c_gotoxy(64, 28 + i - 2);
            c_textcolor(4);
            printf("Invalid CIN format for supplier. It must start with two letters and end with five digits.");
            c_getch();
            c_gotoxy(64, 28 + i - 2);
            printf("                                                                                          ");
            c_textcolor(15);
            i += 4;
            j += 2;
            l++;
            if (l >= 2) break;
        } else {
            do {
                c_gotoxy(64, 26 + i);
                c_textcolor(14);
                printf("Enter the password : ");
                c_textcolor(8);
                strcpy(frn.mdpf, Pass_hide(20));

                c_gotoxy(64, 26 + i);
                c_textcolor(14);
                printf("Confirm the password : ");
                c_textcolor(8);
                strcpy(frn.cmdpf, Pass_hide(20));

                if (strcmp(frn.mdpf, frn.cmdpf) != 0) {
                    c_gotoxy(64, 33 );
                    c_textcolor(4);
                    printf("Passwords do not match! Please try again.");
                    w++;
                    c_getch();
                    c_gotoxy(64, 33 );
                    printf("                                         ");
                    i += 2;
                    if(w >= 2 ) break;
                } else {
                    fprintf(fp, "%s %s %s %s\n", frn.prenomf, frn.nomf, frn.Cinf, frn.mdpf);
                    break;
                }
            } while (1);
            if(w < 3 && l < 3) break;
        }
    } while (1);

    if (l < 2 & w < 2) {
        fclose(fp);
        c_textcolor(15);
        c_textcolor(2);
        c_gotoxy(64, 34 + i);
        printf("Supplier successfully added!!");
        gradientSpinner_s(20);
        c_textcolor(15);
        c_getch();
        c_clrscr();
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
    int i, j, w, l;

    c_textcolor(1);
    c_gotoxy(50, 23);
    c_textcolor(14);
    printf("Prenom       : ");
    c_textcolor(8);
    c_gotoxy(64, 23);
    scanf(" %[^\n]s", frn.prenomf);
    c_gotoxy(50, 24);
    c_textcolor(14);
    printf("Nom          : ");
    c_textcolor(8);
    c_gotoxy(64, 24);
    scanf(" %[^\n]s", frn.nomf);
    l = w = 0;
    do {
        j = i = 0;
        c_gotoxy(50, 25 + j);
        c_textcolor(14);
        printf("CIN          : ");
        c_textcolor(8);
        c_gotoxy(64, 25 + j);
        scanf(" %s", frn.Cinf);

        if (is_CIN_unique_supplier(frn.Cinf) == 0) {
            c_gotoxy(50, 28 + i - 2);
            c_textcolor(4);
            printf("Format CIN invalide pour le fournisseur. Il doit commencer par deux lettres et se terminer par cinq chiffres.");
            c_getch();
            c_gotoxy(50, 28 + i - 2);
            printf("                                                                                          ");
            c_textcolor(15);
            i += 4;
            j += 2;
            l++;
            if (l >= 2) break;
        } else {
            do {
                c_gotoxy(50, 26 + i);
                c_textcolor(14);
                printf("Entrez le mot de passe : ");
                c_textcolor(8);
                strcpy(frn.mdpf, Pass_hide(20));

                c_gotoxy(50, 26 + i);
                c_textcolor(14);
                printf("Confirmez le mot de passe : ");
                c_textcolor(8);
                strcpy(frn.cmdpf, Pass_hide(20));

                if (strcmp(frn.mdpf, frn.cmdpf) != 0) {
                    c_gotoxy(50, 33);
                    c_textcolor(4);
                    printf("Les mots de passe ne correspondent pas ! Veuillez reessayer.");
                    w++;
                    c_getch();
                    c_gotoxy(50, 33);
                    printf("                                         ");
                    i += 2;
                    if (w >= 2) break;
                } else {
                    fprintf(fp, "%s %s %s %s\n", frn.prenomf, frn.nomf, frn.Cinf, frn.mdpf);
                    break;
                }
            } while (1);
            if (w < 3 && l < 3) break;
        }
    } while (1);

    if (l < 2 & w < 2) {
        fclose(fp);
        c_textcolor(15);
        c_textcolor(2);
        c_gotoxy(50, 34 + i);
        printf("Fournisseur ajoute avec succes !!");
        gradientSpinner_s(20);
        c_textcolor(15);
        c_getch();
        c_clrscr();
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
    Options supplier_menu = {
        .ops = (char*[]) {
            "View Product List",
            "Add Product",
            "Modify Product",
            "Delete Product",
            "Display Total Sales for the Day",
            "Exit"
        },
        .len = 6,
        .title = "----- SUPPLIER MENU -----"
    };

    int choice;
    do {
        c_clrscr();
        c_textattr(2); // Green-gray
        c_gotoxy(50, 2);
        printf("----- SUPPLIER MANAGEMENT SYSTEM -----");
        c_textattr(15); // Reset to white
        c_gotoxy(50, 4);
        printf("Welcome, Supplier: %s", Temp_CIN);

        choice = c_select_menu_f(supplier_menu);

        switch (choice) {
            case 0: // View Product List
                c_clrscr();
                c_textattr(10); // Bright green
                c_gotoxy(50, 5);
                printf("Viewing Product List...");
                view_product_supplier(Temp_CIN);
                c_textattr(15);
                break;

            case 1: // Add Product
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Adding a New Product...");
                add_product(Temp_CIN);
                c_textattr(15);
                break;

            case 2: // Modify Product
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Modifying Product...");
                modify_product(Temp_CIN);
                c_textattr(15);
                break;

            case 3: // Delete Product
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Deleting a Product...");
                delete_product(Temp_CIN);
                c_textattr(15);
                break;

            case 4: // Display Total Sales for the Day
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Displaying Total Sales...");
                Display_the_Supplier_Total_amount_sales_in_the_Day(Temp_CIN);
                c_textattr(15);
                break;

            case 5: // Exit
                c_clrscr();
                c_textattr(9);
                c_gotoxy(50, 5);
                printf("Returning to the main menu...");
                c_textattr(15);
                Home_LOGIN_menu();
                break;

            default:
                c_clrscr();
                c_textattr(4);
                c_gotoxy(50, 5);
                printf("Invalid choice! Please retry.");
                c_textattr(15);
                break;
        }

        if (choice != 5) {
            c_textattr(9);
            c_gotoxy(65, 34);
            printf("Press any key to continue...");
            c_getch();
        }
    } while (choice != 5);
}
// french version
void liste_fournisseur_f(char *Temp_CIN) {
    Options supplier_menu = {
        .ops = (char*[]) {
            "Afficher la liste des produits",
            "Ajouter un produit",
            "Modifier un produit",
            "Supprimer un produit",
            "Afficher les ventes totales du jour",
            "Quitter"
        },
        .len = 6,
        .title = "----- MENU FOURNISSEUR -----"
    };

    int choice;
    do {
        c_clrscr();
        c_textattr(2);
        c_gotoxy(50, 2);
        printf("----- SYSTeME DE GESTION DES FOURNISSEURS -----");
        c_textattr(15);
        c_gotoxy(50, 4);
        printf("Bienvenue, Fournisseur : %s", Temp_CIN);

        choice = c_select_menu_f(supplier_menu);

        switch (choice) {
            case 0:
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Affichage de la liste des produits...");
                view_product_supplier(Temp_CIN);
                c_textattr(15);
                break;

            case 1:
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Ajout d'un nouveau produit...");
                add_product(Temp_CIN);
                c_textattr(15);
                break;

            case 2:
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Modification d'un produit...");
                modify_product(Temp_CIN);
                c_textattr(15);
                break;

            case 3:
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Suppression d'un produit...");
                delete_product(Temp_CIN);
                c_textattr(15);
                break;

            case 4:
                c_clrscr();
                c_textattr(10);
                c_gotoxy(50, 5);
                printf("Affichage des ventes totales...");
                Display_the_Supplier_Total_amount_sales_in_the_Day(Temp_CIN);
                c_textattr(15);
                break;

            case 5:
                c_clrscr();
                c_textattr(9);
                c_gotoxy(50, 5);
                printf("Retour au menu principal...");
                c_textattr(15);
                Home_LOGIN_menu();
                break;

            default:
                c_clrscr();
                c_textattr(4);
                c_gotoxy(50, 5);
                printf("Choix invalide ! Veuillez reessayer.");
                c_textattr(15);
                break;
        }

        if (choice != 5) {
            c_textattr(9);
            c_gotoxy(65, 34);
            printf("Appuyez sur une touche pour continuer...");
            c_getch();
        }
    } while (choice != 5);
}

void login_supplier(char *CIN) {
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    c_textattr(2);

    c_gotoxy(32, 8);
    printf("Let's connect to your account:");
    c_textattr(15);

    c_gotoxy(32, 10);
    printf("Enter your CIN: ");
    scanf("%s", CINN);

    c_gotoxy(32, 12);
    printf("Enter your PASSWORD: ");
    strcpy(passw, Pass_hide(20));
    passw[strlen(passw)] = '\0';

    FILE *fp = fopen("FOURNISSEUR.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        c_gotoxy(32, 14);
        printf("Error: Could not open the file.");
        c_textattr(14);
        return;
    }

    fournisseur f;
    while (fscanf(fp, "%*s %*s %s %s", f.Cinf, f.mdpf) == 2) {
        if (strcmp(f.Cinf, CINN) == 0 && strcmp(f.mdpf, passw) == 0) {
            c_textattr(2);
            strcpy(CIN, CINN);
            c_gotoxy(54, 14);
            printf("Connected successfully!");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();

            liste_fournisseur(CIN);
            break;
        }
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(54, 14);
        printf("You need to create an account first!");
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
    c_textattr(2);

    c_gotoxy(32, 8);
    printf("Connectons-nous a votre compte :");
    c_textattr(15);

    c_gotoxy(32, 10);
    printf("Entrez votre CIN : ");
    scanf("%s", CINN);

    c_gotoxy(32, 12);
    printf("Entrez votre MOT DE PASSE : ");
    strcpy(passw, Pass_hide(20));
    passw[strlen(passw)] = '\0';

    FILE *fp = fopen("FOURNISSEUR.txt", "r");
    if (fp == NULL) {
        c_textattr(4);
        c_gotoxy(32, 14);
        printf("Erreur : Impossible d'ouvrir le fichier.");
        c_textattr(14);
        return;
    }

    fournisseur f;
    while (fscanf(fp, "%*s %*s %s %s", f.Cinf, f.mdpf) == 2) {
        if (strcmp(f.Cinf, CINN) == 0 && strcmp(f.mdpf, passw) == 0) {
            c_textattr(2);
            strcpy(CIN, CINN);
            c_gotoxy(54, 14);
            printf("Connecte avec succes !");
            c_textattr(14);
            found = 1;
            c_getch();
            c_clrscr();

            liste_fournisseur(CIN);
            break;
        }
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(54, 14);
        printf("Vous devez d'abord creer un compte !");
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



int generate_random_id() {
    srand(time(0));
    return rand() % 1000000 + 1;
}

int date_to_days_unix(int year, int month, int day) {
    struct tm t;
    time_t t_of_day;

    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    t.tm_isdst = -1;

    t_of_day = mktime(&t);
    return t_of_day;
}

void generate_histogram(const char *title, const char *data_file) {
    // File pointer for reading data
    FILE *file = fopen(data_file, "r");
    if (file == NULL) {
        printf("Error: Unable to open data file '%s'.\n", data_file);
        return;
    }

    // Arrays to hold the parsed data
    char days[7][20];   // Days of the week (string format)
    int data[7];         // Quantities for each day
    int size = 0;        // To track number of valid entries

    // Read data from the file
    while (fscanf(file, "%s %d", days[size], &data[size]) == 2) {
        size++;
        if (size >= 7) break;  // Limit to 7 days (Monday to Sunday)
    }
    fclose(file);

    // Check if we have valid data for all 7 days
    if (size != 7) {
        printf("Error: Data file should contain 7 lines for each day of the week.\n");
        return;
    }

    // Create and write data to a file for Gnuplot
    FILE *gnuplot_data_file = fopen("data.txt", "w");
    if (gnuplot_data_file == NULL) {
        printf("Error: Unable to create data file for Gnuplot.\n");
        return;
    }

    // Writing data to the file
    for (int i = 0; i < size; i++) {
        fprintf(gnuplot_data_file, "%s %d\n", days[i], data[i]); // Format: day quantity
    }
    fclose(gnuplot_data_file);

    // Create a Gnuplot script file
    FILE *gnuplot_script = fopen("plot_commands.gp", "w");
    if (gnuplot_script == NULL) {
        printf("Error: Unable to create Gnuplot script file.\n");
        return;
    }

    // Writing Gnuplot commands for histogram
    fprintf(gnuplot_script, "set terminal pngcairo size 1920,1080 enhanced\n");  // Full-screen resolution
    fprintf(gnuplot_script, "set output 'histogram.png'\n");
    fprintf(gnuplot_script, "set title '%s'\n", title); // Use provided title
    fprintf(gnuplot_script, "set xlabel 'Days of the Week'\n");
    fprintf(gnuplot_script, "set ylabel 'Quantities'\n");
    fprintf(gnuplot_script, "set grid\n");
    fprintf(gnuplot_script, "set style data histograms\n");
    fprintf(gnuplot_script, "set style fill solid border -1\n");
    fprintf(gnuplot_script, "set boxwidth 0.6\n");

    // Custom color for Saturday and Sunday (for example, blue)
    fprintf(gnuplot_script, "set style line 1 lc rgb 'blue' pt 7 ps 1.5 lw 2\n");  
    fprintf(gnuplot_script, "plot 'data.txt' using 2:xtic(1) title 'Quantities' ls 1\n");

    fclose(gnuplot_script);

    // Run Gnuplot
    int result = system("gnuplot plot_commands.gp");
    if (result != 0) {
        printf("Error: Gnuplot command failed.\n");
        return;
    }
    c_gotoxy(50, 30);
    printf("Histogram generated successfully! Open 'histogram.png' to view the plot.");
}
//statistics of the product in  a week  starting  from a  given date
// each  day's  statiscs  are  calculated  separately
void product_statis(int id_prod, int year, int month , int day) {
    FILE *sales = fopen("sales.bin", "rb");
    FILE *sale_prod = fopen("sales_prod.bin", "rb");

    if (sales == NULL || sale_prod == NULL) {
        printf("Error: Unable to open sales.bin or sale_prod.bin!\n");
        exit(1);
    }

    sale s;
    sale_product sp;

    int week_quatities[7] = {0};

    int p_year, p_month, p_day;

    while (fread(&s, sizeof(sale), 1, sales) == 1) {
        sscanf(s.sale_date, "%d-%d-%d", &p_day, &p_month, &p_year);
        if( date_to_days_unix(year,month,day) <= date_to_days_unix (p_year,p_month,p_day) && date_to_days_unix (p_year,p_month,p_day) <= date_to_days_unix (year,month,day) + 6*24*60*60){
            while (fread(&sp, sizeof(sale_product), 1, sale_prod) == 1) {
                if (sp.sale_id == s.sale_id && sp.product_id == id_prod) {
                    week_quatities[(date_to_days_unix (p_year,p_month,p_day) - date_to_days_unix(year,month,day))/86400] += sp.quantity;
                }
            }
            rewind(sale_prod);
        }
    }


    FILE *statis = fopen("statis.txt", "w");

    char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    if (statis == NULL) {
        printf("Error: Unable to open statis.txt!\n");
        exit(1);
    }
    for (int i = 0; i < 7; i++) {
        time_t t = date_to_days_unix (year,month,day) + i*24*60*60 ;
        struct tm *time_info = localtime(&t);

        if (time_info == NULL) {
            printf("Error: Unable to convert Unix timestamp to date.\n");
            return;
        }

        // Extract day, month, and year
        int day = time_info->tm_mday;      // Day of the month (1-31)
        int month = time_info->tm_mon + 1; // Month (0-11, so add 1)
        int year = time_info->tm_year + 1900; // Years since 1900

        fprintf(statis, "%d-%d-%d %d\n",  day, month, year , week_quatities[i]);
    }
    fclose(statis);
    generate_histogram("Product Statistics in a Week", "statis.txt");
    
    fclose(sales);
    fclose(sale_prod);

}
// french version
void product_statis_f(int id_prod, int year, int month , int day) {
    FILE *sales = fopen("sales.bin", "rb");
    FILE *sale_prod = fopen("sales_prod.bin", "rb");

    if (sales == NULL || sale_prod == NULL) {
        printf("Erreur : Impossible d'ouvrir sales.bin ou sale_prod.bin !\n");
        exit(1);
    }

    sale s;
    sale_product sp;

    int week_quatities[7] = {0};

    int p_year, p_month, p_day;

    while (fread(&s, sizeof(sale), 1, sales) == 1) {
        sscanf(s.sale_date, "%d-%d-%d", &p_day, &p_month, &p_year);
        if( date_to_days_unix(year,month,day) <= date_to_days_unix (p_year,p_month,p_day) && date_to_days_unix (p_year,p_month,p_day) <= date_to_days_unix (year,month,day) + 6*24*60*60){
            while (fread(&sp, sizeof(sale_product), 1, sale_prod) == 1) {
                if (sp.sale_id == s.sale_id && sp.product_id == id_prod) {
                    week_quatities[(date_to_days_unix (p_year,p_month,p_day) - date_to_days_unix(year,month,day))/86400] += sp.quantity;
                }
            }
            rewind(sale_prod);
        }
    }


    FILE *statis = fopen("statis.txt", "w");

    char *days[] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};

    if (statis == NULL) {
        printf("Erreur : Impossible d'ouvrir statis.txt !\n");
        exit(1);
    }
    for (int i = 0; i < 7; i++) {
        fprintf(statis, "%s %d\n", days[i], week_quatities[i]);
    }
    fclose(statis);
    generate_histogram("Product Statistics in a Week", "statis.txt");
    
    fclose(sales);
    fclose(sale_prod);

}

void client_factor(char *CIN) {
    FILE *FACT = fopen("FACTEUR.pdf", "w");
    if (FACT == NULL) {
        printf("Error: Unable to create FACTEUR.pdf file!\n");
        exit(1);
    }
    
    CCD client_details;
    int found = 0;
    
    FILE *sales = fopen("sales.bin", "ab");
    FILE *sale_prod = fopen("sales_prod.bin", "ab");

    int sale_id = generate_random_id();
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

        sale_product sp;

        sp.sale_id = sale_id;
        sp.product_id = product.id_product;
        sp.quantity = client_choice_entry.quantity;
        fwrite(&sp, sizeof(sale_product), 1, sale_prod);
    }

    
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    sale s;
    s.sale_id = sale_id;
    sprintf(s.sale_date, "%02d-%02d-%d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
    sprintf(s.client_CIN, "%s", CIN);
    s.total_price = grand_total;
    fwrite(&s, sizeof(sale), 1, sales);

    fclose(client_choice_file);

    // Step 5: Print Grand Total and Close FACTEUR File
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Grand Total: %.2f DH) Tj\n0 -20 Td\n", grand_total);
    fprintf(FACT, "(=============================================) Tj\n");
    fprintf(FACT, pdf_footer);
    fclose(FACT);
    fclose(sales);
    fclose(sale_prod);
    openPDFInBrave("C:\\Users\\rabat\\Desktop\\Desktop_FILE\\c_project_last_updates\\C_PROJET_ACHATS-1\\mh\\FUNCTIONS_MERGE\\FACTEUR.pdf");
}
// french version
void client_factor_f(char *CIN) {
    
    FILE *FACT = fopen("FACTEUR.pdf", "w");

    FILE *sales = fopen("sales.bin", "ab");
    FILE *sale_prod = fopen("sales_prod.bin", "ab");

    int sale_id = generate_random_id();


    if (FACT == NULL || sales == NULL || sale_prod == NULL) {
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

        sale_product sp;

        sp.sale_id = sale_id;
        sp.product_id = product.id_product;
        sp.quantity = client_choice_entry.quantity;
        printf("sale_id : %d\n", sp.sale_id);

        fwrite(&sp, sizeof(sale_product), 1, sale_prod);
        


        fclose(produit_file);


    }


    fclose(client_choice_file);

    // Step 5: Print Grand Total and Close FACTEUR File
    fprintf(FACT, "(---------------------------------------------) Tj\n0 -20 Td\n");
    fprintf(FACT, "(Total general : %.2f DH) Tj\n0 -20 Td\n", grand_total);
    fprintf(FACT, "(=============================================) Tj\n");
    

    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    sale s;
    s.sale_id = sale_id;
    sprintf(s.sale_date, "%02d-%02d-%d", localTime->tm_mday - 3, localTime->tm_mon + 1, localTime->tm_year + 1900);
    sprintf(s.client_CIN, "%s", CIN);
    s.total_price = grand_total;
    fwrite(&s, sizeof(sale), 1, sales);


    fprintf(FACT, pdf_footer);
    fclose(FACT);
    fclose(sales);
    fclose(sale_prod);
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
}

void display_credit_cards_f(char *client_name, char *CIN) {
    c_clrscr();
    FILE *CDM_1 = fopen("CREDIT_CARD.dat", "rb");
    if (CDM_1 == NULL) {
        c_textcolor(4);
        c_gotoxy(50, 8);
        printf("ERREUR : Le fichier 'CREDIT_CARD.dat' n'existe pas !");
        exit(0);
    }

    CCD CD; // CD: CARD DETAIL
    int found = 0;
    int line = 10; // Start printing at line 10

    c_textcolor(14);
    c_gotoxy(50, 8);
    printf("------------------- Details de la Carte Credit -------------------");

    while (fread(&CD, sizeof(CCD), 1, CDM_1) == 1) {
        if (strcmp(CIN, CD.client_CIN) == 0) {
            found = 1;

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("Nom du Client : ");
            c_textcolor(14);
            printf("%s", CD.client_name);

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("CIN : ");
            c_textcolor(14);
            printf("%s", CIN);

            c_textcolor(8);
            c_gotoxy(50, line++);
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

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("CVV : ");
            c_textcolor(5);
            printf("***");

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("Date d'Expiration : ");
            c_textcolor(14);
            printf("%s/%s", CD.expiry_date.month, CD.expiry_date.year);

            line++; // Add spacing after each card
        }
    }

    if (!found) {
        c_textcolor(4);
        c_gotoxy(50, line++);
        printf("Aucune carte de credit trouvee pour le client avec CIN : %s", CIN);
    }

    fclose(CDM_1);

    c_textattr(14);
    c_gotoxy(50, line++);
    printf("----------------------------------------------------------");
}
// french version
void display_credit_cards(char *client_name, char *CIN) {
    c_clrscr();
    FILE *CDM_1 = fopen("CREDIT_CARD.dat", "rb");
    if (CDM_1 == NULL) {
        c_textcolor(4);
        c_gotoxy(50, 8);
        printf("ERREUR : Le fichier 'CREDIT_CARD.dat' n'existe pas !");
        exit(0);
    }

    CCD CD; // CD: DeTAIL DE LA CARTE
    int found = 0;
    int line = 10; // Commence l'affichage a la ligne 10

    c_textcolor(14);
    c_gotoxy(50, 8);
    printf("------------------- Details de la Carte Bancaire -------------------");

    while (fread(&CD, sizeof(CCD), 1, CDM_1) == 1) {
        if (strcmp(CIN, CD.client_CIN) == 0) {
            found = 1;

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("Nom du Client : ");
            c_textcolor(14);
            printf("%s", CD.client_name);

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("CIN : ");
            c_textcolor(14);
            printf("%s", CIN);

            c_textcolor(8);
            c_gotoxy(50, line++);
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

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("CVV : ");
            c_textcolor(5);
            printf("***");

            c_textcolor(8);
            c_gotoxy(50, line++);
            printf("Date d'Expiration : ");
            c_textcolor(14);
            printf("%s/%s", CD.expiry_date.month, CD.expiry_date.year);

            line++; // Ajoute un espace apres chaque carte
        }
    }

    if (!found) {
        c_textcolor(4);
        c_gotoxy(50, line++);
        printf("Aucune carte de credit trouvee pour le client avec le CIN : %s", CIN);
    }

    fclose(CDM_1);

    c_textattr(14);
    c_gotoxy(50, line++);
    printf("----------------------------------------------------------");
}



void Display_the_Supplier_Total_amount_sales_in_the_Day(char *CINF) {
    c_clrscr();
    FILE *sales = fopen("sales.bin", "rb");
    FILE *sale_prod = fopen("sales_prod.bin", "rb");
    FILE *produit_file = fopen("produit.dat", "rb");

    if (sales == NULL || sale_prod == NULL || produit_file == NULL) {
        c_textcolor(4);
        c_gotoxy(65, 10);
        printf("Error: Unable to open required files!\n");
        return;
    }

    // Get current date
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int current_day = localTime->tm_mday;
    int current_month = localTime->tm_mon + 1;
    int current_year = localTime->tm_year + 1900;

    // Display header
    c_textcolor(15);
    c_gotoxy(65, 10);
    printf("======== SUPPLIER TOTAL SALES REPORT ========\n");
    c_gotoxy(65, 11);
    printf("DATE: %02d-%02d-%d\n", current_day, current_month, current_year);
    c_gotoxy(65, 12);
    printf("SUPPLIER CIN: %s\n", CINF);
    c_gotoxy(65, 13);
    printf("============================================\n");
    c_gotoxy(65, 14);
    printf("| %-15s | %-10s | %-12s |\n", "CATEGORY", "QUANTITY", "SALE AMOUNT (DH)");
    c_gotoxy(65, 15);
    printf("|-----------------|------------|-----------------|\n");

    // Track sales data
    float total_sales_amount = 0.0;
    int row = 16;
    
    sale s;
    sale_product sp;
    produit p;

    // Process each sale
    while (fread(&s, sizeof(sale), 1, sales) == 1) {
        int sale_day, sale_month, sale_year;
        sscanf(s.sale_date, "%d-%d-%d", &sale_day, &sale_month, &sale_year);

        // Check if sale is from today
        if (sale_day == current_day && sale_month == current_month && sale_year == current_year) {
            // Process products in this sale
            rewind(sale_prod);
            while (fread(&sp, sizeof(sale_product), 1, sale_prod) == 1) {
                if (sp.sale_id == s.sale_id) {
                    // Find product details
                    rewind(produit_file);
                    while (fread(&p, sizeof(produit), 1, produit_file) == 1) {
                        if (p.id_product == sp.product_id && strcmp(p.CINF, CINF) == 0) {
                            float amount = p.price * sp.quantity;
                            total_sales_amount += amount;

                            // Display sale line
                            c_textcolor(2);
                            c_gotoxy(65, row++);
                            printf("| %-15s | %-10d | %-12.2f |\n", 
                                   p.category, sp.quantity, amount);
                            
                            usleep(50000); // Slow down display for readability
                            break;
                        }
                    }
                }
            }
        }
    }

    // Display totals
    c_textcolor(15);
    c_gotoxy(65, row++);
    printf("============================================\n");
    c_gotoxy(65, row++);
    printf("TOTAL SALES AMOUNT: %.2f DH\n", total_sales_amount);
    c_gotoxy(65, row);
    printf("============================================\n");

    // Cleanup
    fclose(sales);
    fclose(sale_prod);
    fclose(produit_file);

    c_gotoxy(65, row + 2);
    c_textcolor(14);
    printf("Press any key to continue...");
    c_getch();
}
// french version
void Display_the_Supplier_Total_amount_sales_in_the_Day_f(char *CINF) {
    c_clrscr();
    FILE *sales = fopen("sales.bin", "rb");
    FILE *sale_prod = fopen("sales_prod.bin", "rb");
    FILE *produit_file = fopen("produit.dat", "rb");

    if (sales == NULL || sale_prod == NULL || produit_file == NULL) {
        c_textcolor(4);
        c_gotoxy(65, 10);
        printf("Erreur : Impossible d'ouvrir les fichiers requis !\n");
        return;
    }

    // Obtenir la date actuelle
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);
    int current_day = localTime->tm_mday;
    int current_month = localTime->tm_mon + 1;
    int current_year = localTime->tm_year + 1900;

    // Afficher l'en-tête
    c_textcolor(15);
    c_gotoxy(65, 10);
    printf("======== RAPPORT TOTAL DES VENTES FOURNISSEUR ========\n");
    c_gotoxy(65, 11);
    printf("DATE : %02d-%02d-%d\n", current_day, current_month, current_year);
    c_gotoxy(65, 12);
    printf("CIN DU FOURNISSEUR : %s\n", CINF);
    c_gotoxy(65, 13);
    printf("=====================================================\n");
    c_gotoxy(65, 14);
    printf("| %-15s | %-10s | %-15s |\n", "CATEGORIE", "QUANTITE", "MONTANT VENTE (DH)");
    c_gotoxy(65, 15);
    printf("|-----------------|------------|-------------------|\n");

    // Suivre les donnees de vente
    float total_sales_amount = 0.0;
    int row = 16;
    
    sale s;
    sale_product sp;
    produit p;

    // Traiter chaque vente
    while (fread(&s, sizeof(sale), 1, sales) == 1) {
        int sale_day, sale_month, sale_year;
        sscanf(s.sale_date, "%d-%d-%d", &sale_day, &sale_month, &sale_year);

        // Verifier si la vente est d'aujourd'hui
        if (sale_day == current_day && sale_month == current_month && sale_year == current_year) {
            // Traiter les produits dans cette vente
            rewind(sale_prod);
            while (fread(&sp, sizeof(sale_product), 1, sale_prod) == 1) {
                if (sp.sale_id == s.sale_id) {
                    // Trouver les details du produit
                    rewind(produit_file);
                    while (fread(&p, sizeof(produit), 1, produit_file) == 1) {
                        if (p.id_product == sp.product_id && strcmp(p.CINF, CINF) == 0) {
                            float amount = p.price * sp.quantity;
                            total_sales_amount += amount;

                            // Afficher la ligne de vente
                            c_textcolor(2);
                            c_gotoxy(65, row++);
                            printf("| %-15s | %-10d | %-15.2f |\n", 
                                   p.category, sp.quantity, amount);
                            
                            usleep(50000); // Ralentir l'affichage pour une meilleure lisibilite
                            break;
                        }
                    }
                }
            }
        }
    }

    // Afficher les totaux
    c_textcolor(15);
    c_gotoxy(65, row++);
    printf("=====================================================\n");
    c_gotoxy(65, row++);
    printf("MONTANT TOTAL DES VENTES : %.2f DH\n", total_sales_amount);
    c_gotoxy(65, row);
    printf("=====================================================\n");

    // Nettoyage
    fclose(sales);
    fclose(sale_prod);
    fclose(produit_file);

    c_gotoxy(65, row + 2);
    c_textcolor(14);
    printf("Appuyez sur une touche pour continuer...");
    c_getch();
}

void feedback_and_rate_the_product(char *name_cl, int id_product) { 
    c_clrscr();
    FILE *client_opinion = fopen("feedback.txt", "a");
    if (client_opinion == NULL) {
        c_textcolor(4); 
        c_gotoxy(45, 8);
        printf("Error: feedback.txt does not exist!");
        return;
        }

        char comment[256];
        c_textcolor(2); // Green color for prompts
        c_gotoxy(45, 10);
        printf("%s, enter your comment about Product %d: ", name_cl, id_product);
        c_textcolor(15); // White color for input
        fflush(stdin);
        fgets(comment, sizeof(comment), stdin);
        size_t len = strlen(comment);
        if (len > 0 && comment[len - 1] == '\n') 
        comment[len - 1] = '\0'; 
        fprintf(client_opinion, "Client: %s | Product ID: %d | Comment: %s\n", name_cl, id_product, comment);

        int rating;
        c_textcolor(2);
        c_gotoxy(45, 12);
        printf("Rate the product (1 to 5 stars): ");
        c_textcolor(15);
        while (1) {
        if (scanf("%d", &rating) != 1 || rating < 1 || rating > 5) {
            while (getchar() != '\n');
            c_textcolor(4);
            c_gotoxy(45, 14);
            printf("Invalid rating. Please enter a number between 1 and 5: ");
            c_textcolor(15);
        } else {
            break;
        }
        }

        c_textcolor(2);
        c_gotoxy(45, 16);
        printf("You rated this product %d star%s: ", rating, (rating > 1) ? "s" : "");
        fprintf(client_opinion, "Rating: %d star%s\n", rating, (rating > 1) ? "s" : "");

        switch (rating) {
        case 1:
            printf("We're sorry to hear that you had a poor experience.");
            break;
        case 2:
            printf("Thank you! We'll work on improving.");
            break;
        case 3:
            printf("Thanks for the feedback! We're glad it was satisfactory.");
            break;
        case 4:
            printf("Great! Thank you for the positive feedback!");
            break;
        case 5:
            printf("Awesome! We're thrilled you loved it!");
            break;
        }
        c_textcolor(2);
        c_gotoxy(45, 18);
        printf("Thank you for your feedback!");
        fclose(client_opinion);
        c_getch();
}
// French version
void feedback_and_rate_the_product_f(char *name_cl, int id_product) {
        c_clrscr();
        FILE *client_opinion = fopen("feedback.txt", "a");
        if (client_opinion == NULL) {
        c_textcolor(4); 
        c_gotoxy(45, 8);
        printf("Erreur : feedback.txt n'existe pas !");
        return;
        }

        char comment[256];
        c_textcolor(2);
        c_gotoxy(45, 10);
        printf("%s, entrez votre commentaire sur le produit %d : ", name_cl, id_product);
        c_textcolor(15);
        fflush(stdin);
        fgets(comment, sizeof(comment), stdin);
        size_t len = strlen(comment);
        if (len > 0 && comment[len - 1] == '\n') 
        comment[len - 1] = '\0';
        fprintf(client_opinion, "Client : %s | ID Produit : %d | Commentaire : %s\n", name_cl, id_product, comment);

        int rating;
        c_textcolor(2);
        c_gotoxy(45, 12);
        printf("Notez le produit (1 à 5 etoiles) : ");
        c_textcolor(15);
        while (1) {
        if (scanf("%d", &rating) != 1 || rating < 1 || rating > 5) {
            while (getchar() != '\n');
            c_textcolor(4);
            c_gotoxy(45, 14);
            printf("Note invalide. Veuillez entrer un nombre entre 1 et 5 : ");
            c_textcolor(15);
        } else {
            break;
        }
        }

        c_textcolor(2);
        c_gotoxy(45, 16);
        printf("Vous avez attribue %d etoile%s : ", rating, (rating > 1) ? "s" : "");
        fprintf(client_opinion, "Note : %d etoile%s\n", rating, (rating > 1) ? "s" : "");

        switch (rating) {
        case 1:
            printf("Nous sommes desoles d'apprendre que votre experience a ete mauvaise.");
            break;
        case 2:
            printf("Merci ! Nous travaillerons pour nous ameliorer.");
            break;
        case 3:
            printf("Merci pour votre retour ! Nous sommes heureux que ce soit satisfaisant.");
            break;
        case 4:
            printf("Super ! Merci pour ce retour positif !");
            break;
        case 5:
            printf("Genial ! Nous sommes ravis que vous ayez adore !");
            break;
        }
        c_textcolor(2);
        c_gotoxy(45, 18);
        printf("Merci pour votre retour !");
        fclose(client_opinion);
        c_getch();
}


int check_stock_and_get_price(FILE *PCM, const char *category, const char *name, int quantity, float *price) {
    produit prod;
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

void display_supplier_menu() {
    Options menu;
    char *menu_options[] = {
        "Supplier Management",
        "Supplier Statistics",
        "Back"
    };

    menu.ops = menu_options;
    menu.len = 3;
    menu.title = "---->> Administrator Menu <<----";

    while (1) {
        int choice = c_select_menu_f(menu);

        switch (choice) {
            case 0: // Supplier Management
                menu_admin();
                break;
            case 1: { // Supplier Statistics
                c_clrscr();

                int id_prod, year, month, day;
                int valid_input = 0;

                c_textattr(2); 
                c_gotoxy(32, 8);
                printf("Enter product statistics details:");

                do {
                    c_textattr(15);
                    c_gotoxy(32, 10);
                    printf("Enter Product ID: ");
                    if (scanf("%d", &id_prod) != 1 || id_prod <= 0) {
                        c_textattr(4); // Red for error
                        c_gotoxy(32, 11);
                        printf("Invalid Product ID. Please enter a positive integer.");
                        c_textattr(15);
                        while (getchar() != '\n'); // Clear invalid input
                        continue;
                    }
                    break;
                } while (1);

                do {
                    c_textattr(15);
                    c_gotoxy(32, 12);
                    printf("Enter Year (YYYY): ");
                    if (scanf("%d", &year) != 1 || year < 1900 || year > 2100) {
                        c_textattr(4);
                        c_gotoxy(32, 13);
                        printf("Invalid Year. Please enter a year between 1900 and 2100.");
                        c_textattr(15);
                        while (getchar() != '\n'); 
                        continue;
                    }
                    break;
                } while (1);

                do {
                    c_textattr(15);
                    c_gotoxy(32, 14);
                    printf("Enter Month (MM): ");
                    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
                        c_textattr(4);
                        c_gotoxy(32, 15);
                        printf("Invalid Month. Please enter a value between 1 and 12.");
                        c_textattr(15);
                        while (getchar() != '\n'); 
                        continue;
                    }
                    break;
                } while (1);

                do {
                    c_textattr(15);
                    c_gotoxy(32, 16);
                    printf("Enter Day (DD): ");
                    if (scanf("%d", &day) != 1 || day < 1 || day > 31) {
                        c_textattr(4);
                        c_gotoxy(32, 17);
                        printf("Invalid Day. Please enter a value between 1 and 31.");
                        c_textattr(15);
                        while (getchar() != '\n'); 
                        continue;
                    }

                    // Validate day and month combination
                    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
                        c_textattr(4);
                        c_gotoxy(32, 17);
                        printf("Invalid Day for the given month.");
                        c_textattr(15);
                        continue;
                    }
                    if (month == 2) {
                        int is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                        if (day > (is_leap_year ? 29 : 28)) {
                            c_textattr(4);
                            c_gotoxy(32, 17);
                            printf("Invalid Day for February.");
                            c_textattr(15);
                            continue;
                        }
                    }
                    break;
                } while (1);

                c_clrscr();
                c_textattr(10);
                c_gotoxy(55, 5);
                printf("You selected Supplier Statistics.");
                product_statis(id_prod, year, month, day);
                image("C:\\Users\\rabat\\Desktop\\Desktop_FILE\\c_project_last_updates\\C_PROJET_ACHATS-1\\mh\\FUNCTIONS_MERGE\\histogram.png");
                c_textattr(15);
                c_getch();
                break;
            }
            case 2: // Back
                Home_LOGIN_menu();
                break;

            default:
                c_textattr(4);
                c_gotoxy(55, 22);
                printf("Invalid choice.");
                c_textattr(15);
                c_getch();
                break;
        }
    }
}
// french version
void display_supplier_menu_f() {
    Options menu;
    char *menu_options[] = {
        "Gestion des Fournisseurs",
        "Statistiques des Fournisseurs",
        "Retour"
    };

    menu.ops = menu_options;
    menu.len = 3;
    menu.title = "---->> Menu Administrateur <<----";

    while (1) {
        int choice = c_select_menu_f(menu);

        switch (choice) {
            case 0: // Gestion des Fournisseurs
                menu_admin_f();
                break;
            case 1: { // Statistiques des Fournisseurs
                c_clrscr();

                int id_prod, year, month, day;

                c_textattr(2); 
                c_gotoxy(32, 8);
                printf("Entrez les details des statistiques des produits :");

                do {
                    c_textattr(15);
                    c_gotoxy(32, 10);
                    printf("Entrez l'ID du produit : ");
                    if (scanf("%d", &id_prod) != 1 || id_prod <= 0) {
                        c_textattr(4);
                        c_gotoxy(32, 11);
                        printf("ID du produit invalide. Veuillez entrer un entier positif.");
                        c_textattr(15);
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
                } while (1);

                do {
                    c_textattr(15);
                    c_gotoxy(32, 12);
                    printf("Entrez l'annee (AAAA) : ");
                    if (scanf("%d", &year) != 1 || year < 1900 || year > 2100) {
                        c_textattr(4);
                        c_gotoxy(32, 13);
                        printf("Annee invalide. Veuillez entrer une annee entre 1900 et 2100.");
                        c_textattr(15);
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
                } while (1);

                do {
                    c_textattr(15);
                    c_gotoxy(32, 14);
                    printf("Entrez le mois (MM) : ");
                    if (scanf("%d", &month) != 1 || month < 1 || month > 12) {
                        c_textattr(4);
                        c_gotoxy(32, 15);
                        printf("Mois invalide. Veuillez entrer une valeur entre 1 et 12.");
                        c_textattr(15);
                        while (getchar() != '\n');
                        continue;
                    }
                    break;
                } while (1);

                do {
                    c_textattr(15);
                    c_gotoxy(32, 16);
                    printf("Entrez le jour (JJ) : ");
                    if (scanf("%d", &day) != 1 || day < 1 || day > 31) {
                        c_textattr(4);
                        c_gotoxy(32, 17);
                        printf("Jour invalide. Veuillez entrer une valeur entre 1 et 31.");
                        c_textattr(15);
                        while (getchar() != '\n');
                        continue;
                    }

                    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
                        c_textattr(4);
                        c_gotoxy(32, 17);
                        printf("Jour invalide pour le mois donne.");
                        c_textattr(15);
                        continue;
                    }
                    if (month == 2) {
                        int is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                        if (day > (is_leap_year ? 29 : 28)) {
                            c_textattr(4);
                            c_gotoxy(32, 17);
                            printf("Jour invalide pour fevrier.");
                            c_textattr(15);
                            continue;
                        }
                    }
                    break;
                } while (1);

                c_clrscr();
                c_textattr(10);
                c_gotoxy(55, 5);
                printf("Vous avez selectionne Statistiques des Fournisseurs.");
                product_statis(id_prod, year, month, day);
                image("C:\\Users\\rabat\\Desktop\\Desktop_FILE\\c_project_last_updates\\C_PROJET_ACHATS-1\\mh\\FUNCTIONS_MERGE\\histogram.png");
                c_textattr(15);
                c_getch();
                break;
            }
            case 2: // Retour
                Home_LOGIN_menu();
                break;

            default:
                c_textattr(4);
                c_gotoxy(55, 22);
                printf("Choix invalide.");
                c_textattr(15);
                c_getch();
                break;
        }
    }
}


void menu_admin() {
    int current_option = 0;
    int key;
    const int options_count = 4;

    char *options[] = {
        "Add a Supplier",
        "Delete a Supplier",
        "View Supplier List",
        "Exit"
    };

    int frame_width = 60;
    int frame_height = 10;
    int frame_x = 55; 
    int frame_y = 12;

    do {
        c_textattr(2);
        c_clrscr();

        // Draw the menu frame
        draw_frame(frame_width, frame_height, frame_x, frame_y);

        // Print menu title
        c_gotoxy(28, 5);
        printf("---------------------------------  Administrator Menu - Supplier Management  ---------------------------------");

        // Display options
        for (int i = 0; i < options_count; i++) {
            c_gotoxy(70, 15 + i);
            if (i == current_option) {
                c_textcolor(10); // Green for highlighted option
                printf("> %s", options[i]);
            } else {
                c_textcolor(15); // White for other options
                printf("  %s", options[i]);
            }
        }

        // Wait for user input and navigate the menu
        key = c_getch();
        switch (key) {
            case 72: // Arrow up
                current_option = (current_option == 0) ? options_count - 1 : current_option - 1;
                break;
            case 80: // Arrow down
                current_option = (current_option == options_count - 1) ? 0 : current_option + 1;
                break;
            case 13: // Enter key
                c_textattr(2);
                switch (current_option) {
                    case 0:
                        add_supplier();
                        break;
                    case 1:
                        delete_supplier();
                        break;
                    case 2:
                        show_supplier();
                        break;
                    case 3:
                        c_gotoxy(65, 23);
                        c_textcolor(12); // Red for exit message
                        printf("Exiting administrator menu...(tap any key)");
                        c_getch();
                        display_supplier_menu();
                        break;
                }
                break;
        }
    } while (1);
}
// french version
void menu_admin_f() {
    int current_option = 0;
    int key;
    const int options_count = 4;

    char *options[] = {
        "Ajouter un Fournisseur",
        "Supprimer un Fournisseur",
        "Voir la Liste des Fournisseurs",
        "Quitter"
    };

    int frame_width = 60;
    int frame_height = 10;
    int frame_x = 55; 
    int frame_y = 12;

    do {
        c_textattr(2);
        c_clrscr();

        // Draw the menu frame
        draw_frame(frame_width, frame_height, frame_x, frame_y);

        // Print menu title
        c_gotoxy(28, 5);
        printf("---------------------------------  Menu Administrateur - Gestion des Fournisseurs  -----------------------------");

        // Display options
        for (int i = 0; i < options_count; i++) {
            c_gotoxy(70, 15 + i);
            if (i == current_option) {
                c_textcolor(10); // Green for highlighted option
                printf("> %s", options[i]);
            } else {
                c_textcolor(15); // White for other options
                printf("  %s", options[i]);
            }
        }

        // Wait for user input and navigate the menu
        key = c_getch();
        switch (key) {
            case 72: // Arrow up
                current_option = (current_option == 0) ? options_count - 1 : current_option - 1;
                break;
            case 80: // Arrow down
                current_option = (current_option == options_count - 1) ? 0 : current_option + 1;
                break;
            case 13: // Enter key
                c_textattr(2);
                switch (current_option) {
                    case 0:
                        add_supplier_f();
                        break;
                    case 1:
                        delete_supplier_f();
                        break;
                    case 2:
                        show_supplier_f();
                        break;
                    case 3:
                        c_gotoxy(65, 23);
                        c_textcolor(12); // Red for exit message
                        printf("Sortie du menu administrateur...(appuyez sur une touche)");
                        c_getch();
                        display_supplier_menu_f();
                        break;
                }
                break;
        }
    } while (1);
}

// Function to get console dimensions
void get_console_size(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Function to draw the menu frame
void draw_menu_frame(int x, int y, int width, int height) {
    c_textcolor(2);
    c_gotoxy(x, y);
    for (int i = 0; i < width; i++) printf("=");
    for (int i = 1; i <= height; i++) {
        c_textcolor(2);
        c_gotoxy(x, y + i);
        printf("|");
        c_gotoxy(x + width - 1, y + i);
        printf("|");
    }
    // c_textcolor(14);
    c_textcolor(2);
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
    c_textattr(15); 
    c_gotoxy(28, 6);
    printf("****    ****    ****    ****    ****   ---->> Gestion des Achat <<----   ****    ****    ****    ****     ****");
    // Display the title at specific coordinates
    c_textattr(2); 
    c_gotoxy(28, 10);
    printf("%s", options.title);
    c_textattr(7); 
    // Draw the menu frame
    draw_menu_frame(frame_x, frame_y, frame_width, frame_height);

    // Display menu options
    for (int i = 0; i < options.len; i++) {
        c_textattr(op == i ? 2 : 15); // Highlight the current option
        c_gotoxy(frame_x + (frame_width - strlen(options.ops[i])) / 2, frame_y + 2 + i);
        printf("%s", options.ops[i]);
    }

    // Footer instructions
    c_textattr(8);
    c_gotoxy(57, 26);
    printf("Use UP/DOWN arrows to navigate, ENTER to select");
    c_textattr(2); // Reset text color
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
void Home_LOGIN_menu() {
    c_textcolor(2);
    char border_line[130];
    memset(border_line, '=', sizeof(border_line) - 1);
    border_line[sizeof(border_line) - 1] = '\0';

    printf("%s\n", border_line);
    c_gotoxy(1, 2);
    printf("|%-126s|\n", "");
    c_gotoxy(2, 3);
    printf("|%-126s|\n", "---------------------------------------------     HOME -- PAGE    ---------------------------------------------");
    c_gotoxy(1, 4);
    printf("%s\n", border_line);

    options.title = "---->> HOME PAGE <<----";
    options.ops = Home_LOGIN;
    options.len = sizeof(Home_LOGIN) / sizeof(Home_LOGIN[0]);

    int selected = c_select_menu_f(options);

    printf("%s\n", border_line);

    if (selected == 3) { // Option "Exit"
        Home_OPTIONS();
    } else {
        char *Client_CIN = (char *)malloc(20 * sizeof(char));
        char *Supplier_CIN = (char *)malloc(20 * sizeof(char));

        if (selected == 0) {
            display_supplier_menu();
        } else if (selected == 1) { // Fournisseur
            Options menuOptions = {
                .ops = (char *[]) { "Login", "Back to Main Menu", "Leave Program" },
                .len = 3,
                .title = "---->> SUPPLIER MENU <<----"
            };
            int choice;
            do {
                printf("%s\n", border_line);
                choice = c_select_menu_f(menuOptions);
                switch (choice) {
                    case 0: // Login
                        login_supplier(Supplier_CIN);
                        break;
                    case 1: // Back to Main Menu
                        Home_LOGIN_menu();
                        break;
                    case 2: // Leave Program
                        free(Client_CIN);
                        free(Supplier_CIN);
                        c_textcolor(15);
                        exit(0);
                }
            } while (choice != 1 && choice != 2);
        } else if (selected == 2) { // Client
            Options menuOptions = {
                .ops = (char *[]) { "Login", "Sign Up", "Back to Main Menu", "Leave Program" },
                .len = 4,
                .title = "---->> CLIENT MENU <<----"
            };
            int choice;
            do {
                printf("%s\n", border_line);
                choice = c_select_menu_f(menuOptions);
                switch (choice) {
                    case 0: // Login
                        clientLogin(Client_CIN);
                        break;
                    case 1: // Sign Up
                        sign_up_client();
                        break;
                    case 2: // Back to Main Menu
                        Home_LOGIN_menu();
                        break;
                    case 3: // Leave Program
                        free(Client_CIN);
                        free(Supplier_CIN);
                        c_textcolor(15);
                        exit(0);
                }
            } while (choice != 2 && choice != 3);
        } else {
            Home_OPTIONS();
        }

        free(Client_CIN);
        free(Supplier_CIN);
    }
    c_getch();
}

void Home_LOGIN_menu_f() {
    c_textcolor(2);
    char border_line[130];
    memset(border_line, '=', sizeof(border_line) - 1);
    border_line[sizeof(border_line) - 1] = '\0';

    printf("%s\n", border_line);
    c_gotoxy(1, 2);
    printf("|%-126s|\n", "");
    c_gotoxy(2, 3);
    printf("|%-126s|\n", "---------------------------------------------     PAGE D'ACCUEIL    ---------------------------------------------");
    c_gotoxy(1, 4);
    printf("%s\n", border_line);

    options.title = "---->> PAGE D'ACCUEIL <<----";
    options.ops = Accueil_CONNEXION;
    options.len = sizeof(Accueil_CONNEXION) / sizeof(Accueil_CONNEXION[0]);

    int selected = c_select_menu_f(options);

    printf("%s\n", border_line);

    if (selected == 3) { // Option "Quitter"
        Home_OPTIONS();
    } else {
        char *Client_CIN = (char *)malloc(20 * sizeof(char));
        char *Supplier_CIN = (char *)malloc(20 * sizeof(char));

        if (selected == 0) {
            display_supplier_menu_f();
        } else if (selected == 1) { // Fournisseur
            Options menuOptions = {
                .ops = (char *[]) { "Se Connecter", "Retour au Menu Principal", "Quitter le Programme" },
                .len = 3,
                .title = "---->> MENU FOURNISSEUR <<----"
            };
            int choice;
            do {
                printf("%s\n", border_line);
                choice = c_select_menu_f(menuOptions);
                switch (choice) {
                    case 0: // Se Connecter
                        login_supplier_f(Supplier_CIN);
                        break;
                    case 1: // Retour au Menu Principal
                        Home_LOGIN_menu_f();
                        break;
                    case 2: // Quitter le Programme
                        free(Client_CIN);
                        free(Supplier_CIN);
                        c_textcolor(15);
                        exit(0);
                }
            } while (choice != 1 && choice != 2);
        } else if (selected == 2) { // Client
            Options menuOptions = {
                .ops = (char *[]) { "Se Connecter", "S'inscrire", "Retour au Menu Principal", "Quitter le Programme" },
                .len = 4,
                .title = "---->> MENU CLIENT <<----"
            };
            int choice;
            do {
                printf("%s\n", border_line);
                choice = c_select_menu_f(menuOptions);
                switch (choice) {
                    case 0: // Se Connecter
                        clientLogin_f(Client_CIN);
                        break;
                    case 1: // S'inscrire
                        sign_up_client_f();
                        break;
                    case 2: // Retour au Menu Principal
                        Home_LOGIN_menu_f();
                        break;
                    case 3: // Quitter le Programme
                        free(Client_CIN);
                        free(Supplier_CIN);
                        c_textcolor(15);
                        exit(0);
                }
            } while (choice != 2 && choice != 3);
        } else {
            Home_OPTIONS();
        }

        free(Client_CIN);
        free(Supplier_CIN);
    }
    c_getch();
}

//-----------------------function delete supplier--------------

void delete_supplier() {
    FILE *fp = fopen("fournisseur.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        c_gotoxy(50, 25);
        printf("Unable to open the file.");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
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

    while (fscanf(fp, "%s %s %s %s", f.prenomf, f.nomf, f.Cinf, f.mdpf) == 4) {
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

    if (tr == 0) {
        c_gotoxy(60, y);
        c_textcolor(4);
        printf("Warning, the supplier does not exist!!");
        c_textcolor(15);
        remove("temp.txt");
    } else {
        remove("fournisseur.txt");
        rename("temp.txt", "fournisseur.txt");
        gradientSpinner_s(20); // Show the spinner first
        c_gotoxy(60, y); // Set position after the spinner
        c_textcolor(2);
        printf("M. %s %s successfully deleted", fs.nomf, fs.prenomf); // Show the success message after spinner
        c_textcolor(15);
    }
    c_getch();
}
// version french
void delete_supplier_f() {
    FILE *fp = fopen("fournisseur.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL) {
        c_gotoxy(50, 25);
        printf("Impossible d'ouvrir le fichier.");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return;
    }

    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        c_gotoxy(50, 26);
        printf("Le fichier fournisseur.txt est vide.");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }
    rewind(fp);

    char CIN[30];
    c_gotoxy(60, 27);
    printf("Entrez le CIN du fournisseur: ");
    c_gotoxy(90, 27);
    scanf("%s", CIN);
    int tr = 0;
    fournisseur f, fs;
    int y = 29;

    while (fscanf(fp, "%s %s %s %s", f.prenomf, f.nomf, f.Cinf, f.mdpf) == 4) {
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

    if (tr == 0) {
        c_gotoxy(60, y);
        c_textcolor(4);
        printf("Attention, le fournisseur n'existe pas!!");
        c_textcolor(15);
        remove("temp.txt");
    } else {
        remove("fournisseur.txt");
        rename("temp.txt", "fournisseur.txt");
        gradientSpinner_s(20);
        c_gotoxy(60, y);
        c_textcolor(2);
        printf("M. %s %s supprime avec succes", fs.nomf, fs.prenomf);
        c_textcolor(15);
    }
    c_getch();
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
    c_clrscr();
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
    c_clrscr();
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
