

#include "Int__sq_root_header.h"
#include "display_header.h"


int main (void){

char real_num_string[12];// = "86421357";
long num;
char exit_Key_press;

setup_HW;               

if(MCUSR & (1 << PORF))
{User_prompt_Basic;
eeprom_write_byte((uint8_t*)0x1FA, 0);
MCUSR = 0;Clear_segments;}   

if(!(eeprom_read_byte((uint8_t*)0x1FA)))
{eeprom_write_byte((uint8_t*)0x1FA, 0xFF);
String_to_PC_Basic("\r\nEnter integer?");
String_to_PC_Basic ("\r\nAK to display root\r\n");}

else 

String_to_PC_Basic("\r\nAgain\t");


Real_num_from_PC_Basic(real_num_string);
display_real_num(real_num_string);    //needs AK to exit
exit_Key_press = Char_from_PC_Basic();


invert_num_string(real_num_string);
num = atol (real_num_string);
Int_to_PC_Basic(num/2);

String_to_PC_Basic ("\r\n\r\nAK to repeat");
invert_num_string(real_num_string);
display_real_num(real_num_string);

exit_Key_press = Char_from_PC_Basic();


//waitforkeypress_Basic();
SW_reset;}
















void display_real_num(char*num_string){

char   digit;
int digit_num=0;            
int string_counter=0;
int letter_counter=0;
const char* string_ptr = 0;
char dp;

  
while(1){digit_num=0;
do{
  Clear_digits;
  Clear_segments;
  dp_off;
digit = num_string[digit_num];

if(digit & 0x80) {dp = 1; digit &= (~(0x80));} else dp = 0;

switch (digit_num + 1){
case 1:  digit_4_RH_on; break;
case 2:  digit_3_RH_on; break;
case 3:  digit_2_RH_on; break;
case 4:  digit_1_RH_on; break;
case 5:  digit_4_LH_on; break;
case 6:  digit_3_LH_on; break;
case 7:  digit_2_LH_on; break;
case 8:  digit_1_LH_on; break;}
switch(digit){ 
case '0': string_ptr = zero; break;
case '1': string_ptr = one; break;
case '2': string_ptr = two; break;
case '3': string_ptr = three; break;
case '4': string_ptr = four; break;
case '5': string_ptr = five; break;
case '6': string_ptr = six; break;
case '7': string_ptr = seven; break;
case '8': string_ptr = eight; break;
case '9': string_ptr = nine; break;
case 0: break;} 

//if(dp){dp_on;} else {dp_off;}

if(!(digit))break;                       
display_num_string(string_ptr, digit_num, dp);
digit_num++;
_delay_us(1200);
}  while (digit_num < 8); 
if (UCSR0A & (1 << RXC0))return;}
}




/************************************************************************************************************************/
void display_num_string (const char* s, int digit_num, char dp){             //Subroutine requires a pointer to the string   
int char_ptr=0;                                                     //containing segments used to define a digit
char letter;

while(1){
letter = *(s + char_ptr);                                           //Note these two expressions are equivalent
switch(letter){                                                     //Work through the segments contained in the 
case 'a':                                                           //string until '\0' is encountered
case 'b': 
case 'c': 
case 'd': 
case 'e': 
case 'f': 
case 'g': Any_segment(letter);break;
                                                                            //update display one segment at a time
case 0:  break;//return; break;                                             //zero indicates the end of the string
default: break;}
if(!(letter))break;
char_ptr++;}                                                         //incrementing "char_ptr" steps through the string
  
 if(dp){dp_on;} 
 }                                                                   
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
