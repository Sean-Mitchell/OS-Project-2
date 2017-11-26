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
	This is what's run in the Santa thread
*/
void *santaThread(void *args) 
{
	while(1) 
	{ 
		santaHelper();
	}
	
}

/*
	Santa starts sleeping but he is woken up when 9 reindeer or 3 elves show up at his door needing help.
	Santa helps them and then the elves/ reindeer are left to go about their own business
*/
void santaHelper() 
{	
	//Get Lock
	pthread_mutex_lock(&elfAndReindeerCount);
	
	
	//Santa is asleep
	printf("Santa is sleeping.\n");
	
	//Waits while there aren't enough reindeer/ elves to be helped
	while(reindeerCount < 9 && elfCount < 3)
	{
		pthread_cond_wait(&santaSleeping, &elfAndReindeerCount);		
	}
	
	printf("Santa is WOKE.\n");
	
	//Checks reindeer first because Christmas > Elves
	if (reindeerCount == 9)
	{
		printf("Reindeer harnessed.\n");
		
		printf("Begin delivering presents.\n");
		deliverPresents();
		
		//Lets all the reindeer go back on vacation
		pthread_cond_broadcast(&stable);
	}
	
	if (elfCount == 3)
	{
		printf("Begin helping elves.\n");
		helpElves();
		
		//This wakes up the elves and makes it so santa has to wait for all the elves to be done working before starting up again
		pthread_cond_broadcast(&workshop);
		if (elfCount == 3)
		{
			pthread_cond_wait(&santaWaitElf, &elfAndReindeerCount);				
		}
	}
	
	//Release lock
	pthread_mutex_unlock(&elfAndReindeerCount);	
}

// Has santa help the elves for a certain amount than returns
void helpElves() 
{
	//Time to deliver presents
	int amount = ((rand() % (maxWait - minWait)) + minWait) * 1000;
	
	usleep(amount);
	
	//Reset reindeer variable as the reindeer go on vacation again
	printf("Elves helped.\n");
}

// Delivers presents for a random amount of time, than resets the reindeer count variable so the reindeer
// can go back on vacation.
void deliverPresents() 
{
	//Time to deliver presents
	int amount = ((rand() % (maxWait - minWait)) + minWait) * 1000;
	
	usleep(amount);
	
	//Reset reindeer variable as the reindeer go on vacation again
	printf("PRESEENTS DELIVERed\n");
	reindeerCount = 0;
}