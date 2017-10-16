#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define SIZE 20

void merge_sort(int *, int);
void split(int *, int, int, int);
void merge(int *, int, int, int, int);
int *generate_data(int);
void print_arr(char *, int *, int, int);

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
