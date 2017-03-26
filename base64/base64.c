#include "base64.h"

void base64_encode(const char* src, char* result){

    result[0] = (src[0] & 0xfc) >> 2;
    result[1] = ((src[0] & 0x03) << 4) + ((src[1] & 0xf0) >> 4);
    result[2] = ((src[1] & 0x0f) << 2) + ((src[2] & 0xc0) >> 6);
    result[3] = src[2] & 0x3f;

    for (int i = 0; i < 4; ++i) {
        if((unsigned int)result[i] == EMPTYASCII)
            result[i] = EMPTYBASE64;
        else
            result[i] = base64_table[(unsigned int)result[i]];
    }
}