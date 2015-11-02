#include "SEMAPHORE.c"

int main(){
  semaphore_t* t;
  semaphore_t* x;
  t = createSemaphore(3);
  x = createSemaphore(4);
  destroySemaphore(t);
  printf("fuck\n");
}
