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

/* 1. Create share memory using shmget
2. Attach to shared memory using shmat
3. Do operations
4. Detach using shmdt
*/

void printGrid(int*);
void handler(int );

int main() {
	signal(SIGINT, handler);

	key_t key;
	int shmid;
	int *shm;

	key = ftok("SwimMill.c", 'b'); //generate random key
	shmid = shmget(key, SHM_SIZE, IPC_CREAT|0666);
	shm = shmat(shmid, NULL, 0); // Attach

	// Initializing the shared memory to prevent segmentation fault
	for (int i = 0; i < SHM_SIZE; i++){
		shm[i] = -1;
	}

	printGrid(shm);

	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	getchar(); // Pause consol
	return 0;
}

void printGrid(int* shm) {
	int row = 10;
	int column = 10;
	char stream[row][column]; //2D Dimensional array, fish can only move last row of 2d

	//Initializing grid first
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			stream[i][j] = '~';
		}
	}

	int fishRow = shm[0] / 10;
	int fishColumn = shm[0] % 10;
	//Printing out grid with fish and pellet
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			stream[i][j] = '~';
			printf("%c ", stream[i][j]	 );
		}
		printf("\n");
	}

}

void handler(int num) {
	perror("Interrupt signal is pressed!! \n");
	exit(1);
}
