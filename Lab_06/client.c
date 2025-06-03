#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#define BUFFER_SIZE 1024

void sig_handler(int signum) {
    if (signum == SIGINT || signum == SIGTSTP || signum == SIGSTOP) {
        return;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pipe_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *pipe_name = argv[1];

    signal(SIGINT, sig_handler);
    signal(SIGTSTP, sig_handler);
    signal(SIGSTOP, sig_handler);

    int pipe_fd = open(pipe_name, O_WRONLY);
    if (pipe_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
   

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    printf("Enter text to send (type 'Done' to finish):\n");

    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (write(pipe_fd, buffer, strlen(buffer)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        if (strcmp(buffer, "Done") == 0) {
            break;
        }
    }

    close(pipe_fd);

    return 0;
}

