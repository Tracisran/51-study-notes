#include<AT89x51.H> 
#define Right_moto_pwm P1_4 //?????ENA??????PWM 

#define Left_moto_pwm P1_5 //?????ENB??????PWM 
 
#define Left_1_led P2_0 //??????????? 
#define Left_2_led P2_1 //??????????? 
#define Right_1_led P2_2 //??????????? 
#define Right_2_led P2_3 //??????????? 
#define Left_moto_go {P1_0=0,P1_1=1;} //????? 
#define Left_moto_back {P1_0=1,P1_1=0;} //????? 
#define Left_moto_stop {P1_0=1,P1_1=1;} //????? 
#define Right_moto_go {P1_2=0,P1_3=1;} //????? #define Right_moto_back {P1_2=1,P1_3=0;} //????? 
#define Right_moto_stop {P1_2=1,P1_3=1;} //????? 
#define uchar unsigned char 
#define uint unsigned int 
uchar pwm_val_left =0; 
uchar push_val_left =0; //??????N/10 
uchar pwm_val_right =0; 
uchar push_val_right=0; //??????N/10 
bit Right_moto_stp=1; 
bit Left_moto_stp =1; 
/**************************************************************** 
********/ 
void run(void) //???? 
{ 
push_val_left =13; //PWM ????1-20 1????20??? ?? 

push_val_right =15; //PWM ????1-20 1????20??? ? 

Left_moto_go ; //????? 
Right_moto_go ; //????? 
} 
/**************************************************************** 
********/ 
void left(void) //???? 
{ 
push_val_left =8; 
push_val_right =9; 
Right_moto_go; //????? 
Left_moto_stop; //????? 
} 
/************************************************************************/ 
void right(void) //???? 
{ 
push_val_left =8; 
push_val_right =9; 
Right_moto_stop; //????? 
Left_moto_go; //????? 
} 
void Delayms(uint x) 
{ 
uchar i; 
while(x--)for(i=0;i<120;i++); 
} 
void stop(void) 
{ 
Right_moto_stop; //????? 
Left_moto_stop; //????? 
Delayms(3000); 
run(); 
Delayms(100); 
} 
/*************************PWM? ? ? ? ? ? 
********************************/ 
void pwm_out_left_moto(void) //?????,??push_val_left???? 
 
{ 
if(Left_moto_stp) 
{ 
if(pwm_val_left<=push_val_left) 
Left_moto_pwm=1; 
else 
Left_moto_pwm=0; if(pwm_val_left>=20) 
pwm_val_left=0; 
} 
else 
Left_moto_pwm=0; 
} 
void pwm_out_right_moto(void) //?????,??push_val_left???? 
 
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
switch(P2&0x0f) 
{ 
case 0x00: // ????????? 
run(); break; 
case 0x01: // ?????? 
left(); break; 
case 0x02: // ?????? 
left(); break; 
case 0x04: // ?????? 
right(); break; case 0x08: // ?????? 
right();break; 
case 0x0f: 
stop();break; 
default: 
run(); break; 
} 
} 
/***********TIMER0?????????PWM??**********/ 
void timer0()interrupt 1 using 2 
{ 
TH0=0XF8; //2Ms?? 
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
TH0= 0XF8; //2ms?? 
TL0= 0X30; 
TR0= 1; 
ET0= 1; 
EA = 1; 
while(1) /*????*/ 
{ 
xunji(); } 
} 
