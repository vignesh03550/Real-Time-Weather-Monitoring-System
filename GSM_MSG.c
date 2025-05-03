

void UART0_config(void)
{
	PINSEL0|= 0x05;
	U0LCR = 0x83;
	U0DLL = 97;
	U0DLM = 0;
	U0LCR = 0x03;


}
void UART0_TX(unsigned char d)
{
	U0THR = d;
	while(((U0LSR>>5)&1)==0);
}
void UART0_STR(unsigned char * S)
{
	while(*S)
	{
	   UART0_TX(*S++);
	}
}

