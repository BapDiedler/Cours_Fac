//exercice 4
#include <stdlib.h>
#include <stdio.h> 
int main(int argc, char*argv[]){
    short bit;
    scanf("%d",&bit);
    short bit2, ou;
    scanf("%d",&bit2);
    if (bit | bit2){
        printf("pour le ou : 1\n");
    }
    else{
        printf("pour le ou : 0\n");
    }
    if (bit & bit2){
        printf("pour le et : 1\n");
    }
    else{
        printf("pour le et : 0\n");
    }
    if (!bit){
        printf("pour le non avec bit : 1\n");
    }
    else{
        printf("pour le non avec bit : 0\n");
    }
    //autres solutions
    /*printf("et bit à  bit2: %d\n",bit*bit2);
    ou = bit+bit2;
    if(ou==2){
        ou=1;
    }
    printf("ou bit à  bit2: %d\n",ou);
    printf("on (1er bit): %d\n", 1-bit);*/
    int nb1;
    scanf("%d",&nb1);
    int nb2;
    scanf("%d",&nb2);
    int res1;
    res1=nb1;
    int num=1;
    //affichage de nb1
    while(res1!=0){
        printf("le bit numero %d est: %d\n",num,res1%2);
        ++num;
        res1=res1/2;   
        }
    //affichage de nb2
    int res2;
    res2= nb2;
    num=1;
    while(res2!=0){
        printf("le bit numero %d est: %d\n",num,res2%2);
        ++num;
        res2=res2/2;   
        }
    return EXIT_SUCCESS;
}