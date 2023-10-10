#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000000 // Tamaño del vector

// Función para generar un vector de números aleatorios
void generarVector(double *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = ((double)rand() / RAND_MAX) * 10.0; // Números aleatorios entre 0 y 10
    }
}

// Operación DAXPY en una sola hebra
void daxpy_single(double *x, double *y, double a, int size) {
    for (int i = 0; i < size; i++) {
        y[i] = a * x[i] + y[i];
    }
}

int main() {
    // Semilla para la generación de números aleatorios
    srand(time(NULL));

    double *x = (double *)malloc(N * sizeof(double));
    double *y = (double *)malloc(N * sizeof(double));
    double a = 2.0; // Escalar para la operación DAXPY

    generarVector(x, N);
    generarVector(y, N);

    // Versión de un solo hilo (secuencial)
    double start_time = omp_get_wtime();
    daxpy_single(x, y, a, N);
    double run_time = omp_get_wtime() - start_time;
    printf("Tiempo de ejecución (single thread): %.6f segundos\n", run_time);

    // Versión multithread (con OpenMP)
    generarVector(x, N); // Restablecer el vector x
    generarVector(y, N); // Restablecer el vector y

    start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        y[i] = a * x[i] + y[i];
    }

    run_time = omp_get_wtime() - start_time;
    printf("Tiempo de ejecución (multithread): %.6f segundos\n", run_time);

    free(x);
    free(y);

    return 0;
}
