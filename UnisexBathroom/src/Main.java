public class Main {

    public static void main(String[] args) {
	// write your code here
        Bathroom bathroom = new Bathroom(3);

        Thread p1 = new Thread(new Person(bathroom));
        Thread p2 = new Thread(new Person(bathroom));
        Thread p3 = new Thread(new Person(bathroom));
        Thread p4 = new Thread(new Person(bathroom));
        Thread p5 = new Thread(new Person(bathroom));
        Thread p6 = new Thread(new Person(bathroom));

        p1.start();
        p2.start();


        p3.start();
        //p4.start();
        //p5.start();
        //p6.start();
    }
}
