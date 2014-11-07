#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_ARRAY_SIZE 100000
#define DEFAULT_PROCESSES 10

void populateArray(int n) {
  int *a;
  int i;
  time_t seconds;
  
  time(&seconds);
  srand((unsigned int) seconds);

  /* allocate memory for n ints */
  a = (int *)malloc(sizeof(int)*n);
  
  /* read from and write to the array */
  for (i = 0; i < n; i++) {
    if (a[i] == 0)
      a[i] = rand();
  }

  /* neccessary? */
  free(a);
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

  printf("## starting %d processes, each make an array of size %d...\n", n, p);
  
  /* is this ok, or is the point that they should run in parallell? */
  for (i = 0; i < n; i++) {
    pid = fork();
    if (pid < 0 ) {
      printf("## ERROR: fork failed!\n");
      continue;
    }
    if (pid == 0) {
      printf("## child\n");
      /* status = system("./soe"); */
      populateArray(p);
      exit(EXIT_SUCCESS);
    } else {
      printf("## parent\n");
    }
  }

  printf("### last line of main program ###\n");
  exit(EXIT_SUCCESS);
}
