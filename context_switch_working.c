#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sched.h>

int main() 
{
  cpu_set_t mask;
  int pipeMain[2];
  int pipeTime[2];
  double startTime = 0;
  double Ellapsed = 0;
  double totalEllapsed = 0;
  int sampleSize = 5;

  //Message to be sent through the pipe
  char msg[] = "Hello"; 
  char buffer[strlen(msg)+1];
  double timeBuffer[100];

  //To set up the CPU selection and handle the error if the single CPU could not be set.
  //Force to a single CPU to force context switch between processes
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);

  //To handle errors in creating the pipe to switch between processes and create the pipe.
	if (pipe(pipeMain) == -1)
	{
		perror("Pipe error\n");
		return 1;
	}
  if (pipe(pipeTime) == -1)
	{
		perror("Pipe error\n");
		return 1;
	}

  //Fork loop to run context switch i times
  for(int i = 0; i < sampleSize; i++) 
  {
    //Struct for timing item
    struct timespec start, end;

    //Fork creation. Done in loop or else each loop would be using the same fork.
    int f = fork();

    //Error Processing
    if (f < 0) 
    {
      perror ("Fork error\n");
      return 1;

    }
    //Parent Process
    else if (f > 0) 
    {
      //Makes sure process is on single same CPU as child process. Repeated in child.
      if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) 
      {
        perror("Error: Process could not be assigned to a CPU\n");
        return 1;
      }

      printf("In Parent: %d\n", getpid());

      //Wait for child to write something to the pipe. Force context switch. Start timer since this is here siwtch will happen
      clock_gettime(CLOCK_MONOTONIC, &start);
      startTime = start.tv_nsec;
      
      //Need to pipe the start time to the child process so that they can use it to get ellapsed time
      write(pipeTime[1], &startTime, sizeof(startTime));
      wait(NULL);

      //Reads in ellapsed time from the child and adds it to the total
      read(pipeMain[0], &Ellapsed, sizeof(Ellapsed));
      printf("Switch time: %f\n", Ellapsed);
      totalEllapsed += Ellapsed;
      
      //Exits parent and prints results on last iteration
      if(i == sampleSize - 1)
      {
        printf("Total Ellapsed Nano: %f\n", totalEllapsed);
        double totalTimeMilli = totalEllapsed/1000000;
        printf("Total Ellapsed Milli: %f\n", totalTimeMilli);
        double avgTimeMilli = totalTimeMilli/sampleSize;
        printf("Average Time Milii: %f\n", avgTimeMilli);
        exit(0);
      }

    }
    //Child Process
    else 
    {
      if ((sched_setaffinity(getpid(), sizeof(mask), &mask)) == -1) 
      {
        perror("Error: Process could not be assigned to a CPU\n");
        return 1;
      }

      //Ends the timer as soon as context is switched from parent to child
      clock_gettime(CLOCK_MONOTONIC, &end);

      //Reads the start time from the parent
      read(pipeTime[0], &startTime, sizeof(startTime));
      double endTime = end.tv_nsec;
      Ellapsed = endTime - startTime;
      printf("In Child: %d\n", getpid());

      //Pipes the Ellapsed time back to the parent process then exits the child process
      write(pipeMain[1], &Ellapsed, sizeof(Ellapsed));
      exit(0);
    }
  }

  return 0;

}