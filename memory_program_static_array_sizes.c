#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PROCESSES 9
#define SMALL_ARRAY_SIZE 100
#define MEDIUM_ARRAY_SIZE 10000
#define BIG_ARRAY_SIZE 1000000

void allocateMemory(int n) {
  int i;

  /* allocate memory for n char */
  char *array = malloc(n*sizeof(char));

  /* write something to all entries in the array */
  for (i = 0; i < n; i++)
    array[i] = 'z';

  /* free up the used memory */
  free(array);
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
      /* set process use either small, medium or big chunk of memory */
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
