#ifndef _BASE64_H
#define _BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/*DEFINICION CONSTANTES*/
#define EMPTYBASE256 '\0'
#define EMPTYBASE64 '='
#define PLUS '+'
#define SLASH '/'

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



/*Recibe:
 *       Buffer con 3 caracteres en Base256
 *       Buffer para guardar el resultado de la codificacion
 *       Cantidad de caracteres a encodear (que no son padding)
 *
 *Codifica el contenido en Base256 a Base64 y lo guarda en el buffer resultado*/
int base64_encode(int fd_in, int fd_out);

/*Recibe:
 *       Buffer conteniendo 4 bytes en Base64
 *       Buffer de 3 bytes en Base256 para guardar el resultado
 *       Puntero a int que apunta a un entero que guarda la cantidad de caracteres a escribir (que no son padding)
 *
 * Decodifica el contenido en Base64 y de ser una decodificacion existosa lo guarda
 * en el buffer result y devuelve True. Sino, devuelve False*/
int base64_decode(int fd_in, int fd_out);

#endif
