/*
 *  Jason Downing
 *  A4 C File
 *  11/8/2016
 *
 *  This is from Prof. Moloney's help file at the following URL:
 *  http://www.cs.uml.edu/~bill/cs308/call_help_assign4.txt
 *
 */
#include "pc_threads.h"

// Global Variables
struct donut_ring   shared_ring;
pthread_mutex_t   prod [NUMFLAVORS];
pthread_mutex_t   cons [NUMFLAVORS];
pthread_cond_t    prod_cond [NUMFLAVORS];
pthread_cond_t    cons_cond [NUMFLAVORS];
pthread_t         thread_id [NUMCONSUMERS + 1], sig_wait_id;

int threadNum = 0;    // Thread counter

int  main ( int argc, char *argv[] ) {
  int                 i, j, k, nsigs;
  int                 arg_array[NUMCONSUMERS];
  int sigs[]        = { SIGBUS, SIGSEGV, SIGFPE };
  struct timeval      randtime, first_time, last_time;
  struct sigaction    new_act;
  sigset_t            all_signals;
  pthread_attr_t      thread_attr;
  struct sched_param  sched_struct;

  /**********************************************************************/
  /* INITIAL TIMESTAMP VALUE FOR PERFORMANCE MEASURE                    */
  /**********************************************************************/
  gettimeofday (&first_time, (struct timezone *) 0 );

  for ( i = 0; i < NUMCONSUMERS + 1; i++ ) {
    arg_array [i] = i;  /** SET ARRAY OF ARGUMENT VALUES **/
  }

  /**********************************************************************/
  /* GENERAL PTHREAD MUTEX AND CONDITION INIT AND GLOBAL INIT           */
  /**********************************************************************/
  for ( i = 0; i < NUMFLAVORS; i++ ) {
    pthread_mutex_init ( &prod [i], NULL );
    pthread_mutex_init ( &cons [i], NULL );
    pthread_cond_init ( &prod_cond [i],  NULL );
    pthread_cond_init ( &cons_cond [i],  NULL );
    shared_ring.outptr [i]    = 0;
    shared_ring.in_ptr [i]    = 0;
    shared_ring.serial [i]    = 0;
    shared_ring.spaces [i]    = NUMSLOTS;
    shared_ring.donuts [i]    = 0;
  }

  /**********************************************************************/
  /* SETUP FOR MANAGING THE SIGTERM SIGNAL, BLOCK ALL SIGNALS           */
  /**********************************************************************/
  sigfillset (&all_signals );
  nsigs = sizeof ( sigs ) / sizeof ( int );

  for ( i = 0; i < nsigs; i++ ) {
    sigdelset ( &all_signals, sigs [i] );
  }

  sigprocmask ( SIG_BLOCK, &all_signals, NULL );
  sigfillset (&all_signals );

  for( i = 0; i <  nsigs; i++ ) {
    new_act.sa_handler  = sig_handler;
    new_act.sa_mask   = all_signals;
    new_act.sa_flags  = 0;

    if ( sigaction ( sigs[i], &new_act, NULL ) == -1 ) {
      perror("can't set signals: ");
      exit(1);
    }
  }

  printf ( "just before threads created\n" );

  /*********************************************************************/
  /* CREATE SIGNAL HANDLER THREAD, PRODUCER AND CONSUMERS              */
  /*********************************************************************/
  if ( pthread_create (&sig_wait_id, NULL, sig_waiter, NULL) != 0 ) {
    printf ( "pthread_create failed " );
    exit (3);
  }

  pthread_attr_init ( &thread_attr );
  pthread_attr_setinheritsched ( &thread_attr, PTHREAD_INHERIT_SCHED );

  #ifdef  GLOBAL
    sched_struct.sched_priority = sched_get_priority_max(SCHED_OTHER);
    pthread_attr_setinheritsched ( &thread_attr, PTHREAD_EXPLICIT_SCHED );
    pthread_attr_setschedpolicy ( &thread_attr, SCHED_OTHER );
    pthread_attr_setschedparam ( &thread_attr, &sched_struct );
    pthread_attr_setscope ( &thread_attr, PTHREAD_SCOPE_SYSTEM );
  #endif

  if ( pthread_create (&thread_id[0], &thread_attr, producer, NULL ) != 0 ) {
    printf ( "pthread_create failed " );
    exit (3);
  }

  for ( i = 1; i < NUMCONSUMERS + 1; i++ ) {
    if ( pthread_create ( &thread_id [i], &thread_attr, consumer,
                                          ( void * ) &arg_array [i]) != 0 ) {
      printf ( "pthread_create failed" );
      exit (3);
    }
  }

  printf ( "just after threads created\n" );

/*********************************************************************/
/* WAIT FOR ALL CONSUMERS TO FINISH, SIGNAL WAITER WILL              */
/* NOT FINISH UNLESS A SIGTERM ARRIVES AND WILL THEN EXIT            */
/* THE ENTIRE PROCESS....OTHERWISE MAIN THREAD WILL EXIT             */
/* THE PROCESS WHEN ALL CONSUMERS ARE FINISHED                       */
/*********************************************************************/
  for ( i = 1; i < NUMCONSUMERS + 1; i++ ) {
    pthread_join ( thread_id [i], NULL );
  }

/*****************************************************************/
/* GET FINAL TIMESTAMP, CALCULATE ELAPSED SEC AND USEC           */
/*****************************************************************/
  gettimeofday (&last_time, ( struct timezone * ) 0 );

  if ( ( i = last_time.tv_sec - first_time.tv_sec) == 0 ) {
    j = last_time.tv_usec - first_time.tv_usec;
  }
  else {
    if ( last_time.tv_usec - first_time.tv_usec < 0 ) {
      i--;
      j = 1000000 + ( last_time.tv_usec - first_time.tv_usec );
    }
    else {
      j = last_time.tv_usec - first_time.tv_usec;
    }
  }

  printf ( "Elapsed consumer time is %d sec and %d usec\n", i, j );
  printf ( "\n\n ALL CONSUMERS FINISHED, KILLING  PROCESS\n\n" );
  exit (0);
}

