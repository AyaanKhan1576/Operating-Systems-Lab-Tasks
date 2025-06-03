#include <stdio.h>
#include <unistd.h>

#include <signal.h>

int main() {
    char *program_names[] = {
        "stack_overflow",
        "data_overflow",
        "heap_overflow",
        "fork_bomb"
    };
/*
	sigset_t set;
	int ret;
	ret = sigfillset(&set);
	ret = sigprocmask(SIG_BLOCK, &set, NULL);
*/
    int choice;
    printf("Choose a program to run:\n");
    printf("1. Stack Overflow\n");
    printf("2. Data Segment Overflow\n");
    printf("3. Heap Overflow\n");
    printf("4. Fork Bomb\n");
    scanf("%d", &choice);

    if (choice < 1 || choice > 4) {
        printf("Invalid choice.\n");
        return 1;
    }

    char *program = program_names[choice - 1];

    // Safe `exec` usage:
    execl(program, program, NULL);  // Replace with `execlp` or `execv` if needed

    perror("execl failed"); // Handle potential errors
    return 0;
}

