###############################################
# ASM: Generador de n´umeros pseudo-aleatorios#
#                                             #
#	@ Polinomio                               #
#	P(x) = x^6 + x^5 + 1                      #
#   taps: 6 5 1                               #
#	                                          #
#	@ Semilla                                 #
#   Apellido: Guzman                          #
#	=> G : 0x47                               #
#	Posicion en memoria -> 0x100              #
#                                             #
#   @ Posicion de los bytes                   #
#      (MSB)         (LSB)                    #
#   --> [1|2|3|4|5|6|7|8] -->                 #
#                                             #
###############################################


# Agrega el valor semilla
# Asigna el registro a2 la posicion de memoria 0x100
# Almacena en a2 el valor semilla (a1 = 0x47)
# Establecemos un contador
# Detenemos la cuenta al llegar a 100
start:
    li a1, 0x47
    li a2, 0x100
    sw a1, 0(a2)
    li a3, 0x0
    li a4, 0x64

# Al valor semilla le aplicamos >> 2 y guardamos en t0
# Al valor semilla le aplicamos >> 3 y guardamos en t1
# Aplicamos t1 ^ t0 y guardamos en t0
# Agregamos el bit resultante del xor anterior
# Lo agregamos en la posicion MSB aplicando << 7
# Descartamos el valor LSB aplicando >> 1
# 
lsfr:
    srli t0, a1, 0x2
    srli t1, a1, 0x3
    xor t2, t1, t0
    andi t4, t2, 0x1
    slli t4, t4, 0x7
    srli t5, a1, 0x1
    add a1, t5, t4

# Aumentamos el valor del contador en +1
# Aumentamos el valor de posicion de memoria en +4
# Guardamos
# Preguntamos si el contador llego a 100
# De darse que si saltamos al final del programa
checking:
    addi a3, a3, 0x1
    addi a2, a2, 0x4
    sw a1, 0(a2)
    blt a3, a4, lsfr
    j end

# Fin del programa
end:
    nop