#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ARRAY_SIZE 10000
#define DEFAULT_PROCESSES 10

void allocateMemory(int n) {
  /* allocate memory for n char */
  int i;
  char *array = malloc(n*sizeof(char));

  for (i = 0; i < n; i++)
    array[i] = 'z';

  free(array);
}

int main(int argc, char *argv[]) {
  int n = DEFAULT_PROCESSES;
  int p = DEFAULT_ARRAY_SIZE;
  int status = 0, wpid, i;
  pid_t pid = 0;

  if (argc > 1) {
    n = atoi(argv[1]);
    if (argc > 2) {
      p = atoi(argv[2]);
    }
  }

  /* don't take up more than 10MB of memory */
  if (n*p*sizeof(char) > 10000000) {
    printf("## input suggests taking up more than 10MB of memory -- please don't.\n");
    exit(EXIT_SUCCESS);
  }

  printf("## starting %d processes, each to take up memory for %d chars...\n", n, p);
  
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

  /* wait for all children to exit */
  while ( (wpid = wait(&status) ) > 0)
    printf("## process %d exited\n", wpid);

  printf("### last line of main program ###\n");
  exit(EXIT_SUCCESS);
}
