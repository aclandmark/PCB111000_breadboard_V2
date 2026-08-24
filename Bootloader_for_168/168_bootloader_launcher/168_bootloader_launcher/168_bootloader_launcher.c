

/*
Contains HW set up code and strings that are not essential to the bootloading processes

All resets take program control to 0x3800 the start of the bootloader partition
from there a jump to this application is executed immediately
*/

#define F_CPU 8000000

#include <util/delay.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <stdint.h>
#include <stdio.h>

char User_response;
char watch_dog_reset;

#define cal_device \
eeprom_write_byte((uint8_t*)0x1FD, OSCCAL);\
if ((eeprom_read_byte((uint8_t*)0x1FE) > 0x0F)\
&&  (eeprom_read_byte((uint8_t*)0x1FE) < 0xF0) && (eeprom_read_byte((uint8_t*)0x1FE)\
== eeprom_read_byte((uint8_t*)0x1FF))) OSCCAL = eeprom_read_byte((uint8_t*)0x1FE);


#define Initialise_I_O \
MCUCR &= (~(1 << PUD));\
DDRB = 0;\
DDRC = 0;\
DDRD = 0;\
PORTB = 0xFF;\
PORTC = 0xFF;\
PORTD = 0xFF;

		
#define setup_watchdog \
if (MCUSR & (1 << WDRF))watch_dog_reset = 1;\
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}



void USART_init (unsigned char UBRROH_N, unsigned char UBRR0L_N ){
	UCSR0B = 0;
	UBRR0H = UBRROH_N;
	UBRR0L = UBRR0L_N;
	UCSR0A = (1 << U2X0);
	UCSR0B = (1 << RXEN0) | (1<< TXEN0);
UCSR0C =  (1 << UCSZ00)| (1 << UCSZ01);}


void sendChar(char data){
	while (!(UCSR0A & (1 << UDRE0)));
UDR0 = data;}


void sendString(char s[]){
	int i = 0;
	while(1){
		if(s[i] == '\0') return;
	sendChar(s[i++]);}}



	char isCharavailable (int m){int n = 0;
		while (!(UCSR0A & (1 << RXC0))){n++;
			if (n>4000) {m--;n = 0;}if (m == 0)return 0;}
		return 1;}

		char receiveChar(void)
		{return UDR0;}


		



int main (void){									//Loaded at address 0x3580, just ahead of the boot loader section

	if(!(MCUSR & 2)) 								//For EXTRF skip the jmp 0x0000 command
	{asm("jmp 0x0000");}							//Jump to application code for POR and WDTout				
	
	MCUSR &= (~(1 << EXTRF));						//Clear EXTRF
	
	setup_watchdog;
	ADMUX |= (1 << REFS0);
	cal_device;
	Initialise_I_O;
	USART_init(0,16);
	for(char p = 0; p<= 100; p++){asm("nop");}
	
	while(1){
	do{sendString("p/r    ");}  while((isCharavailable (250) == 0));
	User_response = receiveChar();
	switch(User_response){
		case 'p': break;
		case 'r': eeprom_write_byte((uint8_t*)0x1EF,0b11111011);
		asm("jmp 0x0000");break;
		default: sendString("?\r\n");continue; break;}
		if(User_response =='p')break;}
	
	sendString("\r\nSend_Atmega 168 Hex file\r\n");


MCUCR = (1<<IVCE);  								//Select the interrupt vector table starting at start of boot section
MCUCR = (1<<IVSEL);
				
eeprom_write_byte((uint8_t*)0x1EF,0b11111110);		//Activates bootloading
asm("jmp 0x3800");}									//Jump to bootloader

