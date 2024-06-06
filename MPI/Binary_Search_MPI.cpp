#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void search_binary(int arr[], int left, int right, int target);
void sort_bubble(int arr[], int n);

int main(int argc, char *argv[])
{
    srand(time(NULL)); // Initialize random seed
    int process_rank, total_processes;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processes);

    double start_time, end_time;

    const int array_size = 10000; // Size of the array
    int search_key;

    // Generate the search key randomly in process 0
    if (process_rank == 0) {
        search_key = rand() % 100; // Generate a random search key between 0 and 99
    }

    start_time = MPI_Wtime(); // Start execution time

    // Broadcast the search key to all processes
    MPI_Bcast(&search_key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the local array size for each process
    int local_array_size = array_size / total_processes + (process_rank < array_size % total_processes ? 1 : 0);
    int *local_array = (int *)malloc(local_array_size * sizeof(int));

    // Generate random elements for the array in each process
    for (int i = 0; i < local_array_size; i++) {
        local_array[i] = rand() % 100; // Generate random numbers between 0 and 99
    }

    // Each process sorts its part of the array
    sort_bubble(local_array, local_array_size);

    // Gather the local arrays to form a global array in process 0
    int *global_array = NULL;
    if (process_rank == 0) {
        global_array = (int *)malloc(array_size * sizeof(int));
    }
    MPI_Gather(local_array, local_array_size, MPI_INT, global_array, local_array_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (process_rank == 0) {
        // Perform the binary search
        search_binary(global_array, 0, array_size - 1, search_key);
        end_time = MPI_Wtime(); // End execution time
        printf("Time taken: %f seconds\n", end_time - start_time); // Print execution time
        free(global_array);
    }

    free(local_array);
    MPI_Finalize();
    return 0;
}

void sort_bubble(int arr[], int n)
{
    int temp, i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void search_binary(int arr[], int left, int right, int target)
{
    int mid;

    while (left <= right)
    {
        mid = (left + right) / 2;
        if (arr[mid] == target)
        {
            printf("Key found at index %d\n", mid);
            return;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    printf("Key not found\n");
}
