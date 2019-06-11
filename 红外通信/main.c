#include "reg52.h"			 
	
typedef unsigned int u16;	  
typedef unsigned char u8;

sbit led1=P2^0;
sbit IRIN=P3^2;
sbit a=P1^4;
sbit b=P1^0;
u8 IrValue[6];
u8 Time;
//45h,46h,47h,44h,40h,43h,07h,15h,09h,16h,e4h,f3h,
//0ch,18h,5eh,08h,1ch,43h,4h,52h,4ah
void delay(u16 i)
{
	while(i--);	
}
void delay2(u16 i)
{	u16 j;
	for(i;i>0;i--)		
		for(j=100;j>0;j--);
}



void IrInit()
{
	IT0=1;
	EX0=1;
	EA=1;	

	IRIN=1;
}
void main()
{	
	IrInit();
	while(1)
	{	
	if((a==1)&&(b==1
	))
	{
	led1=0;
	delay2(24000);
	}
	else
	{led1=1;}

	if (((IrValue[2]/16)==4)&&((IrValue[2]%16)==5))
	{
	led1=0;delay2(24000);IrValue[2]=0;	
	}			   
	}
			   
}
		

void ReadIr() interrupt 0
{
	u8 j,k;
	u16 err;
	Time=0;					 
	delay(700);	
	if(IRIN==0)		
	{	 
		
		err=1000;				
		
		while((IRIN==0)&&(err>0))	  		
		{			
			delay(1);
			err--;
		} 
		if(IRIN==1)			
		{
			err=500;
			while((IRIN==1)&&(err>0))		
			{
				delay(1);
				err--;
			}
			for(k=0;k<4;k++)	
			{				
				for(j=0;j<8;j++)	
				{

					err=60;		
					while((IRIN==0)&&(err>0))
					{
						delay(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0))
					{
						delay(10);
						Time++;
						err--;
						if(Time>30)
						{
							return;
						}
					}
					IrValue[k]>>=1;	 
					if(Time>=8)			
					{
						IrValue[k]|=0x80;
					}
					Time=0;									
				}
			}
		}
		if(IrValue[2]!=~IrValue[3])
		{
			return;
		}
	}			
}

