#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int data_1[10] = {8, 5, 3, 9, 7, 6, 2, 1, 4, 0};
int data_2[21] = {15, 8, 3, 4, 1, 3, 2, 7, 6, 10, 9, 1, 3, 8, 3, 9, 4, 2, 11, 6, 5};

void merge_sort(int *, int);
void split(int *, int, int, int *);
void merge(int *, int, int, int *);
void print_arr(char *, int *, int, int);

int main() {
    merge_sort(data_1, SIZE);

    return 0;
}

void merge_sort(int *arr, int size) {
    int *copy = (int *) malloc(sizeof(int) * size);

    split(arr, 0, size, copy);
}

void split(int *arr_1, int start, int end, int *arr_2) {
    if (end - start == 1) {
        return;
    }

    int mid = (start + end) / 2;
    print_arr("1_spl_s", arr_1, start, mid);
    split(arr_1, start, mid, arr_2);
    print_arr("1_spl_e", arr_1, start, mid);
    split(arr_1, mid, end, arr_2);

//    merge(arr_1, start, end, arr_2);
}

void merge(int *arr_1, int start, int end, int *arr_2) {
    int i = 0;
//    for (; i) {
//
//    }
}

void print_arr(char *msg, int *arr, int start, int end) {
    if (msg) {
        printf("%s: ", msg);
    }
    int i = start;
    for (; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}