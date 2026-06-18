
//10 projects that explore
          //Text strings
          //Askii characters
          //Downloading and printing text files
          //Storing strings in working memory
          //Upper to lower case conversion
          //Printing .hex files with text in clear




#include "Receiver_Transmitter_header.h"
#include "Local_subroutines.c"


//Ten simple examples to experiment with.
int main (void)                //Example 6
  { setup_HW;         //Exploring program memory
  char *mem_add;
 wdt_enable(WDTO_120MS);
   
  
  String_to_PC_Local("\0Null string\r\n");
  String_to_PC_Local("Defining and using text strings\r\n\r\n");
  const char *message_1 = "Hello world\r\n";
  const char *message_2 = "Sending text to a PC\r\n";
  const char message_3[] = "Writing C programs and\r\n";
  const char message_4[] = "Uploading them to a device\r\n\r\n";
  String_to_PC_Local(message_1);
  String_to_PC_Local(message_2);
  String_to_PC_Local(message_3);
  String_to_PC_Local(message_4);
  while(switch_3_up)wdr();

 String_to_PC_Local("Print out of program memory\r\n\r\n");

mem_add = (char*)256;
for(int m = 0; m <=185; m++){
  if ((*(mem_add + m))== '\0')Hex_and_Int_to_PC_Basic (10,256+m);
 else Char_to_PC_Basic(*(mem_add + m));}
  newline_Basic();newline_Basic();
    while(switch_3_down)wdr();
   return 1;}
 



/*
  
 int main (void)               //Example 1
  { setup_HW;
  User_prompt;
  String_to_PC_Local("\r\nExploring the operation of the USART\r\n");
  Char_to_PC_Local('?');
  newline_Basic();
  while (1)
  { Char_to_PC_Local
    (waitforkeypress_Local());
  } return 1;}
  
  
  int main (void)             //Example 2
  { setup_HW;
  char keypress;
 
  if (watch_dog_reset == 1) String_to_PC_Local("\r\n?  ");
  else {User_prompt;String_to_PC_Local("\r\nWe often send\
  detailed text the first time our program runs\r\n\
  and a simple prompt on subsequent ocaissions\r\n\
  Enter number -cr- when done\r\n    ");}
  
  while (1)
  { keypress = waitforkeypress_Local();
    if  ((keypress =='\r') ||  (keypress =='\n'))break; 
    else Char_to_PC_Local(keypress); }
 SW_reset; }
 
 
  int main (void)              //Example 3
  { char symbol;        //Prints all askii symbols
  setup_HW;
  newline_Basic();
  symbol = '!';
  while (symbol <= '~')
  { Char_to_PC_Local(symbol);
    _delay_ms(10);
    symbol++;
    wdr();
  }
  waitforkeypress_Local();
  SW_reset;
  return 1; } 
  
  
  
  
  int main (void)                //Example 6
  { setup_HW;         //Exploring program memory
  char *mem_add;
 wdt_enable(WDTO_120MS);
   
  
  String_to_PC_Local("\0Null string\r\n");
  String_to_PC_Local("Defining and using text strings\r\n\r\n");
  const char *message_1 = "Hello world\r\n";
  const char *message_2 = "Sending text to a PC\r\n";
  const char message_3[] = "Writing C programs and\r\n";
  const char message_4[] = "Uploading them to a device\r\n\r\n";
  String_to_PC_Local(message_1);
  String_to_PC_Local(message_2);
  String_to_PC_Local(message_3);
  String_to_PC_Local(message_4);
  while(switch_3_up)wdr();

 String_to_PC_Local("Print out of program memory\r\n\r\n");

mem_add = (char*)256;
for(int m = 0; m <=185; m++){
  if ((*(mem_add + m))== '\0')Hex_and_Int_to_PC_Basic (10,256+m);
 else Char_to_PC_Basic(*(mem_add + m));}
  newline_Basic();newline_Basic();
    while(switch_3_down)wdr();
   return 1;}
 
 */


//**************************************************************************************************************************************
