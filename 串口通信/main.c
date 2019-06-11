#include<reg52.h>
typedef unsigned int u16;
typedef unsigned char u8;

void UsartInit()
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X80;			//�����ʼӱ�
	TH1=0XF3;				//��������ʼֵ���ã�ע�Ⲩ������4800��
	TL1=0XF3;
	ES=1;						//�򿪽����ж�
	EA=1;						//�����ж�
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