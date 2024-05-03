/* 
 * C Program to Implement Postman Sort Algorithm
 */
#include <stdio.h>
// include rand() function
#include <stdlib.h>
// Include mpi
#include <omp.h>
 
void arrange(int,int);
int array[100], array1[100];
int i, j, temp, max, count, maxdigits = 0, c = 0;
 


void main()
{
    // Find a random array of integers and print it
    count = 99;
    for (i = 0; i < count; i++)
    {
        array[i] = rand() % 1000;
        array1[i] = array[i];            
    }

    //Print the array
    printf("Array before sorting: ");
    for (i = 0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
}

void arrange(int k1, int k2)
{
    printf("Funcion de prueba");
}
