
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "SEMAPHORE.c"

#define BARBERS	2
#define CUSTOMERS 6
#define CHAIRS 5

semaphore_t *barberSem;
semaphore_t *customerSem;
semaphore_t *mutex;
int waiting = 0;


void * receive_cut(void *customer_id){
  usleep(10000);
  printf("Customer %d left with stylish haircut\n",customer_id+1);
  fflush(stdout);
}

void * cut_hair(void *barber_id){
  usleep(10000);
  printf("Barber %d is cutting hair.\n",barber_id+1);
  fflush(stdout);
}

void * barber(void *barber_id)
{
  printf("Barber %d created\n",barber_id+1);
  while(1){
    printf("Barber %d is sleeping\n", barber_id+1 );
    down(customerSem);
    printf("Barber %d wakes up\n",barber_id+1);
    down(mutex);
    --waiting;
    up(barberSem);
    printf("Barber %d beckons customer to chair\n",barber_id+1);
    up(mutex);
    cut_hair(barber_id);
  }
}

void * customer(void *customer_id){
  printf("Customer %d walks into the barber shop\n",customer_id+1);
  down(mutex);
  if(waiting < CHAIRS){
    ++waiting;
    printf("Customer %d wakes up barber\n",customer_id+1);
    up(customerSem);
    up(mutex);
    printf("Customer %d waits in chair %d\n",customer_id+1,customer_id+1);
    down(barberSem);
    printf("Customer %d sits in barber chair\n",customer_id+1);
    receive_cut(customer_id);
  }else{
    up(mutex);
  }
  if(waiting == CHAIRS){
    printf("Customer %d is leaving because no chairs.\n", customer_id+1 );
  }
  pthread_exit(NULL);
}


int main( void )
{

  int i;
  pthread_t barberThreads[BARBERS];
  pthread_t customerThreads[CUSTOMERS];

  barberSem = createSemaphore(0);
  customerSem = createSemaphore(0);
  mutex = createSemaphore(1);
  setbuf(stdout,NULL);


  // *************** This creates the Barber threads ****************** //
  for ( i = 0; i < BARBERS; ++i )
  {
    // make the threads
    if( pthread_create( &barberThreads[i], NULL, barber, (void *)i) )
    {
      printf( "ERROR: creating thread %d\n", i );
      fflush(stdout);
      exit(-1);
    }
  }

  // *************** This creates the Customer threads *************** //
  for ( i = 0; i < CUSTOMERS; ++i )
  {
    // make the threads
    if( pthread_create( &customerThreads[i], NULL, customer, (void *)i) )
    {
      printf( "ERROR: creating thread %d\n", i );
      fflush(stdout);
      exit(-1);
    }
  }

  // **************** This destroys the Customer Threads *************** //
  for ( i = 0; i < CUSTOMERS; ++i )
  {
    if ( pthread_join( customerThreads[i], NULL) )
    {
      printf("ERROR: joining thread %d\n", i );
      fflush(stdout);
    }
  }

  // ***************** This destroys the Barber threads *************** //
  sleep(1);
  for ( i = 0; i < BARBERS; ++i )
  {
    if ( pthread_cancel( barberThreads[i] ) )
    {
      printf("ERROR: Barber joining thread %d\n", i );
      fflush(stdout);
    }
  }

  destroySemaphore(barberSem);
  destroySemaphore(customerSem);
  pthread_exit(NULL);
}
