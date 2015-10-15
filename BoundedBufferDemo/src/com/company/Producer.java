package com.company;
import java.util.Random;
/**
 * Created by Denzel on 9/28/2015.
 */
public class Producer implements Runnable{
    public int quota;
    public int sleep;
    public int unique_id;
    public static int count = 0;
    public BoundedBuffer bb;

    Random randomQ = new Random();
    public int randomQuota = randomQ.nextInt(5) + 1;
    public int randomSleep = randomQ.nextInt(100) + 10;

    //Constructor
    public Producer(BoundedBuffer bb) {
        this.unique_id = count + 1;
        this.quota = randomQuota;
        this.sleep = randomSleep;
        this.bb = bb;
        count++;
    }

    //Method for producer to create an item to insert into
    public Item produceItem(){
        Item item1 = new Item();
        return item1;
    }

    //Method to check if producer finished job
    public Boolean notFinished(){
        if(quota != 0){
            return true;
        }
        else{
            return false;
        }
    }


    //the insertion process
    public void run() {
        while(Thread.currentThread().isInterrupted()){
            break;
        }
          while (notFinished()) {
              quota--;
              bb.insert(this, produceItem());
              System.out.print("");
          }
        if(!notFinished()){
            this.quota = randomQuota;
            this.sleep = randomSleep;
            System.out.println("Producer " + this.unique_id + " waiting to insert: " + randomQuota);
        }
    }

    @Override
    public String toString() {
        String message;
        message = "Producer " + String.valueOf(this.unique_id);
        return message;
    }
}