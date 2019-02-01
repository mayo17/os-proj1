//Program to measure the cost of context switch on a single cpu
//Have to complile with -std=c99

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sched.h>

int main() {
	//unsigned long mask = 1;
	cpu_set_t mask;
	int pA[2];
	int pB[2];
	pid_t f;
	char* msg = "hello\n";

	//To handle errors in creating the pipe to switch between processes.
	// if (pipe(pA) == -1)
	// {
	// 	perror("Pipe A creation unsuccessful\n");
	// 	return 1;
	// }
	// if (pipe(pB) == -1)
	// {
	// 	perror("Pipe B creation unsuccessful\n");
	// 	return 1;
	// }

	//Checks the conditions of the fork to determine if the program can run.
	//If successful, runs either the parent process or the child process else, prints error.
	//for (int i = 0; i < 5; i++) {
		f = fork(); //Initializes and runs the fork();

		//To set up the CPU selection and handle the error if the single CPU could not be set.
		// CPU_ZERO(&mask);
		// CPU_SET(0, &mask);
		//
		// if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
		// 	perror("Error: Process could not be assigned to a CPU\n");
		// 	return 1;
		// }

		//int cpu_id = CPU_ISSET(0, &mask);
		//printf("%s\n", cpu_id);
		switch (fork()) {
			case -1:		//Error Processing
				perror ("Could not run the fork\n");
				return 1;
			case 0:
				printf("This is the Child\n");
			default:
				printf("This is the Parent\n");
		}

		// if (fork() < 0) {
		// 	perror ("Could not run the fork\n");
		// 	return 1;
		// }else if (f > 0) {	//Parent Process
		// 	printf("This is the Parent\n");
		//
		// 	// printf("Parent PID: %d\n", getpid());	//DEBUG GING
		// 	//
		// 	// char* string;
		// 	//
		// 	// //close(pA[0]);
		// 	// printf("In p1: ");
		// 	// printf("%d\n", i);
		// 	//
		// 	// printf("%d", wait(NULL));
		//
		// }else if (f = 0) {	//Child Process
		//
		// 	printf("This is the Child\n");
		//
		// 	// printf("Child PID: ");	//DEBUG GING
		// 	// printf("%d\n", getpid());
		// 	//
		// 	// char* string;
		// 	//
		// 	// //close(pA[1]);
		// 	// printf("In p2: ");
		// 	// printf("%d\n", i);
		// 	//
		// 	// //close(pA[0]);
		// 	// //close(pB[0]);
		// 	//
		// 	// //write(pB[1], msg, strlen(msg));
		// 	// //close(pB[1]);
		// }
	//}

return 0;
}
