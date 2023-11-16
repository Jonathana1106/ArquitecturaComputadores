#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double);

double f(double a)
{
    return (4.0 / (1.0 + a * a));
}

int main(int argc, char *argv[])
{
    int n, myid, numprocs, i, size;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime, endwtime;
    int namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Get_processor_name(processor_name, &namelen);

    fprintf(stdout, "Process %d of %d is on %s\n", myid, numprocs, processor_name);
    fflush(stdout);

    // Evaluar rendimiento para diferentes tamaños de mensaje
    for (size = 1; size <= 10000; size *= 10) {
        n = size;  // Tamaño del mensaje
        h = 1.0 / (double) n;

        if (myid == 0)
            startwtime = MPI_Wtime();
            // printf("%d,%.6f\n", size, endwtime - startwtime);
            fflush(stdout);

        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        sum = 0.0;
        for (i = myid + 1; i <= n; i += numprocs) {
            x = h * ((double) i - 0.5);
            sum += f(x);
        }

        mypi = h * sum;

        MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if (myid == 0) {
            endwtime = MPI_Wtime();
            printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT));
            printf("wall clock time for size %d = %f\n", size, endwtime - startwtime);
            fflush(stdout);
        }

        MPI_Barrier(MPI_COMM_WORLD);  // Sincronizar todos los procesos antes de cambiar el tamaño del mensaje
    }

    MPI_Finalize();
    return 0;
}
