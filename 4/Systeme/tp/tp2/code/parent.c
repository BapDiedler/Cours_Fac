#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    if(argc == 5){
        pid_t res;
        pid_t res2;
        pid_t res3;
        int status = 0;
        
        //création d'un processus
        switch ( res = fork() ){
            case (pid_t) -1 :
                perror("création impossible");fflush(stdout);
                exit(1);
            case (pid_t) 0 :
            /* on est dans le fils */
                printf("le fils est %d\n",getpid());fflush(stdout);
                execl("./enfant","enfant",argv[1],argv[2],argv[3],NULL);
                break;
            default :
            /* on est dans le père*/
                printf("creation du premier processus : %d\n",getpid());
        }
        /* creation du processus numero 2*/
        switch (res2 = fork()){
            case (pid_t) -1://le processus n'a pas été créé
                perror("création impossible");fflush(stdout);
                exit(1);
            case (pid_t) 0://on est dans le processus fils
            /* on est dans le fils */
                printf("le fils est %d\n",getpid());fflush(stdout);
                execl("./enfant","enfant",argv[1],argv[2],argv[4],NULL);
                break;
            default:
                printf("creation du deuxieme processus : %d\n",getpid());fflush(stdout);
                break;
        }
        res3 = waitpid(res2,&status,0);
        printf("%d\n",WEXITSTATUS(status));fflush(stdout);//affichage de la valeur de res2
        return 0;
    }else{
        perror("le nombre d'argument doit être de 3");fflush(stdout);
        return 1;
    }
}