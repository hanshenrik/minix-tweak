#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ARRAY_SIZE 100000
#define DEFAULT_PROCESSES 10

void allocateMemory(int n) {
  /* allocate  n kB of memory */
  malloc(n*128*sizeof(double));
}

int main(int argc, char *argv[]) {
  int n = DEFAULT_PROCESSES;
  int p = DEFAULT_ARRAY_SIZE;
  int status, i;
  pid_t pid = 0;

  if (argc > 1) {
    n = atoi(argv[1]);
    if (argc > 2) {
      p = atoi(argv[2]);
    }
  }

  /* don't take up more than 1GB of memory */
  if (n*p > 1000000000) {
    printf("## input suggests taking up 1GB of memory -- please don't.\n");
    exit(EXIT_SUCCESS);
  }

  printf("## starting %d processes, each to take up %d kB of memory...\n", n, p);
  
  for (i = 0; i < n; i++) {
    pid = fork();
    if (pid < 0 ) {
      printf("## ERROR: fork failed!\n");
      continue;
    }
    if (pid == 0) {
      printf("## child\n");
      allocateMemory(p);
      exit(EXIT_SUCCESS);
    } else {
      printf("## parent\n");
    }
  }

  printf("### last line of main program ###\n");
  exit(EXIT_SUCCESS);
}
