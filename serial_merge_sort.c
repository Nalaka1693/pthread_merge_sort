#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

int data_0[4] = {4, 1, 3, 2};
int data_1[8] = {5, 3, 7, 6, 2, 1, 4, 0};
int data_2[10] = {8, 5, 3, 9, 7, 6, 2, 1, 4, 0};
int data_3[21] = {15, 8, 3, 4, 1, 3, 2, 7, 6, 10, 9, 1, 3, 8, 3, 9, 4, 2, 11, 6, 5};

void merge_sort(int *, int);
void split(int *, int, int, int);
void merge(int *, int, int, int, int);
void print_arr(char *, int *, int, int);

int main() {
    merge_sort(data_1, SIZE);
    print_arr(NULL, data_1, 0, SIZE);

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