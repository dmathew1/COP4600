#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


pid_t sender,receiver;
int i;
char c = 90;
int fildes[2];
int isSender,isReceiver;
size_t readVal;
char reader;

int main(){
  printf("Receiever before fork: %d\n",receiver);
  printf("Sender before fork: %d\n",sender);



  //create pipe
  pipe(fildes);

//Forks out the receiver and the sender

  receiver = fork();
  if(receiver==0){
    isReceiver=1;
  }
  if(receiver != 0){
    sender = fork();
    if(sender==0){
      isSender = 1;
    }
  }

if(isSender == 0 && isReceiver == 0){
  close(fildes[1]);
  close(fildes[0]);
  sleep(30);
  printf("FUCK YOU BITCHES: %d", getpid());
}

  if(isReceiver==1){

    //close write
    close(fildes[1]);

    //read from pipe
    while(reader != 65){
      read(fildes[0],&reader,1);
      write(STDOUT_FILENO,&reader,1);
    }

    //close read
    close(fildes[0]);

    //print termination
    printf("\nFUCK YOUUUUUUU RECEIVER GOING OUT: %d", getpid());

    //terminate
    exit(0);

  }else if (isSender==1){

    //close read
    close(fildes[0]);

    //write to pipe
    for(i=90;i>64;--i){
      write(fildes[1],&i,1);
      sleep(1);
    }

    //close write
    close(fildes[1]);

    //print termination
    printf("\nFUCK YOU SENDER: %d", getpid());
    fflush(stdout);

    //terminate
    exit(0);

  }

  return 0;
}
