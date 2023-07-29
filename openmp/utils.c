#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


// void random_elements(int arr[],int size)
// {
//     int th;    
//     #pragma omp parallel
//     {
//         #pragma omp for
//         for (int i = 0; i < size; i++) 
//         {
//             arr[i]= rand();
//             //th= omp_get_thread_num();
//             //printf("i=%d,th=%d\n",i,th);
//         }       
//     }   

// }
int* array_sum(int* arr1, int* arr2,int size)
{
    int i,th;
    int *res = (int *) malloc(sizeof(int) * size);
    
    #pragma omp parallel
    {
        #pragma omp for
        for(i=0;i<size;i++){
            res[i]= arr1[i]+arr2[i];
            th= omp_get_thread_num();
            printf("i=%d,th=%d\n",i,th);
        }
    }
    return res;   
}