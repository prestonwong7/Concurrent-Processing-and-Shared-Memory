#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define SHM_SIZE 1000

int shmid;
int *shm;
pid_t fish;
pid_t pellet;


void attachSharedMemory() {
  key_t key = ftok("SwimMill.c", 'b'); //generate random key
  shmid = shmget(key, SHM_SIZE, IPC_CREAT|0666);
  shm = shmat(shmid, NULL, 0);

}
