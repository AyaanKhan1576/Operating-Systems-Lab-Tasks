#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void handleSIGSEGV(int sig);

int main() {
    signal(SIGSEGV, handleSIGSEGV);  // Install signal handler

	char *buffer;
	
    buffer = (char *)malloc(10 * sizeof(char));
    if (buffer = NULL)
    {
		printf("Memory Allocation failure");
		return 1;
	}
	
	strcpy(buffer, "hello");
	strcpy(buffer, "We are gonna destroy the buffer by exceeding its holding capacity");
	printf("Buffer:%s\n", buffer);
	
	
    //printf("This line may or may not be printed depending on the overflow behavior.\n");
    return 0;
}

void handleSIGSEGV(int sig) {
    printf("Segmentation fault (heap overflow) detected!\n");
    exit(1); // Terminate program gracefully
}



