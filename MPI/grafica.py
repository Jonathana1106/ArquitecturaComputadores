import matplotlib.pyplot as plt
import pandas as pd

# Leer los datos desde el archivo CSV
df = pd.read_csv('output.csv', names=['Size', 'Time'])

# Crear la gráfica
plt.plot(df['Size'], df['Time'], marker='o', linestyle='-', color='b')
plt.title('Tiempo de ejecución vs Tamaño del mensaje')
plt.xlabel('Tamaño del mensaje')
plt.ylabel('Tiempo de ejecución (segundos)')
plt.grid(True)
plt.show()
