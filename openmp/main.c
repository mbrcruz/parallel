#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "utils.h"

void random_elements(int arr[],int size)
{
    int th;    
    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < size; i++) 
        {
            arr[i]= rand();
            //th= omp_get_thread_num();
            //printf("i=%d,th=%d\n",i,th);
        }       
    }   

}

// Função para trocar dois elementos no vetor
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o vetor e retornar o índice do pivô
int partition(int arr[], int low, int high) {
    int th;
    int pivot = arr[high];
    int i = low - 1;

    #pragma omp parallel shared(i,arr,low,high)
    {
        #pragma omp for
        for (int j = low; j < high; j++) {
            // th= omp_get_thread_num();
            // printf("i=%d,th=%d\n",j,th);
            if (arr[j] <= pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        } 
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Implementação do QuickSort iterativo
void quickSort(int arr[], int low, int high) {
    // Crie uma pilha auxiliar    
    int *stack= malloc(sizeof(int)* (high - low + 1));

    // Inicialize o topo da pilha
    int top = -1;

    // Empilhe os valores inicial e final de 'low' e 'high'
    stack[++top] = low;
    stack[++top] = high;

    #pragma omp parallel
    {
        // Repetir enquanto a pilha não estiver vazia
        #pragma omp single
        {
             while (top >= 0) {       
        
                // Desempilhe os valores de 'low' e 'high'
                high = stack[top--];
                low = stack[top--];

                // Obtenha o índice do pivô usando a função partition
                int pivotIndex; 
                int pivot = arr[high];
                int i = low - 1;
                for (int j = low; j < high; j++) {
                    #pragma opm task
                    {
                        //int th= omp_get_thread_num();
                        //printf("i=%d,j=%d,th=%d\n",i,j,th);
                        if (arr[j] <= pivot) {
                            #pragma opm atomic
                            i++;
                            swap(&arr[i], &arr[j]);
                        }
                    }
                    
                } 
                swap(&arr[i + 1], &arr[high]);
                pivotIndex = i + 1;  
                 
                    
                if (pivotIndex - 1 > low) {
                    stack[++top] = low;
                    stack[++top] = pivotIndex - 1;
                } 

                if (pivotIndex + 1 < high) {
                    stack[++top] = pivotIndex + 1;
                    stack[++top] = high;
                }
            
            }

        }
       

    }
    
}

void print_array(int *array, int size){
    int i;
    for(i=0;i<size;i++){
        printf("i=%d=>[%d]\n",i,array[i]);
    }
}

int main() {
    int *arr = malloc(sizeof(int) * N_ELEMENTS);      
    int n = N_ELEMENTS;    

    random_elements(arr,n);
    quickSort(arr, 0, n - 1);
    //print_array(arr,n);
    


    return 0;
}
