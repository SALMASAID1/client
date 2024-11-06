#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include "function.h"
void set_color(int color_code) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}


typedef struct {
    char nomf[30];
    char prenomf[30];
    char Cinf[30]; // CIN de fournisseur
    int mdpf;      // Mot de passe de fournisseur
}fournisseur;
typedef struct {
    char name[20];         // Nom du produit
    float price;           // Prix du produit
    int quantity;         // Quantite en stock
    char category[50];   // Categorie du produit
    char description[100];    // description 
}produit;
//----------------------------------------add product--------------------------------------
 void add_product(){
    FILE *fp;
    fp=fopen("produit.txt","a+");
    if(fp==NULL){
        printf(" unable to open file");
        exit(1);
    }
    produit p;
    printf("\n\n\n\n\n\n\n\t\t\t\tenter product name      :");scanf(" %[^\n]s",p.name);
    printf("\t\t\t\tenter product category :");scanf(" %[^\n]s",p.category);
    printf("\t\t\t\tenter product price     :");scanf(" %f",&p.price);
    printf("\t\t\t\tenter product quantity :");scanf(" %d",&p.quantity);
    printf("\t\t\t\tenter product description :");scanf(" %[^\n]s",p.description);
    fprintf(fp,"%s %s %.2f %d %s\n",p.name,p.category,p.price,p.quantity,p.description);
    fclose(fp);
    printf("\t\t\t\t\tProduct added successfully \n");

}
//------------------------------------delete product-----------------------
void delete_product(){
    FILE *fp,*temp;
    fp=fopen("produit.txt","r");
    temp=fopen("temp.txt","w");
    char name_pr[20];
    int tr=0;
    if(fp==NULL && temp==NULL){
        printf("unable to open file");
        exit(1);
    }
    printf("enter the product name to delete:");
    scanf(" %[^\n]s",name_pr);
    produit p;
    while(fscanf(fp,"%s %s %f %d %s",p.name,p.category,&p.price,&p.quantity,p.description)==5){
        if(strcmp(p.name,name_pr)!=0){
            tr=1;
            fprintf(temp,"%s %s %.2f %d %s\n",p.name,p.category,p.price,p.quantity,p.description);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt","produit.txt");
    if(tr==0) printf("\nbe careful the product does not exist !!");
    else printf("\nthe product is successfully deleted!!\n");

}














//------------------------------------modify product---------------------


void modify_product(){
    FILE *fp,*temp;
    fp=fopen("produit.txt","r");
    temp=fopen("temp.txt","w");
    if(fp==NULL && temp==NULL){
        printf("unable to open file");
        exit(1);
    }
    produit p,pv;
  
   // char name_pr[20];
    int tr=0;
    printf("enter the product to modify:");scanf(" %[^\n]s",pv.name);
    while(fscanf(fp,"%s %s %f %d %s \n",p.name,p.category,&p.price,&p.quantity,p.description)==5){
     if(strcmp(p.name,pv.name)==0){
        tr=1;
        //strcpy(p.name,pv.name);
        printf(" enter the new category:");scanf(" %[^\n]s",pv.category);
        strcpy(p.category,pv.category);
        printf("       enter the new price :");scanf("%f",&pv.price);
        p.price=pv.price;
        printf("    enter the new quantity :");scanf("%d",&pv.quantity);
        p.quantity=pv.quantity;
        printf(" enter the new description :");scanf(" %[^\n]s",pv.description);
        strcpy(p.description,pv.description);
     }
     fprintf(temp,"%s %s %.2f %d %s\n",p.name,p.category,p.price,p.quantity,p.description);


    }
    fclose(fp);
    fclose(temp);
    remove("produit.txt");
    rename("temp.txt","produit.txt");
    
    if(tr==0) printf("\nbe careful the product does not exist !!");
    else printf("\nthe product is successfully modified !!\n");

}



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
//------------------------------------add supplier-----------------------------

void add_supplier() {
    FILE *fp;
    fp = fopen("fournisseur.txt", "a+");
    if (fp == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }

    fournisseur frn;

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
            

            printf("Enter password : ");
            scanf("%d", &frn.mdpf);

            fprintf(fp, "%s %s %s %d\n", frn.prenomf, frn.nomf, frn.Cinf,  frn.mdpf);
            break;
        }
    } while (1);

    fclose(fp);
    int vert=2;
     set_color(vert);
    printf("\nsupplier adds successfully!!\n");
}

int main() {
   // add_supplier();
   //delete_product();
    add_product();
    //modify_product();
    
    //printf("Fournisseur ajoute avec succes!!\n");
   
    return 0;
}
