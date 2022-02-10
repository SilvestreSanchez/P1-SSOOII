/*
-- PROCESO B --
CREADO POR SILVESTRE SANCHEZ-BERMEJO SANCHEZ
Este proceso copia en cada directorio creado por el proceso a, el modelo de examen que le corresponda al estudiante
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUF 1024

char * obtenerDNI(char line[MAX_BUF]){
  char *token= malloc(MAX_BUF);
  token=strtok(line," ");
  return token;
}

char obtenerEXAM(char line[MAX_BUF]){
  char *p;
  char a='A';
  char b='B';
  char c='C';
  
  p=strchr(line,a);
  if (p != NULL){
    return a;
  }else{
    p=strchr(line,b);
    if(p != NULL){
      return b;
    }else{
      return c;
    }
  }
}

void copiarExam(char EXAM, char DNI[MAX_BUF]){
  char command[MAX_BUF];
  char pdf[MAX_BUF];
  sprintf(pdf,"./utils/MODELO%c.pdf",EXAM);
  sprintf(command,"cp %s ./estudiantes/%s",pdf,DNI);
  system(command);
}



int main(){
  FILE * fp;
  char archivo[]= "./utils/estudiantes_p1.text";
  char linea[MAX_BUF];
 
  fp=fopen(archivo,"r");
  if (fp==NULL){
    printf("No se ha podido acceder al archivo");
    exit(EXIT_FAILURE);
  }
  
  while(fgets(linea,100,fp) != NULL){
    char EXAM=obtenerEXAM(linea);
    char *DNI=obtenerDNI(linea);
    copiarExam(EXAM,DNI);
  }
  sleep(5);
  return EXIT_SUCCESS;
}
