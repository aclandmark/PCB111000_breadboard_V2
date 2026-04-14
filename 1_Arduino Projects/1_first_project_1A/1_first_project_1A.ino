

//14 more projects very like those saved under            
//“0_project_zero” this time generating simple patterns on the display 
//some of them regular and repeating and some of them random.
//Why not copy the C code for one or two examples to be found in folder "C_file_images\1_first_project"



#include "First_project_header.h"
#include "Local_subroutines.c"
#include "display_header.h"

unsigned int PRN;
unsigned char PRN_counter;

 int main (void)                //Example 13
  {
unsigned int Port_1, Port_2;
  char digits[8];
    
  setup_HW;
  Port_1 = 1;
  Port_2 = 0;
  Clear_segments;
  Clear_digits;

for(int m = 0; m <= 7; m++)digits[m] = 0;
Int_from_PC_Basic(digits);
invert_num_string(digits);
Port_1 = atol(digits);
Int_to_PC_Basic(Port_1);
while(1){
update_display
 (Port_1, Port_2);}



for(int m = 0; m <= 15; m++){
update_display
 (Port_1, Port_2);
Port_1 = Port_1 << 1;
Port_2 = Port_2 << 1; 
//waitforkeypress_Basic();
  }SW_reset;}
 
 
