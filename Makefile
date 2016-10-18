all:
	gcc expression.c
	gcc main.c
	gcc -o menu menu.c `pkg-config --libs --cflags gtk+-2.0` -lm
	gcc -o spin spin.c `pkg-config --libs --cflags gtk+-2.0` -lm
	gcc -o truth truth.c `pkg-config --libs --cflags gtk+-2.0` -lm

