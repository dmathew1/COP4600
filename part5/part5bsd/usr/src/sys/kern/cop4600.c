
/*	$OpenBSD: cop4600.c,v 1.00 2003/07/12 01:33:27 dts Exp $	*/

#include <sys/param.h>
#include <sys/acct.h>
#include <sys/systm.h>
#include <sys/ucred.h>
#include <sys/proc.h>
#include <sys/timeb.h>
#include <sys/times.h>
#include <sys/malloc.h>
#include <sys/filedesc.h>
#include <sys/pool.h>
#include <sys/semaphore.h>
#include <lib/libkern/libkern.h>

#include <sys/mount.h>
#include <sys/syscallargs.h>

/*========================================================================**
**  Dave's example system calls                                           **
**========================================================================*/

/*
** hello() prints to the tty a hello message and returns the process id
*/

int
sys_hello( struct proc *p, void *v, register_t *retval )
{
  uprintf( "\nHello, process %d!\n", p->p_pid );
  *retval = p->p_pid;

  return (0);
}

/*
** showargs() demonstrates passing arguments to the kernel
*/

#define MAX_STR_LENGTH  1024

int
sys_showargs( struct proc *p, void *v, register_t *retval )
{
  /* The arguments are passed in a structure defined as:
  **
  **  struct sys_showargs_args
  **  {
  **      syscallarg(char *) str;
  **      syscallarg(int)    val;
  **  }
  */

  struct sys_showargs_args *uap = v;

  char kstr[MAX_STR_LENGTH+1]; /* will hold kernal-space copy of uap->str */
  int err = 0;
  int size = 0;

  /* copy the user-space arg string to kernal-space */

  err = copyinstr( SCARG(uap, str), &kstr, MAX_STR_LENGTH, &size );
  if (err == EFAULT)
    return( err );

  uprintf( "The argument string is \"%s\"\n", kstr );
  uprintf( "The argument integer is %d\n", SCARG(uap, val) );
  *retval = 0;

  return (0);
}

/*========================================================================**
**  <Denzel>'s COP4600 2004C system calls                        **
**========================================================================*/

int x;
int offset;
char *c;
int numquads;
int finalquad;
int count,temp,temp1,temp2,i;
int lkey,nkey;
char text[MAX_STR_LENGTH];
int len;

int sys_cipher(struct proc *p, void *v, register_t *retval){

  struct sys_cipher_args *uap = v;
  // uprintf("v has shit: %s", v);

   /* will hold kernal-space copy of uap->str */
  int err = 0;
  int size = 0;
  //uprintf("v has shit: %s",v);


  /* copy the user-space arg string to kernal-space */
  err = copyinstr( SCARG(uap, text), &text, MAX_STR_LENGTH+1, &size );
  uprintf("text has : %s \n",text);

  len = strlen(text);
 // uprintf("len: ", len);
 if(len >= 1024){
   len = 1024;
   size = 1025;
   text[MAX_STR_LENGTH] = '\0';
   }

  if (err == EFAULT)
    return( err );
  else if (err == ENAMETOOLONG)
    text[MAX_STR_LENGTH] = '\0';

  lkey = SCARG(uap,lkey);
  nkey = SCARG(uap,nkey);


   //Substitution Cipher
   //loop through all the contents
   for(c=text; *c != '\0'; c++){
    //check to see if the letter is an uppercase: ASCII
    if(*c >= 'A' && *c <= 'Z'){
      x = ((*c - 'A' + (lkey % 26) + 26) % 26);
      offset = ((lkey < 0) && (lkey & 0x1)) ?
               (((x - 'A') & 0x1) ? 'A' : 'a' ) :
               (((x - 'A') & 0x1) ? 'a' : 'A' );
      *c = x + offset;
    }
    //check to see if the letter is an lowercase: ASCII
    else if(*c >= 'a' && *c <= 'z'){
      x = ((*c - 'a' + (lkey % 26) + 26) % 26);
       offset = ((lkey < 0) && (lkey & 0x1)) ?
                (((x - 'a') & 0x1) ? 'a' : 'A' ) :
                (((x - 'a') & 0x1) ? 'A' : 'a' );
       *c = x + offset;
    }
    //check to see if the letter is a digit: ASCII
    else if(*c >= 0 && *c <= 9){
      *c = ((*c - '0' + (nkey % 10) + 10) % 10) + '0';
    }
    //default
    else{
      *c = *c;
    }
   }


   //Transposition Cipher

   //gets the number of quads
   numquads = len/4;
   //gets the final quads number
   finalquad = len%4;

   //start off at the first element of the array
   count = 0;

   //perfect quad; swap the 1st and 2nd with the 3rd and 4th
   for(i=0;i<numquads;i++){

       //store the first and second element
       temp = text[count];
       temp1 = text[count+1];

       //swap the 3rd and 4th element into the 1st and 2nd
       text[count] = text[count+2];
       text[count+1] = text[count+3];

       //swap the stored first and second into the 3rd and 4th
       text[count+2] = temp;
       text[count+3] = temp1;

       count += 4;
   }

   //handle each case for the different quad sizes
   if(finalquad == 1){
     text[len] = text[len];
   }
   else if(finalquad == 2){
     temp = text[len-1]; //last element
     temp1 = text[len-2]; //second last element

     text[len-1] = temp1;
     text[len-2] = temp;
   }
   else if(finalquad == 3){
     temp = text[len-1]; //last element
     temp2 = text[len-3]; //third last element


     text[len-1] = temp2; //insert the last element into the first
     text[len-3] = temp; //insert the first element into the last
   }

   err = copyoutstr( &text, SCARG(uap, text), MAX_STR_LENGTH+1, &size );
    if (err == EFAULT)
    return( err );

  *retval = len;
  return (0);
}

