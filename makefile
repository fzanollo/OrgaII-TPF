all:
	nasm -f elf64 fun.asm -o funcion.o
	g++ main.cpp upliftTerrainGenerator2D.cpp upliftTerrainGenerator2D_C.cpp upliftTerrainGenerator2D_ASM.cpp funcion.o -msse3 -std=c++11 -w -g -lSDL2 -lSDL2_gfx -o upliftTerrainGeneratorCAndASM
