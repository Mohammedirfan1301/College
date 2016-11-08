/*
 *  Jason Downing
 *  A4
 *  11/8/2016
 *
 */


/*****************************************************************/
/* INCLUDE FILES, DEFINES AND DECLARATIONS AS SEEN IN CLASS      */
/*        THESE BELONG IN A    .h     FILE                       */
/*****************************************************************/
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>


#define         NUMFLAVORS        4
#define         NUMSLOTS          50
#define         NUMCONSUMERS      5
#define   NUMPRODUCERS    5


struct  donut_ring {
  int       flavor [NUMFLAVORS] [NUMSLOTS];
  int       outptr [NUMFLAVORS];
  int   in_ptr [NUMFLAVORS];
  int   serial [NUMFLAVORS];
  int   spaces [NUMFLAVORS];
  int   donuts [NUMFLAVORS];
};

/**********************************************************************/
/* SIGNAL WAITER, PRODUCER AND CONSUMER THREAD FUNCTIONS              */
/**********************************************************************/

  void  *sig_waiter ( void *arg );
  void  *producer   ( void *arg );
  void  *consumer ( void *arg) ;
  void    sig_handler ( int );
