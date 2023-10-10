#!/bin/bash

# Carpeta de resultados
results_folder="results"

# Crea la carpeta de resultados si no existe
mkdir -p results

# Bucle para ejecutar el comando 100 veces
for i in {1..100}
do
    # Nombre del archivo de salida
    output_file="$results_folder/pi_loop_$(printf "%02d" $i).txt"
    
    # Ejecuta el comando y guarda la salida en el archivo
    gcc -o pi_loop pi_loop.c -fopenmp
    ./pi_loop >> "$output_file"
    
    # Limpia el ejecutable
    rm -f pi_loop
done
