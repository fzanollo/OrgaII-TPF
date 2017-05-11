#g++ -o ejec main.cpp funcion.o `sdl2-config --cflags --libs`
#g++ main.cpp funcion.o -std=c++11 -w -g -lSDL2 -lSDL2_gfx -o ejec

all:
	nasm -f elf64 fun.asm -o funcion.o
	g++ main.cpp funcion.o -msse3 -std=c++11 -w -g -lSDL2 -lSDL2_gfx -o ejec
