#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h> // Encabezado necesario para intrínsecos SSE
#include <cstdlib>
#include <ctime>

int main() {
    // Tamaño de los vectores, debe ser un múltiplo de 4 y mayor que 500
    const int N = 1000;

    std::vector<float> arr1(N, 0.87654321);  // Inicializa con valores constantes
    std::vector<float> arr2(N, 0.12345678);  // Inicializa con valores constantes

    float dotProduct = 0;

    auto start = std::chrono::high_resolution_clock::now();

    // Vectorización con intrínsecos SSE
    __m128 sum = _mm_setzero_ps(); // Inicializa un registro SSE con ceros

    for (int i = 0; i < N; i += 4) {
        __m128 a = _mm_loadu_ps(&arr1[i]); // Carga 4 elementos de arr1 en un registro SSE
        __m128 b = _mm_loadu_ps(&arr2[i]); // Carga 4 elementos de arr2 en otro registro SSE
        __m128 product = _mm_mul_ps(a, b); // Realiza la multiplicación de los registros SSE
        sum = _mm_add_ps(sum, product); // Acumula los resultados en el registro 'sum'
    }

    // Suma horizontal de los elementos en el registro SSE
    float result[4];
    _mm_store_ps(result, sum);
    dotProduct = result[0] + result[1] + result[2] + result[3];

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Imprime el resultado del producto punto y el tiempo de ejecución con vectorización SSE
    std::cout << "Resultado del producto punto: " << dotProduct << std::endl;
    std::cout << "Tiempo de ejecución con vectorización SSE: " << elapsed.count() << " segundos" << std::endl;

    return 0;
}