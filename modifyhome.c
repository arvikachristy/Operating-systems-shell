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