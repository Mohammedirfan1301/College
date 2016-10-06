/*
    This is a Utility C File for A3
*/

/**********************************************************/
/***  a utility  .c  file should include the following  ***/
/***                     semaphore untilities:          ***/


int   p (int semidgroup, int donut_type)
{
  struct sembuf semopbuf;  /*** struct in <sys/sem.h> ***/

/** begin syscall semop comment for semaphore operations

     #include <sys/types.h>
     #include <sys/ipc.h>
     #include <sys/sem.h>

int semop (int semid, struct sembuf *sops, int nsops);
struct sembuf {
  short sem_num;  /* semaphore index
  short sem_op;   /* semaphore operation
  short sem_flg;    /* operation flags
};

************* end syscall semop comment ******/

  semopbuf.sem_num = donut_type;
        semopbuf.sem_op = (-1);     /*** -1 is a P operation ***/
  semopbuf.sem_flg = 0;

  if(semop (semidgroup, &semopbuf,1) == -1){
    return (-1);
  }
  return (0);
}


int   v (int semidgroup, int donut_type)
{
  struct sembuf semopbuf;

  semopbuf.sem_num = donut_type;
        semopbuf.sem_op = (+1);     /*** +1 is a V operation ***/
  semopbuf.sem_flg = 0;

  if(semop(semidgroup, &semopbuf,1) == -1){
    return (-1);
  }
  return (0);
}



int   semsetall (int semgroup, int number_in_group,
            int set_all_value)
{
  int i, j, k;
  union semun     /*** need this union ***/
  {
       int val;
       struct semid_ds *buf;
       unsigned short int *array;
    }sem_ctl_un;

/**  begin syscall semctl comment for semaphore control

     #include <sys/types.h>
     #include <sys/ipc.h>
     #include <sys/sem.h>
     int semctl (int semid, int semnum, int cmd, ...);

      The fourth argument is optional and depends on the
        operation requested.  If required, it is of the type
        union semun, which the application program
      must explicitly declare as follows:

   The user should define a union like the following to use for
   command specific values for `semctl' in the fourth argument
   position ... when used this argument is needed, the union
   is passed by value and the semctl call selects the appropriate
   member (based on the command argument)

   union semun
   {
     int val;                    <= value for SETVAL
     struct semid_ds *buf;       <= buffer for IPC_STAT & IPC_SET
     unsigned short int *array;  <= array for GETALL & SETALL
   };

   Previous versions of <sys/sem.h> used to define this union but
   this is incorrect.  One can test the macro _SEM_SEMUN_UNDEFINED
   to see whether one must define the union or not, but I will
   define it myself for this example function (semsetall)

************* end syscall semctl comment ******/


  // previously declared:  union semun sem_ctl_un;
  sem_ctl_un.val = set_all_value;  /*** for command SETVAL ***/
  for (i = 0; i < number_in_group; i++){
    if(semctl(semgroup, i, SETVAL, sem_ctl_un) == -1){
    return (-1);
    }
  }
  return (0);
}
