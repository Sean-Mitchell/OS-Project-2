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
	This is what's run in the elf threads
*/

void *elfThread(void *args) 
{	
	while(1) 
	{ 
		elvesHelper();
	}	
}


/*
	This is the Elf helper thread, it takes care of making the Elves work for a while then need help from santa.
	Once a queue of 3 elves are ready to be helped the last one will wake up santa.
*/
void elvesHelper() 
{
	//Need to lock to make sure that no one can modify this var at the same time seperately from the other counts
	pthread_mutex_lock(&elfwWaitingLock);
	
	printf("Elf beginning work.\n");
	
	int amount = ((rand() % (maxWait - minWait)) + minWait) * 1000;
	
	usleep(amount);
	
	//Elf done working
	
	//Make it so the elves have to wait until the other elves are done being helped
	while (elfDoor == 1)
	{
		pthread_cond_wait(&elfWaiting, &elfwWaitingLock);
	}
	
	pthread_mutex_lock(&elfAndReindeerCount);

	//variable to make it so 1 elf can request help from santa
	elfDoor = 1;	
	elfCount++;
		
	
	if (elfCount == 3)
	{		
		printf("3rd elf is waiking Santa up.\n");
		
		//Signal santa after he wakes up
		pthread_cond_signal(&santaSleeping);
		
		//Wait to be done with delivering presents
		pthread_cond_wait(&workshop, &elfAndReindeerCount);
		
	}
	else
	{
		printf("Elf waits for help from santa.\n");
		
		//Allows next elf to come in
		elfDoor = 0;
		pthread_mutex_unlock(&elfwWaitingLock);	
			
		//Make reindeer wait until the count = 0 again
		pthread_cond_wait(&workshop, &elfAndReindeerCount);
		
	}
	
	//Brings the elves out of the queue
	elfCount--;
	
	//Makes it so 
	if (elfCount == 0)
	{
		elfDoor = 0;
		
		//Lets santa go back to sleep since all the elves are done working
		pthread_cond_signal(&santaWaitElf);
		
		//Resets all elves waiting
		pthread_cond_broadcast(&elfWaiting);
		pthread_mutex_unlock(&elfwWaitingLock);	
		
		printf("Last Elf done working for the moment.\n");
	}
	else
	{
		printf("Elf done working for the moment.\n");		
	}
	
	//Release lock
	pthread_mutex_unlock(&elfAndReindeerCount);	
	
}