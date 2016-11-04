#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#define MAXINT 1024

char *home;
char *path;
char **arrayPath;
char *arrayInput[256];

char *getDirectory(){
   static char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       return cwd;
   else
       perror("getcwd() error");
   return 0;
}

bool stringStart(const char *a,const char *b){
  if(strncmp(a, b, strlen(b)) == 0){
	return 1;
  }
  return 0;
}
int colonSplitter(char* buf, char* x){
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
    int i = 0;
    char *p = strtok (buf, " ");

    while (p != NULL)
    {
      arrayInput[i]= malloc(sizeof(p)*sizeof(char));
        strcpy(arrayInput[i],p);
        
        i++;
        p = strtok (NULL, " ");
    }
    // printf("final i=%d\n\n", i);
    arrayInput[i-1][strlen(arrayInput[i-1])-1] = '\0';
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

int checkExistance(char **userInput)
{
  char* filePath;
  char arrayPathNew[1000];
  int p=0;

  while(arrayPath[p] !=NULL){
    strcpy(arrayPathNew, arrayPath[p]);
    filePath = arrayPathNew;
//    strcat(filePath, "/"); //TODO REPLACE STATIC LS
    strcat(filePath,"/");
    strcat(filePath,  userInput[0]);

    int exist = cfileexists(filePath);
    if(exist){
        //printf("File %s exist \n",filePath);
        //printf("%s\n", resizableArray(userInput)[0]);
        char **newUserInput = resizableArray(userInput);
        lsh_launch(filePath, newUserInput);
        break;
    }else{
        printf("File %s does not exist \n",filePath);
    }
    p++;
  }
    
}

int cfileexists(char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else 
        return 0;
}

int lsh_launch(char *filePath, char** commandArray){
  //TODO MAKE A CONDITION IF commandArray IS NULL
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
    // Child process
    // if (execvp(filePath, commandArray) == -1) { when no arg
    //   perror("lsh");
    // }
    if (execvp(filePath, forkInput) == -1) {
      perror("lsh");
    }    
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("lsh");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}


int getFile(){
//reading the file from profile   
    FILE* file = fopen("profile", "r");
    char line[256];
    char substring[256];

    while (fgets(line, sizeof(line), file)) {
      if(stringStart(line, "HOME")){
        strcpy(home, line);
      }else if(stringStart(line, "PATH")){
        strncpy(substring, line+5, sizeof(line));
        strcpy(path, substring);
        colonSplitter(path, ":");
      }
    }
    if (ferror(file)) {
  /* deal with error */
    }

    fclose(file);

    return 0;
}

int main() {
    home  = malloc(256);
    path  = malloc(256);
    getFile();

    while(1){
      char data[200];
      printf("%s> ", getDirectory());
      fgets(data, 300, stdin);

      spaceSplitter(data);//split the input's white space and add it to arrayInpu
      checkExistance(arrayInput);
    }

    free(home);
    free(path);
}
	
