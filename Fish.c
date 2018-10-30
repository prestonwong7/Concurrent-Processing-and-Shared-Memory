// 1 fish
// Scan the entire array, and focus on one pellet
// Arrange itself

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void moveLeft(int, int*);
void moveRight(int, int*);

int main() {
  key_t key = ftok("SwimMill.c", 'b');
  int shmid = shmget(key, 1024, IPC_CREAT|0666);
  int *shm = (int*) shmat(shmid, NULL, 0);

  int fish = 94;
  shm[94] = fish;
  for (int i = 99; i >= 0; i--) {
    if (shm[i] == 1) { // 1 if exists, -1 if it doesnt
      if ((i % 10) > (fish % 10) ) {
        if (fish == 99){
        }
        else{
          moveRight(fish, shm);
        }
      }
      else if ((i % 10) < (fish % 10)) {
        if (fish == 90) {
        }
        else{
          moveLeft(fish, shm);
        }
      }
    }
  }

  return 0;
}

void moveLeft(int fish, int* shm) {
  fish--;
  shm[fish]--;
}

void moveRight(int fish, int* shm) {
  fish++;
  shm[fish]++;
}
