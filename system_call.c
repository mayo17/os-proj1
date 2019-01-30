//Program to measure length of system calls

#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
int main() {

	int sampleSize = 1000;
	int i;
	double totalTimeMicro;
	for(i = 0; i < sampleSize; i++)
	{
		struct timeval start, end;

		gettimeofday(&start, NULL);

		int openFile = open("rfile.txt", O_RDONLY);
		read(openFile, NULL, 1);
		close(openFile);
	
		gettimeofday(&end, NULL);
	
		int endtime = end.tv_usec;
		int starttime = start.tv_usec;
		int ellapsedtime = endtime - starttime;
		totalTimeMicro += ellapsedtime;
	}
	double totalTimeMilli = totalTimeMicro/1000;
	double averageTimeMilli = totalTimeMilli/sampleSize;
	printf("Total Time in Microseconds: %f\n", totalTimeMicro);
	printf("Total Time in Millseconds: %f\n", totalTimeMilli);
	printf("Average Time in Milliseconds: %f\n", averageTimeMilli);


return 0;
}
