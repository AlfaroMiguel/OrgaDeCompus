# OrgaDeCompus
TPs - Organización de computadoras - 1er Cuatrimestre 2017

:pushpin:Integrantes
* [Alfaro Miguel](https://github.com/AlfaroMiguel) :boy:
* [Errazquin Martín](https://github.com/martinerrazquin) :boy:
* [Mendez Agustina](https://github.com/abmendez) :girl:

:pushpin:Done

- [x] TP0
- [ ] TP1 (FIX!)
 - [x] Cambios en el main
 - [x] Assembly de encode
 - [x] Assembly de decode
 - [ ] Indicar como compilar
 - [ ] Revisar el caso que no funciona de decode (agrega ceros de mas)
  
               root@:~/2017q1/alfaro# hexdump -C in.bin
               00000000  62                                                |b|
               00000001
               root@:~/2017q1/alfaro# hexdump -C out.b64
               00000000  59 67 3d 3d                                       |Yg==|
               00000004
               root@:~/2017q1/alfaro# hexdump -C out.bin
               00000000  62 00 00                                          |b..|
               00000003
               
  - [ ] Chequear errores de I/O
  - [ ] Problema en parsing de parámetros
  
             root@:~/2017q1/alfaro# ./tp1 -h
             Segmentation fault (core dumped)
  
- [x] Informe TP0 https://www.overleaf.com/8715138fyzktgmsrwqc
- [ ] Informe TP1 https://www.overleaf.com/9580983spqfnfhnpdbn


Como ejecutar el "maravilloso" emulador y probar el programa for dummies:

* Ir a la carpeta gxemul-6620-20070927
* En una terminal nueva ejecutar "./xgxemul -e 3max -d netbsd-pmax.img" (sin el -x asi corre en una terminal de linux y podemos hacer copy paste)
* En esa terminar ingresar con el usuario "root" y pass "orga6620"
* En otra terminal de linux "sudo ifconfig lo:0 172.20.0.1"
* En la terminal que corrimos el primer comando (donde esta corriendo NETBSD) ejecutar: "ssh -R 2222:127.0.0.1:22 miguelalfaro@172.20.0.1" donde dice 'miguelalfaro' obviamente, va el nombre que tengas en linux
* Ahora esa terminal no nos sirve mas ya que abrimos un tunel ssh a linux (no queremos eso) NO LA CIERRRES, minimizala
* En una terminal nueva de linux necesitamos conectarnos a NETBSD, para eso: "ssh -p 2222 root@127.0.0.1" y nos pide la pass que es "orga6620"
* Ahora tenemos una terminal de linux si aparece algo como "Terminal type?" apretar ctrl + c
* Ahora necesitamos copiar el tp a NETBSD para eso en otra terminal nueva de linux hacemos por ejemplo:

      scp -P2222 -r /home/miguelalfaro/Desktop/Organizacion\ de\ Computadoras/TP1/OrgaDeCompus/ root@127.0.0.1:/home/tp1/
      scp -P2222 -r /home/miguelalfaro/Desktop/Organizacion\ de\ Computadoras/TP1/OrgaDeCompus/base64.S root@127.0.0.1:/home/tp1/
    
    
Ahora en la terminal que tenemos el tunel a NETBSD, podemos ejecutar comandos como cd o ls para ir hasta donde esta el tp, en este caso home/tp1 y alli para compilar el tp se hace:

     gcc -c -ggdb -Wall tp1.c
     gcc -c -ggdb -Wall parser_tp0.c
     gcc -c -ggdb -Wall base64.S
     
     gcc tp1.o parser_tp0.o base64.o -o tpexe

Si todo salio bien podemos hacer:

    echo -n Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.|./tpexe
    
    
Lo que nos da la salida:

      TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=
      
      
La cual es la correcta :)
