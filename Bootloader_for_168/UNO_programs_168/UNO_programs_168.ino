
/*
Version of the UNO_AVR programmer adapted for the PCB111000_CP2102 project
Designed to be uploaded to a UNO
Programmming pins are:
  data out    PORTB3 (MOSI)   connect to target device MOSI
  data in     PORTB4 (MISO)   connect to target device MISO
  clock       PORTB5 (SCK)    connect to target device SCK
  reset       PORTC3          connect to target device pin 1 reset

Calibration pin:   This also uses PORTB5

Can also be used to program target EEPROM
but not flash with text
 */




#include "UNO_AVR_programmer.h"
#define Version "UNO_programmes_168_prototype\r\n" 

int main (void){ 

setup_328_HW;                                                         //Reduces clock to 8MHz"

Reset_L;                                                              //Put target in reset state to dissable UART

while(1){
do{sendString("s  ");} 
while((isCharavailable(255) == 0));                                   //User prompt 
if(receiveChar() == 's')break;}
sendString("\r\n");

Atmel_powerup_and_target_detect;                                      //Leave target in programming mode                              


sendString(" detected.\r\n\r\nTo program flash:  press -P- for bootloader or \
-p-  for other routines,\r\n\
//Press -t- to run 168 calibration routine,\r\n\
Press -r- for other routines,\r\n");
sendString("Press -V- to read flash or -x- to escape.\r\n\r\n");


while(1){
op_code = waitforkeypress();
switch (op_code){

case 'r': Exit_programming_mode; break;                               //Wait for UNO reset
case 'e': Prog_EEPROM(); SW_reset; break;
//case 't': set_cal_clock();break;

case 'd':                                                             //Delete contents of the EEPROM
sendString("\r\nReset EEPROM! D or AOK to escape");                   //but leave cal data.
newline();
if(waitforkeypress() == 'D'){
sendString("5 sec wait");
for (int m = 0; m < EE_top; m++)  
{Read_write_mem('I', m, 0xFF);}                                       //Write 0xFF to all EEPROM loactions bar the top 3
sendString(" Done. \r\nPress D to delete cal bytes or AOK\r\n");
if(waitforkeypress() == 'D')
{for (int m = EE_top; m < EE_top + 3; m++)Read_write_mem('I', m, 0xFF);}
}
SW_reset;break;

case 'V': prog_counter = 0x2000; Verify_Flash_Hex();SW_reset; break;

case 'x': SW_reset; break;
default: break;} 

if ((op_code == 'p')||(op_code == 'P')) break;} 
sendString("Send hex file (or x to escape).\r\n");

Program_Flash_Hex();
Verify_Flash_Hex();

sendString("\r\nProgrammming completed\r\n");
cli();
//while(1);
sendString (Version);
newline();

Read_write_mem('I', EE_size - 4, \
(Atmel_config(signature_bit_2_h, signature_bit_2_l)));                  //Define target type on target device
Read_write_mem('I', EE_size - 5, \
(Atmel_config(signature_bit_3_h, signature_bit_3_l)));       

Read_write_mem('I', 0x1FC, 0xF3);                                          //Initialise EEP locations for PRN use

//sendString("Press -t- if running 328 cal routine or AOK for other routines.");

//if(waitforkeypress()== 't')set_cal_clock();
//else

sendString("Set BR to 57600 then press AK\r\n");
USART_init(0,16);
waitforkeypress();
{Exit_programming_mode; }                                               //Wait for UNO reset

return 1;}





/***************************************************************************************************************************************************/
ISR(USART_RX_vect){
switch (op_code){
case 'p':
case 'P': upload_hex(); break;}}



/***************************************************************************************************************************************************/
/*ISR(TIMER2_OVF_vect) { //NOT USED in this version               Timer2 times out and halts at the end of the text file 
if(text_started == 3)                                           //Ignore timeouts occurring before start of file download
  {endoftext -= 1; TCCR2B = 0; TIMSK2 &= (~(1 << TOIE2));       //Shut timer down
  inc_w_pointer; store[w_pointer] = 0;                          //Append two '\0' chars to the end of the text
  inc_w_pointer; store[w_pointer] = 0; }}*/




/****************************************************************************************************************************************************/
/*void set_cal_clock(void){

sendString("Square wave generates PCI on PB5 every 8.192mS\r\n\
Results are sent to a separate terminal screen.\r\n");
UCSR0B &= (~((1 << RXEN0) | (1<< TXEN0)));
initialise_IO;
Set_LED_ports;
LEDs_off;
DDRB |= 1 << DDB5;
PORTB &= (~(1 << PORTB5));                                       //Output low
TCNT0 = 0;
//TCCR0B = (1 << CS02) | (1 << CS00);                             //7.8125 KHz clock counts to 256 in 32.768mS                    
TCCR0B = (1 << CS02);                                             //31.25KHz clock counts to 256 in 8.192KHz

Reset_H;

while(1){
while(!(TIFR0 & (1<<TOV0)));
TIFR0 |= (1<<TOV0);
PORTB ^= (1 << PORTB5);}}*/
