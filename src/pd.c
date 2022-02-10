/*
-- PROCESO D --
CREADO POR SILVESTRE SANCHEZ-BERMEJO SANCHEZ
Este proceso se ejecuta cuando el usuario pulsa CTRL+C
Borra todos los archivos creados anteriormente
*/

#include <stdlib.h>
#include <dirent.h>
#include <stdlib.h>
int main(){
  DIR *dirp;
  dirp = opendir("estudiantes");
  if(dirp != NULL)
    system("rm -r ./estudiantes");
  return EXIT_SUCCESS;
}
