

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
  {int T1_period = 15;
  char direction;
  char seg_counter;
  setup_HW;
  
  Clear_segments;
  Clear_digits;

  
  PRN_counter = 0;
  PRN = PRN_16bit_GEN (0, &PRN_counter);
   direction=1;
  while(1){
     direction ^= 1;
   seg_counter=0;
 PRN = update_display
 (T1_period, direction, seg_counter, PRN);
  }}
 
 
