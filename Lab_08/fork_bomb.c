#include<stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <signal.h>


int main()
{
    while(1)
    {
	fork();
    }
    
return 0;
}
