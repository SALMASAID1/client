#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h> 
#include "conio.h"
#include "function.h"
typedef struct {
    char nomf[30];
    char prenomf[30];
    char Cinf[30]; // CIN de fournisseur
    char mdpf[20];      // Mot de passe de fournisseur
}fournisseur;
typedef struct {
    int id_product ;
    char name[20];          // Nom du produit
    float price;           // Prix du produit
    int quantity;         // Quantite en stock
    char category[50];   // Categorie du produit
    char description[100];    // description
}product;
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
void set_color(int color_code) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}

void add_product();
int get_next_product_id(FILE *fp);
//----------------------------------------add product--------------------------------------

int get_next_product_id(FILE *fp) {
    product p;
    int id = 1;

    // Go to the end of the file to check if it’s empty
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) != 0) {  // If the file is not empty
        rewind(fp);
        while (fscanf(fp, "%d %s %s %f %d %[^\n]s", &p.id_product, p.name, p.category, &p.price, &p.quantity, p.description) == 6) {
            id = p.id_product + 1;  // Find the last ID and increment it
        }
    }
    rewind(fp);
    return id;
}

// Function to add a product
void add_product() {
    FILE *fp = fopen("produit.txt", "a+");
    if (fp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    product p;
    p.id_product = get_next_product_id(fp);  // Set a unique product ID

    // Read product information
    c_textcolor(1);
    c_gotoxy(30, 3);
    printf("Enter product name: ");
    scanf(" %[^\n]s", p.name);
    c_gotoxy(30, 4);
    printf("Enter product category: ");
    scanf(" %[^\n]s", p.category);
    c_gotoxy(30, 5);
    printf("Enter product price: ");
    scanf("%f", &p.price);
    c_gotoxy(30, 6);
    printf("Enter product quantity: ");
    scanf("%d", &p.quantity);
    c_gotoxy(30, 7);
    printf("Enter product description: ");
    scanf(" %[^\n]s", p.description);
    c_textcolor(15);

    // Save the product to the file
    fprintf(fp, "%d %s %s %.2f %d %s\n",p.id_product,p.name,p.category,p.price,p.quantity,p.description);
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

//------------------------------------add supplier-----------------------------

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
//---------------------------------------------------------menu 2-------
void Menu3(int *c) {
    // Set gray color for the surrounding text
    printf("\033[90m\n\n\n\n\n\n");

    // Set yellow color for the borders
    printf("\t\t\t\t\t\t\033[1;33m  ======================================================\033[0m\n");

    // Set yellow background with gray text for the main heading
    printf("\033[43;90m");
    printf("\t\t\t\t\t\t  | Vous voulez :                                      | \n");
    printf("\033[0m");

    // Set gray color for the options text
    printf("\033[90m");
    printf("\t\t\t\t\t\t  | 1. Ajouter un Produit                              |\n");
    printf("\t\t\t\t\t\t  | 2. Afficher Mes Produits                           |\n");
    printf("\t\t\t\t\t\t  | 3. Modifier un Produit                             |\n");
    printf("\t\t\t\t\t\t  | 4. Chercher un Produit                             |\n");
    printf("\t\t\t\t\t\t  | 5. Supprimer un Produit                            |\n");
    printf("\t\t\t\t\t\t  | 6. Afficher le montant total de mes ventes         |\n");
    printf("\t\t\t\t\t\t  | 7. Afficher les quantites vendues de mes articles  |\n");
    printf("\t\t\t\t\t\t  | 8. Afficher les demandes d'achats non effectuees   |\n");
    printf("\t\t\t\t\t\t  | 9. Retour                                          |\n");
    printf("\033[0m");

    // Set yellow color for the bottom border
    printf("\t\t\t\t\t\t\033[1;33m  ======================================================\033[0m\n");

    // Reset color and prompt user for input
    printf("\033[0m\n\t\t\t\t\t\t Saisissez votre choix : ");
    scanf("%d", c);
}

//-----------------------------------------------------------------------
void add_supplier() {
    c_clrscr();

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
        if (veri_cin(frn.Cinf) == 0) {
            c_gotoxy(60,12);
            printf("Be careful, the CIN is already used!\n");
            c_getch();
            c_clrscr();
        } else {
            c_gotoxy(50,12);
             printf("Saisir le mot de passe : ");
            i = 0;

            // Saisie et masquage du mot de passe avec '*'
            while ((ch = getch()) != '\r' && i < 19) {  // Limite à 19 caractères
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
//--------------------------------leave--------------------------------------------------
void leave(){
    c_textattr(1);
    printf("Exiting the Aplication...\n\t**GOOD BYE**\t");
    exit(0);
   c_textattr(14);

}

//-------------------------------interface-----------------------------------------------
 void Menu(){ 
    int choice;


    do {    c_textattr(8);
       c_gotoxy(50,6); printf("1 - Login"); 
        c_gotoxy(50,7);printf("2 - Sign In");
        c_gotoxy(50,8);printf("3 - Leave page");
        c_textattr(14);
        c_gotoxy(50,9); printf(" ---->> GIVE CHOICE : ");
         if (scanf("%d", &choice) != 1) {
            // Clear invalid input from the buffer
            while (getchar() != '\n');
                 c_textattr(4);
           c_gotoxy(50,11); printf("Invalid input. Please enter a number.\n");
           c_clrscr();
                 c_textattr(14);
            continue;  // Restart the loop
        }
         c_clrscr();
        switch (choice) {
            case 1:
              Login();
              
              
                break;
            case 2:
                  add_supplier();
                break;
            case 3:
                leave();
                break;
            default:
                 c_textattr(4);
                printf("Please choose a valid option.\n");
                 c_textattr(14);
                break;
        }

    } while (choice != 3);  // Exit the loop if choice is 3
    c_getch();
    c_clrscr();
 }
//----------------------------------------------------------------------------------------
//---------------------------login------------------------------------------------------
 void Login() {
    c_clrscr();
    char passw[20];
    int found = 0;
    char CINN[20];
    int k;
      c_textattr(8);
     c_gotoxy(60,6);printf("Let's connect to your account:\n");
      c_textattr(14);
     c_gotoxy(50,8);printf("Enter your CIN: ");
    scanf("%s", CINN);

    c_gotoxy(50,10);printf("Enter your PASSWORD: ");
        for (k = 0; k < 19; k++) {
        passw[k] = getch();

        if (passw[k] == '\r') {
            break;
        }

        printf("*");
    }
    passw[k] = '\0';

    FILE *fp = fopen("fournisseur.txt", "r");
    if (fp == NULL) {
             c_textattr(4);
        printf("\nError: Could not open the file.\n");
     c_textattr(14);
        return;
    }

    fournisseur four;
    while (fscanf(fp, "%*s %*s %s %s", four.Cinf, four.mdpf) == 2) {
        if (strcmp(four.Cinf, CINN) == 0 && strcmp(four.mdpf, passw) == 0) {
                 c_textattr(2);

            c_gotoxy(50,12);printf("\nConnected successfully!\n");
             c_textattr(14);

            found = 1;
            system("cls");
            Menu1();

            break;
        }
    }

    if (!found) {
        c_textattr(4);
        c_gotoxy(50,12);printf("\nYou need to create an account first!\n");
         c_textattr(14);

    }

    fclose(fp);
}












 //-------------------------------------------menu2--------------------------------
void Menu1(){ 
    int choice;


    do { 
         // Set gray color for the surrounding text
    printf("\033[90m\n\n\n\n\n\n");

    // Set yellow color for the borders
    printf("\t\t\t\t\t\t\033[1;33m  ======================================================\033[0m\n");

    // Set yellow background with gray text for the main heading
    printf("\033[43;90m");
    printf("\t\t\t\t\t\t  | What would you like to do:                        | \n");
    printf("\033[0m");

    // Set gray color for the options text
    printf("\033[90m");
    printf("\t\t\t\t\t\t  | 1. Add a Product                                  |\n");
    printf("\t\t\t\t\t\t  | 2. Modify a Product                               |\n");
    printf("\t\t\t\t\t\t  | 3. Delete a Product                               |\n");
    printf("\t\t\t\t\t\t  | 4. Search for a Product                           |\n");
    printf("\t\t\t\t\t\t  | 5. Return                                         |\n");
    printf("\033[0m");

    // Set yellow color for the bottom border
    printf("\t\t\t\t\t\t\033[1;33m  ======================================================\033[0m\n");

    // Reset color and prompt user for input
    printf("\033[0m\n\t\t\t\t\t\t Enter your choice: ");   
         if (scanf("%d", &choice) != 1) {
            // Clear invalid input from the buffer
            while (getchar() != '\n');
                 c_textattr(4);
           c_gotoxy(50,11); printf("Invalid input. Please enter a number.\n");
           c_clrscr();
                 c_textattr(14);
            continue;  // Restart the loop
        }
         c_clrscr();
        switch (choice) {
            case 1:
              add_product();
                break;
            case 2:
                  modify_product();
                break;
            case 3:
               delete_product();
                break;
            case 4:
               //delete_product();
                break;
            case 5:
            leave();
                break;
            default:
                 c_textattr(4);
                printf("Please choose a valid option.\n");
                 c_textattr(14);
                break;
        }

    } while (choice != 5);  // Exit the loop if choice is 3
    c_getch();
    c_clrscr();
 }


