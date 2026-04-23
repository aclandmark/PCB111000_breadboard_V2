
#include<stdlib.h>
#include<string.h>


void Char_to_PC_Basic(char);
long unpack_FPN(float, int *);
void Long_to_PC(long);
void Int_to_PC_Basic (long);
void String_to_PC_Basic(const char *);
long divide(long, long, long *, long *, int);
char waitforkeypress_Basic(void);
void invert_num_string(char *);
void display_real_num(char*);

void Display_string_to_askii(char * real_num_string){
  char dp_locator;
  
for(int m = 0; m <= 11; m++)if (!(real_num_string[m] & 0x80));
else {dp_locator = m + 2; real_num_string[m] &= ~0x80; break;}
for(int n = 11; n >= dp_locator; n--)
real_num_string[n] = real_num_string[n - 1];
real_num_string[dp_locator - 1] = '.';}


void askii_to_display_string(char * num_string){
  int m;
  char dp = 0;
  for(m = 0; m < 9; m++) {
  if(!(num_string[m]))break;
  if (dp) dp += 1;
  if (num_string[m] == '.'){num_string[m-1] |= 0x80; dp = 1;}
  if(dp > 1){num_string[m-1] = num_string[m];}}
  num_string[8] = 0;
  invert_num_string(num_string);
/*
Display_string_to_askii(num_string);
String_to_PC_Basic("\r\n");
String_to_PC_Basic(num_string);*/
  
  display_real_num(num_string);  }

/**********************************************************************************/
/*void display_string_to_PC(char * real_num_string){
for(int m = 0; m <=11; m++)
{if(!(real_num_string[m]))break;
  if(real_num_string[m] & 0x80){Char_to_PC_Basic(real_num_string[m] & ~0x80);
Char_to_PC_Basic('.');}
else Char_to_PC_Basic(real_num_string[m]);}}*/


/**********************************************************************************/
void Fnum_to_string(float Fnum, char* num_string){
int twos_expnt;
long digits;
long Divisor = 1;
long res, remainder;
int no_decimal_places = 7;
int str_ptr;

digits = unpack_FPN(Fnum, &twos_expnt);

twos_expnt = 23 - twos_expnt;
for(int m = 0; m < twos_expnt; m++) Divisor *= 2;

Int_to_PC_Basic (digits);
String_to_PC_Basic("divided by ");
Int_to_PC_Basic(Divisor);
String_to_PC_Basic(" equals ");

divide(digits, Divisor, &res, &remainder, no_decimal_places);
 
  ltoa(res, num_string, 10);
  str_ptr = strlen(num_string);
  num_string[str_ptr++] = '.';
  
 
    while (no_decimal_places) {
  no_decimal_places =    divide(remainder*10, Divisor, &res, &remainder, no_decimal_places);
   num_string[str_ptr++] = res + '0';if(str_ptr == 9)break;
   }
  num_string[str_ptr] = '\0';}



/**********************************************************************************/
long unpack_FPN(float FPN, int *twos_expnt)
{long FPN_digits;

FPN_digits = (*(long*)&FPN);                                      //Read the FPN using a long pointer
*twos_expnt = (FPN_digits >> 23) - 127;                           //Exponent occupies bits 0 to 7
FPN_digits = (FPN_digits & 0x7FFFFF);                             //Isolate bits zero to 22
FPN_digits |= ((unsigned long)0x80000000 >> 8);                   //Add the unsaved 1 to bit 23
return FPN_digits;}



/********************************************************/
void Binary_to_PC(long num, char mode){

if(!(mode)){
for(int m = 0; m <= 31; m++){  
  if(num & ((unsigned long)0x80000000 >> m)) 
Char_to_PC_Basic('1'); else Char_to_PC_Basic('0');

switch (m)
  {case 0:   case 8:  case 12:  case 16:  case 20:
  case 24:  case 28:  Char_to_PC_Basic(' ');break;
  }}return;}

  else
  
  for(int m = 0; m <= 31; m++){  
  if(num & ((unsigned long)0x80000000 >> m)) 
Char_to_PC_Basic('1'); else Char_to_PC_Basic('0');

switch (m)
  {case 0:     case 11:  case 15:  case 19:
  case 23:  case 27:  Char_to_PC_Basic(' ');break;
  case 8: Char_to_PC_Basic(' ');Char_to_PC_Basic('1');break;}}}



/***********************************************************************************************/
  long divide(long A, long B, long *Div, long *mod, int no_decimal_places)
  {*Div = A/B;
  *mod = A%B;
  no_decimal_places -= 1;
  return no_decimal_places; } 


  /****************************************************************************************************/


/************************************************************/
