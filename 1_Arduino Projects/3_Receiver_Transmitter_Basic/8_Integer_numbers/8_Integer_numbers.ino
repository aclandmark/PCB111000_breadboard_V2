



//Accepts an integer number at the keyboard and 
//prints out its factors.


/************************************************************************************************************/
#include "Integer_numbers_header.h"

#define message_1 "\r\nEnter integer number:  PCB returns all factors of that number.\r\n"
#define message_2 "\r\nNew number?\r\n"


//Type main routine here

int main (void)  
  { 
    char num_string[12];
    long  num;
    long m = 1;
 
 setup_HW;

if ((just_programmed) || (r_prompt))
{clear_resets;
String_to_PC_B(message_1);}

else String_to_PC_B(message_2);
  
num = Int_from_PC_B(num_string);

newline_B();
Int_to_PC_B(num);
String_to_PC_B("\t");

do{
if(!(num%m)){Int_to_PC_B(m);}
m += 1; if(!(m%10000))String_to_PC_B(".");}while(m < num);

SW_reset;
return 1;  }




/******************************************************************************************/
