#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void rearrange_elements(int [], int [], int, int);
int array_length;

int main(int argc, char *argv[]) {
    setenv("OMPI_MCA_btl", "^openib", 1);
    setenv("OMPI_MCA_orte_base_help_aggregate", "0", 1);
    int process_rank, total_processes, start_time, end_time, execution_time;
    int i, j, digit_count, temp_var, divisor, max_digits = 0, temp_val;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total_processes);

    // Size of the array to sort...
    array_length = 100000;

    MPI_Bcast(&array_length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *original_array = (int *)malloc(array_length * sizeof(int));
    int *sorted_array = (int *)malloc(array_length * sizeof(int));

    srand(process_rank); // Seed rand() with process rank for different random values

    // Automatically fill the array with random values
    for (i = 0; i < array_length; i++) {
        original_array[i] = rand() % 100; // Generate a random number between 0 and 99
    }

    printf("Process %d - Unsorted Array:\n", process_rank);
    //for (i = 0; i < array_length; i++)
        //printf("%d ", original_array[i]);
    printf("\n");

    MPI_Barrier(MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    int local_array_length = array_length / total_processes;
    int *local_array = (int *)malloc(local_array_length * sizeof(int));

    MPI_Scatter(original_array, local_array_length, MPI_INT, local_array, local_array_length, MPI_INT, 0, MPI_COMM_WORLD);

    // Sort local array
    for (i = 0; i < local_array_length; i++) {
        temp_var = local_array[i];
        digit_count = 0;
        while (temp_var > 0) {
            digit_count++;
            temp_var = temp_var / 10;
        }
        if (max_digits < digit_count)
            max_digits = digit_count;
        digit_count = 0;
    }
    divisor = 1;
    while (--max_digits)
        divisor *= 10;

    for (i = 0; i < local_array_length; i++) {
        temp_val = local_array[i] / divisor;
        temp_var = i;

        for (j = i + 1; j < local_array_length; j++) {
            if (temp_val > (local_array[j] / divisor)) {
                temp_val = local_array[j] / divisor;
                temp_var = j;
            }
        }

        temp_val = local_array[temp_var];
        local_array[temp_var] = local_array[i];
        local_array[i] = temp_val;
    }
    while (divisor >= 1) {
        for (i = 0; i < local_array_length;) {
            temp_var = local_array[i] / divisor;
            for (j = i + 1; temp_var == (local_array[j] / divisor); j++);
                rearrange_elements(local_array, local_array, i, j);
            i = j;
        }
        divisor /= 10;
    }

    MPI_Gather(local_array, local_array_length, MPI_INT, sorted_array, local_array_length, MPI_INT, 0, MPI_COMM_WORLD);

    if (process_rank == 0) {
        // Final sorting
        rearrange_elements(original_array, sorted_array, 0, array_length);

        printf("Sorted Array:\n");
        //for (i = 0; i < array_length; i++)
            //printf("%d ", sorted_array[i]);
        printf("\n");
    }
    end_time = MPI_Wtime();
    execution_time = end_time - start_time; 
    printf("%f", execution_time);

    free(original_array);
    free(sorted_array);
    free(local_array);

    MPI_Finalize();

    return 0;
}

void rearrange_elements(int arr[], int arr1[], int start, int end) {
    int temp = 0;
    int i = 0;
    int j = 0;

    for (i = start; i < end - 1 && i < array_length; i++) {
        for (j = i + 1; j < end && j < array_length; j++) {
            if (arr1[i] > arr1[j]) {
                temp = arr1[i];
                arr1[i] = arr1[j];
                arr1[j] = temp;

                temp = (arr[i] % 10);
                arr[i] = (arr[j] % 10);
                arr[j] = temp;
            }
        }
    }
}
