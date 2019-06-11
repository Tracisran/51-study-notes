#include<reg52.h>
#include<intrins.h>
typedef unsigned int uint;
typedef unsigned char uchar;
void delayms(uint);
uint aa;
uint i=0;
sbit k1=P3^1;
sbit k3=P3^3;
void delay(uint j)
{
while(j--);
}
void keypros2()
{
if(k3==0)
	{
		delay(1000);
		if(k3==0)
		{
		i=!i;
		}
		while(k3==1);
		}	
}
void keypros1()
{
	if(k1==0)
	{
		delay(1000);
		if(k1==0)
		{
		i=!i;
		}
		while(k1==0);
	}
}
void main()
{
	aa=1;
	while(1)
	{
	keypros1();
	keypros2();	
	while(i)
	{
		P2=~aa;
		delayms(500);
		aa=aa*2;
		if (aa>128)
		aa=1;
		
	}
	}
	
}
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--)
		keypros1();
		keypros2();

}