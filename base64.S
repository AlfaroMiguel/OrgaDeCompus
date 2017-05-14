#include <mips/regdef.h>
#include <sys/syscall.h>

.text
.abicalls
.align 2
.global base64_encode
.ent base64_encode

#a0 = fd_in
#a1 = fd_out

base64_encode:
              .frame $fp, 40, ra
              .set noreorder
              .cpload t9
              .set reorder

              subu sp,sp,40       #size stack frame
              .cprestore 24
              sw ra,32(sp)        #guardo el ra
              sw $fp,28(sp)       #guardo el frame pointer
              move $fp,sp         #inserto el valor del stack pointer en el frame pointer
              sw a0,40(sp)        #guardo a0 en el stack del caller
              sw a1,44(sp)        #guardo a1 en el stack de caller

leer:
              lw a0,40(sp)        # fd = infd
              la a1,buffer        # buf = es el direccion donde quiere que la funcion guarde lo que leyo
              li a2,3             # leo 3 bytes
              li v0,SYS_read      # se guarda en v0 el codigo del system call
              syscall

              li t1, 2            #t1 = shift necesarios para quedarme con los bits mas significativos
              la t2, buffer       #t2 = buffer
              la t3, tabla        #t3 = tabla

              lb t4, (t2)       #t4 = primer byte leido
              addiu t2, t2, 1
              lb t5, (t2)       #t5 = segundo byte leido
              addiu t2, t2, 1
              lb t6, (t2)       #t6 = tercer byte leido


              srl s1, t4, t1      #s1 = indice primer byte base 64

              add t7, t3, s1      #t7 = direc del byte a cargar
              lb s1, (t7)         #s1= byte base64

              la t2, buffer
              sb s1, (t2)       #guardo el byte en el buffer



imprimir:
              lw a0,44(sp)        # a0 = fd_out
              la a1,buffer        # a1 = direccion del buffer a escribir
              li a2,4             # a2 = bytes a escribir
              li v0,SYS_write     # Indicamos que queremos llamar a la syscall write
              syscall
              j fin               # termino

fin:
              lw ra,32(sp)
              lw $fp,28(sp)
              addu sp,sp,40
              jr ra
              .end base64_encode


.data
.align 0
buffer: .space 5
tabla: .ascii "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="
