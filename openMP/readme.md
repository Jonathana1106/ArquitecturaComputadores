# Instrucciones para Ejecutar las Partes II y III del Trabajo en OpenMP

## Parte II del Trabajo

### Paso 1: Preparación

Asegúrate de estar en la carpeta de la Parte II:

cd /openMP/partII

### Paso 2: Ejecutar makerun.sh

chmod +x makerun.sh
./makerun.sh

## Parte II del Trabajo

### Paso 1: Preparación

cd openMP/partIII

### Paso 2: Ejecutar makerun.sh

chmod +x makerun.sh
./makerun.sh

### Paso 3: DIXPY

gcc -o daxpy daxpy.c -fopenmp
./daxpy

### Paso 4: Gráficas

python3 plotter.py

### Discusion

Es importante tener en cuenta que con la Serie de Taylor, el cálculo de 'e' nunca converge al valor exacto de 'e'. En su lugar, se cambió a utilizar el método Mercator para calcular una aproximación de 'e'. El número 'N' se establece en un mínimo de 10 para obtener una aproximación de 'e', y valores mayores a 10 se utilizan para mejorar la precisión.