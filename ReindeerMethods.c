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
int minWait, maxWait;
	
int elfCount;
int reindeerCount;
int elfDoor;
/*
	This is what's run in the reindeer threads
*/
void *reindeerThread(void *args) 
{
	while(1)
	{
		reindeerHelper();
	}	
}

/*
	This is the reindeer helper thread, it takes care of making the reindeer go on vacation for a while;
	And having the reindeer wait until done being helped with santa delivering presents.
*/
void reindeerHelper() {	
	//Get Lock
	pthread_mutex_lock(&elfAndReindeerCount);
	
	//Time reindeer is on vacation
	int amount = ((rand() % (maxWait - minWait)) + minWait) * 1000;
	
	printf("Reindeer on vacation.\n");
		
	usleep(amount);
	
	//Add Reindeer to stable
	reindeerCount++;
	
	if (reindeerCount == 9) 
	{
		printf("Last Reindeer is waking santa santa.\n");
		
		//Signal santa after he wakes up
		pthread_cond_signal(&santaSleeping);
		
		//Wait to be done with delivering presents
		pthread_cond_wait(&stable, &elfAndReindeerCount);
	}
	else
	{
		printf("Reindeer is in the stable waiting for santa.\n");			
			
		pthread_cond_wait(&stable, &elfAndReindeerCount);		
	}		
	
	//Release lock
	pthread_mutex_unlock(&elfAndReindeerCount);
}