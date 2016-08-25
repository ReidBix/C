#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>

//g++ -O2 -Wall -pthread -std=c++11 numbers.cpp -o numbers

using namespace std;

typedef struct {
	double *a;
	double *b;
	double sum;
	int veclen;
	int thread_id;
} thread_data;

struct maxVal {
	int thread_id;
	int a;
	int b;
	int max;
};

#define NUMTHRDS 3
#define TCOUNT 4
#define COUNT_LIMIT 2
#define VECLEN 100

#define THREADS 20

maxVal mstr;
vector<int> max_vals;
sem_t OKToStart;
int roundsLeft;
int EXTRA_LIMIT;
int extras;
int currentNum;
int extraComplete;
pthread_cond_t max_extra_cv;

thread_data tdstr;
pthread_t callThd[NUMTHRDS];
pthread_mutex_t mutexsum;
int count = 0;
int thread_ids[3] = {0,1,2};
pthread_cond_t count_threshold_cv;
pthread_mutex_t count_mutex;

sem_t OKToBuyMilk;
int milkAvailable;

//int arr[] = {15, 8, 15, 34, 91, 24, 17, 68, 14, 13, 12};
int arr[] = {15, 8, 15, 34, 91, 24, 17, 68, 12, 4};
int MAX_DEPTH = 0;
int dCount = 0;
pthread_cond_t max_threshold_cv;
pthread_mutex_t max_mutex;
int check = 0;


int currentRound;

void *buyer(void *arg) {
	// P()
	sem_wait(&OKToBuyMilk);
	if(milkAvailable < 10){
		//Buy some milk
		//printf("buyer(): Able to buy some milk!\n");
		++milkAvailable;
	} else {
		//printf("buyer(): Unable to buy some milk!\n");
	}
	// V()
	sem_post(&OKToBuyMilk);

	return NULL;
}

void *inc_count(void *t) {
	int i;
	//long my_id = (long)t;
	for (i=0; i<TCOUNT; i++) {
		pthread_mutex_lock(&count_mutex);
		count++;
	
		/* Check if value of count and signal waiting thread when condition is reached. Occurs while mutex is locked */
		if (count == COUNT_LIMIT) {
			//printf("inc_count(): thread %ld, count = %d, Threshold reached\n", my_id, count);
			pthread_cond_signal(&count_threshold_cv);
			//printf("Just sent signal.\n");
		}
		//printf("inc_count(): thread %ld, count = %d, unlocking mutex\n", my_id, count);
		pthread_mutex_unlock(&count_mutex);
		
		/*Do "work" so threads can alternate on mutex lock */
		sleep(1);
	}
	pthread_exit(NULL);	
}

int getMax(int a[], int l, int r, int depth){
	//long my_id = (long)t;
	
	//Compare extras past 2^X and start from end

	//pthread_mutex_lock(&max_mutex);
	if(depth == MAX_DEPTH-1){
		//pthread_mutex_lock(&max_mutex);
		//printf("maxFind(): Updating dCount...\n");
		dCount += 1;	
		//printf("maxFind(): dCount is %d\n", dCount);
		//printf("maxFind(): unlocking mutex\n");
		//pthread_mutex_unlock(&count_mutex);
	}

	if(r-l==1){
		//printf("maxFind(): Ans is %d, Depth is %d, dCount is %d\n",a[l],depth,dCount);
		if(depth == MAX_DEPTH) {
			//printf("maxFind(): Do in one round of threads\n");
		} else {
			//printf("maxFind(): Wait on condition variable.\n");
		}
		if(dCount == pow(2,MAX_DEPTH-1)){
			if (check) {
				//printf("maxFind(): Finished a round!\n");
				MAX_DEPTH -= 1;
				dCount = 0;
				check = 0;
				//printf("maxFind(): dCount = %d, Threshold reached\n", dCount);
				//pthread_cond_signal(&count_threshold_cv);
				//printf("maxFind(): Just sent signal.\n");
			}
			check = 1;
		}
		return a[l];
	}

	//If at max depth, do all things, then signal next level
	/*
	pthread_mutex_lock(&max_mutex);

	}

	pthread_exit(NULL);
	*/	

	//Do all in one level until complete
	//printf("maxFind(): Comparison being made between range %d and %d\n", l, r);
	int m=(l+r)/2;
	int newDepth = depth + 1;
	int u=getMax(a,l,m,newDepth);
	int v=getMax(a,m,r,newDepth);
	int ans = u>v?u:v;
	//int size = sizeof(a)/sizeof(int);
	//printf("maxFind(): Left and Right are %d, %d, Ans is %d, Depth is %d\n",u,v,ans,depth);
	return ans;
}

