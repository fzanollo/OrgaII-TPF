all:
	nasm -f elf64 fun.asm -o funcion.o
	g++ main.cpp funcion.o -std=c++11 -w -g -lSDL2 -lSDL2_gfx -o ejec

