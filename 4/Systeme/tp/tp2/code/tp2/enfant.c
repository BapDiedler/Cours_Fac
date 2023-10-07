#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char** argv){

   sleep(atoi(argv[3]));
   printf("processus %d | parent %d\n",getpid(), getppid());fflush(stdout);
   printf("fils (%d) J'ai %d %s\n",getpid(), atoi(argv[1])*2, argv[2]);fflush(stdout);
   return atoi(argv[3]);
}