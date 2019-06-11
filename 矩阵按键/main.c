#include<reg52.h>
typedef unsigned int uint;
sbit led1=P2^0;
sbit led2=P2^1;
sbit led3=P2^2;
sbit led4=P2^3;
void delay(uint i)
{
	while(i--);
}
void Keydown()
{
P1=0x0f;
if(P1!=0x0f)
{
	delay(100);
	if(P1!=0x0f)
	{
		switch(P1)
		{
			case(0x07):led1=~led1;break;
			case(0x0b):led2=~led2;break;
			case(0x0d):led3=~led3;break;
			case(0x0e):led4=~led4;break;
		}
	}
	while(P1!=0x0f)

}
}
void main ()
{
	while(1)
	{
	keydown();
	 }
}