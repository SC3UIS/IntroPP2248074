/* 
 * C Program to Implement Postman Sort Algorithm
 */
#include <stdio.h>
// include rand() function
#include <stdlib.h>
// Include mpi
#include <omp.h>
//Import time library
#include <time.h>

//Define the constant len of the array length
#define len 100000

int array[len], array1[len];
int i, j, temp, max, count, maxdigits = 0, c = 0;
//Declare the array of buckets
int bucket[10][len], bucket_count[10];


// Algorithm to sort numbers in a bucket
void sort_bucket(int bucket[], int bucket_count) {
    int i, j, temp;
    for (i = 0; i < bucket_count; i++)
    {
        for (j = i + 1; j < bucket_count; j++)
        {
            if (bucket[i] > bucket[j])
            {
                temp = bucket[i];
                bucket[i] = bucket[j];
                bucket[j] = temp;
            }
        }
    }
}

void main ()
{   
    double start = omp_get_wtime();
    int t1, t2, k, t, n = 1; // Declare integer variables

    printf("The length of the array is: %d\n", len);

    count = len;
    for (i = 0; i < count; i++)
    {
        array[i] = rand() % len;
        array1[i] = array[i];            
    }
    //Start counting time
    

    //Print the random array
    // printf("Random array is : ");
    // for (i = 0; i < count; i++)
    //     printf("%d ", array[i]);

    // Get the number of digits of the largest number in the array
    for (i = 0; i < count; i++)
    {
        t = array[i];        /*first element in t */
        while(t > 0) {   
            c++;
            t = t / 10;        /* Find MSB */
        }
        if (maxdigits < c) 
            maxdigits = c;   /* number of digits of a each number */
        c = 0;   
    }

    printf("Checkpoint 1\n");

    // Assign the value of n
    while(--maxdigits)  //--maxdigits means maxdigits-1
        n = n * 10;
    
    // Initialize the bucket_count array
    for (i = 0; i < 10; i++)
        bucket_count[i] = 0;
    
    // Distribute the numbers into the buckets
    for (i = 0; i < count; i++)
    {
        k = array[i] / n;        /* MSB - Dividnng by perticular base */
        bucket[k][bucket_count[k]] = array[i];
        bucket_count[k]++;
    }

    printf("Checkpoint 2\n");

    //Sort the numbers in each bucket
    for (i = 0; i < 10; i++)
    {
        sort_bucket(bucket[i], bucket_count[i]);
    }

    // Merge the numbers from the buckets
    k = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < bucket_count[i]; j++)
        {
            array[k] = bucket[i][j];
            k++;
        }
    }

    // Print the sorted array 
    // printf("Sorted array is : ");
    // for (i = 0; i < count; i++)
    //     printf("%d ", array[i]);

    //End counting time and print in seconds
    double end = omp_get_wtime();
    printf("\nTime spent: %f\n", end - start);
}
