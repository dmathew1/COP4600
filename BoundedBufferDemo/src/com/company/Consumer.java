package com.company;

import java.util.Random;

/**
 * Created by Denzel on 9/28/2015.
 */
public class Consumer implements Runnable{
    public int quota;
    public int unique_id;
    public int sleep;
    public static int count = 0;
    public BoundedBuffer bb;


    Random randomQ = new Random();
    public int randomQuota = randomQ.nextInt(5) + 1;
    public int randomSleep = randomQ.nextInt(100) + 10;

    //Constructor
    public Consumer(BoundedBuffer bb, int quota) {
        this.unique_id = count + 1;
        this.quota = randomQuota;
        this.sleep = randomSleep;
        this.bb = bb;
        count++;
    }


    //Method to check if consumer finished job
    public Boolean notFinished(){
        if(quota != 0){
            return true;
        }
        else{
            System.out.println("---------------------------------------------------------------------");
            return false;
        }
    }

    //the deletion process
    public void run() {
            while (notFinished()) {
                bb.consume(this);
                quota--;
            }
    }


    @Override
    public String toString() {
        String message;
        message = "Consumer " + String.valueOf(this.unique_id);
        return message;
    }
}