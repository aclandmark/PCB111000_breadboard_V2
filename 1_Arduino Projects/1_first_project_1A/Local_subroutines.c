
#include "display_header.h"
#include <util/delay.h>

void display_pattern(void);

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


void update_display (unsigned long Port_1, unsigned long Port_2)
{

for (int q = 0; q <= 100; q++){

for(int m = 0; m <= 15; m++)
{switch(m){
case 0: if(Port_1 & (1 << m)){digit_4_RH_on; b_on;}
        if(Port_2 & (1 << m)){digit_4_RH_on; c_on;}break;
case 1: if(Port_1 & (1 << m)){digit_4_RH_on; f_on;}
        if(Port_2 & (1 << m)){digit_4_RH_on; e_on;}break;

case 2: if(Port_1 & (1 << m)){digit_3_RH_on; b_on;}
        if(Port_2 & (1 << m)){digit_3_RH_on; c_on;}break;
case 3: if(Port_1 & (1 << m)){digit_3_RH_on; f_on;}
        if(Port_2 & (1 << m)){digit_3_RH_on; e_on;}break;

case 4: if(Port_1 & (1 << m)){digit_2_RH_on; b_on;}
        if(Port_2 & (1 << m)){digit_2_RH_on; c_on;}break;
case 5: if(Port_1 & (1 << m)){digit_2_RH_on; f_on;}
        if(Port_2 & (1 << m)){digit_2_RH_on; e_on;}break;

case 6: if(Port_1 & (1 << m)){digit_1_RH_on; b_on;}
        if(Port_2 & (1 << m)){digit_1_RH_on; c_on;}break;
case 7: if(Port_1 & (1 << m)){digit_1_RH_on; f_on;}
        if(Port_2 & (1 << m)){digit_1_RH_on; e_on;}break;


case 8: if(Port_1 & (1 << m)){digit_4_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_4_LH_on; c_on;}break;
case 9: if(Port_1 & (1 << m)){digit_4_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_4_LH_on; e_on;}break;

case 10: if(Port_1 & (1 << m)){digit_3_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_3_LH_on; c_on;}break;
case 11: if(Port_1 & (1 << m)){digit_3_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_3_LH_on; e_on;}break;

case 12: if(Port_1 & (1 << m)){digit_2_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_2_LH_on; c_on;}break;
case 13: if(Port_1 & (1 << m)){digit_2_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_2_LH_on; e_on;}break;

case 14: if(Port_1 & (1 << m)){digit_1_LH_on; b_on;}
        if(Port_2 & (1 << m)){digit_1_LH_on; c_on;}break;
case 15: if(Port_1 & (1 << m)){digit_1_LH_on; f_on;}
        if(Port_2 & (1 << m)){digit_1_LH_on; e_on;}break;
}
_delay_us(1200);


Clear_segments;
Clear_digits;}}}
      


void display_pattern(void){     //repeat every 1.5ms but return to update display

for (int q = 0; q <= 100; q++){
for(int p = 0; p <= 7; p++){

Clear_segments;
Clear_digits;
  
switch (p){
case 0: digit_1_RH_on; break;
case 1: digit_2_RH_on; break;
case 2: digit_3_RH_on; break;
case 3: digit_4_RH_on; break;
case 4: digit_1_LH_on; break;
case 5: digit_2_LH_on; break;
case 6: digit_3_LH_on; break;
case 7: digit_4_LH_on; break;}

for(int m = 0; m <=7; m++){
  if (seg_store[p] & (1 << m)){switch(m){
  case 0: a_on; break;
  case 1: b_on; break;
  case 2: c_on; break;
  case 3: d_on; break;
  case 4: e_on; break;
  case 5: f_on; break;
  case 6: g_on; break;}}
}
}_delay_us(120);}  
Clear_segments;
Clear_digits;}
    /*************************************************************************************************/
