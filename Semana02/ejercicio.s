

start:
    li a1, 0x47
    li a2, 0x100
    sw a1, 0(a2)
    li a3, 0x0
    li a4, 0x64


lsfr:
    srli t0, a1, 0x2
    srli t1, a1, 0x3
    xor t2, t1, t0
    andi t4, t2, 0x1
    slli t4, t4, 0x7
    srli t5, a1, 0x1
    add a1, t5, t4

checking:
    addi a3, a3, 0x1
    addi a2, a2, 0x4
    sw a1, 0(a2)
    blt a3, a4, lsfr
    j end

end:
    nop