/*********************************************/
/* PRODUCER CODE GOES HERE                   */
/*********************************************/
void  *producer ( void *arg ) {
  int     i, num, k;
  unsigned short  xsub [3];
  struct timeval  randtime;

  // Random numbers
  gettimeofday ( &randtime, ( struct timezone * ) 0 );
  xsub [0] = ( ushort ) randtime.tv_usec;
  xsub [1] = ( ushort ) ( randtime.tv_usec >> 16 );
  xsub [2] = ( ushort ) ( pthread_self() );

  // Infinite loop!
  while (1) {
    num = nrand48(xsub) & 3;            // Get donut
    pthread_mutex_lock( &cons[num] );     // Lock consumer for this flavor

    // Wait for more donuts
    while (shared_ring.spaces[num] == 0) {
      pthread_cond_wait( &prod_cond[num], &prod[num] );
    }

    // Donuts!
    shared_ring.serial[num] = shared_ring.serial[num] + 1;
    shared_ring.flavor[num][shared_ring.in_ptr[num]] = shared_ring.serial[num];
    shared_ring.in_ptr[num] = (shared_ring.in_ptr[num]) + 1 % NUMSLOTS;
    shared_ring.spaces[num] = shared_ring.spaces[num] - 1;

    // Unlock producer & lock consumer
    pthread_mutex_unlock( &cons[num] );
    pthread_mutex_lock( &prod[num] );

    // Next donut
    shared_ring.donuts[num] = shared_ring.donuts[num] + 1;

    // Unlock consumer & signal to consumer that we are complete
    pthread_mutex_unlock( &prod[num] );
    pthread_cond_signal( &cons_cond[num] );
  }

  return NULL;
}


