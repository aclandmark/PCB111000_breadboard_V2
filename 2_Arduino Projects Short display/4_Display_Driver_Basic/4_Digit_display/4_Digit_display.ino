
//Defining digits in terms of their segments
//so that numbers can simply be entered at the keyboard
//For use with breadboard loaded with single digit

#include "header.h"
#include "Local_subroutines.c"


#define zero "abcdef"                   //chars a,b,c,d,e and f are stored in an array named "zero"
#define one "bc"                        //chars b and c are stored in an array named "one"
#define two "abdeg"                     //Note: the compiler terminates each string in zero
#define three "abcdg"
#define four "bcfg"
#define five "acdfg"
#define six "gcdef"
#define seven "bca"
#define eight "abcdefg"
#define nine "gabcf"


int main (void){

char   digit;
 char dig_num;
const char* string_ptr;        //pointer: will be loaded with the address of a segment string 
 char num_string[6];                               //(i.e. the address of string "zero", "one", "two" etc....) 
int m;

setup_HW;               

for(m = 0; m < 4; m++)num_string[m] = '0' + ((m+1)*2); num_string[4] = 0;
Num_string_to_PC_Basic(num_string);

waitforkeypress_Basic();
while(1){

Clear_digits;
Clear_segments;
  
  for(m = 0; m < 4; m++){                                             //start of "do{}while();" loop
  
switch (m){
  case 3: digit_4_LH_on; break;
  case 2: digit_3_LH_on; break;
  case 1: digit_2_LH_on; break;
  case 0: digit_1_LH_on; break;}

digit = num_string[m];                
switch(digit){                                  //The appropriate address is loaded into location 
                                                //"string_pointer"
case '0': string_ptr = zero; break;             //The address of array zero is loaded into 
                                                //location "string_ptr"
case '1': string_ptr = one; break;
case '2': string_ptr = two; break;
case '3': string_ptr = three; break;
case '4': string_ptr = four; break;
case '5': string_ptr = five; break;
case '6': string_ptr = six; break;
case '7': string_ptr = seven; break;
case '8': string_ptr = eight; break;
case '9': string_ptr = nine; break;}  
                                                  //do loop. 

  Clear_segments;                                                //subroutine "display_num_string();"
_delay_us(1500);
display_single_digit(string_ptr);
_delay_us(500);
//waitforkeypress_Basic();
Clear_digits;} 
}}                                                  //return to the top of the "do" loop until all digits 
                                                 //have been illuminated


/************************************************************************************************************************/


void display_single_digit (const char* s){             //Subroutine requires a pointer to the string   
int char_ptr=0;                                                     //containing segments used to define a digit
char letter;

while(1){
letter = *(s + char_ptr);                                           //Note these two expressions are equivalent
switch(letter){                                                     //Work through the segments contained in the 
case 'a':  a_on;    break;                                                           //string until '\0' is encountered
case 'b':  b_on;    break;
case 'c':  c_on;    break;
case 'd':  d_on;    break;
case 'e':  e_on;    break;
case 'f':  f_on;    break;
case 'g':  g_on;    break;
                                                                    //update display one segment at a time
case 0:  break;                                                     //zero indicates the end of the string
default: break;}
if(!(letter))break;
char_ptr++;}}                                                       //incrementing "char_ptr" steps through the string











/************************************************************************************************************************/ 
