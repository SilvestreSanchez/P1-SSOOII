/*
-- PROCESO C --
CREADO POR SILVESTRE SANCHEZ-BERMEJO SANCHEZ
Este proceso crea un archivo txt en el directorio de cada estudiante, el cual contiene la nota que debe sacar en el siguiente examen para aprobar
Calcula la nota media de todos los alumnos en el primer examen y se la envia al manager por una tuberia(redireccionada con la salida estandar)
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_BUF 1024
#define LEER 0
#define ESCRIBIR 1

char * obtenerDNI(char line[MAX_BUF]){
  char *token= malloc(MAX_BUF);
  token=strtok(line," ");
  return token;
}


int obtenerNota(char line[MAX_BUF]){
  char nota[3];
  int len= strlen(line);
  strcpy(nota,&line[len-3]);
  int n= atoi(nota);
  return n;
}

void crearFichero(char DNI[MAX_BUF],int nota){
  FILE *ft;
  char ruta[MAX_BUF];
  char cadena[MAX_BUF];
  sprintf(ruta,"./estudiantes/%s/nota.txt", DNI);
  sprintf(cadena, "La nota que debes obtener en este nuevo examen para superar la prueba es: %d", 10-nota);
  
  ft=fopen(ruta,"w");
  if(ft==NULL)
    printf("No se ha podido crear el archivo nota.txt\n");
  fputs(cadena,ft);
  
}

int main(){
 
  
  FILE * fp;
  char archivo[]= "./utils/estudiantes_p1.text";
  char linea[MAX_BUF];
  int nota_acumulada=0;
  int n_alumnos=0;

  
  fp=fopen(archivo,"r");
  if (fp==NULL){
    printf("No se ha podido acceder al archivo\n");
    exit(EXIT_FAILURE);
  }
  
  while(fgets(linea,100,fp) != NULL){
    int nota=obtenerNota(linea);
    char *DNI=obtenerDNI(linea);
    crearFichero(DNI,nota);
    nota_acumulada += nota;
    n_alumnos++;
  }
  int media= nota_acumulada/n_alumnos;
  printf("La media es: %d\n",media);
  sleep(5);
  return EXIT_SUCCESS;
}
