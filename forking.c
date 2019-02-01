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
  int p[2];

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

    printf("This is the Parent\n");

    wait(NULL);

  }else if (f == 0) { //Child Process
    if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) {
      perror("Error: Process could not be assigned to a CPU\n");
      return 1;
    }

    printf("This is the Child\n");

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
