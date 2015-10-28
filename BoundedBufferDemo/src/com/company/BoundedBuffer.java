package com.company;
/**
 * Created by Denzel on 9/28/2015.
 */
public class BoundedBuffer {
    private final Item[] buffer;
    private final int N;
    private int in = 0;
    private int out = 0;
    private int count;

    public BoundedBuffer (int size){
        N = size + 1;
        buffer = new Item[N];
    }

    public void insert(Producer p, Item item){
        synchronized (this) {
            while ((in + 1) % N == out) {
                try {
                    this.wait();
                } catch (InterruptedException e) {
                    System.out.println("---------------------------------------------------------------------");
                }
            }

            try {
                System.out.println("Producer " + p.unique_id + " is inserting: " + item + "\t" + "( " + (count + 1) + " of " + (N - 1) + " full)");
                buffer[in] = item;
                in = (in + 1) % N;
                ++count;

                //notFinished = true if items
                // !notFinished = true if no items
                if(!p.notFinished()){
                    Thread.currentThread().sleep(p.randomSleep);
                }
            }catch(InterruptedException e){
                System.out.println("Producer " + p.unique_id + " waiting to insert: " + p.randomQuota);
                System.out.println("Producer " + p.unique_id + " for: " + p.randomSleep + "ms");
                this.notifyAll();
            }

        }
    }


    public void consume(Consumer c) {
        synchronized (this) {
            //System.out.println("Consumer " + c.unique_id + " acquired the lock.");
            while ((in == out)) {
                try {
                    System.out.println("Consumer " + c.unique_id + " waiting to remove an item.");
                    this.wait();
                } catch (InterruptedException e) {
                    System.out.println("---------------------------------------------------------------------");
                }
            }

            try {
                System.out.println("Consumer " + c.unique_id + " is consuming: " + buffer[out] + "\t" + "( " + (count - 1) + " of " + (N - 1) + " full)");
                buffer[out] = null;
                this.notifyAll();
                out = (out + 1) % N;
                --count;
                if(!c.notFinished()){
                    Thread.currentThread().sleep(c.randomSleep);
                }
            } catch (InterruptedException e) {
                System.out.println("Consumer " + c.unique_id + " waiting to consume: " + c.randomQuota);
                System.out.println("Consumer " + c.unique_id + " for: " + c.randomSleep + "ms");
                this.notifyAll();
            }
        }
    }


    public int sizeOf(){
       return buffer.length;
    }

    public String toString() {
        String message = "[ ";
        for(int i =0;i<N;i++){

            message += buffer[i] + ", ";
        }
        message += " ]";
        System.out.println(message);
        return message;
    }

}