#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void display_version_info() {
    printf("CDF Utility v1.0\n");
}

void display_help_info() {
    printf("Usage: cdf [options]\n");
    printf("Options:\n");
    printf("  -v                  Display version information\n");
    printf("  -h                  Show help message\n");
    printf("  -c directoryName    Create directory\n");
    printf("  -f filename         Create empty file\n");
    printf("  -t text             Create file with text\n");
}

void create_directory(char *dir_name) {
    if (mkdir(dir_name, 0777) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }
}

void create_file(char *file_name, char *text) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    if (text != NULL) {
        fprintf(file, "%s", text);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Error: No arguments provided. Use 'cdf -h' for help.\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-v") == 0) {
        display_version_info();
    } else if (strcmp(argv[1], "-h") == 0) {
        display_help_info();
    } else if (strcmp(argv[1], "-c") == 0) {
        if (argc == 3) {
            create_directory(argv[2]);
        } else if (argc > 3) {
            for (int i = 2; i < argc; i++) {
                create_directory(argv[i]);
            }
        } else {
            printf("Error: Missing directory name(s).\n");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[1], "-f") == 0) {
        if (argc == 3) {
            create_file(argv[2], NULL);
        } else if (argc == 5 && strcmp(argv[3], "-t") == 0) {
            create_file(argv[2], argv[4]);
        } else {
            printf("Error: Invalid arguments.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Error: Unknown option '%s'. Use 'cdf -h' for help.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}
