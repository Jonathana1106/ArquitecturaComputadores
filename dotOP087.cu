#include <iostream>
#include <cstdlib>
#include <ctime>

// Kernel para calcular el producto punto de dos arreglos
__global__ void dotProduct(float *a, float *b, float *result, int N) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;

    // Cada hilo realiza una parte del trabajo
    while (tid < N) {
        result[tid] += a[tid] * b[tid];
        tid += blockDim.x * gridDim.x;
    }
}

int main() {
    // Tamaño del arreglo (debe ser múltiplo de 4 y mayor que 500)
    const int N = 1000;

    // Inicialización de los arreglos en el host
    float *h_a = new float[N];
    float *h_b = new float[N];
    float *h_result = new float[N];

    // Inicializa los arreglos con valores constantes
    for (int i = 0; i < N; ++i) {
        h_a[i] = 0.87654321;
        h_b[i] = 0.12345678;
    }

    // Allocación de memoria en el dispositivo
    float *d_a, *d_b, *d_result;
    cudaMalloc((void**)&d_a, N * sizeof(float));
    cudaMalloc((void**)&d_b, N * sizeof(float));
    cudaMalloc((void**)&d_result, N * sizeof(float));

    // Copia de los datos del host al dispositivo
    cudaMemcpy(d_a, h_a, N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, N * sizeof(float), cudaMemcpyHostToDevice);

    // Configuración del lanzamiento del kernel
    int blockSize = 256;
    int gridSize = (N + blockSize - 1) / blockSize;

    // Medición del tiempo de inicio
    clock_t start_time = clock();

    // Lanzamiento del kernel
    dotProduct<<<gridSize, blockSize>>>(d_a, d_b, d_result, N);

    // Sincronización
    cudaDeviceSynchronize();

    // Medición del tiempo de finalización
    clock_t end_time = clock();
    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    // Copia del resultado desde el dispositivo al host
    cudaMemcpy(h_result, d_result, N * sizeof(float), cudaMemcpyDeviceToHost);

    // Suma de todos los resultados parciales para obtener el resultado total
    float totalResult = 0.0;
    for (int i = 0; i < N; ++i) {
        totalResult += h_result[i];
    }

    // Impresión del resultado total y tiempo de ejecución
    std::cout << "Resultado total del producto punto: " << totalResult << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsed_time << " segundos" << std::endl;

    // Liberación de memoria en el dispositivo
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_result);

    // Liberación de memoria en el host
    delete[] h_a;
    delete[] h_b;
    delete[] h_result;

    return 0;
}
