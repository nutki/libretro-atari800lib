CFLAGS=-O3 -shared -Wall
libatari800-5200-libretro.so: core.o core_5200.o libatari800.a
	gcc -shared -o $@ $^
libatari800-libretro.so: core.o core_800.o libatari800.a
	gcc -shared -o $@ $^