void *watch_count(void *t) {
	//long my_id = (long)t;
	
	//printf("Starting watch_count(): thread %ld\n", my_id);

	/*Lock mutex and wait for signal. pthread_cond_wait routine will automatically and atomically unlock mutex while it waits. If COUNT_LIMIT is reached before this routine is run by the waiting thread, the loop will be skipped to prevent pthead_cond_wait from never returning */
	pthread_mutex_lock(&count_mutex);
	while (count<COUNT_LIMIT){
		//printf("watch_count(): thread %ld Count= %d. Going into wait...\n", my_id, count);
		pthread_cond_wait(&count_threshold_cv, &count_mutex);
		//printf("watch_count(): thread %ld Condition signal received. Count= %d\n", my_id, count);
		//printf("watch_count(): thread %ld Updating the value of count...\n", my_id);
		count += 125;
		//printf("watch_count(): thread %ld count now = %d.\n", my_id, count);
	}
	//printf("watch_count(): thread %ld Unlocking mutex.\n", my_id);
	pthread_mutex_unlock(&count_mutex);
	pthread_exit(NULL);
}

void *call_from_thread(void *arg){
	int i, start, end, len;
	long offset;
	double mysum, *x, *y;
	offset = (long)arg;
	
	len = tdstr.veclen;
	start = offset*len;
	end = start + len;
	x = tdstr.a;
	y = tdstr.b;
	
	mysum = 0;
	for (i=start; i<end; i++){
		mysum += (x[i] * y[i]);
	}

	pthread_mutex_lock (&mutexsum);
	tdstr.sum += mysum;
	//cout << mysum << endl;
	//thread_data *my_data = (thread_data *) args;
	//cout << "Launched by thread " << my_data->thread_id << endl;
	pthread_mutex_unlock (&mutexsum);

	pthread_exit((void *) 0);
}

void *compare_thread(void *arg){
	int x, y, max;
	struct maxVal *my_data;
	sleep(1);
	my_data = (struct maxVal *) arg;
	x = my_data->a;
	y = my_data->b;
	max = x>y?x:y;
	//printf("Thread %d: Val a=%d, Val b=%d, max=%d\n",taskid,x,y,max);
	pthread_mutex_lock(&max_mutex);
	max_vals.push_back(max);
	extras += 1;
	if (extras == EXTRA_LIMIT) {
		pthread_cond_signal(&max_threshold_cv);
	}
	pthread_mutex_unlock(&max_mutex);
	pthread_exit(NULL);
}

void *compare_thread2(void *arg){
	int x, y, max;
	struct maxVal *my_data;
	sleep(1);
	my_data = (struct maxVal *) arg;
	x = my_data->a;
	y = my_data->b;
	max = x>y?x:y;
	//printf("Thread %d: Val a=%d, Val b=%d, max=%d\n",taskid,x,y,max);
	pthread_mutex_lock(&max_mutex);
	while (extras<EXTRA_LIMIT){
		pthread_cond_wait(&max_threshold_cv, &max_mutex);
		max_vals.push_back(max);
	}
	pthread_mutex_unlock(&max_mutex);
	pthread_exit(NULL);
}


