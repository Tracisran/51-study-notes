#include <reg52.h>
typedef unsigned int uint;
uint i;
uint j;
sbit a=P1^5;
sbit b=P1^6;
sbit c=P1^7;
sbit k1=P3^1;
sbit k3=P3^3;

void delay(uint i)
{
	uint j;
	for(i;i>0;i--)		
		for(j=100;j>0;j--);
}
void keypros1()
{
	if (k1==0)
		{
		delay (50);
			if (k1==0)
				{
				a=~a;
				b=~b;
				while (k1==0);
				}						
		}
}
void keypros3()
{
	if (k3==0)
		{
		delay (50);
			if (k3==0)
				{
				i=i+10;
				while (k3==0);
				}						
		}
}
void delayms(uint i)
{
	while(i--);
	keypros1();
	keypros3();

	}

void main ()
	{
	a=1;
	b=0;
	i=10;

	while(1)
	{
		while(1)
		{
		delayms(100);
		c=~c;
		delayms(i);
		c=~c;
		}
	}
	}