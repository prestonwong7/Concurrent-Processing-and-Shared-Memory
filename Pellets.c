// Multiple pellets
//Process ID, position, eaten/misse
#include <time.h>
#include "include.h"

#define SHM_SIZE 1000

void handler(int);
void eatPellet();
void missPellet();

int main(int argc, char* argv[]) {
  // fp = fopen("example.txt", "w");
  signal(SIGINT, handler);

  attachSharedMemory();
  shm[20]++;
  int i = shm[20];
  for (; i < 20; i++) {
    srand(time(NULL));
    shm[i] = rand() % 9 ; // random number from 0 - 9
    // printf("shm[i] is %d \n" , shm[i]);
    break;
  }
  // printf("i: %d \n", i);
  sleep(1);
  // pelletCount++;

  // printf("helloasd %d \n", pelletCount);
  while(1) {
    sleep(1);
    if (shm[i] < 90) {
      shm[i] += 10;
    }
    else if (shm[i] == shm[0]) {
      eatPellet();
      printf("Position: %d\n", shm[i] );
      // fprintf(fp, "Position: %d\n", shm[i] );
      shm[i] = -1;
      break;
      // EATEN and KILL
    }
    else {
      // KIll process, terminate
      missPellet();
      printf("Position: %d\n", shm[i] );
      // fprintf(fp,"Position: %d\n", shm[i] );
      shm[i] = 0;
      break;
    }

    i++;

  }
  shmdt(shm);
  return 0;
}

void eatPellet() {
  printf("Pellet eaten! \n");
  // fprintf(fp, "Pellet eaten! \n");
  printf("PID: %d \n", getpid());
  // fprintf(fp, "PID: %d \n", getpid());

}

void missPellet() {
  printf("Pellet missed \n");
  // fprintf(fp,"Pellet missed \n");
  printf("PID: %d \n", getpid());
  // fprintf(fp,"PID: %d \n", getpid());
}

void handler(int num) {
  shmdt(shm);
  exit(1);
}
