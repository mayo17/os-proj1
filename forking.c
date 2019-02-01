#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sched.h>

int main() {
  cpu_set_t mask;
  int pipe1[2];
  int pipe2[2];
  char msg[6] = "hello"; 
  char buffer[100];

  //To set up the CPU selection and handle the error if the single CPU could not be set.
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);

  //To handle errors in creating the pipe to switch between processes.
	if (pipe(pipe1) == -1)
	{
		perror("Pipe A creation unsuccessful\n");
		return 1;
	}
	if (pipe(pipe2) == -1)
	{
		perror("Pipe B creation unsuccessful\n");
		return 1;
	}

for(int i = 0; i < 5; i++) {
  int f = fork();
  if (f < 0) {      //Error Processing
    perror ("Could not run the fork\n");
    return 1;

  }else if (f > 0) {  //Parent Process
    if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
      perror("Error: Process could not be assigned to a CPU\n");
      return 1;
    }

    char string[100];

    printf("In p1\n");
	  printf("Parent PID: %d\n", getpid());
	  //printf("%d\n", i);
	  //write(pipe1[1], msg, strlen(msg));
    //printf("here1\n");
  //  close(pipe1[0]);
    write(pipe1[1], msg, strlen(msg)+1);
    //close(pipe1[1]);

    wait(NULL);

    //close(pipe2[1]);
	  read(pipe2[0], buffer, 100);
    printf("%s no\n", &buffer);
    //close(pipe2[0]);
    //exit(EXIT_SUCCESS);

  }else { //Child Process
    if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
      perror("Error: Process could not be assigned to a CPU\n");
      return 1;
    }

    printf("In p2\n");
	  printf("Parent PID in Child: %d\n", getpid());
	  //printf("%d\n", i);
    //printf("here3\n");
	  //read(pipe1[0], buffer, strlen(msg));
    //close(pipe1[1]);

    char string[100];

    read(pipe1[0], string, 100);
    //close(pipe1[0]);
    //close(pipe2[0]);
    string[5] = i + '0'; //REMOVE, DEBUGGING
	  write(pipe2[1], string, strlen(string)+1);    
    //close(pipe2[1]);   
    exit(0);
  }
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