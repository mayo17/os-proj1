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

  cpu_set_t mask;
  int pipe1[2];
  int pipe2[2];
  char* msg = "hello\n";
  char buffer[strlen("hello\n")];

  //To set up the CPU selection and handle the error if the single CPU could not be set.
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);

  int f = fork();

  if (f == -1) {      //Error Processing
    perror ("Could not run the fork\n");
    return 1;

  }else if (f > 0) {  //Parent Process
    if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
      perror("Error: Process could not be assigned to a CPU\n");
      return 1;
    }

    printf("In p1\n");
	printf("Parent PID: %d\n", getpid());
	//printf("%d\n", i);
	wait(NULL);
	write(pipe1[1], msg, strlen(msg));
	read(pipe2[0], buffer, strlen(msg));

  }else if (f == 0) { //Child Process
    if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
      perror("Error: Process could not be assigned to a CPU\n");
      return 1;
    }

    printf("In p2\n");
	printf("Parent PID in Child: %d\n", getpid());
	//printf("%d\n", i);
	read(pipe1[0], buffer, strlen(msg));
	write(pipe2[1], msg, strlen(msg));

    exit(EXIT_SUCCESS);
  }

  // switch (fork()) {
  //   case -1:		//Error Processing
  //     perror ("Could not run the fork\n");
  //     return 1;
  //
  //   case 0:     //Child Process
  //
  //     if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
  //       perror("Error: Process could not be assigned to a CPU\n");
  //       return 1;
  //     }
  //
  //     printf("This is the Child\n");
  //     exit(EXIT_SUCCESS);
  //
  //   default:    //Parent Process
  //
  //     if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
  //       perror("Error: Process could not be assigned to a CPU\n");
  //       return 1;
  //     }
  //
  //     printf("This is the Parent\n");
  //
  //     wait(NULL);
  //
  //
  //     //exit(EXIT_SUCCESS);
  // }

  return 0;

}