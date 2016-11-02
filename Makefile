all:
	gcc -o project project.c `pkg-config --libs --cflags gtk+-2.0` -lm -Wall


