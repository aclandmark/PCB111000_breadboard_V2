

#include "0_project_zero_header.h"


int main (void)    //Example 2  Red LED flashes
{  setup_HW;
 Clear_digit;
if(switch_3_down){wdt_enable(WDTO_250MS); _delay_ms(60);}
else wdt_enable(WDTO_60MS);
 c_on;
 while(1);}
