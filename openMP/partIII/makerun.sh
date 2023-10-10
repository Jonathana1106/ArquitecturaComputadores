#!/bin/bash

# Carpeta de resultados
results_folder="results"

# Crea la carpeta de resultados si no existe
mkdir -p results

# Bucle para ejecutar el comando 10 veces
for i in {1..10}
do
    # Nombre del archivo de salida
    output_file="$results_folder/e_taylor_$(printf "%02d" $i).txt"
    
    # Ejecuta el comando y guarda la salida en el archivo
    gcc -o e_taylor e_taylor.c -fopenmp
    ./e_taylor >> "$output_file"
    
    # Limpia el ejecutable
    rm -f e_taylor
done

# Después de ejecutar e_taylor 10 veces, ejecuta plotter.py
/bin/python3 plotter.py