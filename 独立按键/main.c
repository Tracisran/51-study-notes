#include<reg52.h>
typedef unsigned int uint;
sbit led = P2^0;
sbit k1=P3^1;
void delay(uint i)
{
	while(i--);
}
void keypros()
{
	if (k1==0)
		{
		delay (5000);
			if (k1==0)
				{
				led=~led;
				while (k1==0);
				}
				
		
		}
}
void main()
{
	while(1)
	{
	keypros();

	}
}
