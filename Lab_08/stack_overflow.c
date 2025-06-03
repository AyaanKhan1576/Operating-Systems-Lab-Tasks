#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void causeStackOverflow(int depth) {
    if (depth > 1000000) {
        return;
    }
    causeStackOverflow(depth + 1); 
}

void handleSIGSEGV(int sig) {
    printf("Segmentation fault (stack overflow) detected!\n");
    exit(1); 
}

void sighandler(int sig)
{
	printf("Segmentation fault (stack overflow) detected!\n");
	
	signal(signum, SIG_DFL);
	kill(getpid(), sig);
}

int main() {
    signal(SIGSEGV, handleSIGSEGV); 
    signal(SIGSEGV, sighandler); 
    causeStackOverflow(0);
    //int mat[100000][100000];
    printf("This line will not be printed due to stack overflow.\n");
    return 0;
}

