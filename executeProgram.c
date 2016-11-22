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
    newInput[y] = userInput[y+1];//start from parameter
    y++;
  }
    newInput[sizeof(newInput)+1] = NULL;
  return newInput;
}


int checkExistance(char **userInput, char **arrayPath){
  /*
  this program will try to execute the given input by the user.
  if it exist it will execute it.
  */
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