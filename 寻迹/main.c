#include<reg52.h> 
sbit Right_moto_pwm= P1^5; //������ģ��ENAʹ�ܶ˪�����PWM  
sbit Left_moto_pwm= P1^4; //������ģ��ENBʹ�ܶ˪�����PWM 
sbit Left_1_led =P2^0; //��·Ѱ��ģ��ӿڵ�һ· 
sbit Left_2_led =P2^1; //��·Ѱ��ģ��ӿڵڶ�· 
sbit Right_1_led =P2^2; //��·Ѱ��ģ��ӿڵ���· 
sbit Right_2_led =P2^ 3; //��·Ѱ��ģ��ӿڵ���·
sbit a = P1^0;
sbit b = P1^1;
sbit d = P1^2;
sbit c = P1^3;
int S[2]=0;

#define Left_moto_go {a=0,b=1;} //����ǰ�� 
#define Left_moto_back {a=1,b=0;}; //�������� 
#define Left_moto_stop {a=1,b=1;}; //����ͣת 
#define Right_moto_go {c=0,d=1;}; //�ҵ��ǰת 
#define Right_moto_back {c=1,d=0;}; //�ҵ������ 
#define Right_moto_stop {c=1,d=1;}; //�ҵ��ͣת 
#define uchar unsigned char 
#define uint unsigned int 
uchar pwm_val_left =0; 
uchar push_val_left =0; //����ռ�ձ�N/10 
uchar pwm_val_right =0; 
uchar push_val_right=0; //�ҵ��ռ�ձ�N/10 
bit Right_moto_stp=1; 
bit Left_moto_stp =1; 
/**************************************************************** 
********/ 
void run(void) //ǰ������ 
{ 
push_val_left =20; //PWM ���ڲ���1-20 1Ϊ������20�����  
push_val_right=20 ; //PWM ���ڲ���1-20 1Ϊ������20�����   
Left_moto_go ; //����ǰ�� 
Right_moto_go ; //�ҵ��ǰ�� 
} 
/************************************************************************/ 
void left1(void) //��ת���� 
{ 
push_val_left =15; 
push_val_right =20; 
Right_moto_go;  
Left_moto_back;  
}
void left2(void)  
{ 
push_val_left =20; 
push_val_right =20;
 
Right_moto_go;  
Left_moto_back;  
}  
/************************************************************************/ 
void right1(void) //��ת���� 
{ 
push_val_left =20; 
push_val_right =15; 
Right_moto_back; 
Left_moto_go; 
}
void right2(void) 
{ 
push_val_left =20; 
push_val_right =20; 
Right_moto_back; 
Left_moto_go;  
} 
void back(void) 
{
push_val_left =20; 
push_val_right =20; 
Right_moto_back; 
Left_moto_back; 
}

void stop(void) 
{ 
Right_moto_stop;
Left_moto_stop; 

} 

void Delayms(uint x) 
{ 
uchar i; 
while(x--)for(i=0;i<120;i++); 
} 
/*************************PWM �� �� �� �� ת ��********************************/ 
void pwm_out_left_moto(void) //��������,����push_val_left��ֵ�ı���ת��,ռ�ձ� 
{ 
if(Left_moto_stp) 
{ 
if(pwm_val_left<=push_val_left) 
Left_moto_pwm=1; 
else 
Left_moto_pwm=0;
 if(pwm_val_left>=20) 
pwm_val_left=0; 
} 
else 
Left_moto_pwm=0; 
} 
void pwm_out_right_moto(void) //�ҵ������,����push_val_left��ֵ�ı���ת��,ռ�ձ� 
{ 
if(Right_moto_stp) 
{ 
if(pwm_val_right<=push_val_right) 
Right_moto_pwm=1; 
else 
Right_moto_pwm=0; 
if(pwm_val_right>=20) 
pwm_val_right=0; 
} 
else 
Right_moto_pwm=0; 
} 
/***************************************************/ 
void xunji() 
{ 
switch(P2&0xff) 
{ 
case 0xf0: // ȫ��û��ѹ�ߪ�ֱ��   11110000
S[0]=S[1];
S[1]=0;
run();
break;
case 0xf9:		//1111001
S[0]=S[1];
S[1]=1;
run();
break;  
case 0xf1: // ��ѹ�ߪ���ת 	11110001
S[0]=S[1];
S[1]=2;
run();
break; 
case 0xf2: // ��ѹ�ߪ���ת 	11110010
S[0]=S[1];
S[1]=3;
right1(); 
break;
case 0xf3:		//			11110011
S[0]=S[1];
S[1]=4;
if(S[0]!=4)
{
back();
Delayms(500);
}
else
{
right2();
}
right2();
break;
case 0xf7: // ��ѹ�ߪ���ת 	  11110111
S[0]=S[1];
S[1]=5;
run(); 
break; 
case 0xf4: // ��ѹ�ߪ�ת�� 		 11110100
S[0]=S[1];
S[1]=6;
left1(); 
break; 
case 0xf8: // ��ѹ�ߪ���ת 		  11111000
S[0]=S[1];
S[1]=7;
run();
break;
case 0xfc:					  // 11111100
S[0]=S[1];
S[1]=8;
if(S[0]!=8)
{
back();
Delayms(500);	
}
else
{
left2();
}
left2();
break; 
case 0xfe:					  // 11111110
S[0]=S[1];
S[1]=9;
run();
break; 
case 0xff: 					  // 11111111
S[0]=S[1];
S[1]=S[1];
//run();
break; 
case 0xf6:					//11110110
S[0]=S[1];
S[1]=11;
left1();
break; 

default: 
S[0]=S[1];
S[1]=12;
run(); 
break; 
} 
} 
/***********TIMER0�жϷ����Ӻ�������PWM�ź�**********/ 
 void timer0()interrupt 1 using 2 
{ 
TH0=0XF8; 				//2Ms��ʱ 
TL0=0X30; 
pwm_val_left++; 
pwm_val_right++; 
pwm_out_left_moto(); 
pwm_out_right_moto(); 
} 
/***************************************************/ 
void main(void) 
{ 
TMOD=0X01; 
TH0= 0XF8; //2ms��ʱ 
TL0= 0X30; 
TR0= 1; 
ET0= 1; 
EA = 1;

while(1) /*����ѭ��*/ 
{ 
xunji(); 
} 
} 
