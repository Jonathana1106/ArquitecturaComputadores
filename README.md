# ArquitecturaComputadores


## Sesion asincronica semana 02

### ASM: Generador de numeros pseudo-aleatorios

#### Requisitos

Para ejecutar el codigo es necesario tener instalado algun programa simulador del lenguaje ensamblador, como recomendacion tenemos el simulador de procesador `RISC-V`: [Ripes](https://github.com/mortbopet/Ripes/releases).

El mismo se encuentra disponible para Linux, Max y Windows. Las instrucciones de su respectiva instalacion se detallan [aquí](https://github.com/mortbopet/Ripes/blob/master/README.md).

#### Instrucciones

Para ejecutar el programa:

1. Abra el simulador Ripes.
2. Debe cargar un archivo, esto lo hace de la siguiente manera `File > Load Program` y seleccione el archivo deseado, en este caso `ejercicio.s`. Ademas verique que en las opciones de `File type` este seleccionada la opcion `Source file`.
3. En la seccion izquierda del programa se encuentran distintas opciones, si desea revisar el codigo utilice la opcion `Editor`.
4. Este codigo cuenta con un valor semilla que por defecto esta predeterminado en `0x47`, dado que se requeria la representacion hexadecimal de la primera letra del apellido del estudiante, en este caso `G`, el mismo puede cambiarse en la siguiente parte del codigo:

```gas:
start: 
    li, a1, <hex value>
```
5. Finalmente ejecute el programa dando _click_ al boton de `play` que se ubica en la barra superior cono un triangulo de color verde.

#### Funcionamiento del programa

Este generador se conoce como
_linear-feedback shift register_ `(LFSR)`, en este caso la version Fibonacci. Este generador obtiene
numeros en un orden secuencial aleatorio, cabe destacar que este generador tiene multiples aplicaciones: criptografıa, videojuegos, simulacion, etc.

1. Se tiene un valor semilla.
2. Luego se pasan por una serie de compuertas `XOR`, que toman los bits de las posiciones del polinomio `LFSR`.
3. Se realizan rotaciones de tipo `shift left`, esto con el fin de descartar el bit `LSB`.
4. Se actualizan los valores y se realiza de nuevo el paso `1`.

En la siguiente imagen se puede apreciar lo descrito anteriormente.

![lfsr](https://raw.githubusercontent.com/nikeshbajaj/Linear_Feedback_Shift_Register/master/images/LFSR.jpg)