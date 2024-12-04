/* Cristopher Ahuatl
   Dr Jeffrey
   CS-420-02 Project 04 Step 3: myremove
        Take an file at the command line and delete it. Use unlink and rmdir to deleting operations.
        Ignore cases where file is not a directory or regular file.
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main (int argc, char* argv[]){
        if (argc !=2){
                printf("Usage %s <filename> \n", argv[0]);
                exit(1);
        }

        //filename = file to be deleted
        const char* filename = argv[1];

        /* =====  struct stat essentially is the container for a file's attributes ===== 
                the st_mode field contains the flags that describe the file type
                S_ISREG and S_ISDR check the file type
                SYNTAX: stat(fileName, struct to be filled)
                RETURNS: 0 = success populating stat struct
                        -1 = failure    
         */
        struct stat fileStat;
        if(stat(filename,  &fileStat) != 0){
                perror("Error accessing file");
                exit(1);
        }

        //checking file type. If is regular file -> use unlink. If is directory -> rmdir

        if (S_ISREG(fileStat.st_mode)){
                if (unlink(filename) == 0) {
                        printf("Regular file '%s' deleted successfully\n", filename);
                }
                else{
                        perror("Error deleting regular file\n");
                        exit(1);
                }
        }
        else if (S_ISDIR(fileStat.st_mode)){
                if(rmdir(filename) == 0 ){
                        printf("Directory '%s' deleted successfully \n", filename);
                }
                else{
                        perror("Error deleting directory");
                        exit(1);
                }
        }
        //ignore removal for files that aren't directories or regular files
        else{
                printf("File '%s' is not a directory or regular file. Ignoring removal \n");
        }

        return 0;
