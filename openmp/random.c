#include <stdio.h>
#include <stdlib.h>


void random_elements(int arr[],int size)
{
    printf("Inicializado vetor aleatorio...\n");
    for (int i = 0; i < size; i++) 
    {
        arr[i]= rand();
    }
    printf("Vetor aleatorio inicializado.\n");
   

}