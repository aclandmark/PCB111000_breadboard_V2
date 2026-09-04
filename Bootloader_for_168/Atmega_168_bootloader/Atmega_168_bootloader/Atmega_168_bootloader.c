

#include "Atmega_168_bootloader_header.h"
#define Version "Hex_txt_bootloader_V1 "

#define T0_delay_5ms  5,217
  
void Timer_T0_sub(char, unsigned char);



int main (void){ 											//Loaded at address 0x3800, the start of the boot loader section

if((eeprom_read_byte((uint8_t*)(0x1EF))) & 1)					//Test bit zero (set by verification and UNO programmer)
asm("jmp 0x3580");														//Jump to launcher which can set 0x1EF to zero

		PageSZ = 0x40; PAmask = 0x1FC0;										//Define flash memory parameters for Atmega 168

		record_length_old=0;				
		Flash_flag = 0;  HW_address = 0;  
		w_pointer = 0; r_pointer = 0; short_record=0; 

		UCSR0B |= (1<<RXCIE0); sei();										//Receive interrupts now active

		new_record();  														//Start reading first record which is being downloaded to array "store"
		start_new_code_block(); 											//Initialize new programming block (usually starts at address zero but not exclusively so)
		Program_record();													//Copy commands from array "store" to the page_buffer
			
			while(1){
				new_record();														//Continue reading subsequent records
				if (record_length==0)break; 										//Escape when end of hex file is reached
				
				switch(short_record){
					case 0: if (space_on_page == (PageSZ - line_offset))				//If starting new page
					{page_address = (Hex_address & PAmask);}break;			//get new page address
					

					case 1:	start_new_code_block();										//Short line with no break in file (often found in WinAVR hex files).
				short_record=0;break;}
	
			Program_record();}											//Continue filling page_buffer

		UCSR0B &= (~(1<<RXCIE0));	cli();									//download complete, disable UART Rx interrupt
		
		UCSR0B &= (~(1 << RXEN0));									//disable Rx module
		DDRD &= (~(1 << DDD0)); PORTD |= (1 << DDD0);				//Set Rx pins to week pull up
		Timer_T0_sub(T0_delay_5ms);									//Complete download
		//while(1){if (isCharavailable(5)==1)receiveChar();else break;}		//Clear last few characters of hex file
				
		if((Flash_flag) && (!(orphan))){write_page_SUB(page_address);}	//Burn final contents of page_buffer to flash
		if(orphan) {write_page_SUB(page_address + PageSZ);}cli();


		clear_read_block();											//Subroutine provided in assembly file
		
		asm("jmp 0x2E80");}											//Jump to verification routine




	/***********************************************************************************************************************************/
	ISR(USART_RX_vect){
		
		unsigned char Rx_askii_char;
	
	unsigned char Rx_Hex_char=0;
	int local_pointer;
		
	Rx_askii_char = receiveChar();	
				
	if (Rx_askii_char == ':')counter = 0;									//First char of hex file is ':'
	else {if (Rx_askii_char <= '9')
	Rx_Hex_char = Rx_askii_char - '0'; 										//Convert chars '0' to '9' to numbers 0 to 9
	else Rx_Hex_char = Rx_askii_char - '7';}								//and chars 'A' to 'F' to numbers 0xA to 0xF

	switch (counter){
	case 0x0:  	break;														//Detect -:- at start of new line
	case 0x1: 	tempInt1 = Rx_Hex_char<<4;  break;							//Acquire first digit
	case 0x2: 	tempInt1 += Rx_Hex_char;  									//Acquire second digit and combine with first to obtain number of commands in line
	char_count = 9 + ((tempInt1) *2); 										//Calculate line length in terms of individual characters
	local_pointer = w_pointer++; 											//Update pointer to array "store"
	store[local_pointer] = tempInt1; break;									//Save the number of commands in the line to the array
	case 0x3: 	tempInt1 = Rx_Hex_char<<4;  break;							//Next 4 digits give the address of the first command in the line
	case 0x4:	tempInt1 += Rx_Hex_char; tempInt1=tempInt1<<8; 
	break;																	//Acquire second digit and combine it with first
	case 0x5:	tempInt1 += Rx_Hex_char<<4;  break;							//Continue for third digit
	case 0x6: 	tempInt1 += Rx_Hex_char; 									//Acquire final digit and calculate address of next command
	local_pointer = w_pointer++; 											//Update pointers to array "store"
	store[local_pointer] = tempInt1; break;									//Save address of next command to array "store"
	case 0x7: 	break;														//chars 7 and 8 are not used
	case 0x8: 	break;
	default: 	break;}

	if ((counter > 8)&&(counter < char_count)){								//Continue to acquire, decode and store commands
	if ((counter & 0x03) == 0x01){tempInt1 = Rx_Hex_char<<4;}				//Note: Final two chars at the end of every line are ignored
	if ((counter & 0x03) == 0x02)  {tempInt1 += Rx_Hex_char;}
	if ((counter & 0x03) == 0x03)  {tempInt2 = Rx_Hex_char<<4;}
	if ((counter & 0x03) == 0x0)  	{tempInt2+= Rx_Hex_char;
	tempInt2=tempInt2<<8;tempInt1+=tempInt2;
	local_pointer = w_pointer++;
	store[local_pointer] = tempInt1; }}

	counter++;
	w_pointer = w_pointer & 0x1F;	}  											//Overwrites array after 32 entries




/*********************************************************************/
void Timer_T0_sub(char Counter_speed, unsigned char Start_point){
	TCNT0 = Start_point;
	TCCR0B = Counter_speed;
	while(!(TIFR0 & (1<<TOV0)));
TIFR0 |= (1<<TOV0); TCCR0B = 0;}
