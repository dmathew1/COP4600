#include <stdio.h>

int main(void){

  //create semaphores
  syscall(292,"semaphore1",1);
  syscall(292,"semaphore2",2);
  syscall(292,"semaphore3",3);
  syscall(292,"semaphore4",4);
  fork();
  syscall(293,"semaphore3");
  //call up on semaphores
  //syscall(294);

  //free up semaphores
  //syscall(295);

}
