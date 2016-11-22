# OS-coursework
Coursework for Operating System UCL - Third Year Computer Science

##Shell.c
1. This file includes the `main()` function which operates the main structure of the program
2. `getFile()` function reads the `profile` file and it reads line by line and store it on the right folder by looking at the first words within the string (e.g. `HOME` or `PATH`);
3. `getDirectory()` function is to read the current working directory.
4. `runsCD()` function is to give the shell the ability to run `cd` command (I didn't seperate this into headers since it's only a few lines function).
5. The other functions are simply just string manipulation function that helps the program to screen through both profile string and user input

##executeProgram.c
1. This file includes the `checkExistance()` function that mainly operates the whole file. After screening through the input string;
2. It will check whether file exist or not using the `cfileexists()` function.
3. If it exist, we launch the program using the `lsh_launch()` program 
4. Else, it gives an error.
5. Other function is simply for string or data structure manipulation purposes.

##modifyHomePath.c
1. This file is pretty straightforward, `dollarHome()` function changes the `HOME` whenever the user type `$HOME=.....`
2. This file is pretty straightforward, `dollarPath()` function changes the `PATH` whenever the user type `$PATH=.....`

##profile
I also purposedly leave a profile file just in case it wont run on other files. I have tested both lines swapped in `LINUX` operating system.

**HOWEVER, in WINDOWS machine occured minor difference when HOME is placed below PATH on profile as somehow WINDOWS reads more trailing zeros than Linux. For line 105 in shell.c:
getFile() In Windows: strncpy(home, homeHolder, strlen(homeHolder)-2);
getFile() In Linux: strncpy(home, homeHolder, strlen(homeHolder)-1);
-> I have decided to use Linux but just in case other machine reads different trailing zeros**
