#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define len 100000

int array[len], array1[len];
int i, j, temp, max, count, maxdigits = 0, c = 0;
int bucket[10][len], bucket_count[10];

void sort_bucket(int bucket[], int bucket_count) {
    int i, j, temp;
    for (i = 0; i < bucket_count; i++) {
        for (j = i + 1; j < bucket_count; j++) {
            if (bucket[i] > bucket[j]) {
                temp = bucket[i];
                bucket[i] = bucket[j];
                bucket[j] = temp;
            }
        }
    }
}

int main () {
    int t1, t2, k, t, n = 1;
    double start = omp_get_wtime();

    printf("The length of the array is: %d\n", len);

    count = len;
    for (i = 0; i < count; i++) {
        array[i] = rand() % len;
        array1[i] = array[i];            
    }

    

    for (i = 0; i < count; i++) {
        t = array[i];
        while(t > 0) {
            c++;
            t = t / 10;
        }
        if (maxdigits < c)
            maxdigits = c;
        c = 0;
    }

    printf("Checkpoint 1\n");

    while(--maxdigits)
        n = n * 10;

    for (i = 0; i < 10; i++)
        bucket_count[i] = 0;
    
    #pragma omp parallel for private(k)
    for (i = 0; i < count; i++) {
        k = array[i] / n;
        #pragma omp critical
        {
            bucket[k][bucket_count[k]] = array[i];
            bucket_count[k]++;
        }
    }

    printf("Checkpoint 2\n");

    #pragma omp parallel for
    for (i = 0; i < 10; i++) {
        sort_bucket(bucket[i], bucket_count[i]);
    }

    k = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < bucket_count[i]; j++) {
            array[k] = bucket[i][j];
            k++;
        }
    }

    double end = omp_get_wtime();
    printf("Time taken: %f\n", end - start);

    return 0;
}
