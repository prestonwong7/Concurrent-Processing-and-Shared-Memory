// 1 fish
// Scan the entire array, and focus on one pellet
// Arrange itself

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>
#include <unistd.h>

int findClosestPellet(int*);
void moveLeft(int, int*);
void moveRight(int, int*);

int main() {
  key_t key = ftok("SwimMill.c", 'b');
  int shmid = shmget(key, 1024, IPC_CREAT|0666);
  int *shm = (int*) shmat(shmid, NULL, 0);

  int fish = 94; // Middle position
  shm[0] = fish; // Store first shared memory space to fish
  int columnToMoveTo = 0;
  while(1) {
    int closestPellet = shm[findClosestPellet(shm)];
    if ((closestPellet % 10) > (fish % 10) ) {
      moveRight(fish, shm);
    }
    else if ((closestPellet % 10) < (fish % 10)) {
      moveLeft(fish, shm);
    }
    sleep(1);
  }
  shmdt(shm);
  return 0;
}

int findClosestPellet(int* shm) {
  // Using distance formula to find closest pellet
  // (x2 - x1)^2 + (y2 - y1)^2
  int closestPellet = 0;
  int distance[20] = {0}; // Distance of all 20 pellets
  int minimumDistance = 0;
  // shm[1] = 11;
  // shm[2] = 14;
  // shm[3] = 10;
  // shm[4] = 55;
  int x2 =  shm[0] % 10;
  int y2 = shm[0] / 10;
  for (int i = 1; i < 20; i++) {
    int x1 = shm[i] % 10;
    int y1 = shm[i] / 10;
    distance[i] = pow(x2-x1,2) + pow(y2-y1,2); // Storing them
  }
  minimumDistance = distance[1];

  //Finding smallest distance
  for (int i = 2; i < 20; i++) {
    if (distance[i] <= minimumDistance) {
      closestPellet = i;
    }
  }
  printf("Closest pellet %d \n", closestPellet);
  return shm[closestPellet];
}

void moveLeft(int fish, int* shm) {
  if (shm[0] <= 90) {
  }
  else{
    fish--;
    shm[0]--;
  }
}

void moveRight(int fish, int* shm) {
  if (shm[0] >= 99){
  }
  else{
    fish++;
    shm[0]++;
  }
}
