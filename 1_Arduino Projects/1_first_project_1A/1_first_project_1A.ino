

//14 more projects very like those saved under            
//“0_project_zero” this time generating simple patterns on the display 
//some of them regular and repeating and some of them random.
//Why not copy the C code for one or two examples to be found in folder "C_file_images\1_first_project"



#include "First_project_header.h"
#include "Local_subroutines.c"
#include "display_header.h"

 
 int main (void)             //Example 8
  { char digit[] =  "01234567777654321000";
        char letter = 'a';
    char counter=0;
    int top = 1000;
    char dig_no;
    setup_HW;
  
  while(1){//I2C_Tx_any_segment(letter,digit[counter]-'0');

//for(int m = 0; m <= 7; m++)seg_store[m] = 0;

  //dig_no = digit[counter]-'0'];
  //for(int m = 0; m < top; m++)_delay_us(100);
  
if (counter < 7)letter = 'a';
if (counter == 7) letter = 'f';
if (counter == 8) letter = 'e';
if ((counter >= 9) && (counter <= 16)) letter = 'd';
if (counter == 17) letter = 'c';
if (counter == 18) letter = 'b';
if (counter == 19) letter = 'a';
counter = (counter + 1)%20;

  seg_store[digit[counter]-'0'] |= (1 << (letter - 'a'));  //letter - 'a';
//Int_to_PC_Basic(counter);Char_to_PC_Basic(letter);
  
  display_pattern(50);

if (counter == 19)for(int m = 0; m <= 7; m++)seg_store[m] = 0;

//if (switch_2_down) I2C_Tx_any_segment_clear_all();

//if(counter == 19){if((switch_1_down)|| (top <= 50))break;
//if(switch_3_down)top = top*2/3;}
}SW_reset;}
 
 
  
 
/*********************************************************  
int main (void)               //Example_1
{unsigned int Port_1, Port_2;

setup_HW;

  Port_1 = 1;
  Port_2 = 1;
for(int m = 0; m <= 15; m++){
display_binary (Port_1, Port_2, 5);
Port_1 = Port_1 << 1;
Port_2 = Port_2 << 1; 
  }SW_reset;}

************************************************************
int main (void)   //Example 3
  { unsigned int Port_1;

  setup_HW;
  wdt_enable(WDTO_30MS);
  Port_1 = 1;
  for (int m = 0; m <= 15; m++)
  {  display_binary (Port_1 << m, Port_1 << m, 5);}
for (int m = 14; m; m--)
{  display_binary
(Port_1 << m, Port_1 << m, 5);}
  while(1); }


************************************************************
int main (void)    //Example 5
  { unsigned int PORT_1, PORT_2;
  setup_HW;
  while (1)
  { PORT_1 = 0b0000000000000001; 
    PORT_2 = 0b1000000000000000;  
    for (int m = 0; m <= 15; m++)
    { display_binary(PORT_1, PORT_2,2);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    }}return 1;  }



 int main (void)       //Example 6
  { unsigned long PORT_1, PORT_2;
  setup_HW;
  while (1)
  { PORT_1 = 1;
    PORT_2 = 0x80000000;
    for (int m = 0; m <= 31; m++)
    {  display_binary(PORT_1, PORT_2, 4);
      PORT_1 = PORT_1 << 1;
      PORT_2 = PORT_2 >> 1;
    } }return 1;}



    
 ************************************************************
 int main (void){                //numerical sequences
unsigned int Port_1, Port_2;
  char digits[12];
   char Inc = 0; 
   int duration;
   
  setup_HW;
  Port_1 = 1;
  Port_2 = 0;
 String_to_PC_Basic("Enter speed 1 - 9");
duration = waitforkeypress_Basic() - '0';

Port_1 = 1;
while(1){
Port_2 = 0x8000 - Port_1;
display_binary(Port_1, Port_2, duration);
if(char_present){if (!(Inc))Inc = 1;
else Inc = 0;
if (Char_from_PC_Basic() == 'x')SW_reset;}

if (!(Inc)) Port_1 += 1;}}



************************************************************
int main (void)     //Randon display
  {int T1_period = 15;
  char direction;
  char duration = 50;
  char seg_counter;
  setup_HW;
    
  PRN_counter = 0;
  PRN = PRN_16bit_GEN (0, &PRN_counter);
   direction=1;
  while(1){
     direction ^= 1;
   seg_counter=0;
 PRN = random_display
 (direction, seg_counter, PRN, duration);}}
 

  
 *********************************************************/

 
