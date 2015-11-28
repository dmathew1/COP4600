#include <stdio.h>

int main(void){

  //create semaphores
  syscall(292,"semaphore1",3);
  syscall(292,"semaphore2",2);
  // syscall(292,"semaphore3",1);

  //call down on semaphores
  syscall(293,"semaphore2");

  //call up on semaphores
  //syscall(294);

  //free up semaphores
  //syscall(295);

}
