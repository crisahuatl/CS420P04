/* Cristopher Ahuatl
 * Dr Jeffrey
 * CS 420-02 Fall 2024
 * Project 04 Step 4
 *      Write a two argument mymove command semantically similar to the rename command on windows.
 * */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[]){
        if(argc != 3){
                fprintf(stderr, "Usage:  %s <oldfilename> <newfilename>\n", argv[0]);
                exit(1);
        }
        const char* oldFileName = argv[1];
        const char* newFileName = argv[2];

        /* ===== rename system call  ===== */
        /*      SYNTAX: rename(const char *oldPath, const char* newPath)
                RETURN: 0 = success
                       -1 = failure 
        */

        if(rename(oldFileName, newFileName) == 0){
                printf("Successfully renamed/moved file '%s' to '%s'\n", oldFileName, newFileName);
        }
        else{
                perror("Error in file removal");
                exit(1);
        }

        return 0;
}
