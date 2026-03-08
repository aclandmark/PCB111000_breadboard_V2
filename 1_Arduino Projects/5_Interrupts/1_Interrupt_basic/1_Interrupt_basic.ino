

      //Six examples using a timer interrupt to drive the display
      //Take special care with examples 5 and 6: main routine has one extra line

#include "Interrupt_basic_header.h"

volatile long PORT_1 = 1, PORT_2 = 0x8000;                            //For example 1, 2 and 3
volatile int m = 0, n = 0, n_max;                                     //Extras for example 3
volatile unsigned int clock_rate = 500;                               //Extra for examples 2 and 3
volatile unsigned int PRN;                                            //For example 4
unsigned char PRN_counter = 0;                                        //For example 4
volatile unsigned char counter = 0;                                   //For example 4


volatile int switch_down = 0;
 int main (void)   
  {
  setup_HW;
set_up_PCI_on_sw3;                                             //Eamples 2 and 3 only
enable_pci_on_sw3;                                              //Eamples 2 and 3 only
    Clear_digit;

   String_to_PC_Basic("\r\n Momentarily switch pin4 to gnd to increase flash rate");
    
    sei();
   T1_clock_tick(clock_rate);
   //initialise_display();                                              //Examples 5 and 6 ONLY
while(1){if(switch_down){cli();_delay_ms(50); switch_down = 0;sei();}};
   SW_reset;
    }




//*****************************************************************************************************
void T1_clock_tick(unsigned int T1_period_in_ms)              //Sets up the T1 clock (default value of T1_period_in_ms is 150) 
{ TCNT1 = 0;                                                  //TCNT1 increases by 1 for each clock tick 
OCR1A = T1_period_in_ms * 125;                                //Set register OCR1A to 150 x 125 = 18750
  TIMSK1 |= (1 <<  OCIE1A);                                   //Generates an intrerrupt TCNT1 equals OCR1A (i.e. after 150mS) 
  TCCR1B = 0x03;}                                             //Starts the clock with a speed of 125 ticks per mS



//*****************************************************************************************************
ISR(PCINT2_vect) {  switch_down = 1;                                                    //Use with examples 2 & 3 only
  //if ((switch_2_down)|| (clock_rate <= 10))clock_rate = 150;
  //else
  
    //if (switch_1_down)clock_rate += 20;
  if (switch_3_down)clock_rate -= clock_rate/7;
  if(clock_rate <= 25)clock_rate = 500;
  }





//*****************************************************************************************************
/*void initialise_display()
{ n = 1;
  PORT_1 = 1;
  PORT_2 = 0x8000;
   n_max = 16;
  
 I2C_Tx_2_integers(PORT_1, PORT_2);}*/


//*****************************************************************************************************


//Type Timer1 ISR here

ISR(TIMER1_COMPA_vect)     
  { OCR1A = clock_rate * 125;
  TCNT1 = 0; 
   switch_Seg_c; }

/***************************************************************************************************************/



  



//********************************************************************************************************
