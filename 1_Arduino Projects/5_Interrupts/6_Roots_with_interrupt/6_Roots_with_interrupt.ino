
/*
 Drives the display while calculating and printing out the square root
 of an integer number entered at the keyboard.
 Calculates square roots by trial and error starting with 2.
 */
 

#include "Roots_with_interrrupt_header.h"
#include "Local_subroutines.c"

void Num_string_from_KBD_Local(char *);

#define message_1 "\r\nThis program calculates roots.\r\n\
Enter integer number\r\n?"




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



volatile char num_present = 0;                    //Set to one when number has been entered and -cr- presses (See Local subroutines)
volatile char ready_to_compute = 0;               //Set to one as the ISR exits (to provide a fixed known time for calculations)
long Num;
char Num_string[12];

const char* string_ptr = 0; 

volatile char dig = 0;
volatile char counter = 0;

int main (void)
{  setup_HW;

if(MCUSR & (1 << PORF)){User_prompt_Basic;eeprom_write_byte((uint8_t*)0x1FA, 0);MCUSR = 0;}
if(!(eeprom_read_byte((uint8_t*)0x1FA)))
{String_to_PC_Basic(message_1);
eeprom_write_byte((uint8_t*)0x1FA, 0xFF);}   

  
  sei();
  T1_clock_tick(150); 
  while (1) {
    Num_string_from_KBD_Local(Num_string);
    Num_string_to_PC_Basic(Num_string);
    Char_to_PC_Basic('\t');
   while(!(ready_to_compute));                    //Wait here for best time to start computation
  ready_to_compute = 0;
  num_present = 0; 
   Num = Askii_to_binary_Local(Num_string);       //Convert number entered at the KBD to binary
    root_computation(Num, Num_string);            //Calculate the root, and save in "Num_string" (see Int_to_String_Basic() in Localsubroutines)
    Num_string_to_PC_Basic(Num_string);           //Send result to the PC
    newline_Basic();
    Char_to_PC_Basic('?'); }}


/********************************************************************************************************/
void T1_clock_tick(int T1_period_in_ms)                               //Start the T1 clock
{ TCNT1 = 0;
  OCR1A = T1_period_in_ms * 125;
  TIMSK1 |= (1 <<  OCIE1A);
  TCCR1B = 0x03;}



/********************************************************************************************************/
ISR(TIMER1_COMPA_vect) 
{
 TCNT1 = 0;
counter += 1;
if (!(counter%3))
{Clear_digit; dig = (dig+1)%10;
  
switch(dig){        
case 0: string_ptr = zero; break;     
case 1: string_ptr = one; break;    
case 2: string_ptr = two; break;
case 3: string_ptr = three; break;
case 4: string_ptr = four; break;
case 5: string_ptr = five; break;
case 6: string_ptr = six; break;
case 7: string_ptr = seven; break;
case 8: string_ptr = eight; break;
case 9: string_ptr = nine; break;} 

display_num_string (string_ptr);}
if (num_present) {ready_to_compute = 1;} }



/********************************************************************************************************/
void display_num_string (const char* s){ 
int char_ptr=0; 
char letter;

while(1){
letter = *(s + char_ptr);
switch(letter){ 
case 'a': 
case 'b': 
case 'c': 
case 'd': 
case 'e': 
case 'f': 
case 'g': Any_segment(letter);
break;        
case 0:  return; break; 
default: break;}char_ptr++;}} 


                          
/********************************************************************************************************/
void Any_segment(char letter){
switch (letter){
case 'a': a_on;    break;
case 'b': b_on;    break;
case 'c': c_on;    break;
case 'd': d_on;    break;
case 'e': e_on;    break;
case 'f': f_on;    break;
case 'g': g_on;    break;}}





/********************************************************************************************************/
long Askii_to_binary_Local(char * array_ptr) {
  long num = 0;
{ int m = 0; while (*(array_ptr + m)) {
      num = num * 10 + (*(array_ptr + m++))  - '0';}}
  return num;}






  /*************************************************************************************/
