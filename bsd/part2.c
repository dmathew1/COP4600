/* SIMPLEQ_demo.c
**
** Demonstrates how to use the BSD SIMPLEQ macros; the comments try to explain
** some of the more confusing terminology and behaviors
**
** By Dave Small
** For COP 4600
** 200607.04 - v1.0: created
*/

#include <stdio.h>
#include <sys/queue.h>

int main( void )
{
  int i;

  // Non-standard terminology alert #1: "head" != first entry in the Q
  // rather, "head" is a struct that represents the ENTIRE Q
  // (it contains pointers to the first and last entries in the Q)
  SIMPLEQ_HEAD(queuehead, entry) head = SIMPLEQ_HEAD_INITIALIZER(head);

  // Non-standard terminology alert #2: "entry" doesn't refer to a
  // piece of data stored in the queue; rather, it means the node
  // holding the data that is inserted in the Q's linked list
  struct entry
  {
    int i;                       // data
    SIMPLEQ_ENTRY(entry) next;   // link to next entry
  } *np;

  //----------------------------------------------------------------
  // Enqueue some data

  for ( i = 1; i < 5; ++i )
  {
    // create an "entry" and store the data in it
    np = (struct entry *) malloc( sizeof( struct entry ) );
    np->i = i;  // store the data in the entry

    // enqueue the entry
    SIMPLEQ_INSERT_TAIL( &head, np, next );
  }

  //----------------------------------------------------------------
  // Two ways to non-destructively traverse the Q

  // explicitly controlled forward traversal
  printf( "Traverse the Q explicitly\n" );
  for ( np = SIMPLEQ_FIRST(&head); np != NULL; np = SIMPLEQ_NEXT(np, next) )
    printf( "   entry %d\n", np->i );

  // Alternatively, use the a macro to do the traversal
  printf( "Traverse the implicitly\n" );
  SIMPLEQ_FOREACH( np, &head, next )
    printf( "   entry %d\n", np->i );


  //----------------------------------------------------------------
  // Dequeue the entries

  // The macro SIMPLEQ_REMOVE_HEAD is weird: in addition to passing
  // the "head" you must also pass it a pointer to the first entry in
  // the Q!  (I don't know why they didn't have retrieved the first
  // entry from the "head." I assume the authors had a good reason.

  while ( ! SIMPLEQ_EMPTY( &head ) )
  {
    SIMPLEQ_REMOVE_HEAD( &head, (np = SIMPLEQ_FIRST(&head)), next );
    printf( "Removed entry %d\n", np->i );

    // free the allocated entry
    free( np );

    // show the remove was successful
    printf( "Remaining Q contents:\n" );
    SIMPLEQ_FOREACH( np, &head, next )
      printf( "   entry %d\n", np->i );
  }

  /* The preceeding could also have been written:

  while ( (np = SIMPLEQ_FIRST(&head)) != NULL )
  {
    SIMPLEQ_REMOVE_HEAD( &head, np, next );
    printf( "Removed entry %d\n", np->i );

    // free the allocated entry
    free( np );

    // show the remove was successful
    printf( "Remaining Q contents:\n" );
    SIMPLEQ_FOREACH( np, &head, next )
      printf( "   entry %d\n", np->i );
  }
  */

  return 0;
}
