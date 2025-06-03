#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main() 
{
    int sz=20;
    int arr[sz];
    int childpipe[2];
    int parentpipe[2];
    int total_parent = 0;
	int total_child = 0;
    pid_t pid;

    // Creating pipes
    if (pipe(childpipe) == -1 || pipe(parentpipe) == -1) 
	{
        perror("Pipe was not created!");
        exit(0);
    }

    //  array in parent
    printf("Enter %d integers for the array:\n", sz);
    for (int i = 0; i < sz; i++)
	{
        scanf("%d", &arr[i]);
    }

    pid = fork();

    if (pid < 0)
	{
        perror("Forking failed");
        exit(0);
    }

    if (pid == 0) 
	{
        close(childpipe[WRITE_END]);
        close(parentpipe[READ_END]);

        int child_sum = 0;
        for (int i = sz - 10; i < sz; i++)
		{
            child_sum += arr[i];
        }

        write(parentpipe[WRITE_END], &child_sum, sizeof(child_sum));
        close(parentpipe[WRITE_END]);

        exit(1);
    }
	
	else 
	{
        close(childpipe[READ_END]);
        close(parentpipe[WRITE_END]);

        for (int i = 0; i < 10; i++) 
		{
            total_parent += arr[i];
        }

        write(childpipe[WRITE_END], &arr[sz - 10], sizeof(int) * 10);
        close(childpipe[WRITE_END]);

        read(parentpipe[READ_END], &total_child, sizeof(total_child));
        close(parentpipe[READ_END]);

        int total_sum = total_parent + total_child;
        printf("Total Sum: %d\n", total_sum);

        wait(NULL);
    }

    return 0;
}
