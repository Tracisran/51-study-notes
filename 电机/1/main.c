#include"reg51.h"

sbit Left_1_led =P2^0; //四路寻迹模块接口第一路 
sbit Left_2_led =P2^1; //四路寻迹模块接口第二路 
sbit Right_1_led =P2^2; //四路寻迹模块接口第三路 
sbit Right_2_led =P2^3; //四路寻迹模块接口第四路
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