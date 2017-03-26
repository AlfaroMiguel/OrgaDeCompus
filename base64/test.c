#include "base64.h"

int main(){
    char* in = "skf";
    char result[4];
    base64_encode(in, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }
    printf("\n");



    return 0;
}