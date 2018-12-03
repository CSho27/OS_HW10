//Christopher Shorter
//cws68
//HW10 problem 2


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>


struct interval{
	int id;
	double begin;
	double end;
};

struct interval global_range;
double p_mins[10000];


// Compute Shubert value for x1,x2 combination
double shubert(double x1, double x2) {
	double sum1 = 0; 
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((double)(i + 1) * x1 + i);
		sum2 += i * cos(((double)i + 1) * x2 + i);
	}
	return sum1 * sum2;
}

void* pShubertRun (void *param) {
	double x1, x2, y;
	struct interval range = *(struct interval*) param;
    double begin, end;
    int id = range.id;
    begin = range.begin;
    end = range.end;;

	// Loops 
	for (x1 = begin; x1 <= end; x1 += 0.05) { // x1 parameter of Shubert function
		for (x2 = begin; x2 <= end; x2 += 0.05) { // x2 parameter of Shubert function
	    	y = shubert(x1, x2); // Evaluate Shubert function defined below
	     	//printf("%.2f ", y); // Print value for demonstration purposes
	     	if (y < p_mins[id]) // Check for global minimum
	       	p_mins[id] = y;
    		}
	    //printf("\n"); // Print on next row
	}

  	pthread_exit(0);

}

int main(int argc, char* argv[]){
	if(argc==2){
		int threads = atoi(argv[1]);
		global_range.begin = -500;
		global_range.end = 500;

		if(threads>0){
			printf("Running Shubert with %d threads...\n", threads);
			struct timeval start_time, stop_time, elapsed_time;  // timers
		  	gettimeofday(&start_time,NULL); // Unix timer

			double range = global_range.end - global_range.begin;
			double increment = range/threads;

			pthread_t tids[threads];
			struct interval local_ranges[threads];

			int i=0;
			for(; i<threads; i++){
				local_ranges[i].begin = global_range.begin+(i*increment);
				local_ranges[i].end = global_range.begin+((i+1)*increment);
				local_ranges[i].id = i;
				
				pthread_t tid; /* the thread identifier */
				pthread_attr_t attr; /* set of attributes for the thread */

				
				/* get the default attributes */
				pthread_attr_init(&attr);
				/* create the thread */
				pthread_create(&tid,&attr,pShubertRun, &local_ranges[i]);
				tids[i] = tid;
			}


			/* now wait for all threads to exit */
			for(i=0; i<threads; i++){
				pthread_join(tids[i],NULL);
			}

			double min = 0;
			for(i=0; i<threads; i++){
				printf("min[%d]: %f\n", i, p_mins[i]);
				if(p_mins[i]<min)
					min = p_mins[i];
			}
			

			gettimeofday(&stop_time,NULL);
			timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
			printf("Total time was %f seconds.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
			printf("minimum = %f\n", min);

		}
		else{
			printf("ERROR: Please make sure your argument conains an integer between 1 and 10,000\n");
		}
	}
	else{
		printf("ERROR: Please include one, and only one argument containing the number of threads you wish to run\n");
	}
	return 0;
}