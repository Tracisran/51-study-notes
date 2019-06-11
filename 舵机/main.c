#include<reg52.h>
#include<intrins.h>
typedef unsigned int uint;
sbit a=P1^1;
sbit b=P1^0;
void delay(uint i)
{
	uint j;
	for(i;i>0;i--)		
		for(j=10;j>0;j--);
}
void delay2ms(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=4;b>0;b--)
        for(a=248;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}



void main()
{uint d;
b=0;
d=0;if(b=1)
d=1;
while(d)
{
uint j;

uint i;
for(i;i<26;i++)
{
j=50;

while(j--)
{
a=0;
delay2ms();
a=1;
delay(i);
}
}
for(i;i>5;i--)
{
j=50;
while(j--)
{
a=0;
delay2ms();
a=1;
delay(i);
}
}



}

}