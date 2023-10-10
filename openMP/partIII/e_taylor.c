#include <stdio.h>
#include <math.h>
#include <omp.h>

static long num_terms = 10000; // Número de términos en la serie de Taylor
double sum = 0.0;

int main() {
    int max_threads = omp_get_max_threads(); // Obtiene el número máximo de hilos disponibles en la máquina
    double start_time, run_time;

    // printf("Número máximo de hilos: %d\n", max_threads);

    int num_threads = max_threads; // Número de hilos a utilizar

    sum = 0.0;

    omp_set_num_threads(num_threads); // Configura el número de hilos a utilizar con OpenMP

    start_time = omp_get_wtime(); // Obtiene el tiempo de inicio de la ejecución

    #pragma omp parallel // Inicio de la región paralela
    {
        // #pragma omp single
        // printf("Número de hilos = %d\n", omp_get_num_threads()); // Imprime el número de hilos activos en la región paralela
    }

    #pragma omp parallel for reduction(+:sum)
    for (int n = 0; n < num_terms; n++) { // Bucle paralelo para calcular la suma de la serie de Taylor
        double term = 1.0;
        for (int i = 1; i <= n; i++) {
            term /= (double)i; // Calcula el término actual de la serie
        }
        sum += term; // Agrega el término actual a la suma
    }

    double e_estimate = sum; // La estimación final de "e" se encuentra en 'sum'
    run_time = omp_get_wtime() - start_time; // Calcula el tiempo de ejecución

    // Imprime los resultados
    printf("Número de términos = %ld, e estimada = %.15f, tiempo = %.6f segundos, hilos = %d\n",
           num_terms, e_estimate, run_time, num_threads);

    return 0;
}
