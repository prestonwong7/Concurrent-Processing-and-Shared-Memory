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
  printf(column);
  shm[1] = column;
  int i = 1; // 1 - 19 are pellets
  while(1) {
    column = rand() % 9 + 0; // random number from 0 - 9
    if (i < 20){
      shm[i] = column;
    }
    if (shm[i] < 90) {
      shm[i] += 10;
    }
    else if (shm[i] == shm[0]) {
      printf("Pellet eaten");
      break;
      // EATEN and KILL
    }
    else {
      // KIll process, terminate
      printf("Pellet missed");
      break;
    }
    i++;
  }

  return 0;
}
