#ifndef _BASE64_H
#define _BASE64_H

#include <stdio.h>
#include <stdlib.h>

#define EMPTYASCII '\0'
#define EMPTYBASE64 '='

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

/*Recibe 3 caracteres en ASCII y los codifica a 4 Base64*/
void base64_encode(const char* source_code, char* result);

void base64_decode(const char* source_code, char* result);

#endif
