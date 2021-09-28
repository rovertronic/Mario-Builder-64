# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64

.include "macros.inc"


.section .text, "ax"

.global mtxf_to_mtx_asm
.balign 32
mtxf_to_mtx_asm:
    addiu $v0, $zero, 0x0001
    lui $t2, 0x4780
    mtc1 $t2, $f4 
loop:
    lwc1 $f0, 0x0000($a1)
    andi $t0, $v0, 0x0002
    mul.s $f0, $f0, $f4
    lwc1 $f2, 0x0004($a1)
    trunc.w.s $f0, $f0
    mfc1 $t3, $f0
    addiu $a1, $a1, 0x0008
    sra $t4, $t3, 16
    sh $t4, 0x0000($a0)
    sh $t3, 0x0020($a0)
    bne $t0, $zero, storezero
    addiu $v0, $v0, 0x0002
    mul.s $f2, $f2, $f4
    addiu $t1, $zero, 1
    trunc.w.s $f2, $f2
    mfc1 $t3, $f2
    addiu $v1, $zero, 0x0011
    sra $t4, $t3, 16
    sh $t4, 0x0002($a0)
    sh $t3, 0x0022($a0)
loopend:
    bne $v0, $v1, loop
    addiu $a0, $a0, 0x0004
    jr $ra
    sh $t1, -2 ($a0)
storezero:
    sh $zero, 0x0002($a0)
    j loopend
    sh $zero, 0x0022($a0)