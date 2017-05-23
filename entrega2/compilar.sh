gcc -c -ggdb -Wall tp1.c
gcc -c -ggdb -Wall parser/parser_tp0.c
gcc -c -ggdb -Wall base64.S

gcc tp1.o parser_tp0.o base64.o -o tpexe