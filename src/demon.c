/*
-- PROCESO DEMON --
CREADO POR SILVESTRE SANCHEZ-BERMEJO SANCHEZ
Este proceso se ejecuta en segundo plano al ejecutar el manager
Crea una copia de seguridad del diretorio estudiantes
Con el formato fecha--estudiantes--nº de copia
*/

#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF 256

char * getFecha(){
  char *fecha= malloc(20);
  
  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);
  strftime(fecha,128,"%d%m%y",tlocal);
  
  return fecha;
}

void backUp(char dname[MAX_BUF],char com[MAX_BUF]){
  DIR *dirp;
  char f_command[MAX_BUF];
  dirp= opendir("estudiantes");
  if(dirp != NULL){
    sprintf(f_command,"%s %s",com,dname);
    system(f_command);
  }
  
}

int main(){
  char command[MAX_BUF]="cp -r estudiantes";
  char *date=getFecha();
  int i=0;
  
  while(1){
    char dirName[MAX_BUF];
    sprintf(dirName,"%s--%s--%d","estudiantes",date,i);
    backUp(dirName,command);
    i++;
    sleep(60);
  }
}
