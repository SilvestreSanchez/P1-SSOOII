/*
-- PROCESO A --
CREADO POR SILVESTRE SANCHEZ-BERMEJO SANCHEZ

Este proceso crea un directorio para cada DNI especificado en el archivo txt

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define MAX_BUF 1024

char * obtenerDNI(char line[MAX_BUF]){
  char *token= malloc(20);
  token=strtok(line," ");
  return token;
}

void crearDIR(char com[MAX_BUF],char DNI[MAX_BUF]){
  char f_command[MAX_BUF];
  sprintf(f_command,"%s/%s",com,DNI);
  system(f_command);
}


int main(){
  
  FILE * fp;
  char archivo[]= "./utils/estudiantes_p1.text";
  char linea[MAX_BUF];
  int i=1;
  fp=fopen(archivo,"r");
  if (fp==NULL){
    printf("No se ha podido acceder al archivo");
    exit(EXIT_FAILURE);
  }
  
  while(fgets(linea,100,fp) != NULL){
    char command[]="mkdir ./estudiantes";
    char *DNI=obtenerDNI(linea);
    if(i==1)
      system(command);
    crearDIR(command,DNI);
    i++;
  }

  return EXIT_SUCCESS;
}
