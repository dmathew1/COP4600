/**
 * Created by Denzel on 10/14/2015.
 */
public class Person {
    int gender;
    int boy = 0;
    int girl = 1;
    Bathroom bathroom;


    public Person(Bathroom bathroom){
        this.bathroom = bathroom;
    }

    public void createMale(){
        this.gender = 0; //Male = 0
    }
    public void createFemale(){
        this.gender = 1; //Female = 1
    }
}
