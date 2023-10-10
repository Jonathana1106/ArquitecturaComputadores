section .data
    semilla: dd 0x4A   ; Valor inicial de la semilla (J)
    contador: dd 0     ; Contador de números generados
    limite: dd 10      ; Número máximo de números a generar

section .text
    global _start
_start:
    ; Almacenar la semilla en memoria
    mov eax, [semilla]
    mov ebx, 0x100
    mov [ebx], eax

    ; Inicializar contador en 0
    mov eax, [contador]
    mov ebx, 0
    mov [eax], ebx

lsfr:
    ; Generar el siguiente número aleatorio
    mov eax, [ebx]
    mov edx, eax
    shr edx, 1
    xor edx, eax
    and edx, 1
    shl edx, 7
    shr eax, 1
    add eax, edx
    mov [ebx], eax

    ; Incrementar contador
    mov eax, [contador]
    add dword [eax], 1

    ; Comprobar si se han generado suficientes números
    mov eax, [contador]
    cmp eax, [limite]
    jl lsfr

    ; Fin del programa
    mov eax, 1
    xor ebx, ebx
    int 0x80
