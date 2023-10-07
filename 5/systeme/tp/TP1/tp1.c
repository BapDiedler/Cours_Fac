#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    //question 1
    sleep(3);

    //question 2
    struct timespec req, rem;

    req.tv_sec = 3;
    req.tv_nsec = 0;

    if(nanosleep(&req, &rem) != 0){
        perror("erreur avec la fonction nanosleep");
        exit(-1);
    }
    
    return EXIT_SUCCESS;
}