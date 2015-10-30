#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//array to be converted to pipe
int fd [2];


//pid's for receiver and sender
pid_t receiver, sender;

//status flags for if succesful receiver/sender forks
int isSender, isReceiver,i;

//a buffer reader
char reader;

int main(){

  //this converts the array to a pipe
  pipe(fd);

  //forking the receiver
  receiver = fork();

  //if receiver fork was succesful, set status flag
  if(receiver == 0){
    isReceiver = 1;
  }else if(receiver == -1){
    perror("fork");
    exit(1);
  }

  //making the parent fork to sender now
  if(receiver != 0){
    sender = fork();
    //if the sender fork is sucessful, set status flag
    if(sender == 0){
      isSender = 1;
    }else if(sender == -1){
      perror("fork");
      exit(1);
    }
  }

  //If the isSender and isReceiver flags are both 0 then this is the parent
  if(isSender == 0 && isReceiver == 0){
    //close both pipes
    close(fd[0]);
    close(fd[1]);
    sleep(30);
    printf("Parent process: %d is terminating.\n", getpid());
  }


  //Receiver process
  if(isReceiver == 1){

    //close write end of the pipe
    close(fd[1]);

    //read from the pipe
    while(reader != 65){
      read(fd[0],&reader,1);
      write(STDOUT_FILENO,&reader,1);
    }

    //close read end of the pipe
    close(fd[0]);

    //print termination method
    printf("\nReceiver: %d is terminating.\n",getpid());

    //terminate
    exit(0);

  } else if(isSender == 1){

    //close read end of the pipe
    close(fd[0]);


    //write to the pipe
    for(i=90;i>64;--i){
      write(fd[1],&i,1);

      sleep(1);
    }

    //close write end of the pipe
    close(fd[1]);

    //print termination message
    printf("Sender: %d is terminating.\n",getpid());

    //terminate
    exit(0);
  }

return 0;
}
