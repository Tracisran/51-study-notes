#include"reg51.h"

sbit Left_1_led =P2^0; //��·Ѱ��ģ��ӿڵ�һ· 
sbit Left_2_led =P2^1; //��·Ѱ��ģ��ӿڵڶ�· 
sbit Right_1_led =P2^2; //��·Ѱ��ģ��ӿڵ���· 
sbit Right_2_led =P2^3; //��·Ѱ��ģ��ӿڵ���·
sbit a = P1^1;
sbit b = P1^0;
sbit c = P1^2;
sbit d = P1^3;	



void main(void) 
{
	a=1;
	b=0;
//while(1)
//{
//if((Left_1_led==0)&&(Left_2_led==0)&&(Right_1_led==0)&&(Right_2_led==0))
//{
//a=1;
//b=0;
//c=1;
//d=0;
//
//}
//if((Left_1_led==0)&&(Left_2_led==1)&&(Right_1_led==0)&&(Right_2_led==0))
//{
//a=1;
//b=0;
//c=0;
//d=1;
//
//}
//if((Left_1_led==1)&&(Left_2_led==1)&&(Right_1_led==1)&&(Right_2_led==1))
//{
//a=0;
//b=0;
//c=0;
//d=0;
//
//}
//if((Left_1_led==0)&&(Left_2_led==0)&&(Right_1_led==1)&&(Right_2_led==0))
//{
//a=0;
//b=1;
//c=1;
//d=0;
//
//}
//}


}