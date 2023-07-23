#include <stdio.h>
#include <stdlib.h>
#include "random.h"

// Função para trocar dois elementos no vetor
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o vetor e retornar o índice do pivô
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Implementação do QuickSort iterativo
void quickSortIterative(int arr[], int low, int high) {
    // Crie uma pilha auxiliar
    int *stack= malloc(sizeof(int)* (high - low + 1));

    // Inicialize o topo da pilha
    int top = -1;

    // Empilhe os valores inicial e final de 'low' e 'high'
    stack[++top] = low;
    stack[++top] = high;

    // Repetir enquanto a pilha não estiver vazia
    while (top >= 0) {
        //printf("top=%d\n",top);
        // Desempilhe os valores de 'low' e 'high'
        high = stack[top--];
        low = stack[top--];

        // Obtenha o índice do pivô usando a função partition
        int pivotIndex = partition(arr, low, high);

        // Se houver elementos à esquerda do pivô, empilhe-os
        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        // Se houver elementos à direita do pivô, empilhe-os
        if (pivotIndex + 1 < high) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}

int main() {
    int *arr = malloc(sizeof(int) * N_ELEMENTS);   
    int n = N_ELEMENTS; 
    int num_threads;
    random_elements(arr,n);   

    quickSortIterative(arr, 0, n - 1);


    return 0;
}
