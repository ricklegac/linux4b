#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
/* A handle for a temporary file created with write_temp_file.  In
   this implementation, it's just a file descriptor.  */
typedef int temp_file_handle;
temp_file_handle write_temp_file (char* buffer, size_t length);
/* Writes LENGTH bytes from BUFFER into a temporary file.  The
   temporary file is immediately unlinked.  Returns a handle to the
   temporary file.  */
int main(){
   char nombrebuffer[32];
   char buffer[] = "seo puto";
   int filedes = -1,count=0;
   // memset the buffers to 0
  /* memset(nameBuff,0,sizeof(nameBuff));
   memset(buffer,0,sizeof(buffer));*/
   //strncpy(nombrebuffer,"/tmp/myTmpFile-XXXXXX",21);
   size_t buffer_size = strlen(buffer);
   write_temp_file(buffer,buffer_size);
   return 0;
   
}

temp_file_handle write_temp_file (char* buffer, size_t length) {
    /* Create the filename and file.  The XXXXXX will be replaced with
       characters that make the filename unique.  */
    char temp_filename[] = "/tmp/temp_file.XXXXXX";
    /*function generates a unique temporary filename from
       template, creates and opens the file, and returns an open file
       descriptor for the file.*/
    int fd = mkstemp (temp_filename);
    // Call unlink so that whenever the file is closed or the program exits
    // the temporary file is deleted
    /* Unlink the file immediately, so that it will be removed when the
       file descriptor is closed.  */
    unlink (temp_filename);
    /* Write the number of bytes to the file first.  */
    write (fd, &length, sizeof (length));
    /* Now write the data itself.  */
    write (fd, buffer, length);
    printf("\n Temporary file [%s] created\n", temp_filename);
    printf("\n Data written to temporary file is [%s]\n",buffer);
    /* Use the file descriptor as the handle for the temporary file.  */ 
    printf("%d",fd);
    return fd;
    /*
   On success, these functions return the file descriptor of the
   temporary file.  On error, -1 is returned, and errno is set
   appropriately.
    */
}

/* Reads the contents of a temporary file TEMP_FILE created with
   write_temp_file.  The return value is a newly-allocated buffer of
   those contents, which the caller must deallocate with free.
   *LENGTH is set to the size of the contents, in bytes.  The
   temporary file is removed.  */

char* read_temp_file (temp_file_handle temp_file, size_t* length) {
    char* buffer;
    /* The TEMP_FILE handle is a file descriptor to the temporary file.  */
    int fd = temp_file;
    /* Rewind to the beginning of the file.  */
    lseek (fd, 0, SEEK_SET);
    /* Read the size of the data in the temporary file.  */
    read (fd, length, sizeof (*length));
    /* Allocate a buffer and read the data.  */
    buffer = (char*) malloc (*length);
    read (fd, buffer, *length);
    /* Close the file descriptor, which will cause the temporary file to
       go away.  */
    close (fd);
    return buffer;
}