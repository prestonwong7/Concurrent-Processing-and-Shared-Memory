// Multiple pellets
//Process ID, position, eaten/misse
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler(int);
void eatPellet();
void missPellet();

int main(int argc, char* argv[]) {
  signal(SIGINT, handler);

  key_t key = ftok("SwimMill.c", 'b');
  int shmid = shmget(key, 1024, IPC_CREAT|0666);
  int *shm = shmat(shmid, NULL, 0);

  int i = 1; // 1 - 19 are pellets
  printf("%d \n", shm[1]);
  for (; i < 20; i++) {
    int pelletPosition = rand() % 9 ; // random number from 0 - 9
    if (shm[i] == -1){
      printf("hello %d \n", pelletPosition);
      shm[i] = pelletPosition;
    }
    break;
  }
  while(1) {
    if (shm[i] < 90) {
      shm[i] += 10;
    }
    else if (shm[i] == shm[0]) {
      eatPellet();
      printf("Position: %d\n", shm[i] );
      break;
      // EATEN and KILL
    }
    else {
      // KIll process, terminate
      missPellet();
      printf("Position: %d\n", shm[i] );
      break;
    }
    // printf("%d\n",shm[i] );
    i++;
    sleep(1);
  }
  shmdt(shm);
  return 0;
}

void eatPellet() {
  printf("Pellet eaten!");
  printf("PID: %d \n", getpid());

}

void missPellet() {
  printf("Pellet missed");
  printf("PID: %d \n", getpid());
}

void handler(int num) {
	// perror(" Interrupt signal is pressed!! \n");
	exit(1);
}
