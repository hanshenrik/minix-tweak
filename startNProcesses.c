#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DEFAULT_PRIMES 1000
#define DEFAULT_PROCESSES 10

void eratosthenes(int n) {
  if(n < 2)
    return;

  int sieve[n+1];
  sieve[0] = false;
  sieve[1] = false;

  int i, j, m;
  m = (int) sqrt((double) n);

  // initialize all entries > 1 to true
  for(i = 2; i < n; i++)
    sieve[i] = true;

  // remove non-primes
  for(i = 2; i <= m; i++) {
    if(sieve[i]) {
      for(j = i*i; j <= n; j += i) {
          sieve[j] = false;
      }
    }
  }

  // print the primes
  printf("## finding all primes < %d...\n", n);
  for(i = 0; i < n; i++) {
    if(sieve[i])
      printf("%d, ", i);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  int n = DEFAULT_PROCESSES;
  int p = DEFAULT_PRIMES;
  
  if (argc > 1) {
    n = atoi(argv[1]);
    if (argc > 2) {
      p = atoi(argv[2]);
    }
  }

  printf("## starting %d processes that will each compute all primes up to %d...\n", n, p);

  int status, i;
  pid_t pid = 0;
  
  // is this ok, or is the point that they should run in parallell?
  for (i = 0; i < n; i++) {
    pid = fork();
    if (pid < 0 ) {
      printf("## ERROR: fork failed!\n");
      continue;
    }
    if (pid == 0) {
      // Child process will return 0 from fork()
      printf("## child\n");
      // status = system("./soe");
      eratosthenes(p);
      exit(EXIT_SUCCESS);
    } else {
      // Parent process will return a non-zero value from fork()
      printf("## parent\n");
    }
  }

  printf("### last line of main program ###\n");
  exit(EXIT_SUCCESS);
}