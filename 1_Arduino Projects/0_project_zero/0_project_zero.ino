
//Use CA56-11 display
#include "0_project_zero_header.h"




 


/************************************************************************

int main (void)    //Example 1  Red LED flashes
{  setup_HW;
  c_on;
  SW_reset;}


 
int main (void)    //Example 2  Red LED flashes
{  setup_HW;
 
if(switch_3_down){wdt_enable(WDTO_250MS); _delay_ms(60);}
else wdt_enable(WDTO_60MS);
 c_on;
 while(1);}


int main (void)    //Example 3  Red LED flashes
{ setup_HW;
  while(1){
  switch_Seg_c;
  _delay_ms(50);}}



int main (void)                   //Example 4  Red LED flashes 
{  setup_HW;  //when switch_1 is pressed
  while (1) {
    while (switch_3_up);
    {switch_Seg_c; }
    Timer_T0_10mS_delay_x_m(20);  }}


 int main (void)    //Example 8  Random display
{ unsigned int PRN = 1;
char timer_on = 50;
  setup_HW;
while(1){
    c_off; f_off;
PRN = (PRN_8bit_GEN() % 4);
      switch (PRN) {
        case 0: c_on; break;
        case 1: f_on; break;
        case 2: c_on; f_on; break;
        case 4:  c_off; f_off; break; }
Timer_T0_10mS_delay_x_m(timer_on);
if (switch_3_down)timer_on = timer_on*2/3;
while(switch_3_down);
if(timer_on <= 2)break;}SW_reset;}



     int main (void)       //Example 10    
{ int counter, ON_time;   //Variable brightness

  setup_HW;
  counter = 0;
  ON_time = 160;
  
    g_on;
  while (switch_3_up);

  while (1) {
    if (g_is_on) {
      g_off;
      for (int m = 0; m <= (320 - ON_time); m++)
    _delay_us(6); }
    else {  g_on;
      for (int m = 0; m <= ON_time; m++)
    _delay_us(6);}
    counter += 1;
    if ((counter >= 100)  && (switch_3_down)) {
      counter = 0;
      ON_time = ON_time * 2/3; }
    if (ON_time == 1) {
      ON_time = 160;
      while (switch_3_down); }}}



      
  int main (void)       //Example 12    
{ int counter, ON_time;   //LED flasher with variable brightness

  setup_HW;
  ON_time = 160;
  
  g_on;
   while (1) {
    drive_led(ON_time);  
  c_off; f_off;
  Timer_T1_sub(T1_delay_100ms);
  if(switch_3_down){ON_time = ON_time * 2/3;
  if (ON_time == 1)ON_time = 160; }}}


void  drive_led(int ON_time){
  Start_timer_T1_sub(T1_delay_100ms);

  while (!(TIFR1 & (1 << TOV1))){
  
  if (g_is_on) {
      g_off;
      for (int m = 0; m <= (320 - ON_time); m++)
    _delay_us(6); }
    else {g_on;
      for (int m = 0; m <= ON_time; m++)
    _delay_us(6);}}

    TIFR1 |= (1 << TOV1);}
 
 ***************************************************************************/
