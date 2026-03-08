
/*
 A crude attempt to implement a new line function without also
 resetting the cursor to the start of the line 
 */

volatile char sym_counter;

#include "4C_Rx_interrupt_header.h"


//Type main here

int main (void)
  { char symbol;
    char q = 0;
    int n = 0;
    
  setup_HW;

  if (watch_dog_reset != 1)
newline_Basic();

    UCSR0B |= (1 << RXCIE0);
  sei();
newline_Basic();

while (1);
  

  cli();waitforkeypress_Basic();
  
newline_Basic();
SW_reset;}


ISR(USART_RX_vect){
  char keypress;
if ((keypress = Char_from_PC_Basic()) != '!'){sym_counter++;Char_to_PC_Basic(keypress);return;}
else
newline_Basic();
for (int m = 0; m <= sym_counter; m++)String_to_PC_Basic(" ");}




/*******************************************************************/
