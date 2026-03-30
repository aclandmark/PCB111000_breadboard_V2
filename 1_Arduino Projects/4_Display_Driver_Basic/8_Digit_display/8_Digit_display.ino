
//Defining digits in terms of their segments
//so that numbers can simply be entered at the keyboard


#include "8_Digit_header.h"
#include "display_header.h"


int main (void){

char   digit='0';
int digit_num=0;            
int string_counter=0;
int letter_counter=0;
const char* string_ptr = 0;
char num_string[9] = "86421357";


setup_HW;               
//digit_1_LH_on;

if(MCUSR & (1 << PORF))
{User_prompt_Basic;
eeprom_write_byte((uint8_t*)0x1FA, 0);
MCUSR = 0;Clear_segments;}   

if(!(eeprom_read_byte((uint8_t*)0x1FA)))
{eeprom_write_byte((uint8_t*)0x1FA, 0xFF);
String_to_PC_Basic("\r\nSend digits?");}

else 

String_to_PC_Basic("\r\nAgain");
Clear_segments;

while(1){
String_to_PC_Basic("1 to 8?");
switch (waitforkeypress_Basic()){
case '1':  digit_4_RH_on; break;
case '2':  digit_3_RH_on; break;
case '3':  digit_2_RH_on; break;
case '4':  digit_1_RH_on; break;
case '5':  digit_4_LH_on; break;
case '6':  digit_3_LH_on; break;
case '7':  digit_2_LH_on; break;
case '8':  digit_1_LH_on; break;
}

  
digit_num = 0;                                  //First digit on display

do{                                             //start of "do{}while();" loop
//while(!(isCharavailable_Basic(1)))wdr(); 
Clear_segments;//digit_4_RH_on;
//digit = Char_from_PC_Basic();                   //user enters digit (0 to 9) at the PC keyboard
digit = num_string[digit_num];
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
case '9': string_ptr = nine; break;
default: continue; break;}                        
display_num_string(string_ptr, digit_num);
digit_num++;
_delay_ms(250);
}while (digit_num < 8);
                                                  //return to the top of the "do" loop until all digits 
                                                  //have been illuminated

while(!(isCharavailable_Basic(1)))wdr(); 
Char_from_PC_Basic();
Clear_segments;Clear_digits; }                                       //clear display and repeat
SW_reset;}



/************************************************************************************************************************/
void display_num_string (const char* s, int digit_num){             //Subroutine requires a pointer to the string   
int char_ptr=0;                                                     //containing segments used to define a digit
char letter;

while(1){
letter = *(s + char_ptr);// (s[char_ptr]);                          //Note these two expressions are equivalent
switch(letter){                                                     //Work through the segments contained in the 
case 'a':                                                           //string until '\0' is encountered
case 'b': 
case 'c': 
case 'd': 
case 'e': 
case 'f': 
case 'g': Any_segment(letter);
break;                                                              //update display one segment at a time
case 0:  return; break;                                             //zero indicates the end of the string
default: break;}char_ptr++;}}                                       //incrementing "char_ptr" steps through the string
                                                                    //Selecting segment letters in turn
/********************************************************/

void Any_segment(char letter){
switch (letter){
case 'a': a_on;    break;
case 'b': b_on;    break;
case 'c': c_on;    break;
case 'd': d_on;    break;
case 'e': e_on;    break;
case 'f': f_on;    break;
case 'g': g_on;    break;}}



/************************************************************************************************************************/ 
