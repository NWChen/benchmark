#include <assert.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int find_primes(int n_max) {

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

	return 0;
}

int main(int argc, char **argv) {

	// inputs
	assert(argc == 3);
	int n_cpus = atoi(argv[1]);
	int n_max = atoi(argv[2]);
	assert(n_cpus >= 1 && n_cpus <= 48);
	assert(n_max >= 0 && n_max <= 5000);
	printf("CPUs=%d / n=%d", n_cpus, n_max);

	pid_t child_pid = fork();
	if(child_pid == 0) { // child
		sleep(1); // wait for parent (???)
		find_primes(n_max);
	} else {
		char str_cpus[10], str_pid[12];
		sprintf(str_pid, "%d", child_pid);
		if(n_cpus > 1) 
			sprintf(str_cpus, "0-%d", n_cpus-1);
		else
			sprintf(str_cpus, "%d", 0);
		char* params[] = {"-p", "-c", str_cpus, str_pid, NULL};
		execv("taskset", params);
	}
}
