#include "types.h"
//#include<lpc21xx.h>
#include "Delay.c"
#define LCD_D 0x0f<<20
#define RS 1<<17
#define RW 1<<18
#define E 1<<19
int i;
void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void str(u8 *);
void lcd_integer(int);
void Float_display(f32);
void str(u8 *s)

{

	while(*s)

		LCD_DATA(*s++);

}


void lcd_integer(int n)

{

	s8 arr[5],i=0;

	if(n==0)

		LCD_DATA('0');

	else

	{

		   if(n<0)

		   {

				 LCD_DATA('-');

				 n=-n;

       }

	      while(n>0)

      	{

		     arr[i++]=n%10;

		     n=n/10;

        }

        for(--i;i>=0;i--)

   	      LCD_DATA(arr[i]+48);

  }

}

void Float_display(f32 f_val)

{

  u32 number;

  number = f_val;

  lcd_integer(number);

  LCD_DATA('.');

  number=(f_val-number)*100;

  lcd_integer(number);	

}



void LCD_INIT(void){
	IODIR1=LCD_D|RS|E|RW;
	IOCLR1=RW;
	LCD_COMMAND(0x01);
	LCD_COMMAND(0x02);
	LCD_COMMAND(0x0c);
	LCD_COMMAND(0x28); 
	LCD_COMMAND(0x80);
 }
 void LCD_COMMAND(unsigned char CMD){
	IOCLR1=LCD_D;
	IOSET1=((CMD&0xf0)<<16);
	IOCLR1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=((CMD&0x0f)<<20);
	IOCLR1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;
	 }
void LCD_DATA(unsigned char d)
{
	IOCLR1=LCD_D;
	IOSET1=((d&0xf0)<<16);
	IOSET1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;

	IOCLR1=LCD_D;
	IOSET1=((d&0x0f)<<20);
	IOSET1=RS;
	IOSET1=E;
	Delay_milliseconds(2);
	IOCLR1=E;
	
}


