#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

void split(int *, int *, int, int, int, int, int);
void merge(int *, int *, int, int, int, int);

void serial_merge_sort(int *arr, int start, int end, int size) {
    int *copy = malloc(sizeof(int) * size);
    split(arr, copy, start, end, size, 0, 0);
    free(copy);
}

void split(int *arr, int *copy, int start, int end, int size, int depth, int max_depth) {
    if (end - start == 1) {
        return;
    }

    int mid = (start + end) / 2;
    printf("s = %d, m = %d, e = %d, d = %d, md = %d\n", start, mid, end, depth, max_depth);
    split(arr, copy, start, mid, size, depth + 1, max_depth);
    split(arr, copy, mid, end, size, depth + 1, max_depth);

    int *src, *dst;
    if (mid - start == 1 || end - mid == 1) {
        src = arr;
        dst = copy;
        max_depth = depth;
    } else if (max_depth != 0 && (max_depth - depth) % 2 == 1 ) {
        src = copy;
        dst = arr;
    } else if (max_depth != 0 && (max_depth - depth) % 2 == 0) {
        src = arr;
        dst = copy;
    }

    merge(src, dst, start, mid, end, size);
}

void merge(int *src, int *dst, int start, int mid, int end, int size) {
//    memcpy(dst, src, sizeof(int) * size);

    int i = start, j = mid, k = start;

    while (i < mid && j < end) {
        if (dst[i] < dst[j]) {
            src[k++] = dst[i++];
        } else {
            src[k++] = dst[j++];
        }
    }
    
    while (i < mid) {
        src[k++] = dst[i++];
    }
    while (j < end) {
        src[k++] = dst[j++];
    }
}

int *generate_data(int size, int max) {
    int *p = malloc(sizeof(int) * size);
    int i;
    for(i = 0; i < size; i++) {
        p[i] = rand() % max;
    }

    return p;
}

void print_arr(char *msg, int *arr, int start, int end) {
    if (msg) {
        printf("%s ", msg);
    }
    int i = start;
    for (; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int *merge_sorted_arr(int *arr_1, int *arr_2, int size_1, int size_2) {
    int i = 0, j = 0, k = 0;
    int *result = (int *) malloc(sizeof(int) * (size_1 + size_2));

    while (i < size_1 && j < size_2) {
        if (arr_1[i] < arr_2[j]) {
            result[k++] = arr_1[i++];
        } else {
            result[k++] = arr_2[j++];
        }
    }

    while (i < size_1) {
        result[k++] = arr_1[i++];
    }
    while (j < size_2) {
        result[k++] = arr_2[j++];
    }

    return result;
}
