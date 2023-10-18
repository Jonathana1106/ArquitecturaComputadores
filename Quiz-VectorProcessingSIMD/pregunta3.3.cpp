#include <iostream>
#include <vector>
#include <chrono>
#include <immintrin.h> // Encabezado necesario para intrínsecos AVX
#include <cstdlib>
#include <ctime>

int main() {
    // Tamaño de los vectores, debe ser un múltiplo de 8 y mayor que 500 para AVX
    const int N = 1000;

    std::vector<float> arr1(N);
    std::vector<float> arr2(N);

    // Inicializa los arreglos con valores aleatorios
    srand(static_cast<unsigned>(time(nullptr))); // Inicializa el generador de números aleatorios

    for (int i = 0; i < N; i++) {
        // Genera valores entre 0.0 y 1.0
        arr1[i] = static_cast<float>(rand()) / RAND_MAX;
        arr2[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    float dotProduct = 0;

    auto start = std::chrono::high_resolution_clock::now();

    // Vectorización con intrínsecos AVX
    __m256 sum = _mm256_setzero_ps(); // Inicializa un registro AVX con ceros

    for (int i = 0; i < N; i += 8) {
        __m256 a = _mm256_loadu_ps(&arr1[i]); // Carga 8 elementos de arr1 en un registro AVX
        __m256 b = _mm256_loadu_ps(&arr2[i]); // Carga 8 elementos de arr2 en otro registro AVX
        __m256 product = _mm256_mul_ps(a, b); // Realiza la multiplicación de los registros AVX
        sum = _mm256_add_ps(sum, product); // Acumula los resultados en el registro 'sum'
    }

    // Suma horizontal de los elementos en el registro AVX
    float result[8];
    _mm256_storeu_ps(result, sum);
    dotProduct = result[0] + result[1] + result[2] + result[3] + result[4] + result[5] + result[6] + result[7];

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Imprime el resultado del producto punto y el tiempo de ejecución con vectorización AVX
    std::cout << "Resultado del producto punto: " << dotProduct << std::endl;
    std::cout << "Tiempo de ejecución con vectorización AVX: " << elapsed.count() << " segundos" << std::endl;

    return 0;
}
