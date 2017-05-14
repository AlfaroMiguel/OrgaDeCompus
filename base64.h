#ifndef _BASE64_H
#define _BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/*DEFINICION CONSTANTES*/
//#define EMPTYBASE256 '\0'
#define EMPTYBASE256  0
//#define EMPTYBASE64 '='
#define EMPTYBASE64 61
//#define PLUS '+'
#define PLUS 43
//#define SLASH '/'
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


int base64_encode(int fd_in, int fd_out);

int base64_decode(int fd_in, int fd_out);

#endif
