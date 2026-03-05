

void timer_T0_sub(char, unsigned char);




/*********************************************************************************************/
void USART_init (unsigned char UBRROH_N, unsigned char UBRR0L_N ){
{twenty_msec_delay;}	
UCSR0B = 0;
UBRR0H = UBRROH_N;  
UBRR0L = UBRR0L_N;  
UCSR0A = (1 << U2X0);
UCSR0B = (1 << RXEN0) | (1<< TXEN0);
UCSR0C =  (1 << UCSZ00)| (1 << UCSZ01);} 


/*********************************************************************************************/
void sendString(char s[]){
int i = 0;
while(i < 200){
if(s[i] == '\0') break;
sendChar(s[i++]);} }



/*********************************************************************************************/
char isCharavailable (int m){int n = 0;		
while (!(UCSR0A & (1 << RXC0))){n++;
if (n>4000) {m--;n = 0;}if (m == 0)return 0;}
return 1;}


/*********************************************************************************************/
char receiveChar(void)
{return UDR0;}



/*********************************************************************************************/
void sendChar(char data){
while (!(UCSR0A & (1 << UDRE0)));
UDR0 = data;}



/*********************************************************************************************/
char waitforkeypress(void){
while (!(UCSR0A & (1 << RXC0)));
return UDR0;}

char decimal_digit_Basic (char data){                      //Returns 1 if data is a character of 0 to 9 inclusive
	if (((data > '9') || (data < '0')) )return 0;             //Otherwise return zero
else return 1;}

char wait_for_return_key_Basic(void){                              //Returns key presses one at a time
	char keypress;
	while(1){													 //Remain in while loop until a character is received
		if (isCharavailable(8)){									//Pauses but returns 1 immediately that a character is received
			keypress = receiveChar();							 //Skip if no character has been received
		break;}}													//Exit while loop when character has been read
		if((keypress == '\r') || (keypress == '\n')){             //Detect \r\n, \r or \n and converts to \r
			if (isCharavailable(1)){receiveChar();}
		keypress = '\r';}
	return keypress;}



	int Int_from_PC(char digits[]){
		char keypress;
		int p = 0;
		for(int n = 0; n<=7; n++) digits[n] = 0;

		do
		{keypress =  waitforkeypress();}
		while (!(decimal_digit_Basic(keypress)));                                      //(non_decimal_char(keypress));  //Not -,0,1,2,3,4,5,6,7,8 or 9
		digits[p++] = keypress;

		while(1){
			if ((keypress = wait_for_return_key_Basic())  =='\r')break;
			if (decimal_digit_Basic (keypress))                                           //012345678or9  :Builds up the number one keypress at a time
		digits[p++] = keypress;}
		
	return atoi(digits);}
	
	
	
