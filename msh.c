#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main (int argc, char* argv[]){
        if (argc < 2){
                fprintf(stderr, "Usage: '%s' <command> [args...]\n", argv[0]);
                exit(1);
        }
        //spawning a child process
        pid_t pid = fork();
        if (pid < 0){
                perror("Fork failed");
                exit(-1);
        }
        //executions for the child process
        else if (pid == 0){
                /*      
                execl() replaces the currently running process with another while retaining the 
                same PID 

                SYNTAX: execl(const* char Path, const char* arguement0, ..., NULL )                                            Path = path to file/program we want to run
                        Any number of arguments can then follow.
                        NULL = sentinel value to represent end of arguments
                RETURN: 
                Success = No return as current process is replaced. Lines after execl() aren't executed
                Failure = -1 
                */

                //Case for unary operations like myremove
                if(argc == 3) {
                        printf("Executing %s in child process...\n", argv[1]);
                        execl(argv[1], argv[1], argv[2], NULL);
                }
                //case for operations with two arguments
                else if(argc == 4) {
                        printf("Executing %s in child process...\n", argv[1]);
                        execl(argv[1], argv[1], argv[2], argv[3], NULL);
                }
                else{
                        perror("command is invalid.\n");
                        exit(-1);
                }

        }// end fork 

        //in parent process
        else{
                printf("Parent waiting for child execution...\n");
                wait((int*)0);
                printf("Child process terminated. Successful execution\n");
        }
        return 0;

}
