#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

void split(int *, int *, int, int, int, int, int *);
void merge(int *, int *, int, int, int, int);

void serial_merge_sort(int *arr, int start, int end, int size) {
    int max_depth = 0, *copy = malloc(sizeof(int) * size);
    split(arr, copy, start, end, size, 0, &max_depth);

    if (max_depth % 2 == 0) {
        memcpy(arr, copy, sizeof(int) * size);
    }
    free(copy);
}

void split(int *arr, int *copy, int start, int end, int size, int depth, int *max_depth) {

    if (end - start == 1) {
        return;
    }

    int mid = (start + end) / 2;

    split(arr, copy, start, mid, size, depth + 1, max_depth);
    split(arr, copy, mid, end, size, depth + 1, max_depth);

    int *src, *dst;
    if (end - start == 2) {
        *max_depth = depth;
    }

    if (*max_depth != 0) {
        if ((*max_depth - depth) % 2 == 0) {
            src = arr;
            dst = copy;
        } else if ((*max_depth - depth) % 2 == 1) {
            src = copy;
            dst = arr;
        }
    }

    merge(src, dst, start, mid, end, size);
}

void merge(int *src, int *dst, int start, int mid, int end, int size) {
    int i = start, j = mid, k = start;

    while (i < mid && j < end) {
        if (src[i] < src[j]) {
            dst[k++] = src[i++];
        } else {
            dst[k++] = src[j++];
        }
    }
    
    while (i < mid) {
        dst[k++] = src[i++];
    }
    while (j < end) {
        dst[k++] = src[j++];
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
