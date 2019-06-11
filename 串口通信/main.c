#include<reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=0XF3;				//计数器初始值设置，注意波特率是4800的
	TL1=0XF3;
	ES=1;						//打开接收中断
	EA=1;						//打开总中断
	TR1=1;
}
void main()
{
UsartInit();
while(1);

}
void Usart() interrupt	 4
{
	u8 receiveData;
	receiveData=SBUF;
	RI=0;
	SBUF=receiveData;
	while(!TI);
	TI=0;

}