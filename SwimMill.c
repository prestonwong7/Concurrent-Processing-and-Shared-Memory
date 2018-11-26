// Uses both fish and pellets, 30 seconds, then print it out
// Create pellets at random intervals, from 0x80
// Eating --> Get rid of most significant bit
// Use shared memory for fish and pellet position only
// #include <stdio.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/types.h>
// #include <signal.h>
// #include <stdlib.h>
// #include <time.h>
// #include <unistd.h>
#include <semaphore.h>
#include "include.h"

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
void killProgram(pid_t, pid_t, int*, int);
pid_t fish;
pid_t pellet;

int main(int argc, char* argv[]) {

	int timer = 0;
	attachSharedMemory(); // from include.h
	signal(SIGINT, handler);


	// Initializing the shared memory to prevent segmentation fault
	// for (int i = 0; i < SHM_SIZE; i++){
	// 	shm[i] = -1;
	// }

	fish = fork();

	if (fish == -1) {
		perror("Fish fork failed1");
		exit(1);
	}	else if (fish == 0) {
		execl("Fish", "Fish", NULL);
		perror("Fish exec failed");
		exit(1);
	}
	while(timer <= 30){
		pellet = fork();
		if (pellet == -1) {
			perror("Pellet Fork failed1");
			exit(1);
		}	else if (pellet == 0) {
			execl("./Pellets", "Pellets", NULL);
			perror("Pellets Fork failed");
			exit(1);
		}
		printGrid(shm);
		sleep(1);
		printf("Timer: %d\n", timer);
		timer++;
	}

	killProgram(fish, pellet, shm, shmid);
	getchar(); // Pause consol
	return 0;
}


void printGrid(int* shm) {
	int row = 10;
	int column = 10;
	char (*stream)[row][column]; //2D Dimensional array, fish can only move last row of 2d

	//Initializing grid first
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			(*stream)[i][j] = '~';
		}
	}
	// printf("Fish: %d \n", shm[0]);
	// printf("Shm2 is: %d \n", shm[1] );
	for (int k = 1; k < 20; k++) {
		(*stream)[shm[k]/10][shm[k]%10] = 'O'; // pellets
	}
	(*stream)[shm[0]/10][shm[0]%10] = 'Y'; // Fish
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			printf("%c ", (*stream)[i][j]);
		}
		printf("\n");
	}

}

void killProgram(pid_t fish, pid_t pellet, int *shm, int shmid) {
	kill(fish,SIGUSR1);
	kill(pellet, SIGUSR1);
	sleep(5);
	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	printf("Program finished! \n");
}

void handler(int num ) {
	kill(fish,SIGUSR1);
	kill(pellet, SIGUSR1);
	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	perror(" Interrupt signal is pressed!! \n");

	exit(1);
}
