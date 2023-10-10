import os
import glob
from plotly.subplots import make_subplots
import plotly.graph_objects as go
import re

def plotter():
    files = [txt for txt in glob.glob("openMP/partIII/results/*.txt")]
    
    # Nuevo patrón para el formato de los datos
    # Número de términos = 100000, e estimada = 2.718281828459046, tiempo = 6.371832 segundos, hilos = 8
    pattern = re.compile("Número de términos = (\d+), e estimada = ([\d.]+), tiempo = ([\d.]+) segundos, hilos = (\d+)")
    
    total_tests = float(len(files))
    acc_times = []
    acc_threads = []

    for txt in files:
        with open(txt) as fd:
            # get data lists
            terms, estimated_e, runtime, num_threads = zip(*[(int(match.group(1)), float(match.group(2)), float(match.group(3)), int(match.group(4))) for line in fd.readlines() for match in [pattern.search(line)] if match])
            
            # first iteration acc is empty
            if len(acc_times) == 0:
                acc_times = [0.0] * len(runtime)
                acc_threads = [0] * len(num_threads)

            # add previous runtimes
            acc_times = [sum(time) for time in zip(runtime, acc_times)]

            # add previous thread counts
            acc_threads = [sum(threads) for threads in zip(num_threads, acc_threads)]

    average_runtimes = [acc_time / total_tests for acc_time in acc_times]
    average_threads = [acc_thread / total_tests for acc_thread in acc_threads]

    fig = make_subplots(rows=2, cols=1, subplot_titles=("Términos y Tiempo Promedio", "Hilos y Tiempo Promedio"))

    fig.add_trace(
        go.Scatter(x=terms, y=average_runtimes, mode="lines+markers", name="Tiempo Promedio"),
        row=1, col=1
    )

    fig.add_trace(
        go.Scatter(x=terms, y=estimated_e, mode="lines+markers", name="e Estimada"),
        row=1, col=1
    )

    fig.add_trace(
        go.Scatter(x=average_threads, y=average_runtimes, mode="lines+markers"),
        row=2, col=1
    )

    # edit axis labels
    fig['layout']['xaxis']['title'] = 'Número de Términos'
    fig['layout']['xaxis2']['title'] = 'Número de Hilos'
    fig['layout']['yaxis']['title'] = 'Tiempo Promedio (segundos)'
    fig['layout']['yaxis2']['title'] = 'Tiempo Promedio (segundos)'

    fig.show()

if __name__ == "__main__":
    plotter()
