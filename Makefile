build:
	gcc src/*.c -o bin/test -lX11
run: build
	./bin/test
keysyms:
	cat /usr/include/X11/keysymdef.h