/*********************************************/
/* CONSUMER                                  */
/*********************************************/
void    *consumer ( void *arg ) {
  int i, k, m, y, z, rand_num, id;
  unsigned short xsub[3];

  // Donuts, and donut types
  int donuts[4][12];
  int type, type1, type2, type3, type4;

  // Time variables
  struct timeval randtime;
  struct tm *ptm;
  char sTime[40];
  long ms;

  // Get a 9 letter file name
  char *fName = (char *) malloc(sizeof(char) * 10);
  threadNum++;
  sprintf(fName, "c%d", threadNum);
  FILE *fp = fopen(fName, "w");

  // Random numbers
  id = *(int *) arg;
  gettimeofday(&randtime, (struct timezone *) 0);
  xsub[0] = (ushort) (randtime.tv_usec);
  xsub[1] = (ushort) (randtime.tv_usec >> 16);
  xsub[2] = (ushort) (pthread_self() );

  // Number of donuts we want to collect.
  for (i = 0; i < 200; i++) {
    type1 = 0;
    type2 = 0;    // FOUR DIFFERENT TYPES OF DONUTS!
    type3 = 0;    // PLAIN! JELLY! COCONUT! AND HONEY-DIP!
    type4 = 0;

    // One dozen donuts
    for (m = 0; m < 12; m++) {
      rand_num = nrand48(xsub) & 3;            // Get donut
      pthread_mutex_lock(&cons[rand_num]);     // Lock consumer for this flavor

      // Wait for more donuts
      while (shared_ring.donuts[rand_num] == 0) {
        pthread_cond_wait(&cons_cond[rand_num], &cons[rand_num]);
      }

      // Collect a random type of donut
      type = shared_ring.flavor[rand_num][shared_ring.outptr[rand_num]];

      // Four types of donuts to pick from
      switch (rand_num) {
        case 0: {
          donuts[rand_num][type1] = type;
          type1++;
          break;
        }

        case 1: {
          donuts[rand_num][type2] = type;
          type2++;
          break;
        }

        case 2: {
          donuts[rand_num][type3] = type;
          type3++;
          break;
        }

        case 3: {
          donuts[rand_num][type4] = type;
          type4++;
          break;
        }
      }

      // Reset the outptr if we need to
      if (shared_ring.outptr[rand_num] >= NUMSLOTS) {
          shared_ring.outptr[rand_num] = 0;
      } else {
          shared_ring.outptr[rand_num] = shared_ring.outptr[rand_num] + 1;
      }

      // Decrement count
      shared_ring.donuts[rand_num] = shared_ring.donuts[rand_num] - 1;

      // Lock consumer and unlock producer
      pthread_mutex_unlock(&cons[rand_num]);
      pthread_mutex_lock(&prod[rand_num]);

      // Next space
      shared_ring.spaces[rand_num] = shared_ring.spaces[rand_num] + 1;

      // Unlock producer & signal to producer that we are complete
      pthread_mutex_unlock(&prod[rand_num]);
      pthread_cond_signal(&prod_cond[rand_num]);
    }

    // Only write the first 10 dozen to the file
    if (i < 10) {
      // Time stuff - Format time as hour:minute:seconds
      ptm = localtime(&randtime.tv_sec);
      strftime(sTime, sizeof(sTime), "%H:%M:%S", ptm);    // HH:MM:SS
      long ms = randtime.tv_usec / 1000;

      // Entry in local file
      fprintf(fp, "\nthread #: %d", threadNum);
      fprintf(fp, "\ntime: %s", sTime);
      fprintf(fp, "\ndozen #: %d\n", i + 1);
      fprintf(fp, "Plain\tJelly\tCoconut\tHoney-dip\n");

      // Print donuts
      for (y = 0; y < 12; y++) {
        fprintf(fp, "%d\t%d\t%d\t%d\n",
                donuts[0][y], donuts[1][y], donuts[2][y], donuts[3][y]);
      }

      // Reset donut flavors
      for (y = 0; y < NUMFLAVORS; y++) {
        for (z = 0; z < 12; z++) {
          donuts[y][z] = 0;
        }
      }
    }

    /*****************************************************************/
    /* USING A MICRO-SLEEP AFTER EACH DOZEN WILL ALLOW ANOTHER       */
    /* CONSUMER TO START RUNNING, PROVIDING DESIRED RANDOM BEHVIOR   */
    /*****************************************************************/
    usleep(1000); /* sleep 1 ms */
  }

  return NULL;
}


/***********************************************************/
/* PTHREAD ASYNCH SIGNAL HANDLER ROUTINE...                */
/***********************************************************/
void    *sig_waiter ( void *arg ) {
  int       signo;
  sigset_t  sigterm_signal;

  sigemptyset ( &sigterm_signal );
  sigaddset   ( &sigterm_signal, SIGTERM );
  sigaddset   ( &sigterm_signal, SIGINT );

  if ( sigwait ( &sigterm_signal, & signo)  != 0 ) {
    printf ( "\n  sigwait() failed, exiting \n");
    exit (2);
  }

  printf ( "process going down on SIGNAL (number %d)\n\n", signo );
  exit (1);
  return NULL;
}


/**********************************************************/
/* PTHREAD SYNCH SIGNAL HANDLER ROUTINE...                */
/**********************************************************/
void  sig_handler ( int sig ) {
  int   i, thread_index;
  pthread_t signaled_thread_id;

  signaled_thread_id = pthread_self ( );

  for ( i = 0; i < (NUMCONSUMERS + 1 ); i++) {
    if ( signaled_thread_id == thread_id [i] )  {
      thread_index = i;
      break;
    }
  }

  printf ( "\nThread %d took signal # %d, PROCESS HALT\n", thread_index, sig );
  exit (1);
}
