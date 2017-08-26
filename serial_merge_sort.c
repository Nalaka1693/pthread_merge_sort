#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

int data_0[4] = {4, 1, 3, 2};
int data_1[8] = {5, 3, 7, 6, 2, 1, 4, 0};
int data_2[10] = {8, 5, 3, 9, 7, 6, 2, 1, 4, 0};
int data_3[21] = {15, 8, 3, 4, 1, 3, 2, 7, 6, 10, 9, 1, 3, 8, 3, 9, 4, 2, 11, 6, 5};

void merge_sort(int *, int);

void split(int *, int, int, int *);

void merge(int *, int, int, int, int *);

void print_arr(char *, int *, int, int);

int main() {
    merge_sort(data_1, SIZE);

    return 0;
}

void merge_sort(int *arr, int size) {
    int *copy = (int *) malloc(sizeof(int) * size);

    split(arr, 0, size, copy);
    print_arr(NULL, copy, 0, SIZE);
}

void split(int *arr_1, int start, int end, int *arr_2) {
    if (end - start == 1) {
        return;
    }

    int mid = (start + end) / 2;
//    print_arr("1_spl_s:", arr_1, start, mid);
    split(arr_1, start, mid, arr_2);
//    print_arr("1_spl_e:", arr_1, start, mid);
//    print_arr("2_spl_s:", arr_1, mid, end);
    split(arr_1, mid, end, arr_2);
//    print_arr("2_spl_e:", arr_1, mid, end);
    printf("s = %d m = %d e = %d\n", start, mid, end);
    merge(arr_1, start, mid, end, arr_2);
}

void merge(int *arr_1, int start, int mid, int end, int *arr_2) {
    print_arr("ms", arr_2, 0, SIZE);
    if (mid - start <= 1) {
        int i = start, j = 0;
        for (; i < mid; i++) {
            printf("a_s = %d a_m = %d\n", arr_1[i], arr_1[mid + j]);
            if (arr_1[i] > arr_1[mid + j]) {
                arr_2[i] = arr_1[mid + j];
                arr_2[mid + j] = arr_1[i];
            } else {
                arr_2[i] = arr_1[i];
                arr_2[mid + j] = arr_1[mid + j];
            }
            j++;
        }
    } else {

    }
    print_arr("me", arr_2, 0, SIZE);
}

void print_arr(char *msg, int *arr, int start, int end) {
//    printf("s=%d, e=%d: ", start, end);
    if (msg) {
        printf("%s ", msg);
    }
    int i = start;
    for (; i < end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}