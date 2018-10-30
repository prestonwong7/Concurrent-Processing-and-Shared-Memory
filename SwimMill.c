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
#include <time.h>
#include <unistd.h>

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
void handler(int);

int main(int argc, char* argv[]) {

	key_t key;
	int shmid;
	int *shm;
	int timer = 0;
	int fish = 0;
	int pellet[20];

	signal(SIGINT, handler);

	key = ftok("SwimMill.c", 'b'); //generate random ke
	shmid = shmget(key, SHM_SIZE, IPC_CREAT|0666);
	shm = shmat(shmid, NULL, 0); // Attach

	// Initializing the shared memory to prevent segmentation fault
	for (int i = 0; i < SHM_SIZE; i++){
		shm[i] = -1;
	}

	int index = 1;
	fish = fork();
	
	if (fish == -1) {
		perror("Fish fork failed");
		exit(1);
	}	else if (fish == 0) {
		execv("Fish", argv);
		perror("Fish exec failed");
		exit(1);
	}

	while(timer <= 30){
		pellet[index] = fork();
		if (pellet[index] == -1) {
			perror("Pellet Fork failed");
			exit(1);
		}	else if (pellet[index] == 0) {
			execv("Pellets", argv);
			perror("Pellets Fork failed");
			exit(1);
		}
		sleep(1); // Slow process down
		printGrid(shm);
		printf("\n");

		timer++;
		index++;

	}

	kill(fish,SIGUSR1);
	for(int i = 0; i < 20; i++) {
		kill(pellet[index], SIGUSR1);
	}

	sleep(10);
	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Program finished! \n");
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

	//Printing out grid with fish and
	// printf("Shm2 is: %d \n", shm[1] );
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			// stream[i][j] = '~'; // water
			for (int k = 1; k < 20; k++) {
				stream[shm[k]/10][shm[k]%10] = 'O'; // pellets
			}
			stream[shm[0]/10][shm[0]%10] = 'Y'; // Fish
			printf("%c ", stream[i][j]	 );
		}
		printf("\n");
	}

}

void handler(int num) {
	perror(" Interrupt signal is pressed!! \n");
	exit(1);
}
