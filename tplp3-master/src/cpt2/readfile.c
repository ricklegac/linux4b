#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>
char* read_from_file (const char* filename, size_t length){
    char* buffer;
    int fd;
    ssize_t bytes_read;
/* Asignamos memoria al buffer. */
    buffer = (char*) malloc (length);
    if (buffer == NULL)
        return NULL;
/* Abrimos el archivo. */
    fd = open (filename, O_RDONLY);
    if (fd == -1) {
/* No pudimos abrir el archivo, desasignamos memoria antes de regresar. */
        free (buffer);
		printf("g");
        return NULL;
    }
/* Leemos los datos. */
    bytes_read = read (fd, buffer, length);
    if (bytes_read != length) {
/* Si la lectura falla, desalojamos el buffer y volvemos. */
      //  printf("%d %d", bytes_read, length);
        free (buffer);
        close (fd);
        return NULL;
    }
/* Todo salió bien. */
    close (fd);
    return buffer;
}

int main(){
    char s [] = "a seo le gusta mucho lp3";
    printf("%s\n", read_from_file("cpt2/prueba.txt", sizeof(s)));
    return 0;
}
