
#include "display_header.h"

char display_bkp[7];
char seg_store[8];
char digit_num;
extern  unsigned char PRN_counter;


unsigned int PRN_16bit_GEN(unsigned int, unsigned char*);
void save_segment(char);
//void I2C_Tx_any_segment(char, char);
void Timer_T0_10mS_delay_x_m(int m);


#include <avr/wdt.h>
#define wdr()  __asm__ __volatile__("wdr")

#define switch_1_down  ((PIND & 0x04)^0x04)


int Adjust_T1_period(int T1_period){
  if (T1_period <= 1)T1_period = 15;
  else
  T1_period = T1_period *12/15;
  return T1_period;}



  void backup_the_display(char segment, char digit_num)
  { display_bkp[segment - 'a'] =
    display_bkp[segment - 'a'] ^ (1 << digit_num);}



unsigned long update_display (int T1_period, char direction, char seg_counter, unsigned long PRN)
{char letter;
char prompt;

  while (seg_counter < 56) {
      letter = (PRN % 7) + 'a';
      PRN = PRN_16bit_GEN (PRN, &PRN_counter);
      digit_num = (PRN % 8);
      if ((!(direction)) && (display_bkp[letter - 'a'] & (1 << digit_num))) {
        PRN_counter -= 1;
        continue; }

      if ((direction) && (!(display_bkp[letter - 'a'] & (1 << digit_num)))) {
       PRN_counter -= 1;
       continue;}
       
      seg_store[digit_num] |= (1 << (letter - 'a'));;
      
      backup_the_display(letter, digit_num);
      seg_counter += 1;
      Timer_T0_10mS_delay_x_m(T1_period);}
      return PRN;}


void display_pattern(){     //repeat every 1.5ms but return to update display

for(int p = 0; p <= 7; p++){

  switch (p){
case 0: Clear_digits; digit_1_RH_on; break;
case 1: Clear_digits; digit_2_RH_on; break;
case 2: Clear_digits; digit_3_RH_on; break;
case 3: Clear_digits; digit_4_RH_on; break;
case 4: Clear_digits; digit_1_LH_on; break;
case 5: Clear_digits; digit_2_LH_on; break;
case 6: Clear_digits; digit_3_LH_on; break;
case 7: Clear_digits; digit_4_LH_on; break;}

for(int m = 0; m <=7; m++){
  if (seg_store[p] & (1 << m))switch(m){
  case 0: a_on; break;
  case 1: b_on; break;
  case 2: c_on; break;
  case 3: d_on; break;
  case 4: e_on; break;
  case 5: f_on; break;
  case 6: g_on; break;}
}
}}  

    /*************************************************************************************************/
