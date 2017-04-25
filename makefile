all:
	nasm -f elf64 fun.asm -o funcion.o
	g++ -std=c++11 -pthread -o ejec main.cpp funcion.o `sdl2-config --cflags --libs`
