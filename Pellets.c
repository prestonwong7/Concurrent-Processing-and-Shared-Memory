// Multiple pellets
//Process ID, position, eaten/missed
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main() {
  key_t key = ftok("SwimMill.c", 'b');
  int shmid = shmget(key, 1024, IPC_CREAT|0660);
  char *str = (char*) shmat(shmid, NULL, 0);
  return 0;
}
