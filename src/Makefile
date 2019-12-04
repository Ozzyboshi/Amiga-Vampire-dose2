CC = m68k-amigaos-gcc
LIBVORBIS = -L/opt/amiga/libvorbis/lib -lvorbisfile -lvorbis -logg
#LIBSDL = -I/opt/amiga/ammx/libSDL12/include/

# -- These are for Mac OS X only, remove for other targets
#SDLPREFIX = /usr/local/bin/
#CFLAGS += -DOSX
# --
SDLBASEPATH=/opt/amiga/ammx/libSDL12
LIBSDL = -L$(SDLBASEPATH) -lSDL
INCLUDESDL = -I$(SDLBASEPATH)/include/SDL
CFLAGS = -ffast-math -m68040 -m68881 -mhard-float -noixemul -fomit-frame-pointer  -Os $(INCLUDESDL) -I/opt/amiga/libvorbis/include/vorbis -I/opt/amiga/libvorbis/include -I/opt/amiga/SDL_mixer/include



# Endianness of the system. Leave commented for MSB systems (PPC/MIPS/etc.)
#CFLAGS += -DINTEL

objs = alue.o argb.o blob.o demo.o layer.o line.o main.o obu2d.o  palette.o schaibe.o taso.o

all dose2: $(objs)
	$(CC)  -o dose2 $(objs) $(CFLAGS) -L/opt/amiga/SDL_mixer/lib -lSDL_mixer  -L/tmp   $(LIBSDL) $(LIBVORBIS)  -L/opt/amiga/zlib-package/lib -lz -ldebug /opt/amiga/m68k-amigaos/lib/libm.a
#$(CC) -o dose2  $(objs) $(CFLAGS)   -L/opt/amiga/m68k-amigaos/lib -L /opt/amiga/SDL_mixer/lib -lSDL_mixer -L/opt/amiga/libvorbis/lib -lvorbisfile -lvorbis -logg  -lSDL -ldebug /opt/amiga/m68k-amigaos/lib/libm.a
#m68k-amigaos-gcc -o dose2  $(objs) -noixemul -Os -Wall -Wno-unused -m68040 -mhard-float -fomit-frame-pointer  -L/opt/amiga/m68k-amigaos/lib -L /opt/amiga/SDL_mixer/lib -lSDL_mixer -L/opt/amiga/libvorbis/lib -lvorbisfile -lvorbis -logg  -lSDL -ldebug /opt/amiga/m68k-amigaos/lib/libm.a
#m68k-amigaos-strip -g dose2

clean:
	rm -f  *.o dose2
	
