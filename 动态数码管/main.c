#include<reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
uint num[]={0,0,0,0,0,0,0,0,0};
uchar code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					  0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
i=1;
void p(uchar i)
{

if(num[i]<9)
		{
		num[i]++;
		}
	else
		{
		num[i]=0;
		p(i+1);
		}
}
void digdisplay(uint i , uint j )
{	uint k;k=100;
	switch(i)
	{
		case(0): LSA=0;LSB=0;LSC=0;break;
		case(1): LSA=1;LSB=0;LSC=0;break;
		case(2): LSA=0;LSB=1;LSC=0;break;
		case(3): LSA=1;LSB=1;LSC=0;break;
		case(4): LSA=0;LSB=0;LSC=1;break;
		case(5): LSA=1;LSB=0;LSC=1;break;
		case(6): LSA=0;LSB=1;LSC=1;break;		
		case(7): LSA=1;LSB=1;LSC=1;break;
	}
	P0=smgduan[j];
	for(k;k>0;k--);
	P0=0x00;
}
void delay(uint i)
{
for(i;i>0;i--)
	{
		digdisplay(7,num[8]);
		digdisplay(6,num[7]);
		digdisplay(5,num[6]);
		digdisplay(4,num[5]);
		digdisplay(3,num[4]);
		digdisplay(2,num[3]);
		digdisplay(1,num[2]);
		digdisplay(0,num[1]);	
	}
}
void main()
{
	while(1)
	{ 
	delay(10);
	p(1);
	}

}