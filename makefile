all: executeProgram.c modifyHomePath.c shell.c
	gcc executeProgram.c modifyHomePath.c shell.c -o exec