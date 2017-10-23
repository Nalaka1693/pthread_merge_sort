#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

#define SIZE 10
#define MAX 100

#define GET_US(X) (X.tv_sec * 1000000 + X.tv_usec)

int main() {
    int *arr = generate_data(SIZE, MAX);
	print_arr(NULL, arr, 0, SIZE);
	parallel_merge_sort(arr, SIZE);
	print_arr(NULL, arr, 0, SIZE);

    // arr = generate_data(SIZE, MAX);
    // print_arr(NULL, arr, 0, SIZE);
    // quick_sort(arr, 0, SIZE-1);
    // print_arr(NULL, arr, 0, SIZE);

//    struct timeval start, end;
//    struct timezone z;
//    double diff;
//    int i;
//
//    for (i = 1000; i < 20000; i += 1000) {
//        *arr = generate_data(i, MAX);
//
//        if (gettimeofday(&start, &z)) goto error_exit;
//        serial_merge_sort(arr, i);
//        if (gettimeofday(&end, &z)) goto error_exit;
//        diff = GET_US(end) - GET_US(start);
//        printf("serial = %f\t", diff / 1000000.0);
//
//        if (gettimeofday(&start, &z)) goto error_exit;
//        parallel_merge_sort(arr, i);
//        if (gettimeofday(&end, &z)) goto error_exit;
//        diff = GET_US(end) - GET_US(start);
//        printf("parallel = %f\n", diff / 1000000.0);
//
//        free(arr);
//    }
    return 0;

    error_exit:
    printf("cannot read time\n");
    return -1;
}
