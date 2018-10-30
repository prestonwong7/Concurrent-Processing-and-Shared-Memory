// Uses both fish and pellets, 30 seconds, then print it out
// Create pellets at random intervals, from 0x80
// Eating --> Get rid of most significant bit
// Use shared memory for fish and pellet position only
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

#define SHM_SIZE 1000

/*
TODO: SwimMIll FIRST, draw and get everything working
*/
void handler(int num) {
	perror("Interrupt signal is pressed!! \n");
	exit(1);
}

/* 1. Create share memory using shmget
	 2. Attach to shared memory using shmat
	 3. Do operations
	 4. Detach using shmdt
*/
int main() {
	signal(SIGINT, handler);

	key_t key;
	int shmid;
	int *shm;

	key = ftok("SwimMill.c", 'b'); //generate random key
	shmid = shmget(key, SHM_SIZE, IPC_CREAT|0666);
	shm = shmat(shmid, NULL, 0); // Attach
	// SHM like an array, from 0 - 99
	// 90 - 99 is for fish
	// 0 - 9 is for pellet

	 // Initializing the shared memory to prevent segmentation fault
	for (int i = 0; i < SHM_SIZE; i++){
		shm[i] = -1;
	}


	// shm[5] = 1;

	int row = 10;
	int column = 10;
	char stream[row][column]; //2D Dimensional array, fish can only move last row of 2d
	int fish = 0;
	int fishPositionX = 5; // Moves last row, in the column, so (10,0)
	int numberOfPellets[20] = {0}; // Create array

	//Printing out grid
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
				stream[i][j] = '~';
		}
	}

	getchar(); // Pause consol
	return 0;
}

void dropPellet(int pellet, int positionY) {
	positionY++;
}

// void travelToPellet(int fish) {
// 	if (fishPositionX > pellet.positionX) {
// 		fish.positionX--;
// 	}
// 	else if (fish.positionX < pellet.positionX) {
// 		fish.positionX++;
// 	}
// 	else{
// 	}
// }

void eaten(int fish){
	if (fish  == 10) {

	}
}
