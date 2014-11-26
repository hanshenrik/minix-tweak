#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULT_PRIMES 100000
#define DEFAULT_PROCESSES 10

void eratosthenes(void) {
  int i, j, m, n = DEFAULT_PRIMES;
  int sieve[DEFAULT_PRIMES];
  m = (int) sqrt((double) n);

  sieve[0] = 0;
  sieve[1] = 0;

  /* initialize all entries > 1 to true */
  for(i = 2; i < n; i++)
    sieve[i] = 1;

  /* remove non-primes */
  for(i = 2; i <= m; i++) {
    if(sieve[i]) {
      for(j = i*i; j < n; j += i) {
          sieve[j] = 0;
      }
    }
  }

  /* print the primes */
  for(i = 0; i < n; i++) {
    if(sieve[i])
      printf("%d, ", i);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  int n = DEFAULT_PROCESSES, p = DEFAULT_PRIMES;
  int status = 0, wpid, i;
  pid_t pid = 0;

  if (argc > 1) {
    n = atoi(argv[1]);
  }

  printf("## starting %d processes, each compute all primes up to %d...\n", n, p);
  
  for (i = 0; i < n; i++) {
    pid = fork();
    if (pid < 0 ) {
      printf("## ERROR: fork failed!\n");
      continue;
    }
    if (pid == 0) {
      printf("## child executing\n");
      eratosthenes();
      exit(EXIT_SUCCESS);
    } else {
      printf("## parent executing\n");
    }
  }

  /* wait for all children to exit */
  while ( (wpid = wait(&status) ) > 0)
    printf("## process %d exited\n", wpid);

  printf("### last line of main program ###\n");
  exit(EXIT_SUCCESS);
}