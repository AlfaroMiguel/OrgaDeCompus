#include <mips/regdef.h>
#include <sys/syscall.h>


#define EMPTYBASE256  0
#define EMPTYBASE64 61
#define PLUS 43
#define SLASH 47
#define A_ASCII 65
#define Z_ASCII 90
#define A_MIN_ASCII 97
#define Z_MIN_ASCII 122
#define ZERO_ASCII 48
#define NINE_ASCII 57
#define OFFSET1 65
#define OFFSET2 71
#define OFFSET3 4
#define PLUSB64 62
#define SLASHB64 63

.text
.abicalls
.align 2
.global base64_encode
.global base64_decode
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
              .frame $fp, 16, ra
              .set noreorder
              .cpload t9
              .set reorder

              subu sp,sp,16       #size stack frame
              .cprestore 12
              sw ra,8(sp)        #guardo el ra
              sw $fp,4(sp)       #guardo el frame pointer
              move $fp,sp         #inserto el valor del stack pointer en el frame pointer
              sw a0,16(sp)        #guardo a0 en el stack del caller
              sw a1,20(sp)        #guardo a1 en el stack de caller

leer:
              lw a0, 16(sp)        # fd = infd
              la a1, buffer        # buf = es el direccion donde quiere que la funcion guarde lo que leyo
              li a2, 3             # leo 3 bytes
              li v0, SYS_read      # se guarda en v0 el codigo del system call
              syscall

              bnez a3, e_error_lectura #(a3!=0) => error_lectura

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
              lw a0, 20(sp)        # a0 = fd_out
              la a1, buffer        # a1 = direccion del buffer a escribir
              li a2, 4             # a2 = bytes a escribir
              li v0, SYS_write     # Indicamos que queremos llamar a la syscall write
              syscall

              bnez a3, e_error_escritura  #(a3!=0) => error_escritura

              sw zero, buffer      #limpio el buffer
              j leer               # leo de nuevo

e_error_escritura:
              li v0, 2 #v0 = indice del mensaje en el arreglo en tp1.c
              j fin

e_error_lectura:
              li v0, 3 #v0 = indice del mensaje en el arreglo en tp1.c
              j fin

fin:
              lw ra,8(sp)
              lw $fp,4(sp)
              addu sp,sp,16
              jr ra
              .end base64_encode
.align 2
.ent base64_decode

base64_decode:
            .frame $fp, 16, ra
            .set noreorder
            .cpload t9
            .set reorder

            subu sp,sp,16       	#sizeof stack frame
            .cprestore 12
            sw ra,8(sp)       
            sw $fp,4(sp)      
            move $fp,sp        
            sw a0,16(sp)    	    
            sw a1,20(sp)        	

d_leer:
            lw a0, 16(sp)        	# fd = fd_in
            la a1, buffer       	# buf = dest_addr
            li a2, 4            	# leo 4 bytes
            li v0, SYS_read      	# se guarda en v0 el codigo del system call
            syscall

            bnez a3, d_error_lectura #(a3!=0) => error lectura

            la t2, buffer       	#t2 = buffer

            lw t4, 0(t2)        	#t4 = 4 bytes (IMPORTANTE: buffer[0] es t4 & 0xFF)

			beqz v0, d_fin  		#read = 0 => EOF
			bltu v0,4,decode_error	#si no leyo 4 bytes devolver error siempre

			li t5, 0				#IDX = 0
			li t3, 0				#tmp
			li t0, 0				#cant paddings leidos, <=2 por precond

d_loop:		
			beq t5,v0,d_formateo	#DEBUG	
			sll t6,t5,3				#t6 = t5 * 8	
			srl	t2,t4,t6			#t2 = t4 >> IDX = buffer[IDX]
			andi t2,t2,0xff			#solo me quedo con ese B
			
			bne t2,EMPTYBASE64,sigue0
			li	t2,EMPTYBASE256
			addiu t0,t0,1
			j d_fin_loop
			
sigue0:		bltu t2,A_ASCII,sigue1
			bgtu t2,Z_ASCII,sigue1
			subu t2,t2,OFFSET1
			j d_fin_loop

sigue1:		bltu t2,A_MIN_ASCII,sigue2
			bgtu t2,Z_MIN_ASCII,sigue2
			subu t2,t2,OFFSET2
			j d_fin_loop

sigue2:		bltu t2,ZERO_ASCII,sigue3
			bgtu t2,NINE_ASCII,sigue3
			addiu t2,t2,OFFSET3
			j d_fin_loop

sigue3:		bne t2,PLUS,sigue4
			li	t7,PLUSB64
			move t2,t7
			j d_fin_loop

sigue4:		bne t2,SLASH,decode_error
			li	t2,SLASHB64
			j d_fin_loop

decode_error:		
			li v0,1
			j d_fin

d_fin_loop:	
			sll	t2,t2,t6
			or	t3,t3,t2			
			addiu t5,t5,1
			j d_loop

#t5 es la cantidad de Bytes leidos (ahora es igual a v0)
#t3 es tmp
#a1 es &buffer

#    result[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4)
#    result[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2)
#    result[2] = ((tmp[2] & 0x3) << 6) + tmp[3]

d_formateo:
			andi t2,t3,0xff		#t2=tmp[0]
			sll	t2,t2,2	
			srl	t4,t3,12		#t4=tmp[1]>>4	
			andi t4,t4,0x3		#t4 &= 0x3
			addu t2,t2,t4
			sb	t2,0(a1)		#buffer[0]=t2

#tras esto buffer[0] = | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
#					   | 		tmp[0][0:5]    |tmp[1][4:5]|
	
			srl	t2,t3,4		
			andi t2,t2,0xf0		#t2=(tmp[1] & 0xf) <<4
			srl t4,t3,18
			andi t4,t4,0xf		#t4= (tmp[2] >> 2) & 0xf
			addu t2,t2,t4
			sb	t2,1(a1)		#buffer[1]=t2

#tras esto buffer[1] = | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
#					   | tmp[0][0:3]   |   tmp[2][2:5] |

			li t2,0x30000
			and t2,t3,t2
			srl t2,t2,10		#t2=(tmp[2] & 0x3) <<6
			srl t4,t3,24		#t4=tmp[3]
			addu t2,t2,t4
			sb t2,2(a1)			#buffer[2]=t2
	
#tras esto buffer[2] = | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
#				   |tmp[2][0:1]|      tmp[3][0:5]	   |	


d_imprimir:
            lw a0, 20(sp)       #a0 = fd_out
            la a1, buffer       #a1 = direccion del buffer a escribir
            li a2, 3            #a2 = bytes a escribir
			subu a2,a2,t0		#a2 = 3 - cant paddings
            li v0, SYS_write     
            syscall

            bnez a3, d_error_escritura #(a3!=0) => error escritura

            sw zero, buffer     #limpio el buffer
            j d_leer            # leo de nuevo

#si vengo de error ya cargo v0 con 1
#si leyo 0 del read entonces v0 ya es 0

d_error_escritura:
              li v0, 2 #v0 = indice del mensaje en el arreglo en tp1.c
              j d_fin

d_error_lectura:
              li v0, 3 #v0 = indice del mensaje en el arreglo en tp1.c
              j d_fin


d_fin:
            lw ra,8(sp)
            lw $fp,4(sp)
            addu sp,sp,16
            jr ra
            .end base64_decode


.data
.align 2
buffer: .space 4
tabla: .ascii "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="

