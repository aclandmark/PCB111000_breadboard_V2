

#include <avr/wdt.h>

char watch_dog_reset;

#define T0_delay_10ms   5,178

#define setup_HW \
Clear_digit;\
setup_watchdog;\
ADMUX |= (1 << REFS0);\
Set_Led_outputs;\
set_up_switched_inputs;\
setup_PC_comms_Basic(0,16);\
Timer_T0_10mS_delay_x_m(5);


#define setup_watchdog \
if (MCUSR & (1 << WDRF))watch_dog_reset = 1;\
wdr();\
MCUSR &= ~(1<<WDRF);\
WDTCSR |= (1 <<WDCE) | (1<< WDE);\
WDTCSR = 0;

#define wdr()  __asm__ __volatile__("wdr")

#define SW_reset {wdt_enable(WDTO_30MS);while(1);}

#define Set_Led_outputs \
DDRB = (1 << DDB5) | (1 << DDB4) | (1 << DDB3) | (1 << DDB2);\
DDRD = (1 << DDD5) | (1 << DDD6) | (1 << DDD7);

#define a_off   PORTD |= (1 << PD6);
#define a_on  PORTD &= (~(1 << PD6));

#define b_off   PORTD |= (1 << PD5);
#define b_on  PORTD &= (~(1 << PD5));

#define c_off   PORTB |= (1 << PB5);
#define c_on  PORTB &= (~(1 << PB5));
#define   switch_Seg_c  PORTB ^= (1 << PB5);

#define d_off   PORTB |= (1 << PB3);
#define d_on  PORTB &= (~(1 << PB3));

#define e_off   PORTB |= (1 << PB2);
#define e_on  PORTB &= (~(1 << PB2));

#define f_off   PORTD |= (1 << PD7);
#define f_on  PORTD &= (~(1 << PD7));

#define g_off   PORTB |= (1 << PB4);
#define g_on  PORTB &= (~(1 << PB4));
#define g_is_on   (!(PORTB & (1 << PB4)))

#define set_up_switched_inputs \
MCUCR &= (~(1 << PUD));\
DDRD &= (~(1 << PD2));\
PORTD |= (1 << PD2);

#define set_up_PCI_on_sw3                PCICR |= (1 << PCIE2);
#define enable_pci_on_sw3                PCMSK2 |= (1 << PCINT18);


#define switch_3_down ((PIND & 0x04)^0x04)
#define switch_3_up   (PIND & 0x04)

#define Clear_digit    PORTD |= ((1 << PD5) | (1 << PD6)| (1 << PD7));\
PORTB |= ((1 << PB2) | (1 << PB3)| (1 << PB4) | (1 << PB5));


/*****************************************************************************/
#include "Resources/Subroutines/HW_timers.c"
#include "Resources/PC_comms/Basic_Rx_Tx_Basic.c"
#include "Resources/Subroutines/Random_and_prime_nos.c"


/******************************************************************************/
