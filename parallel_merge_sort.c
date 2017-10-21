#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

#define MAX 100
#define SIZE 1024
#define THREADS 4

static int thread_count = 0;
pthread_mutex_t mutex;

typedef struct {
    int start;
    int end;
    int *arr;
    int size;
} thread_data_t;

void parallel_merge_sort(int *, int);
void merge(int *, int, int, int, int);
int *generate_data(int);
void quick_sort(int *, int, int);
void print_arr(char *, int *, int, int);

void *thread_routine_split(void *arg) {
    int start = ((thread_data_t *) arg)->start;
    int end = ((thread_data_t *) arg)->end;
    int *arr = ((thread_data_t *) arg)->arr;
    int size = ((thread_data_t *) arg)->size;

    pthread_mutex_lock(&mutex);
    thread_count++;
    pthread_mutex_unlock(&mutex);

    if (end - start == 1) {
        pthread_exit(NULL);
    }

    int mid = (start + end) / 2;

    thread_data_t *thread_data_1 = (thread_data_t *) malloc(sizeof(thread_data_t));
    thread_data_1->start = start;
    thread_data_1->end = mid;
    thread_data_1->arr = arr;
    thread_data_1->size = size;

    thread_data_t *thread_data_2 = (thread_data_t *) malloc(sizeof(thread_data_t));
    thread_data_2->start = mid;
    thread_data_2->end = end;
    thread_data_2->arr = arr;
    thread_data_2->size = size;

    pthread_t thread_1, thread_2;
    assert(!pthread_create(&thread_1, NULL, thread_routine_split, (void *) thread_data_1));
    assert(!pthread_create(&thread_2, NULL, thread_routine_split, (void *) thread_data_2));

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    merge(arr, start, mid, end, size);

    pthread_exit(NULL);
}

int main() {
    int *arr = generate_data(SIZE);
    print_arr(NULL, arr, 0, SIZE);
    parallel_merge_sort(arr, SIZE);
    print_arr(NULL, arr, 0, SIZE);

    printf("thread count: = %d\n", thread_count);

    arr = generate_data(SIZE);
    print_arr(NULL, arr, 0, SIZE);
    quick_sort(arr, 0, SIZE-1);
    print_arr(NULL, arr, 0, SIZE);

    return 0;
}

void parallel_merge_sort(int *arr, int size) {
    int mid = size / 2;

    thread_data_t *thread_data_1 = (thread_data_t *) malloc(sizeof(thread_data_t));
    thread_data_1->start = 0;
    thread_data_1->end = mid;
    thread_data_1->arr = arr;
    thread_data_1->size = size;

    thread_data_t *thread_data_2 = (thread_data_t *) malloc(sizeof(thread_data_t));
    thread_data_2->start = mid;
    thread_data_2->end = size;
    thread_data_2->arr = arr;
    thread_data_2->size = size;

    pthread_t thread_1, thread_2;
    assert(!pthread_create(&thread_1, NULL, thread_routine_split, (void *) thread_data_1));
    assert(!pthread_create(&thread_2, NULL, thread_routine_split, (void *) thread_data_2));

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
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

int partition(int *arr, int start, int end) {
    int pivot = arr[end];    // pivot
    int i = (start - 1);  // Index of smaller element

    for (int j = start; j <= end - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;    // increment index of smaller element
            int temp_1 = arr[i];
            arr[i] = arr[j];
            arr[j] = temp_1;
        }
    }
    int temp_2 = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = temp_2;

    return (i + 1);
}

void quick_sort(int *arr, int start, int end) {
    if (start < end) {
        int pi = partition(arr, start, end);

        quick_sort(arr, start, pi - 1);
        quick_sort(arr, pi + 1, end);
    }
}

/* generate some random data of given size
 */
int *generate_data(int size) {
    int *p = malloc(sizeof(int) * size);
    int i;
    for (i = 0; i < size; i++) {
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
