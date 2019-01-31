//Program to measure the cost of context switch on a single cpu
//Have to complile with -std=c99 
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main() {
	unsigned long mask = 1;
	sched_setaffinity(getpid(), sizeof(mask), &mask);
	int pipe1[2];
	int pipe2[2];
	pid_t f = fork();
	char* msg = "hello\n";
	char buffer[strlen("hello\n")];
for(int i = 0; i < 20; i++)
{
	if(f != 0)
	{
		printf("In p1\n");
		printf("%d\n", i);
		write(pipe1[1], msg, strlen(msg));
		read(pipe2[0], buffer, strlen(msg));
	}
	else
	{
		printf("In p2\n");
		printf("%d\n", i);
		read(pipe1[0], buffer, strlen(msg));
		write(pipe2[1], msg, strlen(msg));
	}
}

return 0;
}
