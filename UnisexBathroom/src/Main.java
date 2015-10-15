public class Main {

    public static void main(String[] args) {
	// write your code here
        Bathroom bathroom = new Bathroom();

        Person p1 = new Person(bathroom);
        p1.createFemale();
        System.out.println(p1.gender);


    }
}
