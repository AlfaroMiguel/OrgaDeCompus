CFLAGS := -std=c99 -Wall -pedantic
DIREC1 = parser
DIREC2 = base64

tp0:
	gcc ${CFLAGS} $@.c $(DIREC1)/*.h $(DIREC1)/*.c $(DIREC2)/*.h $(DIREC2)/*.c -o $@

clean:
	rm -f tp0 *.o

.PHONY: clean
