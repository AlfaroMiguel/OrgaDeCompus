#ifndef _BASE64_H
#define _BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/*DEFINICION CONSTANTES*/
#define EMPTYBASE256 '\0'
#define EMPTYBASE64 '='

/*Tabla de simbolos Base64*/
static const char base64_table[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
};

/*Recibe:
 *       Buffer con 3 caracteres en Base256
 *       Buffer para guardar el resultado de la codificacion
 *
 *Codifica el contenido en Base256 a Base64 y lo guarda en el buffer resultado*/
bool base64_encode(const char* source_code, char* result, int char_to_encode);

/*Recibe:
 *       Buffer conteniendo 4 bytes en Base64
 *       Buffer de 3 bytes en Base256 para guardar el resultado
 *
 * Decodifica el contenido en Base64 y de ser una decodificacion existosa lo guarda
 * en el buffer result y devuelve True. Sino, devuelve False*/
bool base64_decode(const char* source_code, char* result, int* write);

#endif
