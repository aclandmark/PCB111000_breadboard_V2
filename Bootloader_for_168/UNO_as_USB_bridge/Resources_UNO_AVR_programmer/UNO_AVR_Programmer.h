
void Prog_EEPROM(void);

void Program_Flash_Hex (void);
void Program_Flash_Text(void);
void Verify_Flash_Hex(void);
void Verify_Flash_Text(void);
void upload_hex(void);
void upload_text(void);

void set_up_target_parameters(void);



void Clock_period(void){for(int p = 0; p<= 3; p++){asm("nop");}}

#define PGClock_L 
#define PGClock_H Clock_period();

#define T0_delay_10ms 5,183
#define T0_delay_5ms 5,220
#define T0_delay_2ms 4,195
#define T0_delay_20ms 5,100
#define T0_delay_33ms 5,0
#define T1_delay_250mS 5,0xF85E
#define T1_delay_500mS 5,0xF0BD
#define T1_delay_1sec 5,0xE17B

	
unsigned char reset_pin;



/************************************************************************************************************************************/
#define setup_328_HW \
CLKPR = (1 << CLKPCE);\
CLKPR = (1 << CLKPS0);\
ADMUX |= (1 << REFS0);\
initialise_IO;\
Define_programmining_pins;\
Reset_L;\
Timer_T0_sub(T0_delay_5ms);


/*
#define setup_328_HW \
CLKPR = (1 << CLKPCE);\
CLKPR = (1 << CLKPS0);\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
initialise_IO;\
Set_LED_ports;\
LEDs_off;\
Timer_T0_sub(T0_delay_5ms);\
Define_programmining_pins;\
Reset_L;\
Config_Xtal_port;\
USART_init(0,25);
*/

/************************************************************************************************************************************/





/************************************************************************************************************************************/
#define Define_programmining_pins   reset_pin = 0x08;  DDRC |= 0x08;
#define Reset_L PORTC &= ~(reset_pin)
#define Reset_H PORTC |= reset_pin


/************************************************************************************************************************************/
#define initialise_IO \
MCUCR &= (~(1 << PUD));\
DDRB = 0;\
DDRC = 0;\
DDRD = 0;\
PORTB = 0xFF;\
PORTC = 0xFF;\
PORTD = 0xFF;\

//All week pull ups


/************************************************************************************************************************************/




/**************************************************************************************************************************************/
#define Exit_programming_mode \
UCSR0B &= (~((1 << RXEN0) | (1<< TXEN0)));\
initialise_IO;\
Reset_H;\
while(1);


