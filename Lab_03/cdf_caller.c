#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void display_menu() {
    printf("CDF Tool Menu:\n");
    printf("1. Press 1 for version\n");
    printf("2. Press 2 for help\n");
    printf("3. Press 3 to create directory (directories)\n");
    printf("4. Press 4 to create an empty file\n");
    printf("5. Press 5 to create a file with text\n");
}

int main() {
    int choice;
    display_menu();
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            execl("./cdf", "./cdf", "-v", NULL);
            break;
        case 2:
            execl("./cdf", "./cdf", "-h", NULL);
            break;
        case 3:
            execl("./cdf", "./cdf", "-c", "directoryName", NULL);
            break;
        case 4:
            execl("./cdf", "./cdf", "-f", "filename", NULL);
            break;
        case 5:
            execl("./cdf", "./cdf", "-f", "filename", "-t", "hello world", NULL);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
