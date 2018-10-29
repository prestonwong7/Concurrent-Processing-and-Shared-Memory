// Uses both fish and pellets, 30 seconds, then print it out
// Create pellets at random intervals, from 0x80
// Eating --> Get rid of most significant bit
// Use shared memory for fish and pellet position only
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define SHM_SIZE 30;

void handler(int num) {
	perror("Interrupt signal is pressed!! \n");
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
	char *shm;

	key = ftok("SwimMill.c", 'b'); //generate random key
	shmid = shmget(key, 1024, IPC_CREAT|0660);
	if (shmid < 0) {
		perror("shmget");
		exit(1);
	}
	shm = shmat(shmid, NULL, 0);
	shm = 1;

	int row = 10;
	int column = 10;
	int stream[row][column]; //2D Dimensional array, fish can only move last row of 2d
	int fish = 0;
	int fishPositionX = 0;
	int numberOfPellets[20] = {0}; // Create array
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
