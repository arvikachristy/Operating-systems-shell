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
    while (p != NULL)
    {
        arrayPath[i++] = p;
        p = strtok (NULL, x);
    }

    for (i = 0; i < 3; ++i) 
        printf("%s\n", arrayPath[i]);
    //strcpy(arrayPath, array);

    return 0;    
}

int spaceSplitter(char* buf){
    int i = 0;
    char *p = strtok (buf, " ");

    while (p != NULL)
    {
        arrayInput[i++] = p;
        p = strtok (NULL, " ");
    }
    return 0;    
}

int openDirectory(char *argc)
{
  const char* folderr;
  char arrayPathNew[256];
  int p=0;
  while(arrayPath[p] !=NULL){

    strcpy(arrayPathNew, arrayPath[p]);
    folderr = arrayPathNew;
    struct stat sb;

    if (stat(folderr, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    p++;
  }
    
}



int getFile(){
//reading the file from profile   
    FILE* file = fopen("profile", "r");
    char line[256];
    char substring[256];

    while (fgets(line, sizeof(line), file)) {
	if(stringStart(line, "HOME")){
	  strcpy(home, line);
          //printf("%s", home); //GET RID DEBUGGING
	}else if(stringStart(line, "PATH")){
	  strncpy(substring, line+5, sizeof(line));
	  strcpy(path, substring);
          printf("%s", colonSplitter(path, ":")); //GET RID  DEBUGGING
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
	spaceSplitter(data);//split the input's white space

	if(openDirectory(arrayInput[0])){
          printf("%s\n", arrayInput[0]);
	}
    }

    free(home);
    free(path);
}
	
