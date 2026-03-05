
/*
This program is used to verify that a hex file has been successfully loaded into flash.
It is loaded onto the Atmega328 at address 0x6880 and works alongside the "Hex_text_programmer".
It is accessed by the "Hex_text_programmer" using an assembly jump command and a WDTout returns
control the the "Hex_text_programmer"
The EEPROM is used to share variables between the two programs

Compile it using optimisation level s ONLY
Rx/Tx work at 57.6k
*/


#include "Hex_verification.h"



int main (void){
	char digits[8];	
	//cmd_counter = ((eeprom_read_byte((uint8_t*)0x3F9)) << 8) +
	//eeprom_read_byte((uint8_t*)0x3F8);

sendString("cmd_counter?\t");
cmd_counter = (Int_from_PC(digits))/2;						///0x40;
Hex_to_PC (cmd_counter);
	prog_counter = cmd_counter;											//These are the same if everything is working OK

	sendString("\t0 to verify or AOK\r\n");								//Press '0' to read out hex file from flash
	if (!(waitforkeypress() - '0'))
	{Verify_Flash();
		newline();
		sendString("Hex_file_size:	0x");								//Confirm file sizes are all identical
		Hex_to_PC(cmd_counter); sendString("  d'loaded:  0x");
		
	Hex_to_PC(read_ops); sendString(" out\r\n");}

	sendString("UNO Fuses E, H, L and lock:\t");						//Print out device configuration bytes
	address_in_flash = 0;
	for(int m = 0; m<4; m++){
		switch(m){
			case 0: address_in_flash = 2; break;						//Print Fuse byte Extended
			case 1: address_in_flash = 3; break;						//Print Fuse byte High
			case 2: address_in_flash = 0; break;						//Print Fuse byte
		case 3: address_in_flash = 1; break;}							//Print lock byte

		Prog_mem_address_H = address_in_flash >> 8;
		Prog_mem_address_L = address_in_flash;
		read_config_bytes();
		short_num_to_PC(Flash_readout);	sendChar('\t');
	}newline(); newline();

MCUSR = 0;
//Write to EEPROM so that bootloader WDTimeouts can be distiguished from project WDTimeouts
	wdt_enable(WDTO_15MS);
	while(1);
return 1;}



/***************************************************************************************************************************************************/
void Verify_Flash (void){
	int  line_counter = 0, print_line = 1;								//Controls printing of hex file
	int line_no;														//Refers to the .hex file
	signed int phys_address;											//Address in flash memory
	signed int prog_counter_mem;										//Initialised with size of .hex file used for programming
	//char print_out_mode = 0;											//Print out flash contents as hex or askii characters
	//char skip_lines[4];													//Enter number to limit the print out

	phys_address = 0;  read_ops=0;
	line_no = 0; prog_counter_mem = prog_counter;
	FlashSZ = 0x1400;

	
	while(1){if((prog_counter_mem <= 0))break;								//print out loop starts here, exit when finished
		while(1){														//Start reading the flash memory searching for the next hex command
			Hex_cmd = readCMD(phys_address);
			phys_address++;
			if (phys_address >= FlashSZ)break;							//No more memory? Quit if yes
			if (Hex_cmd != 0xFFFF) break;								//If the hex command is 0xFFFF remain in this loop otherwise exit.
		LED_1_on;}
		LED_1_off;
		if (print_line == 0){
		if(!(line_no%10))sendChar('*');	
		if(!(line_no & 0b00010000))toggle_led_1;	
		Timer_T0_sub(T0_delay_5ms);}
				
		if(print_line && (!(line_no%print_line)))						//Print out required: Print all lines or just a selection
		{newline(); Hex_to_PC ((phys_address-1)*2);
			sendString("   "); line_counter++;
			 Hex_to_PC (Hex_cmd); 										//Print first command in askii or hex
		if(!(line_no & 0b00100000))toggle_led_1;}
		
		read_ops++;														//Value to be sent to PC for comparison with the hex filer size
		prog_counter_mem--;												//"prog_counter_mem" decrements to zero when the end of the file is reached
		for(int m=0; m<7; m++){    										//Read the next seven locations in the flash memory
			Hex_cmd = readCMD(phys_address);
			phys_address++;
			if(Hex_cmd == 0xFFFF)break;									//Read 0xFFFF: return to start of print out loop
			prog_counter_mem--;
			if(print_line && (!(line_no%print_line)))
			{Timer_T0_sub(T0_delay_5ms);								//5ms delay prevents PC from getting overwhelmed with characters
			 Hex_to_PC (Hex_cmd);}
			read_ops++;
		if(phys_address >= FlashSZ)break;}
		if ((print_line != 0) && (!(line_no%print_line)) && (!(line_counter%8)))sendString("\r\n");
		line_no++;
	if (phys_address >= FlashSZ)break;}
	LED_1_off;
newline(); }
