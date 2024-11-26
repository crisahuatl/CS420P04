/*
Cristopher Ahuatl
Dr. Jeffrey
CS 420 Project 04 Step1: 
    write a program to generate exactly 1000KB (1024000B) text file on the linux genData.c VM system, compile, link, and run.
    Program should take a one arguement command at the command line
    ex: ./genData filename

    Turn in the source code and submit a portion(eg. first 800 bytes of the generated file) and a screenshot of the sample run
*/

#include <sys/types.h>  //Required for file permissions
#include <sys/stat.h>   //Required for file system operations
#include <fcntl.h>      //Provides the open function for file handling
#include <stdio.h>      //standard IO functions like printf and perror and file pointers
#include <errno.h>      //access to error codes for debugging
#include <stdlib.h>     //C standard library
#include <unistd.h>     //System call functions like write and close


void fileGen(char* file);

const int FILE_SIZE = 1024000;      // equivalent to 1000KB or 1,024,000 ASCII characters
const int BUFFER_SIZE = 1024; // data will be pushed to the file in chunks of 1024 characters or 1KB


int main(int argc, char *argv[]){
    /*
    Program expects two arguments (argc=2) where 
    argv[0] = .exe    argv[1] = fileName
    */
       if (argc < 2) {
        printf("Usage %s <filename> \n", argv[0]);
        return 1;
    }
    //take commandLine argument and set is as the file
    char* fileName = argv[1]; 

    fileGen(fileName);

    return 0;
}

void fileGen(char* file){
    //  open a stream to the argv[1] file to be written to
    //  SYNTAX: fopen(fileName, *accessMode) 
    //  r = (read)
    //  w = (write) 
    //  fopen() returns a file pointer if file opened successfully
    
    FILE *fptr;
    fptr = fopen(file, "w");
    if(fptr == NULL){
        perror("File could not be opened, now closing programn\n");
        exit(1);
    }
    printf("File opened successfully\n");

    //initialize a buffer to be pre-filled to be repeatedly written to the file. 
    //This avoids having to refill the buffer after every write operation
    char buffer[BUFFER_SIZE];

    //fill buffer with a repeating sequence of abc
    //using the 'a' as a starting point, other letters in the alphabet can be used by adding integers to generate the ASCII code
    //Ex: 'a' + 1 = 'b'   'b' + 1 = 'c' etc...
    //The modulous operation restricts this process to three characters abc
    for(int i=0; i < BUFFER_SIZE; i++){
        buffer[i] = 'A' + (i % 26);
    }

    //initialize a counter for bytes written
    size_t bytesWritten = 0;

    //loop writes buffer to file 1 chunk at a time. Each write increments bytesWritten. Once file contains 1000KB, process terminates.
    while (bytesWritten < BUFFER_SIZE) {
        //chunk size used to manage possibility of non-clean division of BUFFER_SIZE to FILE_SIZE
        size_t chunkSize = BUFFER_SIZE;
        if (bytesWritten + BUFFER_SIZE > FILE_SIZE){
            chunkSize = FILE_SIZE - bytesWritten;
        }

        size_t result = fwrite(buffer, 1, chunkSize, fptr); //writes one chunk at a time to file. Function returns the total number of successfully written elements

        if (result != chunkSize){
            perror("Error writing to file");
            fclose(fptr);
            exit(1);
        }
        bytesWritten+= result;
    }
    fclose(fptr);
    printf("File written successfully, Total Bytes Written: %lu\n", bytesWritten);

}
