/* 
 * C Program to Implement Postman Sort Algorithm
 */
#include <stdio.h>
// include rand() function
#include <stdlib.h>
// Include mpi
#include <omp.h>
 
//void arrange(int,int);
int array[100], array1[100];
int i, j, temp, min, count, maxdigits = 0, c = 0;
 


void main()
{
    printf("Checkpoint 0");
    int t1, t2, k, t, n = 1;
 
    // printf("Enter size of array :");
    // scanf("%d", &count);
    // printf("Enter elements into array :");
    // for (i = 0; i < count; i++)
    // {
    //     scanf("%d", &array[i]);
    //     array1[i] = array[i];            
    // }
    //Generate a random array of integers
    count = 20;
    for (i = 0; i < count; i++)
    {
        array[i] = rand() % 1000;
        array1[i] = array[i];            
    }
    printf("Checkpoint 1");
    for (i = 0; i < count; i++)
    {
        t = array[i];        /*first element in t */
        while(t > 0)    // CHANGE : Previously it was while(t > 0) but it was not working for 0
        {
            c++;
            t = t / 10;        /* Find MSB */
        }
        if (maxdigits < c) 
            maxdigits = c;   /* number of digits of a each number */
        c = 0;   
    }
    // Here maxdigits is the number of digits of the largest number in the array
    printf("Checkpoint 2");
    while(--maxdigits)  //--maxdigits means maxdigits-1
        n = n * 10;      
 
    for (i = 0; i < count; i++)
    {
        min = array[i] / n;        /* MSB - Dividnng by perticular base */
        t = i;                     // MSB means Most Significant Bit
        for (j = i + 1; j < count;j++)    
        {
            if (min > (array[j] / n))
            {
                min = array[j] / n;   /* greatest MSB */
                t = j;
            }
        } // min stores the lowest number in the remaining array
        temp = array1[t];
        array1[t] = array1[i];
        array1[i] = temp;
        temp = array[t];
        array[t] = array[i]; 
        array[i] = temp;
    } 
    // At this point the array is sorted based on the most significant bit
    // The most significant bit is the first digit of the number ????
    printf("Checkpoint 3");
    while (n >= 1)
    {
        for (i = 0; i < count;)
        {
            t1 = array[i] / n;
            for (j = i + 1; t1 == (array[j] / n); j++); // For each element, checks if t1 is equal to the jth element/n, 
                arrange(i, j);                          // then increment j to get the bucket of elements with the same MSB                    
            i = j;                                      // arrange orders the bucket
        }
        n = n / 10;
    }
    printf("\nSorted Array (Postman sort) :");    
    for (i = 0; i < count; i++)
        printf("%d ", array1[i]);
    printf("\n");
}
 
/* Function to arrange the of sequence having same base */
void arrange(int k,int n)
{
    for (i = k; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (array1[i] > array1[j])
            {
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
                temp = (array[i] % 10);
                array[i] = (array[j] % 10);
                array[j] = temp;
            }
        }
    }
}
