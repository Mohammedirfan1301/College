/*
    This is a Utility C File for A3
*/
#include "donuts.h"

int p (int semidgroup, int donut_type) {
  struct sembuf semopbuf;         /*** struct in <sys/sem.h> ***/

  semopbuf.sem_num = donut_type;
  semopbuf.sem_op = (-1);         /*** -1 is a P operation ***/
  semopbuf.sem_flg = 0;

  if(semop (semidgroup, &semopbuf,1) == -1) {
    return (-1);
  }

  return (0);
}

int v (int semidgroup, int donut_type) {
  struct sembuf semopbuf;

  semopbuf.sem_num = donut_type;
  semopbuf.sem_op = (+1);     /*** +1 is a V operation ***/
  semopbuf.sem_flg = 0;

  if(semop(semidgroup, &semopbuf,1) == -1) {
    return (-1);
  }

  return (0);
}

int semsetall (int semgroup, int number_in_group, int set_all_value)
{
  int i, j, k;
  union semun     /*** need this union ***/
  {
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
  } sem_ctl_un;

  // previously declared:  union semun sem_ctl_un;
  sem_ctl_un.val = set_all_value;  /*** for command SETVAL ***/
  for (i = 0; i < number_in_group; i++) {
    if(semctl(semgroup, i, SETVAL, sem_ctl_un) == -1) {
      return (-1);
    }
  }

  return (0);
}
