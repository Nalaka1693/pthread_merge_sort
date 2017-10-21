#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

#define MAX 100
#define SIZE 20

void merge_sort(int *, int);
void split(int *, int, int, int);
void merge(int *, int, int, int, int);
int *generate_data(int);
void print_arr(char *, int *, int, int);
int *merge_sorted_arr(int *, int *, int, int);

int main() {
    int *arr = generate_data(SIZE);
    print_arr(NULL, arr, 0, SIZE);
    merge_sort(arr, SIZE);
    print_arr(NULL, arr, 0, SIZE);

    return 0;
}

void merge_sort(int *arr, int size) {
    split(arr, 0, size, size);
}

void split(int *arr, int start, int end, int size) {
    if (end - start == 1) {
        return;
    }

    int mid = (start + end) / 2;
    split(arr, start, mid, size);
    split(arr, mid, end, size);
    merge(arr, start, mid, end, size);
}

void merge(int *arr, int start, int mid, int end, int size) {
    int *copy = malloc(sizeof(int) * size);
    memcpy(copy, arr, sizeof(int) * size);

    int i = start, j = mid, k = start;

    while (i < mid && j < end) {
        if (copy[i] < copy[j]) {
            arr[k++] = copy[i++];
        } else {
            arr[k++] = copy[j++];
        }
    }
    
    while (i < mid) {
        arr[k++] = copy[i++];
    }
    while (j < end) {
        arr[k++] = copy[j++];
    }

    free(copy);
}

/* generate some random data of given size
 */
int *generate_data(int size) {
    int *p = malloc(sizeof(int) * size);
    int i;
    for(i = 0; i < size; i++) {
        p[i] = rand() % MAX;
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
