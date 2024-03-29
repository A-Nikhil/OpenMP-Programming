#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_THREADS 8
#define STEPS 1000000000
int main (int argc, const char *argv[]) {
    int i,j;
    double x;
    double pi, sum = 0.0;
    double start, delta;
    double step = 1.0/(double) STEPS;

    printf("Finding the value of PI by using %d threads and %d steps \n", MAX_THREADS, STEPS);

    omp_set_num_threads(MAX_THREADS);
    sum = 0.0;
    #pragma omp parallel for reduction(+:sum) private(x)
        for (i=0; i < STEPS; i++) {
            x = (i+0.5)*step;
            sum += 4.0 / (1.0+x*x); 
        }
    pi = step * sum;
    delta = omp_get_wtime() - start;
    printf("PI = %.16g \n", pi);
}