/*========================================================================**
**  <Denzel> Part 5 Sys_calls                      **
**========================================================================*/



int
allocate_semaphore( struct proc *p, void *v, register_t *retval )
{

  //Check to see if the list already has the semaphore name

  semaphore_t *sem;

  char kstr[MAX_NAME_LENGTH+1];
  int size = 0;
  int err = 0;

  //gets the arguments for allocate_semaphore as a struct
  struct allocate_semaphore_args *uap = v;
  err = copyinstr( SCARG(uap, name), &kstr, MAX_NAME_LENGTH+1, &size );

  for ( np = LIST_FIRST(&p->createdSemaphore); np != NULL; np = LIST_NEXT(np, next) ){
    if(strcmp(np->semaphore.name, kstr)==0){
      uprintf("This semaphore already exists.\n");
      break;
    }
  }

  //Allocates semaphore and its attributes
  sem = (semaphore_t *) malloc( sizeof(  semaphore_t ),M_SUBPROC,M_NOWAIT );
  sem->count=SCARG(uap,initial_count);
  sem->name = (char*)malloc((unsigned long)32,M_SUBPROC,M_NOWAIT);
  strncpy(sem->name,kstr,MAX_NAME_LENGTH);
  sem->ID = p->p_pid;

  //Allocate Mutex Lock
  sem->mutex = (struct lock*)malloc(sizeof(struct lock),M_SUBPROC,M_NOWAIT);
  lockinit(sem->mutex, 0, "Mutex is locked", p->p_priority, LK_NOWAIT);

  //Allocate Down Lock
  sem->down = (struct lock*)malloc(sizeof(struct lock),M_SUBPROC,M_NOWAIT);
  lockinit(sem->down, 0, "Down is locked", p->p_priority, LK_NOWAIT);

  //Allocate Up Lock
  sem->up = (struct lock*)malloc(sizeof(struct lock),M_SUBPROC,M_NOWAIT);
  lockinit(sem->up, 0, "Up is locked", p->p_priority, LK_NOWAIT);

  //allocates memory and assigns the semaphore to it
  np = (struct entry *) malloc( (unsigned long)sizeof( struct entry ),M_SUBPROC,M_NOWAIT );
  np->semaphore = *sem;
  LIST_INSERT_HEAD(&p->createdSemaphore, np, next);

  *retval = p->p_pid;
  return (0);
}

int
down_semaphore( struct proc *p, void *v, register_t *retval )
{
  char kstr1[MAX_NAME_LENGTH+1];
  int size1 = 0;
  int err = 0;
  struct proc *head = p;

  //pass arguments down
  struct down_semaphore_args *uap = v;
  err = copyinstr( SCARG(uap, name), &kstr1, MAX_STR_LENGTH+1, &size1 );

  // Find the semaphore I want
  while(head != NULL){
    for ( np = LIST_FIRST(&p->createdSemaphore); np != NULL; np = LIST_NEXT(np, next) ){
      if(strcmp(np->semaphore.name, kstr1)==0){
          if(np->semaphore.count < 0){
            uprintf("Process ID: %lu Semaphore %s should be sleeping\n",np->semaphore.ID,np->semaphore.name);
            //Sleep the process



            return(0);
          }else{
            //Jerk off

            //Lock
            lockmgr(np->semaphore.mutex,LK_EXCLUSIVE,np->semaphore.slock,curproc);
            uprintf("Process ID: %lu Semaphore %s is decrementing\n",np->semaphore.ID,np->semaphore.name);
            --np->semaphore.count;
            lockmgr(np->semaphore.mutex,LK_RELEASE,np->semaphore.slock,curproc);
            return(0);

            }
          }
        }
        head = head->p_pptr;
      }

  *retval = p->p_pid;
  return (0);
}

int
up_semaphore( struct proc *p, void *v, register_t *retval )
{
//
//   uprintf( "\nI am from the up semaphore section\n");
//   *retval = p->p_pid;
//
//   return (0);
// }
// int
// free_semaphore( struct proc *p, void *v, register_t *retval )
// {
//   uprintf( "\nI am from the free semaphore section\n");
//   *retval = p->p_pid;
//
  return (0);
}

int
free_semaphore( struct proc *p, void *v, register_t *retval )
{
//
//   uprintf( "\nI am from the up semaphore section\n");
//   *retval = p->p_pid;
//
//   return (0);
// }
// int
// free_semaphore( struct proc *p, void *v, register_t *retval )
// {
//   uprintf( "\nI am from the free semaphore section\n");
//   *retval = p->p_pid;
//
  return (0);
}
