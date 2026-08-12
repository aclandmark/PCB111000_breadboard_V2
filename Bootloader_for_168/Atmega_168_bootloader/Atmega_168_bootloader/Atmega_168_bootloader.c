/*
Bootloader for PCB111000_CP2102.
Uploads user apps to the Atmega328
Uploads commentary text file to Atmega328 flash when pcb is being set up.

Loaded at address 0x7000


EEPROM locations
0x3FF	User cal
0x3FE	User cal
0x3FD	Default cal
0x3FC	Controls reset and program flow						
	bit 0	POR_bit	
	bit 1	WDTout_bit
	bit 2	Run_BL_bit
	bit 3	prtD_bit
	Note: There is no external reset facility. User control is enabled using a switch on PINC5.

0x3FB	prog_counter high byte				No longer used
0x3FA	prog_counter low byte				No longer used
0x3F9	cmd_counter high byte				Number of commands processed by the UART ISR
0x3F8	cmd_counter low byte
0x3F7	One_wire_cal
0x3F6	One wire cal
0x3F5	Watch dog timeout					No longer used
0x3F4	Used to control text print out  	No longer needed
0x3F3	Used by PRN generators
0x3F2	Used by PRN generators
0x3F1	Reserved or use by PRN
0x3F0	Reserved or use by PRN
0x3EF	Reserved or use by PRN
0x3EE	Reserved or use by PRN
0x3ED	PRN_offset 0, 1 or 2 

*/

#include "Atmega_168_bootloader_header.h"
#define Version "Hex_txt_bootloader_V1 "

#define Reset_control_switch_up		(PINC & 0x20)

#define reset_ctl_reg				0x3FC
/*#define set_POR_bit					eeprom_write_byte((uint8_t*)reset_ctl_reg, ~1)
#define set_WDTout_bit				eeprom_write_byte((uint8_t*)reset_ctl_reg,(eeprom_read_byte((uint8_t*)reset_ctl_reg) & ~2))
#define	set_Run_BL_bit				eeprom_write_byte((uint8_t*)reset_ctl_reg,(eeprom_read_byte((uint8_t*)reset_ctl_reg) & ~4))
#define set_prtD_bit				eeprom_write_byte((uint8_t*)reset_ctl_reg, ~8)
#define prtD_bit_clear				(eeprom_read_byte((uint8_t*)reset_ctl_reg) & 8)			
#define Run_BL_bit_clear			(eeprom_read_byte((uint8_t*)reset_ctl_reg) & 4)
*/

char mode;													//'h' for hex file, 't' for text file

int main (void){ 											//Loaded at address 0x7000, the start of the boot loader section

asm("jmp 0x3580");

//if(!(MCUSR & 2)) asm("jmp 0x0000");

//MCUCR = (1<<IVCE);  										//Select the interrupt vector table starting at start of boot section
//MCUCR = (1<<IVSEL);

//setup_HW;

		PageSZ = 0x40; PAmask = 0x1FC0;										//Define flash memory parameters for Atmega 168

		record_length_old=0;				
		Flash_flag = 0;  HW_address = 0;  
		w_pointer = 0; r_pointer = 0; short_record=0; 

		//sendString("\r\nHex_F?");
		
		UCSR0B |= (1<<RXCIE0); sei();										//Receive interrupts now active

		new_record();  														//Start reading first record which is being downloaded to array "store"
		start_new_code_block(); 											//Initialize new programming block (usually starts at address zero but not exclusively so)
		Program_record();													//Copy commands from array "store" to the page_buffer
			
			while(1){
				new_record();														//Continue reading subsequent records
				if (record_length==0)break; 										//Escape when end of hex file is reached
				
				if(!(short_record)){
					if (space_on_page == (PageSZ - line_offset))				//If starting new page
					{page_address = (Hex_address & PAmask);}}					//get new page address
					
					else	start_new_code_block();										//Short line with no break in file (indicates start of text string section).
				short_record=0;
				
			Program_record();	}											//Continue filling page_buffer

		UCSR0B &= (~(1<<RXCIE0));	cli();									//download complete, disable UART Rx interrupt
		while(1){if (isCharavailable(5)==1)receiveChar();else break;}		//Clear last few characters of hex file
				
		if(Flash_flag){write_page_SUB(page_address);}						//Burn final contents of page_buffer to flash
		cli();

		clear_read_block();											//Subroutine provided in assembly file
		asm("jmp 0x3100");}




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



