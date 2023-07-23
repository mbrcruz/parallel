#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "random.h"

#define MAX_STACK_SIZE 1000

typedef struct {
    int low;
    int high;
} StackItem;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort_parallel(int arr[], int low, int high) {
    int stack_top = -1;
    StackItem stack[MAX_STACK_SIZE];

    #pragma omp parallel
    {
        #pragma omp single
        {
            stack[++stack_top] = (StackItem){low, high};
        }

        while (stack_top >= 0) {
            int top_high = stack[stack_top].high;
            int top_low = stack[stack_top--].low;

            if (top_low < top_high) {
                int pivot_index = partition(arr, top_low, top_high);

                #pragma omp task
                {
                    stack[++stack_top] = (StackItem){top_low, pivot_index - 1};
                }

                #pragma omp task
                {
                    stack[++stack_top] = (StackItem){pivot_index + 1, top_high};
                }
            }
        }
    }
}


int main() {

    int *arr = malloc(sizeof(int) * N_ELEMENTS);   
    int n = N_ELEMENTS; 
    int num_threads;
    random_elements(arr,n);
    printf("Numero de elementosy %d\n", n);

    // Chama a função de ordenação paralela
    #pragma omp parallel
    {
        num_threads = omp_get_thread_num();
        printf("Numero de thread %d\n", num_threads);
        #pragma omp single nowait
        quicksort_parallel(arr, 0, n - 1);
    }

    return 0;
}
