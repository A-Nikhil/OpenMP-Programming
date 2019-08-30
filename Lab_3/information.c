#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define ARRAY_SIZE 8
#define NUM_THREADS 4

int main() {
    int *a;
    int *b;
    int *c;

    int n = ARRAY_SIZE;
    int n_per_thread;
    int total_threads = NUM_THREADS;
    int i;

    a = (int*) malloc(sizeof(int)*n);
    b = (int*) malloc(sizeof(int)*n);
    c = (int*) malloc(sizeof(int)*n);

    for (i=0; i<n; i++) {
        a[i] = i;
        b[i] = i;
    }

    omp_set_num_threads(total_threads);

    n_per_thread = n/total_threads;

    printf("Total Number of Threads = %d\n", omp_get_num_threads());
    printf("Total Number of Processes = %d\n", omp_get_num_procs());
    #pragma omp parallel for shared (a,b,c) private(i) schedule(static, n_per_thread)
        for (i = 0; i<n; i++) {
            c[i] = a[i] + b[i];
            printf("Thread %d works on element %d \n", omp_get_thread_num(), i);
        }

    free(a);
    free(b);
    free(c);

    return 0;
}