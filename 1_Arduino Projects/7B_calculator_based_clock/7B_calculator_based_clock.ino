
//Proj_7B_Demo_Clock_B



//INTRODUCES

//Simple clock in which the display is kept up to date by incrementing a counter every second
//The counter is converted to Hours, Minutes, Seconds each of which is then converted to askii 
//characters and sent to the display.

//As for Project 7A accurracy is not good

//USER INSTRUCTIONS

//Respond to the user prompt by pressing "R" and entering the time when requested or by pressing "r" and letting 
//the clock start at time zero.




#include "Proj_7B_header_file_1.h"
#include "display_subroutines.c"


//Type main routine here

volatile int display_control = 0;


int main (void){
char User_response;

setup_HW;

String_to_PC_Basic("Press 'R' to enter time or 'r' to start at time zero  ");
User_prompt_Basic;

if(User_response == 'R')set_time();
else {reset_clock_1; deci_SecsH = '0'; deci_SecsL = '0'; deci_sec_counter = 0; }
display_8_bytes(digits);

String_to_PC_Basic("AK to start\r\n");
waitforkeypress_Basic();
sei();
Timer_T1_sub_with_interrupt(T1_delay_200ms);

while(1){while(!(display_control)); display_control = 0; deci_sec_counter += 2;
if(deci_sec_counter == 864000)deci_sec_counter = 0;
Format_time_for_display();display_8_bytes(digits);}}

ISR(TIMER1_OVF_vect){display_control = 1;}

/**********************************************************************************************************************/
void Format_time_for_display(void){
Hours =     deci_sec_counter/36000;
Minutes =   (deci_sec_counter%36000)/600;
Seconds =   ((deci_sec_counter%36000)%600)/10;
deci_Secs = ((deci_sec_counter%36000)%600)%10;

timer_utoa(Hours); HoursH = charH; HoursL = charL; 
timer_utoa(Minutes); MinsH = charH; MinsL = charL; 
timer_utoa(Seconds); SecsH = charH; SecsL = charL; 
timer_utoa(deci_Secs * 10); deci_SecsH = charH; deci_SecsL = charL; }



/***********************************************************************************************************************/
void set_time(void){

for(int m = 0; m <= 7; m++)digits[m] = 0;
String_to_PC_Basic("Enter start time Hours, Minutes and Seconds\
\r\n(24 hour clock with no spaces). Terminate with cr\r\n");

while(isCharavailable_Basic(50) == 0){String_to_PC_Basic("T?  ");}

digits[7] = Char_from_PC_Basic();display_8_bytes(digits);
for (int m = 0; m<=4; m++){while(isCharavailable_Basic(5) == 0);
if(m == 4){digits[2] = Char_from_PC_Basic();deci_SecsH = '0'; deci_SecsL = '0';}
else digits[6 - m] = Char_from_PC_Basic(); 
display_8_bytes(digits);}

waitforkeypress_Basic();

deci_sec_counter = 10*(long)((((long)((HoursH -'0') * 10) + HoursL-'0') * 3600) +
((((MinsH-'0') * 10) + MinsL-'0') * 60) +(SecsH-'0') * 10 + SecsL - '0');

clear_display;
_delay_ms(50);}



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
