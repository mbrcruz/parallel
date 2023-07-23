#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 500000000

int main() {
    int i, sum = 0;
    int *array;
    int num_threads = 0;
    array=malloc(sizeof(int)*ARRAY_SIZE);

    // Inicializa o array com valores de 1 a ARRAY_SIZE
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    //omp_set_num_threads(64);
    #pragma omp parallel
    {
        num_threads = omp_get_thread_num();
        printf("Numero de thread %d\n", num_threads);
         // Início da região paralela
        #pragma omp parallel for reduction(+:sum)    
        for (i = 0; i < ARRAY_SIZE; i++) {
            sum += array[i];
        }
        

    }
   
    // Fim da região paralela

    printf("A soma dos elementos do array é: %d\n", sum);

    return 0;
}
