/*
----- MANAGER -----
CREADO POR: SILVESTRE SANCHEZ-BERMEJO SANCHEZ
EJECUTA LOS PROCESOS A, B, C Y D
CREA EL LOG
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>

#define LEER 0
#define ESCRIBIR 1
void crearFailLOG();


void signal_handler(int sig){
  printf("-- CTRL+C DETECTADO, CERRANDO PROCESOS Y CREANDO LOG --\n");
  pid_t pidD;
  /* FINALIZAR PROCESOS HIJOS Y DEMON*/
  kill(0,SIGQUIT);
  system("killall demon");
  /* CREACION DEL PROCESO D*/
  pidD=fork();
  switch(pidD){
  case -1:
    perror("Error al crear el proceso D\n");
    break;
  case 0:
    execl("./exec/pd",NULL);
    break;
  default:
    waitpid(pidD,0,0);
    crearFailLOG();
    exit(0);
    break;
  }
}

void crearFailLOG(){
  
  FILE *ft;
  ft=fopen("./log.txt","w");
  fputs("------ LOG --------\n",ft);
  fputs("PROGRAMA ABORTADO CON CTRL+C\n",ft);
  fputs("Todos los ficheros asociados han sido eliminados\n",ft);
  fputs("El proceso demonio ha sido eliminado\n",ft);
  fputs("Los procesos PB y PC han sido eliminados\n",ft);
 
  
}

void crearLOG(char buf[1024], bool A, bool B, bool C){
  
  FILE *ft;
  ft=fopen("./log.txt","w");
  fputs("------ LOG -------\n",ft);
  if(A){
    fputs("Creacion de directorios finalizada\n",ft);
  }else{
    fputs("Creacion de directorios ERRONEA\n",ft);
  }
  if(B){
    fputs("Copia de modelos de examen finalizada\n",ft);
  }else{
    fputs("Copia de modelos de examenes ERRONEA\n",ft);
  }
  if(C){
    fputs("Creacion de archivos con nota necesaria para alcanzar la nota de corte finalizada\n",ft);
    fputs(buf,ft);
  }else{
    fputs("Creacion de archivos con nota necesaria, y calculo de media ERRONEOS\n",ft);
  }
  
  
}

int main(){
  signal(SIGQUIT,SIG_IGN);
  signal(SIGINT, signal_handler);
  pid_t pidA,pidB,pidC;
  int tuberia[2];
  char pipeBuffer[256];

  pipe(tuberia);
  bool AFinished = true;
  bool BFinished = true;
  bool CFinished = true;
  
  /* CREACION DEL PROCESO A*/
  
  pidA=fork();
  switch(pidA){
  case -1:
    perror("Error al crear el proceso PA\n");
    AFinished = false;
    break;
  case 0:
    execl("./exec/pa",NULL);
    break;
  default:
    waitpid(pidA,0,0);
    /* PROCESO A FINALIZA*/
    /* CREACION DEL PROCESO B*/
    pidB=fork();
    
    switch(pidB){
    case -1:
      perror("Error al crear el proceso PB\n");
      BFinished = false;
      break;
    case 0:
      execl("./exec/pb",NULL);
      break;
    default:
      /*CREACION DEL PROCESO C*/
      
      pidC=fork();
      switch(pidC){
      case -1:
	perror("Error al crear el proceso PC\n");
	CFinished = false;
	break;
      case 0:
	dup2(tuberia[ESCRIBIR], STDOUT_FILENO);
	execl("./exec/pc",NULL);
	break;
      default:
	read(tuberia[LEER],pipeBuffer,sizeof(pipeBuffer));
	waitpid(pidB,0,0);
	waitpid(pidC,0,0);
	/* PROCESOS B Y C FINALIZAN*/
	crearLOG(pipeBuffer,AFinished,BFinished,CFinished);
	printf("-- FINALIZACION CORRECTA COMPLETADA. LOG CREADO --\n");
	printf("-- EL PROCESO DEMON SIGUE CORRIENDO EN SEGUNDO PLANO --\n");
	printf("-- PARA CERRARLO EJECUTE 'killall demon' --\n");
	break;
      }
    }
  }
  return EXIT_SUCCESS;
}
