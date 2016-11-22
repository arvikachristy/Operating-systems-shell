/****************************************************************************
 * Copyright (C) 2016 by Anastasia Arvika Christy                           *
 *                                                                          *
 *                                                                          *
 *   This file is part of the Operating System coursework                   *
 *   that is designed for all of the computer science year 3 in UCL         *
 *   This file is the main file that should be run first                    *
 *   by the makefile                                                        *
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
#include "modifyHomePath.h"
#include "executeProgram.h"
#define DELIMINATOR " \t\r\n\a"

char *home;
char *path;
char **arrayPath;
char *arrayInput[256];
char *homeHolder;

char *getDirectory(){
  /*
    This function gives the current working directory
  */
   static char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
       return cwd;
    }
   else{
       perror("getcwd() error");
    }
   return 0;
}

bool stringStart(const char *a,const char *b){
  /*
    This function will define whether string a starts with string b
  */
  if(strncmp(a, b, strlen(b)) == 0){
	return 1;
  }
  return 0;
}
int colonSplitter(char* buf, char* x){
  /*
    This function is specifically designed for the PATH function.
    The function splits the string by the symbol that's passed by the parameter
    and store it on arrayPath
  */
    int i = 0;
    char *p = strtok (buf, x);
    arrayPath = malloc(10 * sizeof(char*));
    while (p != NULL)
    {
        arrayPath[i++] = p;
        p = strtok (NULL, x);
    }

    return 0;    
}

int spaceSplitter(char* buf){
  /*
    This function detects if the user input a parameter and store it in arrayInput as array of strings
    e.g.: ls -a, ls -l
  */
  char **result = malloc(10*sizeof(char*));
    int i = 0;
    char *saveptr;
    char *p = strtok(buf, DELIMINATOR);

    while (p != NULL)
    {
      arrayInput[i]= malloc(sizeof(p)*sizeof(char));
        strcpy(arrayInput[i],p);
        i++;
        p = strtok(NULL, DELIMINATOR);
    }
    return 0;    
}

int getFile(){
  /*  This function opens the file profile and read its input line by line
      If the line begins with HOME, it will store the Home to variable "home"
      If the line begins with PATH, it will store the Home to variable "path"
  */
    FILE* file = fopen("profile", "r");
    char line[256];
    char substring[256];
    char homeSubstring[256];

    while (fgets(line, sizeof(line), file)) {
      if(stringStart(line, "HOME")){
        strncpy(homeHolder, line+5, strlen(line)-5);
        if(homeHolder[strlen(homeHolder)-1]=='\n'){
          strncpy(home, homeHolder, strlen(homeHolder)-1);
        }
        else{
          strncpy(home, homeHolder, strlen(homeHolder));
        }        
      }else if(stringStart(line, "PATH")){
        strncpy(substring, line+5, sizeof(line));
        strcpy(path, substring);
        colonSplitter(path, ":");
      }
    }
    if (ferror(file)) {
      fputs("No such file or directory\n", stderr);
    }
    fclose(file);

    return 0;
}

int runsCD(){
  if(arrayInput[1]!=NULL){
    if(!opendir(arrayInput[1])){
      fputs("No such file or directory\n", stderr);
    }
    else {
      chdir(arrayInput[1]);
    }
    arrayInput[1]=NULL;
  }  
  else {
    chdir(home);
  }
  return 0;
}

int main() {
    home  = malloc(256);
    homeHolder = malloc(256);
    path  = malloc(256);
    getFile();

    while(1){
      char data[200];
      printf("%s> ", getDirectory());
      fgets(data, 300, stdin);

      spaceSplitter(data);

      if(strcmp(arrayInput[0],"cd")==0){
        runsCD();
      }else if(strncmp(arrayInput[0],"$HOME=",6)==0){
        dollarHome(arrayInput[0], home);
      }else if(strncmp(arrayInput[0],"$PATH=",6)==0){
        dollarPath(arrayInput[0], path);
      }
      else{
        checkExistance(arrayInput, arrayPath);
        if(arrayInput[1]!=NULL){
          arrayInput[1]=NULL;
        }
      }
    }
    free(home);
    free(path);
    free(homeHolder);
}
	
