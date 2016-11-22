/****************************************************************************
 * Copyright (C) 2016 by Anastasia Arvika Christy                           *
 *                                                                          *
 *                                                                          *
 *  this program will try to execute the given input by the user.           *
 *  if it exist it will execute it.                                         *
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

int cfileexists(char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else 
        return 0;
}

char** resizableArray(char **userInput){
  char **newInput;
  int y=0;
  newInput = malloc(10 * sizeof(char*));

  while(userInput[y]!=NULL){
    newInput[y] = userInput[y+1];
    y++;
  }
    newInput[sizeof(newInput)+1] = NULL;
  return newInput;
}

int lsh_launch(char *filePath, char** commandArray){
  /*  This function is used to launch the program within the actual shell
      for example ls -l, ls -a
  */
  pid_t pid, wpid;
  int status;
  char** forkInput = malloc(10 * sizeof(char*));
  int u;
  int i=0;
  forkInput[0]=filePath;

  for(u=0;u<sizeof(commandArray);u++){
    forkInput[u+1]=commandArray[u];
  }

  pid = fork();
  if (pid == 0) {
    if (execvp(filePath, forkInput) == -1) {
      perror("lsh");
    }    
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
      perror("lsh");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

int checkExistance(char **userInput, char **arrayPath){
  char* filePath;
  char arrayPathNew[1000];
  int p=0;

  while(arrayPath[p] !=NULL){
    strcpy(arrayPathNew, arrayPath[p]);
    filePath = arrayPathNew;
    strcat(filePath,"/");
    strcat(filePath,  userInput[0]);

    int exist = cfileexists(filePath);
    if(exist){
        char **newUserInput = resizableArray(userInput);
        lsh_launch(filePath, newUserInput);
        break;
    }else{
      fputs("Command not found\n", stderr);
      break;
    }
    p++;
  }
    
}
