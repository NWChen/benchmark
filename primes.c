#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

	// inputs
	assert(argc == 3);
	int n_cpus = atoi(argv[1]);
	int n_max = atoi(argv[2]);
	assert(n_cpus >= 1 && n_cpus <= 48);
	assert(n_max >= 0 && n_max <= 5000);
	printf("CPUs=%d / n=%d", n_cpus, n_max);

	// measure execution time
	clock_t start, end;
	start = clock();
	srand(time(NULL));

	// populate sieve
	int *ls = (int *)malloc(sizeof(int) * (n_max - 1));
	for(int i=2; i<=n_max; i++)
		ls[i-2] = i;

	// eliminate composite numbers
	int p = 2;
	int stop = 0;
	while(!stop) {	
		for(int i=(2*p)-2; i<=n_max-2; i+=p)
			ls[i] = -1;

		for(int i=p-2; i<n_max; i++) {
			if(ls[i] > p) {
				p = ls[i];
				break;
			} else if(i == n_max-1)
				stop = 1;
		}
	}

	// show output & runtime
	end = clock();
	printf("\n-\n");
	for(int i=0; i<n_max-1; i++)
		if(ls[i] != -1)
			printf("%d ", ls[i]);
	double ms = 1000.0 * ((double) (end - start)) / CLOCKS_PER_SEC;
	double us = 1000.0 * ms;
	printf("\n-\nRan in %f milliseconds (%f microseconds).\r\n", ms, us);

}
