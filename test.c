#include <stdio.h>
#include <stdlib.h>

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

int *sort(int *arr_1, int *arr_2, int size_1, int size_2) {
    int i = 0, j = 0, k = 0, n = 0;
    int *result = (int *) malloc(sizeof(int) * (size_1 + size_2));

    while (i < size_1 && j < size_2) {
        if (arr_1[i] < arr_2[j]) {
            result[k++] = arr_1[i];
            i++;
        } else {
            result[k++] = arr_2[j];
            j++;
        }
    }

    for (; i < size_1; i++) {
        result[k++] = arr_1[i];
    }
    for (; j < size_2; j++) {
        result[k++] = arr_2[j];
    }

    return result;

}

int main() {
    int a[9] = {1, 7, 9, 11, 13, 20, 22, 25, 30};
    int b[8] = {2, 4, 6, 8, 14, 15, 17, 21};

    int *res = sort(a, b, 9, 8);
    print_arr(NULL, res, 0, 17);

    return 0;
}