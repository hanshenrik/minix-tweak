#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <lib.h>

int getallocalgorithm(void){
   message m;
   return(_syscall(MM, 65, &m));
}
int setallocalgorithm(int flag){
   message m;
   m.m1_i1 = flag;
   return(_syscall(MM, 66, &m));
}
int main(int argc, char *argv[]){
   int algorithm_nr;
   if( argc = 0 || !argv[1][0]){
      printf("\n\t0 = First fit\n\t1 = Best fit\n\t2 - Quick fit\n");
      exit(1);
   }
   algorithm_nr = atoi(argv[1]);
   printf("setallocalgorithm(%d)\n", algorithm_nr);
   setallocalgorithm(algorithm_nr);
   printf("getallocalgorithm() = %d\n", getallocalgorithm());
   return 0;
}
