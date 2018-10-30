// 1 fish
// Scan the entire array, and focus on one pellet
// Arrange itself

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main() {
  key_t key = ftok("SwimMill.c", 'b');
  int shmid = shmget(key, 1024, IPC_CREAT|0666);
  int *shm = (int*) shmat(shmid, NULL, 0);

  while (1) {

  }
  return 0;
}

void moveLeft() {
  fishPositionX--;
}

void moveRight() {
  fishPositionX++;
}
