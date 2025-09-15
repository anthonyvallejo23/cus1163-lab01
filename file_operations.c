#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "file_operations.h"

int create_and_write_file(const char *filename, const char *content) {
  int fd;
  ssize_t bytes_written;
  // 'fd' acts as the file descriptor while 'bytes_written' stores how many bytes 

  printf("Creating file: %s \n", filename); // Prints a message showing which file is being created
  
  //printf(filename); -- Obsolete code
  //printf("\n"); -- Obsolete code
  
  printf("Content to write: %s \n", content); // Print a message showing what content will be written.
  
  //printf(content); -- Obsolete code
  //printf("\n"); -- Obsolete code

  fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644); // Opens or creates the file for writing using the open() system call.
  if (fd == -1) // If open() fails, prints an error and returns -1
  {
    perror("Error at open");
    return -1;
  }

  printf("File descriptor: %d \n", fd); // Prints the file descriptor value.
  
  //printf("%d", fd); -- Obsolete code
  //printf("\n"); -- Obsolete code

  bytes_written = write(fd, content, strlen(content)); // Writes the content to the file using the write() system call.
  if (bytes_written == -1) // If write() fails, prints an error and returns -1
  {
    perror("Error at write");
    close(fd);
    return -1;
  }

  printf("Successfully wrote %zd bytes to '%s' \n", bytes_written, filename); // Prints a success message with the number of bytes written and filename.
  
  //printf("%zd", bytes_written); -- Obsolete code
  //printf(" bytes to "); -- Obsolete code
  //printf(filename); -- Obsolete code
  //printf("\n"); -- Obsolete code

  int close_success = close(fd); // Closes the file
  if (close_success != 0) // If close() fails, prints an error and returns -1
  {
    perror("Error at close");
    return -1;
  }

  printf("File closed successfully \n"); // Prints if the file closes successfully.
  return 0;
}

int read_file_contents(const char *filename) {
  int fd;
  char buffer[1024];
  ssize_t bytes_read;
  // 'fd' acts as the file descriptor
  // 'buffer' stores file data
  // 'bytes_read' stores how many bytes 

  printf("Reading file: %s \n", filename); // Prints a message showing which file is being read.
  //printf(filename);
  //printf("\n");

  fd = open(filename, O_RDONLY); // Opens the file for reading using the open() system call.
  if (fd == -1) // If open() fails, prints an error and returns -1
  {
    perror("Error at open");
    return -1;
  }

  printf("File descriptor: %d \n", fd); // Prints the file descriptor value.
  
  //printf("%d", fd); -- Obsolete code
  //printf("\n"); -- Obsolete code
  
  printf("\n--- Contents of '%s' ---\n", filename); // Prints a header for the file contents.
  
  //printf(filename); -- Obsolete code
  //printf(" ---\n"); -- Obsolete code

  while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) // Reads the file contents using read() in a loop, until it returns 0.
  {
    buffer[bytes_read] = '\0'; //I think this is a null-terminate?
    printf("%s", buffer); // Prints the contents of the buffer.
  }

  if (bytes_read == -1) // If read() fails, prints an error and returns -1
  {
    perror("Error at read");
    close(fd);
    return -1;
  }

  printf("\n--- End of file ---\n"); // Prints a footer for the end of the file.

  int close_success = close(fd);
  if (close_success != 0) // If close() fails, prints an error and returns -1
  {
    perror("Error at close");
    return -1;
  }

  printf("File closed successfully \n"); // Prints if the file closes successfully.
  return 0;
}
