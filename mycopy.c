/*
Cristopher Ahuatl
Dr.Jeffrey
CS420-02 Fall 2024
Project 04 Step 2:
        Use Kernel API calls: read, write, exit, open, close etc.. Do NOT use c-library functions.
        Be sure to change access permission bits on the executable so that that the user (you), members of your
        group, and other users can execute the executable file. Use the chmod command to change permission bits.

        Time the mycopy function with different buffer sizes , each used by read/write kernel calls.
        Command line syntax: $time ./mycopy sourcefile targetfile
        Use the 1000KB file from step1 as the sourcefile to be copied for ALL executions.
        BUFFER SIZES TO USE:
                4096 BYTES
                2048 BYTES
                1024 BYTES
                 512 BYTES
                   1 BYTE

*/


#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char* argv[]){
//hard coded to change to different sizes for all tests
  const size_t BUFFERSIZE = 4096;

  if(argc != 3) {
    exit(EXIT_FAILURE);
  }

  char* sourceFile = argv[1];
  char* targetFile = argv[2];

  int sourceFileDescriptor = open(sourceFile, O_RDONLY);
  // if there was an error opening the source file
  if(sourceFileDescriptor == -1){
    perror("Error opening source file\n");
    exit(1);
  }

  //open() returns a file descriptor. 
  int targetFileDescriptor = open(targetFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

  if(targetFileDescriptor == -1){
    // if you cannot open both files, close what you have open.
    close(sourceFileDescriptor);
    exit(1);
  }

  // create a buffer of whatever the constant size is set to.

  char buffer[BUFFERSIZE];
  size_t bytesRead;

  // while it's still possible to read in bytes
  while((bytesRead = read(sourceFileDescriptor, buffer, BUFFERSIZE)) > 0){
    // write to target file
    size_t bytesWritten = write(targetFileDescriptor, buffer, bytesRead);
    // if bytesWritten != bytesRead, possible errors
    if (bytesWritten != bytesRead){
      close(sourceFileDescriptor);
      close(targetFileDescriptor);
      exit(1);
    }
 }
  //if the value returned by a read operation = -1 -> error 
  if(bytesRead == -1){
    exit(1);
  }

  // close all the files when done.
  close(sourceFileDescriptor);
  close(targetFileDescriptor);

  return 0;
}
