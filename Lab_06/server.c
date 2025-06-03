#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

volatile sig_atomic_t done = 0;

void sig_handler(int signum) {
    if (signum == SIGINT || signum == SIGTSTP || signum == SIGSTOP) {
        return;
    }
    done = 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pipe_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *pipe_name = argv[1];

    if (mkfifo(pipe_name, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, sig_handler);
    signal(SIGTSTP, sig_handler);
    signal(SIGSTOP, sig_handler);

    int pipe_fd = open(pipe_name, O_RDONLY);
    if (pipe_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while (!done && (bytes_read = read(pipe_fd, buffer, BUFFER_SIZE)) > 0) {

        write(STDOUT_FILENO, buffer, bytes_read);

        if (strncmp(buffer, "Done", strlen("Done")) == 0) {
            break;
        }
    }

    close(pipe_fd);

    if (unlink(pipe_name) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}

