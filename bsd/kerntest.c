/*========================================================================**
**  Demonstrates Dave's example system calls in action                    **
**========================================================================*/

#include <sys/syscall.h>

int main()
{
  // We can invoke the syscalls by number:

  int pid = syscall( 289 );
  printf( "The value returned from the syscall was %d\n", pid );
  syscall( 290, "This is a test...", 123 );

  // We can invoke the syscalls by symbolic name:

  pid = syscall( SYS_hello );
  printf( "The value returned from the syscall was %d\n", pid );
  syscall( SYS_showargs, "This is a another test...", 456 );
  return (0);
}
