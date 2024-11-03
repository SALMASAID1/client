#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include"fonction.h"

int main(){
    int choice;

do{

    printf("1-Login\n");
    printf("2-Sign In\n");
    printf("3-Leave page\n");
    printf(" ---->> GIVE CHOICE :");scanf("%d",&choice);

    switch(choice){
        case 1:{Login();break;}
         case 2:{sign_in();break;}
          case 3:{leave();break;}

        default:setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY, 0);
                printf("Incorrect choice!!!!! ur choice should be between [1 - 3] ..retry please.\n");
               resetConsoleColor();
    }

}while(choice!=0);



return 0;
}
