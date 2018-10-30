// Multiple pellets
//Process ID, position, eaten/missed
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main() {
  key_t key = ftok("SwimMill.c", 'b');
  int shmid = shmget(key, 1024, IPC_CREAT|0666);
  int *shm = (int*) shmat(shmid, NULL, 0);

  int column = 0;
  column = rand() % 9 + 0; // random number from 0 - 9
  printf(column);
  shm[1] = column;

  return 0;
}
