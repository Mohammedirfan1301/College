/*
 *  Jason Downing
 *  A4 Header File
 *  11/8/2016
 *
 *  This is from Prof. Moloney's help file at the following URL:
 *  http://www.cs.uml.edu/~bill/cs308/call_help_assign4.txt
 *
 */
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define   NUMFLAVORS      4
#define   NUMSLOTS       26500
#define   NUMCONSUMERS    5
#define   NUMPRODUCERS    5

struct  donut_ring {
  int   flavor [NUMFLAVORS] [NUMSLOTS];
  int   outptr [NUMFLAVORS];
  int   in_ptr [NUMFLAVORS];
  int   serial [NUMFLAVORS];
  int   spaces [NUMFLAVORS];
  int   donuts [NUMFLAVORS];
};

/**********************************************************************/
/* SIGNAL WAITER, PRODUCER AND CONSUMER THREAD FUNCTIONS              */
/**********************************************************************/
  void  *sig_waiter  ( void *arg );
  void  *producer    ( void *arg );
  void  *consumer    ( void *arg) ;
  void   sig_handler ( int );
