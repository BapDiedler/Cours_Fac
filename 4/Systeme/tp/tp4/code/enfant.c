#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv){
    if(argc == 3){
        int cptP=0;
        int cptM=0;
        int val_ret;
        int lecture = atoi(argv[1]);
        int ecriture = atoi(argv[2]);


        char buffer;
        close(ecriture) ;
        do{
            buffer='_';
            val_ret = read(lecture,&buffer, sizeof(char));
            if(buffer == '+'){
                cptP++;
            }else if (buffer == '-'){
                cptM++;
            }
        }while(val_ret != -1 && val_ret != 0);
        close(lecture) ;
        printf("+ : %d | - : %d  (%d)\n",cptP,cptM,getpid());fflush(stdout);
        return 0;
    }else{
        perror("le nombre d'argument de fils doit être de 4");
        return 1;
    }
}