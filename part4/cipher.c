#include <stdio.h>
#include <string.h>

int x;
int offset;
char *c;
int numquads;
int finalquad;
int count,temp,temp1,temp2,i,j,i1,j1;

int cipher(char *text, int lkey, int nkey){

  //gets the length of the string
  size_t len = strlen(text);

   //Substitution Cipher
   //loop through all the contents
   for(c=text; *c != '\0'; c++){
    //check to see if the letter is an uppercase: ASCII
    if(*c >= 'A' && *c <= 'Z'){
      x = ((*c - 'A' + (lkey % 26) + 26) % 26);
      offset = ((lkey < 0) && (lkey & 0x1)) ?
               (((x - 'A') & 0x1) ? 'A' : 'a' ) :
               (((x - 'A') & 0x1) ? 'a' : 'A' );
      *c = x + offset;
    }
    //check to see if the letter is an lowercase: ASCII
    else if(*c >= 'a' && *c <= 'z'){
      x = ((*c - 'a' + (lkey % 26) + 26) % 26);
       offset = ((lkey < 0) && (lkey & 0x1)) ?
                (((x - 'a') & 0x1) ? 'a' : 'A' ) :
                (((x - 'a') & 0x1) ? 'A' : 'a' );
       *c = x + offset;
    }
    //check to see if the letter is a digit: ASCII
    else if(*c >= 0 && *c <= 9){
      *c = ((*c - '0' + (nkey % 10) + 10) % 10) + '0';
    }
    //default
    else{
      *c = *c;
    }
   }

   //Transposition Cipher

   //gets the number of quads
   numquads = len/4;
   //gets the final quads number
   finalquad = len%4;

   //start off at the first element of the array
   count = 0;

   //perfect quad; swap the 1st and 2nd with the 3rd and 4th
   for(i=0;i<numquads;i++){

       //store the first and second element
       temp = text[count];
       temp1 = text[count+1];

       //swap the 3rd and 4th element into the 1st and 2nd
       text[count] = text[count+2];
       text[count+1] = text[count+3];

       //swap the stored first and second into the 3rd and 4th
       text[count+2] = temp;
       text[count+3] = temp1;

       count += 4;
   }

   //handle each case for the different quad sizes
   if(finalquad == 1){
     text[len] = text[len];
   }
   else if(finalquad == 2){
     temp = text[len-1]; //last element
     temp1 = text[len-2]; //second last element

     text[len-1] = temp1;
     text[len-2] = temp;
   }
   else if(finalquad == 3){
     temp = text[len-1]; //last element
     temp2 = text[len-3]; //third last element


     text[len-1] = temp2; //insert the last element into the first
     text[len-3] = temp; //insert the first element into the last
   }


  printf("Pass 2: text after Transposition algorithm: %s\n",text);

  return 0;
}


int main(){
  char text[] = "abcdefghijklmnopqrstuvwxyz";
  char text2[] = "abcdefghijklmnopqrstuvwxyz";
  char text3[] = "abcdefghijklmnopqrstuvwxyz";
  char text4[] = "abcdefghijklmnopqrstuvwxyz";

  cipher(text,0,0);
  cipher(text2,1,0);
  cipher(text3,4,0);
  cipher(text4,-50,0);

  //cipher(text,-4,-7);
}
