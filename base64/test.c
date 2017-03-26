#include "base64.h"

void test_decode(char* in, char* result){
    if(base64_decode(in, result)){
        printf("ANDUVO OK CON ENTRADA: ");
        for(int i = 0; i < 4; i++) {
            printf("%c", in[i]);
        }
        printf("\n");

        printf("Y LA SALIDA ES: ");
        for(int i = 0; i < 3; i++) {
            printf("%c", result[i]);
        }
        printf("\n");
    }
    else{
        printf("FALLA CON ENTRADA: ");
        for(int i = 0; i < 4; i++) {
            printf("%c", in[i]);
        }
        printf("\n");
    }
}

int main(){

    /*TEST ENCODE*/
    /*char* in = "any";
    char* in2 = " ca";
    char* in3 = "rna";
    char* in4 = "l p";
    char* in5 = "lea";
    char* in6 = "sur";
    char* in7 = "e\0\0";

    char result[4];

    *//*SI, ESTA HORRIBLE PERO PAJA SON LAS 2:19 AM*//*
    *//*Segun WIKIPEDIA da: YW55IGNhcm5hbCBwbGVhc3VyZQ==*//*
    *//*Chequeado OK*//*

    base64_encode(in, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }
    base64_encode(in2, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }
    base64_encode(in3, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }
    base64_encode(in4, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }
    base64_encode(in5, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }
    base64_encode(in6, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }
    base64_encode(in7, result);
    for(int i = 0; i < 4; i++) {
        printf("%c", result[i]);
    }

    printf("\n");*/






    /*TEST DECODE*/
    /*Se pasan 4 bytes que representan un byte de BASE64 y se obtienen 3 bytes ASCII*/

    char* in = "TWFu"; //OK "Man"
    char* in2 = "lkjd"; //TENDRIA QUE FALLAR
    char* in3 = "jd=="; //TENDRIA QUE FALLAR
    char* in4 = "TW=="; //OK "M'"
    char* in5 = "PAS="; //FALLA

    char result[3];

    test_decode(in, result);

    test_decode(in2, result);

    test_decode(in3, result);

    test_decode(in4, result);

    test_decode(in5, result);



    /*DECODIFICO YW55IGNhcm5hbCBwbGVhc3VyZQ==*/
    char* t1 = "YW55";
    char* t2 = "IGNh";
    char* t3 = "cm5h";
    char* t4 = "bCBw";
    char* t5 = "bGVh";
    char* t6 = "c3Vy";
    char* t7 = "ZQ==";

    base64_decode(t1, result);
    for(int i = 0; i < 3; i++) {
        printf("%c", result[i]);
    }
    base64_decode(t2, result);
    for(int i = 0; i < 3; i++) {
        printf("%c", result[i]);
    }
    base64_decode(t3, result);
    for(int i = 0; i < 3; i++) {
        printf("%c", result[i]);
    }
    base64_decode(t4, result);
    for(int i = 0; i < 3; i++) {
        printf("%c", result[i]);
    }
    base64_decode(t5, result);
    for(int i = 0; i < 3; i++) {
        printf("%c", result[i]);
    }
    base64_decode(t6, result);
    for(int i = 0; i < 3; i++) {
        printf("%c", result[i]);
    }
    base64_decode(t7, result);
    for(int i = 0; i < 3; i++) {
        printf("%c", result[i]);
    }
    printf("\n");

    /*QUE HERMOSAS PRUEBAS TENDRIA QUE IMPRIMIR*/
    /*any carnal pleasure*/
    /*CHECK OK ;) 04:15 AM*/

    /*Esto es lo que tendria que hacerse en el main con los archivos en el caso
     * de decode (el mas complicado) leer 4 bytes y esta funcion devuelve false cuando
     * hubo un error ahi, hay que informar por stderr y parar el proceso
     *
     * Despues retoco un poco mas las funciones de encode y decode pero como estan ahora andan
     * no hay mucho mas por hacer igual :)*/

    return 0;
}