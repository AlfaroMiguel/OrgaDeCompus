#include "base64.h"

bool base64_encode(const char* src, char* result, int char_to_encode){

    result[0] = (src[0] & 0xfc) >> 2;
    result[1] = ((src[0] & 0x03) << 4) + ((src[1] & 0xf0) >> 4);
    result[2] = ((src[1] & 0x0f) << 2) + ((src[2] & 0xc0) >> 6);
    result[3] = src[2] & 0x3f;

    for (int i = 0; i < char_to_encode+1; ++i) {
            result[i] = base64_table[(unsigned int)result[i]];
    }

    for(int j = char_to_encode+1; j < 4; j++){
        result[j] = EMPTYBASE64;
    }

    return true;
}


bool base64_decode(const char* src, char* result, int* write){
    char tmp[4];
    int char_to_write = 0;
    for (int i = 0; i < 4; ++i) {
        tmp[i] = src[i];
    }

    for (int i = 0; i < 4; ++i) {
        if(tmp[i] == EMPTYBASE64){
            tmp[i] = EMPTYBASE256;
            continue;
        }
        for (int l = 0; l < 64; ++l) {
            if (tmp[i] == base64_table[l]) {
                tmp[i] = l;
                char_to_write++;
                break;
            }
        }
    }
    result[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
    result[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
    result[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

    bool decode_status = true;
    for(int i = 0; i < char_to_write-1; i++){
        decode_status &= (result[i] >= -128 && result[i] < 128);
    }
    *write = char_to_write-1;
    return decode_status;
}