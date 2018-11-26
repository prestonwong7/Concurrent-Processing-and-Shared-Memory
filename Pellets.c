// Multiple pellets
//Process ID, position, eaten/misse
// #include <stdio.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <signal.h>
#include <time.h>
#include "include.h"

#define SHM_SIZE 1000

void handler(int);
void eatPellet();
void missPellet();

int main(int argc, char* argv[]) {
  signal(SIGINT, handler);

  attachSharedMemory();
  srand(time(NULL));

  int i = 1; // 1 - 19 are pellets
  for (; i < 20; i++) {
    shm[i] = rand() % 9 ; // random number from 0 - 9
    // if (shm[i] == -1){
    //   // printf("hello %d \n", pelletPosition);
    //   shm[i] = pelletPosition;
    // }
    break;
  }
  while(1) {
    printf("helloasd %d \n", shm[i]);
    printf("i: %d \n", i);
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
	shmdt(shm);
	exit(1);
}
