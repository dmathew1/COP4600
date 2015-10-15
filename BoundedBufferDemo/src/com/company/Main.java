package com.company;

public class Main {

    public static void main(String[] args) {
	// write your code here
        BoundedBuffer bb = new BoundedBuffer(10);


        Thread p1 = new Thread(new Producer(bb));
        Thread p2 = new Thread(new Producer(bb));
        Thread p3 = new Thread(new Producer(bb));

        Thread c1 = new Thread(new Consumer(bb, 20));
        Thread c2 = new Thread(new Consumer(bb, 20));
        Thread c3 = new Thread(new Consumer(bb, 20));
        Thread c4 = new Thread(new Consumer(bb, 20));

        c1.start();
        c2.start();
        //c3.start();
        //c4.start();

        p1.start();
        p2.start();

        p1.interrupt();
        p2.interrupt();
        //p3.start();





    }
}
