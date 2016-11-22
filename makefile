all: executeProgram.c modifyHomePath.c terminal.c
	gcc executeProgram.c modifyHomePath.c terminal.c -o exec