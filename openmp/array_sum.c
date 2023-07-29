#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


int main() {
    int *arr1 = malloc(sizeof(int) * N_ELEMENTS);  
    int *arr2 = malloc(sizeof(int) * N_ELEMENTS);  
    int *arr3;
    int n = N_ELEMENTS;    
      

    random_elements(arr1,n);            
    random_elements(arr2,n);    
    array_sum(arr1,arr2,n);

    // #pragma omp parallel
    // {
    //     #pragma omp single
       
    //     //quickSort(arr, 0, n - 1);
    // }


    return 0;
}