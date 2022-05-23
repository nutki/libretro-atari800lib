CFLAGS=-O3 -shared -Wall
libatari800lib-retro.so: core.o libatari800.a
	gcc -shared -o $@ $^
