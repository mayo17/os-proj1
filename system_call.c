//Program to measure length of system calls (read)
//Compile with -lrt flag at end

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sched.h>

int main() {
	//Set the number of times you want to test read length
	int sampleSize = 1000;
	int i;
	double totalTimeNano;
	for(i = 0; i < sampleSize; i++)
	{
		struct timespec start, end;
		
		int openFile = open("rfile.txt", O_RDONLY);
		
		//gettimeofday called immediatly before and
		//immediatly after read sys call is called
		//to measure time.
		clock_gettime(CLOCK_MONOTONIC, &start);

		read(openFile, NULL, 1);
	
		clock_gettime(CLOCK_MONOTONIC, &end);

		close(openFile);
		
		//.tv_usec used to extract the time in microseconds
		int endtime = end.tv_nsec;
		int starttime = start.tv_nsec;
		int ellapsedtime = endtime - starttime;
		//Adding to running total
		totalTimeNano += ellapsedtime;
	}
	double totalTimeMicro = totalTimeNano/1000;
	double totalTimeMilli = totalTimeMicro/1000;
	double averageTimeMilli = totalTimeMilli/sampleSize;
	printf("Total Time in Microseconds: %f\n", totalTimeMicro);
	printf("Total Time in Millseconds: %f\n", totalTimeMilli);
	printf("Average Time in Milliseconds: %f\n", averageTimeMilli);


return 0;
}
