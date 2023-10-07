#include <stdlib.h>
#include <stdio.h>

//fonction recurrente de la suite fibonacci
int fibonacci(int n){
    if(n==0 && n==1){
        return 1;
    }
    else{
        return fibonacci(n-1)+fibonacci(n-2);
    }
}
int main(int argc, char * argv[]){
    printf("%d",fibonacci(5));
    return EXIT_SUCCESS;
}