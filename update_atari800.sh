LIBATARI800REV=c0f94a7bf15543d8feb87ba046c456087c9d8227
rm -rf atari800
curl -L https://github.com/atari800/atari800/archive/$LIBATARI800REV.zip -o atari800.zip
unzip atari800.zip
rm atari800.zip
mv atari800-${LIBATARI800REV} atari800
cd atari800
./autogen.sh
./configure --target=libatari800
rm -rf .gitignore .travis .travis.yml DOC data debian emuos act Makefile.am util tools raspbian m4 atari800.spec autogen.sh configure.ac config.sub config.guess
rm -rf Makefile Makefile.in aclocal.m4 compile config.log config.status configure depcomp install-sh missing 
cd src
rm -rf .deps Makefile Makefile.in config.h.in stamp-h1 */.deps
rm -rf wince win32 sdl macosx javanvm gles2 falcon dos dc android atari_ntsc amiga
rm -rf atari_basic.c atari_curses.c atari_ps2.c atari_rpi.c atari_x11.c
