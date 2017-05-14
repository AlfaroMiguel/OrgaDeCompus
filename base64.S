#include <mips/regdef.h>
#include <sys/syscall.h>

.text
.abicalls
.align 2
.global base64_encode
.ent base64_encode

#a0 = fd_in
#a1 = fd_out

#Conversion:
#base256  |....8....|....8....|....8....|
#base64   |....6..|...6..|..6...|..6....|

#"Man" a base64
#base256  |  M  |  a  |  n  |
#base64   | T |  W | F  | u |


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
              lw a0, 40(sp)        # fd = infd
              la a1, buffer        # buf = es el direccion donde quiere que la funcion guarde lo que leyo
              li a2, 3             # leo 3 bytes
              li v0, SYS_read      # se guarda en v0 el codigo del system call
              syscall

              la t2, buffer       #t2 = buffer
              la t3, tabla        #t3 = tabla

              lw t4, 0(t2)        #t4 = 4 bytes (me sirven solo los 3 primeros)

              beqz v0, fin        #read = 0 => EOF

              sll s1, t4, 24
              srl s1, s1, 26        #s1 = indice primer byte de base 64

              sll s2, t4, 16
              srl s2, s2, 28

              sll t5, t4, 30
              srl t5, t5, 26
              or s2, s2, t5         #s2 = indice segundo byte de base 64


              beq v0, 1, cargar_s3 #Si se leyo 1 solo byte los ultimos dos bytes base64 son '='

              sll s3, t4, 20
              srl s3, s3, 28
              sll s3, s3, 2
              sll t5, t4, 8
              srl t5, t5, 30
              or s3, s3, t5         #s3 = indice tercer byte base 64


              beq v0, 2, cargar_s4  #si se leyeron 2 bytes el ultimo byte base64 es '='

              sll s4, t4, 10
              srl s4, s4, 26        #s4 = indice cuarto byte base 64

              j cargar_buffer

cargar_s3:
          li s3, 64                 #s3 = '='

cargar_s4:
          li s4, 64                 #s4 = '='
          j cargar_buffer


cargar_buffer:
              la t2, buffer

              add t1, t3, s1  #buffer + indice del primer byte
              lb s1,  (t1)    #s1 = byte base64
              sb s1, 0(t2)    #cargo el byte en buffer+0

              add t1, t3, s2
              lb s2, (t1)
              sb s2, 1(t2)    #cargo el byte en buffer+1

              add t1, t3, s3
              lb s3, (t1)
              sb s3, 2(t2)    #cargo el byte en buffer+2

              add t1, t3, s4
              lb s4, (t1)
              sb s4, 3(t2)    #cargo el byte en buffer+3

imprimir:
              lw a0, 44(sp)        # a0 = fd_out
              la a1, buffer        # a1 = direccion del buffer a escribir
              li a2, 4             # a2 = bytes a escribir
              li v0, SYS_write     # Indicamos que queremos llamar a la syscall write
              syscall
              sw zero, buffer      #limpio el buffer
              j leer               # leo de nuevo

fin:
              lw ra,32(sp)
              lw $fp,28(sp)
              addu sp,sp,40
              jr ra
              .end base64_encode

.data
.align 2
buffer: .space 4
tabla: .ascii "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="
