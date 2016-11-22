/****************************************************************************
 * Copyright (C) 2016 by Anastasia Arvika Christy                           *
 *                                                                          *
 *                                                                          *
 *  These functions adds the shell the capability to handle assignment to	*
 *  $HOME and $PATH from the command line (e.g., $HOME=/home/os2) and to 	*
 *  act upon These cd command by changing the working directory as specified*
 *  (or to the HOME directory by default).                                  *
 *                                                                          *
 ****************************************************************************/

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

int dollarHome(char* dollarInput, char* home){
  if(!opendir(dollarInput+6)){
      fputs("No such file or directory\n", stderr);
  }else{
    strcpy(home, dollarInput+6);
    setenv("HOME", home, 1);
  }
}

int dollarPath(char* dollarInputPath, char* path){
  if(!opendir(dollarInputPath+6)){
      fputs("No such file or directory\n", stderr);
  }else{
    strcpy(path, dollarInputPath+6);
  }
}