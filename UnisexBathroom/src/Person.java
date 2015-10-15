import java.util.ArrayList;
import java.util.Random;

/**
 * Created by Denzel on 10/14/2015.
 */
class Person implements Runnable {
    int gender;
    int boy = 0;
    int girl = 1;
    int bathroomTime;
    int waitTime;
    Bathroom bathroom;

    //Shared gender queue
    public static ArrayList<Integer> genderArray = new ArrayList<>(3);
    public static int genderArrayCount = 0;

    Random random = new Random();


    public Person(Bathroom bathroom){
        this.bathroom = bathroom;
        this.gender = Math.abs(random.nextInt()%2);
        this.bathroomTime = random.nextInt(5000);
        this.waitTime = random.nextInt(1000);
    }

    public void addQueue(){
        this.genderArray.add(gender);
    }



    public void run() {
        try{
            Thread.sleep(waitTime);
        }catch(InterruptedException e){
            System.out.println("Welp");
        }
        this.addQueue();
        bathroom.enter_bathroom(this);
        bathroom.exit_bathroom(this);
    }
}
