#include <stdio.h>
#include <stdlib.h>


void random_elements(int arr[],int size)
{
    
    for (int i = 0; i < size; i++) 
    {
        arr[i]= rand();
    }
    printf("\n");

}