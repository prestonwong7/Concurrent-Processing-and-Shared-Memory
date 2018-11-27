// Uses both fish and pellets, 30 seconds, then print it out
// Create pellets at random intervals, from 0x80
// Eating --> Get rid of most significant bit
// Use shared memory for fish and pellet position only
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

	// Declaring semaphore variables
	sem_t sem;
	int pshared = 1;
  unsigned int value = 1;
	if((sem_init(&sem, pshared, value)) == 1)
	 {
		 perror("Error initializing semaphore");
		 exit(1);
	 }


	// Initializing the shared memory to prevent segmentation fault
	for (int i = 0; i < SHM_SIZE; i++){
		shm[i] = -1;
	}

	fish = fork();

	if (fish == -1) {
		perror("Fish fork failed1");
		exit(1);
	}	else if (fish == 0) { // Fish child returns 0 as pid
		execl("Fish", "Fish", NULL);
		perror("Fish exec failed");
		exit(1);
	}

	while(timer <= 30){ // Run for 30 seconds
		pellet = fork();
		sem_wait(&sem);
		if (pellet == -1) {
			perror("Pellet Fork failed1");
			exit(1);
		}	else if (pellet == 0) { // Child pellet returns 0
			execl("./Pellets", "Pellets", NULL);
			perror("Pellets Fork failed2");
			exit(1);
		}
		printGrid(shm);
		sleep(1);
		printf("Timer: %d\n", timer);
		timer++;
		sem_post(&sem);
	}

	killProgram(fish, pellet, shm, shmid);
	getchar(); // Pause consol
	return 0;
}


void printGrid(int* shm) {
	int row = 10;
	int column = 10;
	char stream[row][column]; // Dont use pointer! Causes bad address!

	//Initializing grid first
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			stream[i][j] = '~';
		}
	}
	printf("Fish: %d \n", shm[0]);
	printf("Pellet is: %d \n", shm[1] );
	for (int k = 1; k < 20; k++) {
		stream[shm[k]/10][shm[k]%10] = 'O'; // pellets
	}
	stream[shm[0]/10][shm[0]%10] = 'Y'; // Fish
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			printf("%c ", stream[i][j]);
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
	printf("Program finished! Press anything to exit! \n");
}

void handler(int num ) { // Ctrl C exits program
	kill(fish,SIGUSR1);
	kill(pellet, SIGUSR1);
	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	perror("Interrupt signal is pressed!! \n");

	exit(1);
}
