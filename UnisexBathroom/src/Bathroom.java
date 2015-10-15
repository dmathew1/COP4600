import java.util.ArrayList;
import java.util.concurrent.Semaphore;

/**
 * Created by Denzel on 10/14/2015.
 */
class Bathroom {

    Semaphore semaphore;
    public int bathroomSize;
    ArrayList<Integer> bathroomWait =  new ArrayList<Integer>();
    ArrayList<Integer> bathroomEnter;

    //Construct initial size of the bathroom
    //as well as setting the semaphore limit
    public  Bathroom(int size){
        this.semaphore = new Semaphore(size);
        this.bathroomEnter = new ArrayList<>(size);
    }




    public void enter_bathroom(Person person) {

        //check to see if girl is there in the genderArray
        synchronized(this){
            System.out.println(person.gender + " is entering the bathroom.");
            try {
                //if the array contains a girl waiting
                if (person.genderArray.contains(1)) {
                    Thread.currentThread().wait();
                }
            } catch (InterruptedException e) {
                System.out.println("Girl has higher priority");
            }
        }

        bathroomEnter.add(person.gender);
    }

    public void exit_bathroom(Person person){
        System.out.println(person.gender + " is leaving the bathroom.");
        person.genderArray.remove(person.genderArray.size()-1);
    }



}