void *getMax(void *arg){
	int x, y, max;
	struct maxVal *my_data;
	sleep(1);
	my_data = (struct maxVal *) arg;
	x = my_data->a;
	y = my_data->b;
	max = x>y?x:y;
	//printf("Thread %d: Val a=%d, Val b=%d, max=%d\n",taskid,x,y,max);
	pthread_mutex_lock(&max_mutex);
	//printf("getMax(): Decrementing currentNum...\n");
	currentNum -= 1;
	//printf("getMax(): currentNum is %d\n",currentNum);
	if (currentNum == 0){
		//printf("getMax(): Broadcasting to everywhere\n");
		extraComplete = 1;
		pthread_cond_broadcast(&max_threshold_cv);
		pthread_cond_signal(&max_extra_cv);
		//printf("getMax(): Done broadcasting\n");
	} else {
		//printf("getMax(): Waiting for currentNum to equal 0\n");
		pthread_cond_wait(&max_threshold_cv, &max_mutex);
	}
	//printf("getMax(): Pushing values to vector\n");
	max_vals.push_back(max);
	//printf("getMax(): Unlocking mutex\n");
	pthread_mutex_unlock(&max_mutex);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	string line;
	ifstream myfile ("inData.txt");
	if (myfile.is_open()) {
		while (getline(myfile,line)) {
			int result;
			stringstream(line) >> result;
			max_vals.push_back(result);
		}
		myfile.close();
	} else {
		cout << "Unable to open file";
	}
	int size = max_vals.size();
	if (size == 0) {
		printf("The file was empty.\n");
		return 0;
	}
	int c[size];
	copy(max_vals.begin(), max_vals.end(),c);
	int n = sizeof(c)/sizeof(int);
	long i;
	double *a, *b;
	void *status;
	pthread_attr_t attr;

	a = (double*) malloc(NUMTHRDS*VECLEN*sizeof(double));
	b = (double*) malloc(NUMTHRDS*VECLEN*sizeof(double));

	for (i=0; i<VECLEN*NUMTHRDS; i++){
		a[i] = 1.0;
		b[i] = a[i];
	}

	tdstr.veclen = VECLEN;
	tdstr.a = a;
	tdstr.b = b;
	tdstr.sum = 0;

	pthread_mutex_init(&mutexsum, NULL);

	/* Create threads to perform stuff */	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	/*Each thread works on different set of data */
	for (int i = 0; i < NUMTHRDS; ++i){
		pthread_create(&callThd[i], &attr, call_from_thread, NULL);
	}
	
	pthread_attr_destroy(&attr);

	// cout << "Launched from the main\n";

	/* Wait on the other threads */
	for (int i = 0; i < NUMTHRDS; ++i){
		pthread_join(callThd[i],&status);
	}

	//printf("Sum = %f \n", tdstr.sum);
	free(a);
	free(b);
	pthread_mutex_destroy(&mutexsum);

	int j;
	long t1=1, t2=2, t3=3;
	pthread_t threads[3];
	pthread_attr_t attr2;
	
	/*Initialize mutex and condition variable objects */	
	pthread_mutex_init(&count_mutex, NULL);
	pthread_cond_init(&count_threshold_cv, NULL);

	/*For portability, explicitly create threads in a joinable state */
	pthread_attr_init(&attr2);
	pthread_attr_setdetachstate(&attr2, PTHREAD_CREATE_JOINABLE);
	pthread_create(&threads[0], &attr2, watch_count, (void*)t1);
	pthread_create(&threads[1], &attr2, inc_count, (void*)t2);
	pthread_create(&threads[2], &attr2, inc_count, (void*)t3);

	/*Wait for all threads to complete */
	for (j=0; j<NUMTHRDS; j++) {
		pthread_join(threads[j], NULL);
	}
	//printf("Main(): Waited on %d threads. Final value of count = %d. Done.\n", NUMTHRDS, count);

	/*Clean up and exit*/
	pthread_attr_destroy(&attr2);
	pthread_mutex_destroy(&count_mutex);
	pthread_cond_destroy(&count_threshold_cv);

	//printf("Main: Starting to buy milk.\n");

	int r = 1;
	pthread_t threads2[THREADS];
	milkAvailable = 0;

	/* Initialize sempahore with a value of 1. Second argument: passing zero denotes that the semaphore is shared between threads (and not processes). */
	if (sem_init(&OKToBuyMilk, 0, 1)) {
		//printf("Could not initialize a semaphore\n");
		return -1;
	}

	for (int i = 0; i < THREADS; ++i) {
		if(pthread_create(&threads2[i], NULL, &buyer, NULL)){
			//printf("Could not create thread %d\n", i);
			return -1;
		}
	}

	for (int i = 0; i < THREADS; ++i) {
		if(pthread_join(threads2[i], NULL)){
			//printf("Could not join thread %d\n", i);
			return -1;
		}
	}
	sem_destroy(&OKToBuyMilk);
	r = getMax(c,0,n,0);

	//Make sure we don't have too much milk.
	//printf("Total milk: %d\n", milkAvailable);

	int nn = sizeof(arr)/sizeof(int);
	int rounds = ceil(log2(n));
	//printf("Main: size of array is: %d, Number of rounds is: %d\n", n, rounds);
	
	int maxThreads = pow(2,rounds);
	int extraThreads, nextThreads, saved;
	//printf("n %d, log2(n) %d\n", n, (int)log2(n));
	if ((n % (int)log2(n)) != 0) {
		extraThreads = n-pow(2,rounds-1);
		nextThreads = pow(2,rounds-1)/2;
		currentNum = extraThreads;
		extraComplete = 0;
	} else {
		extraThreads = 0;
		nextThreads = maxThreads/2;
		currentNum = nextThreads;
		extraComplete = 1;
	}
	MAX_DEPTH = rounds;
	saved = nextThreads;

	//printf("Main: maxThreads is %d\n",maxThreads);
	//printf("Main: MAX_DEPTH is %d\n",MAX_DEPTH);
	//printf("Main: extraThreads is %d\n",extraThreads);
	//printf("Main: nextThreads is %d\n",nextThreads);

	pthread_t eThreads[extraThreads];
	pthread_attr_t attr3;
	struct maxVal maxVal_array[extraThreads];
	struct maxVal maxVal_final[nextThreads];

	/*Initialize mutex and condition variable objects */	
	pthread_mutex_init(&max_mutex, NULL);
	pthread_cond_init(&max_threshold_cv, NULL);

	/*For portability, explicitly create threads in a joinable state */
	pthread_attr_init(&attr3);
	pthread_attr_setdetachstate(&attr3, PTHREAD_CREATE_JOINABLE);

	//Push all values onto vector
	//printf("Main: Copying values into vector\n");
	for(vector<int>::const_iterator i = max_vals.begin(); i != max_vals.end(); ++i){
		//cout << *i << ' ';
	}
	//printf("Main: Starting extraThreads...\n");
	for (int t = 0; t < extraThreads; t++) {
		int max = 0;
		maxVal_array[t].thread_id = t;
		maxVal_array[t].max = max;
		maxVal_array[t].a = max_vals.back();
		max_vals.pop_back();
		maxVal_array[t].b = max_vals.back();
		max_vals.pop_back();
		pthread_create(&eThreads[t], NULL, getMax, (void *)&maxVal_array[t]);
	}
	pthread_mutex_lock(&max_mutex);
	pthread_cond_wait(&max_extra_cv, &max_mutex);
	currentNum = nextThreads/2;
	pthread_mutex_unlock(&max_mutex);
	for (i=0;i<extraThreads; i++) {
		pthread_join(eThreads[i], NULL);
	}
	for(vector<int>::const_iterator i = max_vals.begin(); i != max_vals.end(); ++i){
		//cout << *i << ' ';
	}
	//Iteration
	//printf("Main: Round(%d) We will allow %d threads to pass initially.\n",r,extraThreads);
	pthread_t nThreads[nextThreads];
	while (nextThreads != 1) {
		//Clear extra
		nn -= 1;
		nextThreads = nextThreads % 1;
		pthread_mutex_lock(&max_mutex);
		for (int t = 0; t < nextThreads; t++) {
		//printf("Main: Starting nextThreads...t=%d\n",t);
			int max = 0;
			maxVal_final[t].thread_id = t;
			maxVal_final[t].max = max;
			//printf("Probably failure\n");
			maxVal_final[t].a = max_vals.back();
			max_vals.pop_back();
			//printf("More failure\n");
			maxVal_final[t].b = max_vals.back();
			max_vals.pop_back();
			//printf("Most failure\n");
			pthread_create(&nThreads[t], NULL, getMax, (void *)&maxVal_final[t]);
		}
		r++;	
		saved = 0;
		nextThreads/=2;	
		currentNum = nextThreads;
		if (nextThreads != 1){
			nextThreads = 1;
			r--;
			break;
		}
		//printf("Main: Round(%d) Once we pass those threads, we will make %d other threads.\n",r,nextThreads);
		pthread_mutex_unlock(&max_mutex);
	}	
	for (i=0;i<saved; i++) {
		pthread_join(nThreads[i], NULL);
	}
	//printf("Main(): Waited on %d threads. Final value of count = %d. Done.\n", NUMTHRDS, count);
	for(vector<int>::const_iterator i = max_vals.begin(); i != max_vals.end(); ++i){
		//cout << *i << ' ';
	}
	//cout << endl;
	//printf("Done");
	/*Wait for all threads to complete */
	pthread_attr_destroy(&attr3);
	pthread_mutex_destroy(&max_mutex);
	pthread_cond_destroy(&max_threshold_cv);


	printf("the largest number is %d\n",r);
	pthread_exit(NULL);
}	
