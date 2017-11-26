#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "MethodHeaders.h"

//Global Variables
pthread_cond_t 	stable, //For the waiting reindeer
		workshop, 		//Where elves wait before getting help from santa
		santaSleeping, 	//Where santa is sleeping
		elfWaiting, 	//Where an elf waits before being allowed to work on their project
		santaWaitElf;	//Where santa waits until all elves are done working
pthread_mutex_t elfAndReindeerCount,	//Locks counts/ elfDoor
		elfwWaitingLock;				//Waits until elves are done getting help

//Milliseconds 
//THESE ARE THE VALUES YOU CHANGE TO AGJUST THE SPEED
int minWait = 100, 
	maxWait = 2000;
	
int elfCount = 0;
int reindeerCount = 0;
int elfDoor = 0;

//Initializes all threads and has them run until the end of time before stopping
int main() {
	//Random # generator
	srand(time(NULL));
	
	
	//Create all threads
	pthread_t santa, 
		elf0, elf1, elf2, elf3, elf4, elf5, elf6, elf7, elf8, elf9,
		reindeer0, reindeer1, reindeer2, reindeer3, reindeer4, reindeer5, reindeer6, reindeer7, reindeer8;
	
	//Create Locks and Conditions
	pthread_mutex_init(&elfAndReindeerCount, NULL);
	pthread_mutex_init(&elfwWaitingLock, NULL);
	pthread_cond_init(&santaSleeping, NULL);
	pthread_cond_init(&workshop, NULL);
	pthread_cond_init(&stable, NULL);
	pthread_cond_init(&elfWaiting, NULL);
	pthread_cond_init(&santaWaitElf, NULL);
	
	
	//Create Santa
	pthread_create(&santa,NULL,santaThread,NULL);

	//Create Reindeer
	pthread_create(&reindeer0,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer1,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer2,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer3,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer4,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer5,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer6,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer7,NULL,&reindeerThread,NULL);
	pthread_create(&reindeer8,NULL,&reindeerThread,NULL);

	
	//Create Elves
	pthread_create(&elf0,NULL,elfThread,NULL);
	pthread_create(&elf1,NULL,elfThread,NULL);
	pthread_create(&elf2,NULL,elfThread,NULL);
	pthread_create(&elf3,NULL,elfThread,NULL);
	pthread_create(&elf4,NULL,elfThread,NULL);
	pthread_create(&elf5,NULL,elfThread,NULL);
	pthread_create(&elf6,NULL,elfThread,NULL);
	pthread_create(&elf7,NULL,elfThread,NULL);
	pthread_create(&elf8,NULL,elfThread,NULL);
	pthread_create(&elf9,NULL,elfThread,NULL);
	
	
	//Join Threads
	pthread_join(santa,NULL);
	pthread_join(reindeer0,NULL);
	pthread_join(reindeer1,NULL);
	pthread_join(reindeer2,NULL);
	pthread_join(reindeer3,NULL);
	pthread_join(reindeer4,NULL);
	pthread_join(reindeer5,NULL);
	pthread_join(reindeer6,NULL);
	pthread_join(reindeer7,NULL);
	pthread_join(reindeer8,NULL);
	pthread_join(elf0,NULL);
	pthread_join(elf1,NULL);
	pthread_join(elf2,NULL);
	pthread_join(elf3,NULL);
	pthread_join(elf4,NULL);
	pthread_join(elf5,NULL);
	pthread_join(elf6,NULL);
	pthread_join(elf7,NULL);
	pthread_join(elf8,NULL);
	pthread_join(elf9,NULL);
	
	
	printf("We did it Reddit\n");
	return 0;
}