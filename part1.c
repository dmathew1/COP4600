#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

  pid_t sender,receiver;

  //create pipe
  int fildes[2];
  pipe(fildes);

  //create sender & receiver processes
  receiver = fork();
  if(receiver != 0){
    sender = fork();
  }


  //fildes[1] = write
  //fildes[0] = read

  if(receiver==0){
    printf("I am the receiver: %d\n", getpid());

    //close write buffer
    close(fildes[1]);
    //read contents
    //close read
    //print termination
    //terminate

    exit(0);
  }else if (sender==0){
    printf("I am the sender: %d\n", getpid());

    //close read buffer
    close(fildes[0]);

    //write contents Reverse Alphabet
    for(int i=65;i<91;i++){
      char c = i;
      printf("%c\n",c);

    }
    //close write
    //print termination
    //terminate

    exit(0);
  }

  return 0;
}
