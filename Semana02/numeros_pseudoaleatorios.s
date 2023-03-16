###############################################
# ASM: Generador de numeros pseudo-aleatorios #
#                                             #
#	-Polinomio                                #
#	P(x) = x^7 + x^6 + 1                      #
#   taps: 7 6 1                               #
#	                                          #
#	-Semilla                                  #
#   Apellido: Araya                           #
#	=> A : 0x41                               #
#	Posicion en memoria -> 0x100              #
#                                             #
#   - Posicion de los bytes                   #
#      (MSB)         (LSB)                    #
#   --> [1|2|3|4|5|6|7|8] -->                 #
#                                             #
###############################################

start:               # Inicio de la sección de código
    li a1, 0x41      # Carga el valor hexadecimal 0x41 (A) en el registro a1 (semilla)
    li a2, 0x100     # Carga la dirección de memoria 0x100 en el registro a2
    sw a1, 0(a2)     # Almacena el valor de la semilla en la posición de memoria 0x100
    li a3, 0x0       # Carga el valor 0 en el registro a3
    li a4, 0x64      # Carga el valor hexadecimal 0x64 en el registro a4
lsfr:                # Inicio de la sección que ejecuta el LFSR
    srli t0, a1, 0x1 # Desplaza el valor de la semilla una posición a la derecha y lo almacena en el registro temporal t0
    srli t1, a1, 0x2 # Desplaza el valor de la semilla dos posiciones a la derecha y lo almacena en el registro temporal t1
    xor t2, t1, t0   # Realiza la operación XOR entre los registros temporales t0 y t1 y almacena el resultado en el registro temporal t2
    andi t4, t2, 0x1 # Realiza la operación AND entre el registro temporal t2 y el valor hexadecimal 0x1 y almacena el resultado en el registro temporal t4
    slli t4, t4, 0x7 # Desplaza el valor del registro temporal t4 siete posiciones a la izquierda y lo almacena en el registro temporal t4
    srli t5, a1, 0x1 # Desplaza el valor de la semilla una posición a la derecha y lo almacena en el registro temporal t5
    add a1, t5, t4   # Realiza la suma entre los registros a1, t5 y t4 y almacena el resultado en el registro a1
checking:            # Inicio de la sección que comprueba si se han obtenido los 100 números aleatorios
    addi a3, a3, 0x1 # Incrementa en uno el valor del registro a3 (contador)
    addi a2, a2, 0x4 # Incrementa en cuatro la dirección de memoria almacenada en el registro a2
    sw a1, 0(a2)     # Almacena el valor generado en la dirección de memoria almacenada en el registro a2
    blt a3, a4, lsfr # Comprueba si el valor del registro a3 es menor que el valor hexadecimal 0x64 (100 en decimal), si es así, salta a la sección lsfr
    j end            # Salta a la etiqueta end
end:
    nop              # Fin de la sección de código
