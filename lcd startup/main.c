#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char 
#define DATE_IO P0
sbit RS=P2^6;
sbit E=P2^7;
sbit RW=P2^5;

uchar code table[]="00:00";
uchar code table1[]="0123456789";

void delay_us(unsigned int n) //延时 如果需要高精度延时 请嵌入汇编
{ 
	if (n == 0) 
	{  
	 	return ;  
	} 
  	while (--n);
}
 /*延时函数*/
void delay_ms(uint i) 
{ 
	unsigned char a, b; 
	for (a = 1; a < i; a++) 
	{
   		for (b = 1; b; b++) 
   		{   
			;   
		} 
    }
}
void delay(uint z)
{
	uint x,y;
	for(x=110;x>0;x--)
		for(y=z;y>0;y--);
}
void write_come(uchar come)
{
	RS=0;
	E=1;
	DATE_IO=come;
	delay_us(5);
	E=0;
	RS=1;
}		
void write_date(uchar date)
{
	RS=1;
	E=1;
	DATE_IO=date;
	delay_us(5);
	E=0;
	RS=0;
}		
void init()//这个是初始化函数 你自己理解一下其实差不多是一样的 
{
	RW=0;
	E=0;
	write_come(0x38);
	delay_ms(5);
	write_come(0x08);
	delay_ms(5);
	write_come(0x01);
	delay_ms(5);
	write_come(0x06);
	
	write_come(0x0c);
	delay_ms(5);
}
void init_time()
{
	uchar i;
	for(i=0;i<5;i++)
	{
		write_come(0x80+i);
		write_date(table[i]);
	}
}
void main()
{
	uchar miao,fen,miaoge,miaoshi,fenshi,fenge;
	init();
	init_time();
	while(1)
	{
		miaoge=miao%10;
		miaoshi=miao/10;
		
		write_come(0x80);
		write_date(table1[fenshi]);
		write_date(table1[fenge]);
		write_date(table[2]);
		write_date(table1[miaoshi]);	
		write_date(table1[miaoge]);	
		miao++;
		if(miao==60)
		{
			miao=0;
			fen++;
			fenge=fen%10;
			fenshi=fen/10;
			if(fen==60)
				fen=0;
		}
		delay(1000);
		
	}	
}