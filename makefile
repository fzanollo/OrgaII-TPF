all:
	nasm -f elf64 fun.asm -o funcion.o
	g++ -o ejec uplift_2D_ASMversion.cpp funcion.o
