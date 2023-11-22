#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// size of array
#define ARRAY_SIZE 10

int main(int argc, char *argv[])
{
    int process_id, num_processes,
        elements_per_process,
        num_elements_received;
    // num_processes -> number of processes
    // process_id -> process id

    MPI_Status status;

    // Creation of parallel processes
    MPI_Init(&argc, &argv);

    // find out process ID,
    // and how many processes were started
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    // Check if the number of processes is greater than the array size
    if (num_processes > ARRAY_SIZE)
    {
        if (process_id == 0)
        {
            fprintf(stderr, "Error: Number of processes cannot be greater than the array size.\n");
        }
        MPI_Finalize();
        return 1;
    }

    // master process
    if (process_id == 0)
    {
        int index, i;
        elements_per_process = ARRAY_SIZE / num_processes;
        int extra_elements = ARRAY_SIZE % num_processes; // Extra elements for non-uniform distribution

        // check if more than 1 process is run
        if (num_processes > 1)
        {
            // distributes the portion of array
            // to child processes to calculate
            // their partial sums
            for (i = 1; i < num_processes; i++)
            {
                index = i * elements_per_process + (i < extra_elements ? i : extra_elements);

                // Calculate the number of elements to send to each process
                int send_elements = elements_per_process + (i < extra_elements ? 1 : 0);

                // Send the number of elements and the corresponding portion of the array
                MPI_Send(&send_elements,
                         1, MPI_INT, i, 0,
                         MPI_COMM_WORLD);
                MPI_Send(&a[index],
                         send_elements,
                         MPI_INT, i, 0,
                         MPI_COMM_WORLD);
            }
        }

        // master process adds its own sub-array
        int sum = 0;
        for (i = 0; i < elements_per_process + (process_id < extra_elements ? 1 : 0); i++)
            sum += a[i];

        // collects partial sums from other processes
        int tmp;
        for (i = 1; i < num_processes; i++)
        {
            // Receive partial sums from other processes
            MPI_Recv(&tmp, 1, MPI_INT,
                     MPI_ANY_SOURCE, 0,
                     MPI_COMM_WORLD,
                     &status);
            int sender = status.MPI_SOURCE;

            sum += tmp;
        }

        // prints the final sum of the array
        printf("Sum of array is: %d\n", sum);
    }
    // slave processes
    else
    {
        MPI_Recv(&num_elements_received,
                 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD,
                 &status);

        // stores the received array segment
        // in the local array a2
        int received_array[num_elements_received];
        MPI_Recv(&received_array, num_elements_received,
                 MPI_INT, 0, 0,
                 MPI_COMM_WORLD,
                 &status);

        // calculates its partial sum
        int partial_sum = 0;
        for (int i = 0; i < num_elements_received; i++)
            partial_sum += received_array[i];

        // sends the partial sum to the root process
        MPI_Send(&partial_sum, 1, MPI_INT,
                 0, 0, MPI_COMM_WORLD);
    }

    // cleans up all MPI state before exit of process
    MPI_Finalize();

    return 0;
}
