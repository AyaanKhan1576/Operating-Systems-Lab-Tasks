#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main() {
    void handleSIGSEGV(int sig);

    signal(SIGSEGV, handleSIGSEGV); 

    int veryLargeArray[1000000]; 

    veryLargeArray[100000000005] = 42; 

    printf("This line may or may not be printed depending on the overflow behavior.\n");
    return 0;
}

void handleSIGSEGV(int sig) {
    printf("Segmentation fault (data segment overflow) detected!\nProgram will be terminated :)");
    exit(1); // Terminate program gracefully
}

