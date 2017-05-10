#include <mips/regdef.h>
#include <sys/syscall.h>

.text
.abicalls
.align 2
.globl base64_encode
.ent base64_encode

base64_encode:
    .frame $fp, 40, ra
    .set noreorder
    .cpload t9
    .set reorder

    subu sp, sp, 40
    .cprestore 24
    sw $fp, 28(sp)

    move $fp, sp
    sw a0, 40($fp) #a0 = fd in
    sw a1, 44($fp) #a1 = fd out

    jr ra

.end base64_encode

.ent base64_decode

.globl base64_decode
base64_decode:
    jr ra
.end base64_decode

.align 0
.data
buffer_encode: .space 3
buffer_decode: .space 4
