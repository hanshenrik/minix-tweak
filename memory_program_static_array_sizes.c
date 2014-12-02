#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PROCESSES 9
#define NR_ARRAYS 300
#define SMALL_ARRAY_SIZE 100    /* 100 B  */
#define MEDIUM_ARRAY_SIZE 10000 /* 10  KB */
#define BIG_ARRAY_SIZE 100000   /* 100 KB */

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
  int n = DEFAULT_PROCESSES;
  int status = 0, wpid, i;
  pid_t pid = 0;

  if (argc > 1)
    n = atoi(argv[1]);

  if (!(n%3) == 0) {
    printf("## please let number of processes (%d) be dividable by 3\n", n);
    exit(EXIT_SUCCESS);
  }

  for (i = 0; i < n; i++) {
    pid = fork();
    if (pid < 0 ) {
      printf("## ERROR: fork failed!\n");
      continue;
    }
    if (pid == 0) {
      /* set process take up either small, medium or big chunk of memory */
      if ( (i%3) == 0)
        allocateMemory(SMALL_ARRAY_SIZE);
      else if ( (i%3) == 1)
        allocateMemory(MEDIUM_ARRAY_SIZE);
      else if ( (i%3) == 2)
        allocateMemory(BIG_ARRAY_SIZE);
      exit(EXIT_SUCCESS);
    } else {}
  }

  /* wait for all children to exit */
  while ( (wpid = wait(&status) ) > 0) {}

  exit(EXIT_SUCCESS);
}
