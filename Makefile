CFLAGS=-O3 -shared -Wall
LIBATARI800REV=master

all: libatari800-5200-libretro.so libatari800-libretro.so

libatari800-5200-libretro.so: core.o core_5200.o libatari800.a
	gcc -shared -o $@ $^

libatari800-libretro.so: core.o core_800.o libatari800.a
	gcc -shared -o $@ $^

atari800.zip:
	curl -L https://github.com/atari800/atari800/archive/refs/heads/${LIBATARI800REV}.zip -o $@

atari800: atari800.zip
	unzip $^
	mv atari800-${LIBATARI800REV} atari800

libatari800.a: atari800
	cd atari800; ./autogen.sh
	cd atari800; ./configure --target=libatari800
	make -C atari800
	cp ./atari800/src/libatari800/libatari800.h .
	cp ./atari800/src/libatari800.a .
