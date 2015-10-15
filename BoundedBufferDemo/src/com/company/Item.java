package com.company;


/**
 * Created by Denzel on 9/28/2015.
 */
public class Item {
    private int unique_id;
    public static int count = 1;


    public Item() {
        this.unique_id = count;
        count++;
    }

    @Override
    public String toString() {
        String message;
        message = "Item " + String.valueOf(this.unique_id);
        return message;
    }
}