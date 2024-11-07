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
    c_textcolor(1);
    c_gotoxy(30 , 3 );
    printf("Enter product name: ");
    scanf(" %[^\n]s",p.name);
    c_gotoxy(30 , 4 );
    printf("Enter product category: ");
    scanf(" %[^\n]s",p.category);
    c_gotoxy(30 , 5 );
    printf("Enter product price: ");
    scanf("%f", &p.price);
    c_gotoxy(30 , 6 );
    printf("Enter product quantity: ");
    scanf("%d", &p.quantity);
    c_gotoxy(30 , 7 );
    printf("Enter product description: ");
    scanf(" %[^\n]s",p.description);
    c_textcolor(15);
    //set_color(7);

    // Enregistrement du produit dans le fichier
    fprintf(fp, " %d %s %s %.2f %d %s\n", p.id_product, p.name, p.category, p.price, p.quantity, p.description);
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
             printf("\t\t\t\t\t\t\t\033[1;33m ==========================\033[0m\n");
             c_textcolor(5);
             printf("\t\t\t\t\t\t\t | 1. modify name               |\n");
             printf("\t\t\t\t\t\t\t | 2. modify category           |\n");
             printf("\t\t\t\t\t\t\t | 3. modify price              |\n");
             printf("\t\t\t\t\t\t\t | 4. modify quantity           |\n");
             printf("\t\t\t\t\t\t\t | 5. modify description        |\n");
             printf("\t\t\t\t\t\t\t\033[1;33m ==========================\033[0m\n");
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
                  
                  printf(" enter the new name:");scanf(" %[^\n]s",pn.name);
                  strcpy(p.name,pn.name);

                break;
                case 2:
                  printf(" enter the new category:");scanf(" %[^\n]s",pn.category);
                  strcpy(p.category,pn.category);
                 break;
                case 3:
                   printf("       enter the new price :");scanf("%f",&pn.price);
                   p.price=pn.price;
                 break;
                case 4:
                  printf("    enter the new quantity :");scanf("%d",&pn.quantity);
                  p.quantity=pn.quantity;
                 break;
                case 5:
                  printf(" enter the new description :");scanf(" %[^\n]s",pn.description);
                  strcpy(p.description,pn.description);
                 break;
                 default:
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
     c_gotoxy(30,20);
    if(tr==0 || r==0){
          c_textcolor(4);
         
        printf("\n\n\n\t\t\t\t\tbe careful the product does not exist !!"); 
    c_textcolor(15);
    }
    else{
        
      c_textcolor(2);
      printf("\n\n\n\t\t\t\t\tthe product is successfully modified !!\n");
      c_textcolor(15);
      }
     
     }
//-------------------------------------------sign fournisseur-------------------------------

//------------------------------------add supplier-----------------------------

//------------------------------------verification cin---------------------
int veri_cin(char *cin) {
    FILE *fr;
    fr = fopen("fournisseur.txt", "r");
    if (fr == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }
    fournisseur four;
    while (fscanf(fr, "%s %s %s %d", four.prenomf, four.nomf, four.Cinf,&four.mdpf) == 4) {
        if (strcmp(cin, four.Cinf) == 0) {
            fclose(fr);
            return 0; // CIN deja existant
        }
    }
    fclose(fr);
    return 1; // CIN n'existe pas
}
//-------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
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

    printf("\nfirst name : ");
    scanf(" %[^\n]s", frn.prenomf);

    printf("second name  : ");
    scanf(" %[^\n]s", frn.nomf);

    do {
        printf("    CIN  : ");
        scanf(" %[^\n]s", frn.Cinf);

        if (veri_cin(frn.Cinf) == 0) {
            printf("Be careful, the CIN is already used!\n");
        } else {
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
    int vert=2;
     set_color(vert);
    printf("\nsupplier adds successfully!!\n");
}
