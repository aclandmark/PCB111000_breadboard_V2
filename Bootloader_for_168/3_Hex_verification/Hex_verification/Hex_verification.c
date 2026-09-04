
/*
Compile it using optimization level s ONLY
Rx/Tx work at 57.6k

File size is 0x057E bytes
It is loaded at 0x3000 (0x1800 HW address) and ends at 0x357E
The launcher starts at 0x3580

Space for user apps is 0x3000 (12288) bytes		75%	
Space for bootloader is 0x1000 (4096) bytes		25%
*/


#define T1_delay_200ms 	3, 0x9E62

#include "Hex_verification.h"


int main (void){
	char mode;	
	
	sendString("\r\nVerification: 0 to skip, 1 for full or 2 for basic\r\n");	
		
	Timer_T1_sub(T1_delay_200ms);
	
	UCSR0B |= (1 << RXEN0);										//Turn receiver back on again
	
	mode = waitforkeypress() - '0';
	if (mode)
	{	prog_counter = FlashSZ;
		Verify_Flash(mode - 1);
	
		sendString("Hex_file_size:	0x");								//Confirm file sizes are all identical
		Hex_to_PC(read_ops*2); 

	sendString("\r\nFuses E, H, L and lock:\t");						//Print out device configuration bytes
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
		short_num_to_PC(Flash_readout);	sendChar('\t');	}}
	
	newline(); newline();											//Jump to here if verification not required

eeprom_write_byte((uint8_t*)0x1EF,0b11111101);

MCUSR = 0;
	wdt_enable(WDTO_15MS);
	while(1);														
return 1;}



/***************************************************************************************************************************************************/
void Verify_Flash (char print_mode){
	int  line_counter = 0;												//Controls printing of hex file
	int line_no;														//Refers to the .hex file
	signed int phys_address;											//Address in flash memory
	signed int prog_counter_mem;										//Initialized with size of .hex file used for programming
	
	phys_address = 0;  read_ops=0;
	line_no = 0; prog_counter_mem = prog_counter;


	while(1){if((prog_counter_mem <= 0))break;								//print out loop starts here, exit when finished
		Hex_cmd = readCMD(phys_address);
		phys_address++;
		
		if (print_mode){
		if(!(line_no%10))sendChar('*');		
		Timer_T0_sub(T0_delay_5ms);}
				
		else															//Print out required: Print all lines or just a selection
		{newline(); Hex_to_PC ((phys_address-1)*2);
			sendString("   "); line_counter++;
			 Hex_to_PC (Hex_cmd); 	}									//Print first command in askii or hex
	
		
		read_ops++;														//Value to be sent to PC for comparison with the hex filer size
		prog_counter_mem--;												//"prog_counter_mem" decrements to zero when the end of the file is reached
		for(int m=0; m<7; m++){    										//Read the next seven locations in the flash memory
			Hex_cmd = readCMD(phys_address);
			phys_address++;
			if(Hex_cmd == 0xFFFF)break;									//Read 0xFFFF: return to start of print out loop
			prog_counter_mem--;
			if(!(print_mode))
			{Timer_T0_sub(T0_delay_5ms);								//5ms delay prevents PC from getting overwhelmed with characters
			 Hex_to_PC (Hex_cmd);}
			read_ops++;
		if((phys_address >= FlashSZ))break;}
		if ( (!(print_mode)) && (!(line_counter%8)))sendString("\r\n");
			
		line_no++;
	if ((phys_address >= FlashSZ) || (Hex_cmd == 0xFFFF))break;}
newline(); }


