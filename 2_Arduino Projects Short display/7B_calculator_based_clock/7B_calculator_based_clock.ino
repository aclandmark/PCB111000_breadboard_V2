
//Proj_7B_Demo_Clock_B
//EEPRFOM use 0x1FF to 0x1FD  Cal byte
//            0x1FC & 0x1FB   PRN
//            0x1FA           Reset control
//0x1F9 to 0x1F4  Time
//If 0x1F9 contains digit read time from EEPROM and rerset 0x1F9 to 0xFF
//If 0x1F9 contains 0xFF request time

//INTRODUCES

//Simple clock in which the display is kept up to date by incrementing a counter every second
//The counter is converted to Hours, Minutes, Seconds each of which is then converted to askii 
//characters and sent to the display.

//Timing is controlled by a watch crystal and so is quite good

//USER INSTRUCTIONS

//Respond to the user prompt by pressing "R" and entering the time when requested 
//or by pressing "r" and letting the clock start at time zero.
//Disconnnect the clock from the PC and reconnect to a 5V source and the clock will start immediately




#include "Proj_7B_header_file_1.h"
#include "display_subroutines.c"




int EEP_Location = 0x1F9;
int main (void){
char User_response;

setup_HW;

_delay_ms(1);

if((power_on_reset) && ((eeprom_read_byte((uint8_t*)0x1F9)) != 0xFF)){
EEP_Location = 0x1F9;
for(int m = 0; m < 4; m++){digits[3 - m] =
eeprom_read_byte((uint8_t*)EEP_Location--);}


deci_sec_counter = 10*(long)((((long)((HoursH - '0') * 10) + 
HoursL - '0') * 3600) + ((((MinsH - '0') * 10) + MinsL - '0') * 60));}

else{
String_to_PC_Basic("Press 'R' to enter time or 'r' to start at time zero  "); 
User_prompt_Basic;

if(User_response == 'R'){set_time();}
else {reset_clock_1; clear_display;}
display_time(digits, deci_sec_counter);

String_to_PC_Basic("AK to start\r\n");
waitforkeypress_Basic();}

UCSR0B &= (~(1 << RXEN0));
sei();
initialise_T2_Local();
start_clock_Local();
display_time(digits, deci_sec_counter);}



/**********************************************************************************************************************/
char Format_time_for_display(void){
Hours =     deci_sec_counter/36000;
Minutes =   (deci_sec_counter%36000)/600;
Seconds =   ((deci_sec_counter%36000)%600)/10;
deci_Secs = ((deci_sec_counter%36000)%600)%10;

timer_utoa(Hours); HoursH = charH; HoursL = charL; 
timer_utoa(Minutes); MinsH = charH; MinsL = charL; 

if (Seconds < 15) return 4;
if ((Seconds >= 15) && (Seconds < 30)) return 3;
if ((Seconds >= 30) && (Seconds < 45)) return 2;
if ((Seconds >= 45) && (Seconds < 60)) return 1;}



/***********************************************************************************************************************/
void set_time(void){

for(int m = 0; m <= 7; m++)digits[m] = 0; 

String_to_PC_Basic("Enter start time Hours, Minutes and Seconds\
\r\n(24 hour clock with no spaces). Terminate with cr\r\n");
for(int m = 0; m <= 7; m++)digits[m] = 0;clear_display;
while(isCharavailable_Basic(50) == 0){String_to_PC_Basic("T?  ");}

for(int m = 0; m < 4; m++){digits[3 - m] = waitforkeypress_Basic();
eeprom_write_byte((uint8_t*)EEP_Location--, digits[3-m]);}
Num_string_to_PC_Basic(digits);

deci_sec_counter = 10*(long)((((long)((HoursH - '0') * 10) + HoursL - '0') * 3600) +
((((MinsH - '0') * 10) + MinsL - '0') * 60));
_delay_ms(1);
clear_display;}



/**********************************************************************************************************************/
void timer_utoa(char n){                //converts an unsigned number to a string of digits
if (n>=10)
{charL = n%10;
charH = (n-charL)/10;
charL = charL + '0';
charH = charH + '0';}
else
{charH = '0'; charL = n + '0';}}



/**********************************************************************************/
void initialise_T2_Local(void){
ASSR = (1 << AS2); 
TCNT2 = 0;
TCCR2A = 0;
TCCR2B |= (1 << CS20) | (1 << CS21);
OCR2B = 0;}



/**********************************************************************************/
void start_clock_Local(void){
tick_counter = 0;
clock_tick = 0;
TCNT2 = 0;
OCR2A = 102; 
TIMSK2 |= (1 << OCIE2A);}



/**********************************************************************************/
ISR (TIMER2_COMPA_vect){ char string[5];
  OCR2A += 102;
  clock_tick += 1;
  tick_counter += 1;
  if(tick_counter == 9){tick_counter = -1; OCR2A += 4;}
   if(clock_tick == 2){clock_tick = 0;deci_sec_counter += 2;    //was 2
if(deci_sec_counter == 864000)deci_sec_counter = 0;

{if (!(dp))dp = 1; else dp = 0;}
dp_digit = (Format_time_for_display());}}



/**********************************************************************************/
