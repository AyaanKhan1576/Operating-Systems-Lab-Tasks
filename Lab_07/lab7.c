#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;

    if (argc != 3) {
        printf("Error, enter commands in appropriate format\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) { 
        printf("error creating pipe");
        exit(EXIT_FAILURE);
    }
    
    pid = fork();
    
    if(pid == -1) {
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0) { 
        printf("child pid=%d\n", getpid());
        close(pipefd[0]); 
        
        dup2(pipefd[1], STDOUT_FILENO); // Redirect standard output to pipe write end
        close(pipefd[1]); // Close original pipe write descriptor
        

        char *token = strtok(argv[1], " ");
        char *args[10];
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        
       // printf("%d", i);
        execvp(args[0], args); // Execute command with its arguments
        printf("this should not be printed if exec is successful");
        
    } else {
        // Parent process
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipefd[0]); // Close original pipe read end
        
        char *token = strtok(argv[2], " ");
        char *args[10];
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        //printf("%d", i);
        execvp(args[0], args); // Execute command with its arguments
        printf("this should not be printed if exec is successful");
    }
    
    return 0;
}


