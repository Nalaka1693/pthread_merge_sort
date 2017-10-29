#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "mergesort.h"

#define LEVELS 2    // depth of the parallel decomposition tree

typedef struct {
    int start;
    int end;
    int *arr;
    int size;
} thread_data_t;

void serial_merge(int *, int, int, int, int);
int partition(int *, int, int);

unsigned int ONE = 1;
int thread_count = 0;
pthread_mutex_t mutex;

void *thread_routine_split(void *arg) {
    pthread_mutex_lock(&mutex);
    thread_count++;
    pthread_mutex_unlock(&mutex);

    int start = ((thread_data_t *) arg)->start;
    int end = ((thread_data_t *) arg)->end;
    int *arr = ((thread_data_t *) arg)->arr;
    int size = ((thread_data_t *) arg)->size;

    if (end - start == 1) {
        pthread_exit(NULL);
    }

    if (thread_count > (ONE << LEVELS) - 2) {   // limit the threads by levels, 2^(LVL)-2 threads
        serial_merge_sort(arr, start, end, size);
        pthread_exit(NULL);
    } else {
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

        serial_merge(arr, start, mid, end, size);

        pthread_exit(NULL);
    }
}

void parallel_merge_sort(int *arr, int size) {
    pthread_mutex_init(&mutex, NULL);

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

    serial_merge(arr, 0, mid, size, size);

    pthread_mutex_destroy(&mutex);
}

void serial_merge(int *arr, int start, int mid, int end, int size) {
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
    int pivot = arr[end];   // pivot
    int i = (start - 1);    // index of smaller element
    int j;

    for (j = start; j <= end - 1; j++) {
        // if current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++;            // increment index of smaller element
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
