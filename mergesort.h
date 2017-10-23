#ifndef _MERGESORT_H_
#define _MERGESORT_H_

/* parallel merge sort
 * @ arr: pointer to the array
 * @ size: size of the array
 */
void parallel_merge_sort(int *arr, int size);

/* quick sort
 * @ arr: pointer to the array
 * @ start: start position -> 0
 * @ end: end position -> SIZE-1
 */
void quick_sort(int *arr, int start, int end);

/* serial merge sort
 * @ arr: pointer to the array
 * @ size: size of the array
 */
void serial_merge_sort(int *arr, int size);

/* print one line array
 * @ msg: message to print in a new line
 * @ arr: pointer to the array
 * @ start: start position -> 0
 * @ end: end position -> SIZE
 */
void print_arr(char *msg, int *arr, int start, int end);

/* generate array with random values
 * @ size: size of the square matrix
 * @ max: maximum element value of a element
 */
int *generate_data(int size, int max);

#endif
