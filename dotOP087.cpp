#include <iostream>
#include <vector>
#include <chrono>

int main() {
    // Tamaño de los vectores, (debe ser un múltiplo de 4 y mayor que 500)
    const int N = 1000;
    
    // Vectores para almacenar los valores
    std::vector<float> arr1(N, 0.87654321);  // Inicializa con valores constantes
    std::vector<float> arr2(N, 0.12345678);  // Inicializa con valores constantes

    float dotProduct = 0;

    // Mide el tiempo de inicio
    auto start = std::chrono::high_resolution_clock::now();

    // Realiza el cálculo del producto punto 10,000 veces
    for (int repeat = 0; repeat < 10000; repeat++) {
        dotProduct = 0;
        for (int i = 0; i < N; i++) {
            dotProduct += arr1[i] * arr2[i];
        }
    }

    // Mide el tiempo de finalización
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Imprime el resultado del producto punto
    std::cout << "Resultado del producto punto: " << dotProduct << std::endl;
    
    // Imprime el tiempo promedio de ejecución sin optimización en segundos
    std::cout << "Tiempo promedio de ejecución sin optimización: " << (elapsed.count() / 10000) << " segundos" << std::endl;

    return 0;
}