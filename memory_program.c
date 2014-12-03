#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ARRAY_SIZE 10000
#define DEFAULT_PROCESSES 10
#define NR_ARRAYS 300

void allocateMemory(int n) {
  int i, j;

  /* create an array to take up memory a bunch of times */
  for (i = 0; i < NR_ARRAYS; i++) {
    /* allocate memory for n chars */
    char *array = malloc(n*sizeof(char));
    
    /* write something to all entries in the array */
    for (j = 0; j < n; j++)
      array[j] = 'z';
    
    /* free up the used memory */
    free(array);
  }
}

int main(int argc, char *argv[]) {
  int n = DEFAULT_PROCESSES, p = DEFAULT_ARRAY_SIZE;
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

  for (i = 0; i < n; i++) {
    pid = fork();
    if (pid < 0 ) {
      printf("## ERROR: fork failed!\n");
      continue;
    }
    if (pid == 0) {
      allocateMemory(p);
      exit(EXIT_SUCCESS);
    } else {}
  }

  /* wait for all children to exit */
  while ( (wpid = wait(&status) ) > 0) {}

  exit(EXIT_SUCCESS);
}
