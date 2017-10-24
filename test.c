#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

#define SIZE 16
#define MAX 100

#define GET_US(X) (X.tv_sec * 1000000 + X.tv_usec)

void analyze(void);

int main() {
    int *arr = generate_data(SIZE, MAX);
    print_arr(NULL, arr, 0, SIZE);
    serial_merge_sort(arr, 0, SIZE, SIZE);
    print_arr(NULL, arr, 0, SIZE);

    return 0;
}

void analyze(void) {
    struct timeval start, end;
    struct timezone z;
    double diff;
    int i;

    for (i = 10000; i <= 100000; i += 10000) {
        int *arr = generate_data(i, MAX);
        printf("size = %d\t", i);

        if (gettimeofday(&start, &z)) goto error_exit;
        serial_merge_sort(arr, 0, i, i);
        if (gettimeofday(&end, &z)) goto error_exit;
        diff = GET_US(end) - GET_US(start);
        printf("serial = %f\t", diff / 1000000.0);

        if (gettimeofday(&start, &z)) goto error_exit;
        parallel_merge_sort(arr, i);
        if (gettimeofday(&end, &z)) goto error_exit;
        diff = GET_US(end) - GET_US(start);
        printf("parallel = %f\n", diff / 1000000.0);

        free(arr);
    }

    error_exit:
    printf("cannot read time\n");
    return;
}
