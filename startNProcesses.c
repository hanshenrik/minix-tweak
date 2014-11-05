#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PRIMES 100000
#define DEFAULT_PROCESSES 10

void eratosthenes() {
  int i, j, n, m;
  int sieve[PRIMES];
  n = PRIMES;
  m = (int) sqrt((double) n);

  sieve[0] = 0;
  sieve[1] = 0;

  /* initialize all entries > 1 to true */
  for(i = 2; i < n; i++)
    sieve[i] = 1;

  /* remove non-primes */
  for(i = 2; i <= m; i++) {
    if(sieve[i]) {
      for(j = i*i; j <= n; j += i) {
          sieve[j] = 0;
      }
    }
  }

  /* print the primes */
  printf("## finding all primes < %d...\n", n);
  for(i = 0; i < n; i++) {
    if(sieve[i])
      printf("%d, ", i);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  int n = DEFAULT_PROCESSES;
  int status, i;
  pid_t pid = 0;
  
  if (argc > 1) {
    n = atoi(argv[1]);
  }

  printf("## starting %d processes that will each compute all primes up to %d...\n", n, PRIMES);
  
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
      eratosthenes();
      exit(EXIT_SUCCESS);
    } else {
      printf("## parent\n");
    }
  }

  printf("### last line of main program ###\n");
  exit(EXIT_SUCCESS);
}
