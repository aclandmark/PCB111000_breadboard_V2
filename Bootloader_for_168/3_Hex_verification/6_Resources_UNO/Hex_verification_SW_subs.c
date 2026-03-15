




/*********************************************************************************************/
void newline(void){sendString ("\r\n");}



/***********************************************************************************************/
void Timer_T0_sub(char Counter_speed, unsigned char Start_point){ 
TCNT0 = Start_point;
TCCR0B = Counter_speed;
while(!(TIFR0 & (1<<TOV0)));
TIFR0 |= (1<<TOV0); TCCR0B = 0;}



/*********************************************************************/
void Timer_T1_sub(char Counter_speed, unsigned int Start_point){ 
TCNT1H = (Start_point >> 8);
TCNT1L = Start_point & 0x00FF;
TIFR1 = 0xFF;
TCCR1B = Counter_speed;
while(!(TIFR1 & (1<<TOV1)));
TIFR1 |= (1<<TOV1); 
TCCR1B = 0;}



/***********************************************************************************************/
void Hex_to_PC(int hex){
short_num_to_PC(hex>>8);											//Send hex integer to PC
short_num_to_PC(hex);
sendString(" ");}




/***********************************************************************************************/ 
void short_num_to_PC(char x)										//convert a number to three chars
{if((x>>4)>0x9)
sendChar((x>>4) + '0' + 7);
else sendChar((x>>4) + '0');

if((x&0xF)>0x9)
sendChar((x & 0xF) + '0' + 7);		
else sendChar((x & 0xF) + '0');}	




/***********************************************************************************************/
int readCMD(int address_in_flash){
int cmd;
address_in_flash = address_in_flash*2;
Prog_mem_address_H = (address_in_flash) >> 8;
Prog_mem_address_L = address_in_flash;
read_flash ();																		//Subroutine provided in assembly file
cmd = Flash_readout << 8;
address_in_flash += 1;
Prog_mem_address_H = (address_in_flash) >> 8;
Prog_mem_address_L = address_in_flash;
read_flash ();
cmd += Flash_readout;
return cmd;}

