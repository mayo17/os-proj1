//Program to measure length of system calls (read)

#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
int main() {
	//Set the number of times you want to test read length
	int sampleSize = 1000;
	int i;
	double totalTimeMicro;
	for(i = 0; i < sampleSize; i++)
	{
		struct timeval start, end;
		
		int openFile = open("rfile.txt", O_RDONLY);
		
		//gettimeofday called immediatly before and
		//immediatly after read sys call is called
		//to measure time.
		gettimeofday(&start, NULL);

		read(openFile, NULL, 1);
	
		gettimeofday(&end, NULL);

		close(openFile);
		
		//.tv_usec used to extract the time in microseconds
		int endtime = end.tv_usec;
		int starttime = start.tv_usec;
		int ellapsedtime = endtime - starttime;
		//Adding to running total
		totalTimeMicro += ellapsedtime;
	}
	double totalTimeMilli = totalTimeMicro/1000;
	double averageTimeMilli = totalTimeMilli/sampleSize;
	printf("Total Time in Microseconds: %f\n", totalTimeMicro);
	printf("Total Time in Millseconds: %f\n", totalTimeMilli);
	printf("Average Time in Milliseconds: %f\n", averageTimeMilli);


return 0;
}
