#include<reg51.h>
#include<DS18B20.H>
#define uint unsigned int
#define uchar unsigned char
uchar a,miao,shi,fen,ri,yue,nian,week,flag,key1n,temp;
//flag���ڶ�ȡͷ�ļ��е��¶�ֵ������ʾ�¶�ֵ

#define yh 0x80 //LCD��һ�еĳ�ʼλ��,��ΪLCD1602�ַ���ַ��λD7�㶨Ϊ1��100000000=80��
#define er 0x80+0x40 //LCD�ڶ��г�ʼλ�ã���Ϊ�ڶ��е�һ���ַ�λ�õ�ַ��0x40��

//Һ��������C51֮����������Ӷ��壨��ʾ�����߽�C51��P0�ڣ�
sbit rs=P2^0;
sbit en=P2^2;
sbit rw=P2^1; //���Ӳ����rw�ӵأ��Ͳ���д���ͺ����rw=0��
sbit led=P2^6; //LCD���⿪��

//DS1302ʱ��оƬ��C51֮����������Ӷ���
sbit IO=P1^1;
sbit SCLK=P1^0;
sbit RST=P1^2;

sbit ACC0=ACC^0;
sbit ACC7=ACC^7;
/************************************************************
ACC�ۼ���=A
ACC.0=E0H 

ACC.0����ACC�ĵ�0λ��Acc����λѰַ��
 
***************************************************************/

//Уʱ������C51���������Ӷ���
sbit key1=P1^5;  //���ü�
sbit key2=P1^6;  //�Ӽ�
sbit key3=P1^7;  //����

sbit buzzer=P1^3;//��������ͨ��������9012�������˿ڵ͵�ƽ��

/**************************************************************/

uchar code tab1[]={"20  -  -   "}; //����ʾ�Ĺ̶��ַ�
uchar code tab2[]={"  :  :  "};//ʱ����ʾ�Ĺ̶��ַ�

//��ʱ���������澭������
void delay(uint xms)//��ʱ�������вκ���
{
	uint x,y;
	for(x=xms;x>0;x--)
	 for(y=110;y>0;y--);
}

/********Һ��д��ָ�����д�����ݺ������Ժ�ɵ���**************/

/*����������У�Һ��д���йغ�������DS1302�ĺ����е��ã�����Һ������Ҫ����ǰ��*/

write_1602com(uchar com)//****Һ��д��ָ���****
{
	rs=0;//����/ָ��ѡ����Ϊָ��
	rw=0; //��дѡ����Ϊд
	P0=com;//��������
	delay(1);
	en=1;//����ʹ�ܶˣ�Ϊ������Ч���½�����׼��
	delay(1);
	en=0;//en�ɸ߱�ͣ������½��أ�Һ��ִ������
}


write_1602dat(uchar dat)//***Һ��д�����ݺ���****
{
	rs=1;//����/ָ��ѡ����Ϊ����
	rw=0; //��дѡ����Ϊд
	P0=dat;//��������
	delay(1);
	en=1; //en�øߵ�ƽ��Ϊ�����½�����׼��
	delay(1);
	en=0; //en�ɸ߱�ͣ������½��أ�Һ��ִ������
}


lcd_init()//***Һ����ʼ������****
{
	write_1602com(0x38);//����Һ������ģʽ����˼��16*2����ʾ��5*7����8λ����
	write_1602com(0x0c);//����ʾ����ʾ���
	write_1602com(0x06);//�������ƶ�������Զ�����
	write_1602com(0x01);//����ʾ

	write_1602com(yh+1);//������ʾ�̶����Ŵӵ�һ�е�1��λ��֮��ʼ��ʾ
	for(a=0;a<14;a++)
	{
	write_1602dat(tab1[a]);//��Һ����д������ʾ�Ĺ̶����Ų���
	//delay(3);
	}
	write_1602com(er+2);//ʱ����ʾ�̶�����д��λ�ã��ӵ�2��λ�ú�ʼ��ʾ
	for(a=0;a<8;a++)
	{
	write_1602dat(tab2[a]);//д��ʾʱ��̶����ţ�����ð��
	//delay(3);
	}

}
/*********************over***********************/

/***************DS1302�й��Ӻ���********************/

void write_byte(uchar dat)//дһ���ֽ�
{
	ACC=dat;
	RST=1;
	for(a=8;a>0;a--)
	{
		IO=ACC0;
		SCLK=0;
		SCLK=1;
		ACC=ACC>>1;
	}
}
uchar read_byte()//��һ���ֽ�
{
	RST=1;
	for(a=8;a>0;a--)
	{
		ACC7=IO;
		SCLK=1;
		SCLK=0;
		ACC=ACC>>1;

	}
	return (ACC);
}
//----------------------------------------
void write_1302(uchar add,uchar dat)//��1302оƬд������ָ��д���ַ������
{

	RST=0;
	SCLK=0;
	RST=1;
	write_byte(add);
	write_byte(dat);
	SCLK=1;
	RST=0;
}
uchar read_1302(uchar add)//��1302�����ݺ�����ָ����ȡ������Դ��ַ
{
	uchar temp;
	RST=0;
	SCLK=0;
	RST=1;
	write_byte(add);
	temp=read_byte();
	SCLK=1;
	RST=0;
	return(temp);
}
uchar BCD_Decimal(uchar bcd)//BCD��תʮ���ƺ���������BCD������ʮ����
{
 uchar Decimal;
 Decimal=bcd>>4;
 return(Decimal=Decimal*10+(bcd&=0x0F));
}
//--------------------------------------
void ds1302_init() //1302оƬ��ʼ���Ӻ���(2010-01-07,12:00:00,week4)
{
RST=0;
SCLK=0;

write_1302(0x8e,0x00); //����д����ֹд���� 
//write_1302(0x80,0x00); //��DS1302��д��Ĵ���80Hд���ʼ������00
//write_1302(0x82,0x00);//��DS1302��д�ּĴ���82Hд���ʼ������00
//write_1302(0x84,0x12);//��DS1302��дСʱ�Ĵ���84Hд���ʼСʱ����12
//write_1302(0x8a,0x04);//��DS1302��д�ܼĴ���8aHд���ʼ������4
//write_1302(0x86,0x07);//��DS1302��д���ڼĴ���86Hд���ʼ��������07
//write_1302(0x88,0x01);//��DS1302��д�·ݼĴ���88Hд���ʼ�·�����01
//write_1302(0x8c,0x10);//��DS1302��д��ݼĴ���8cHд���ʼ�������10
write_1302(0x8e,0x80); //��д����
}
//------------------------------------
//�¶���ʾ�Ӻ���
void write_temp(uchar add,uchar dat)//��LCDд�¶�����,��ָ����ʾλ��
{
	uchar gw,sw;
	gw=dat%10;//ȡ�ø�λ����
	sw=dat/10;//ȡ��ʮλ����
	write_1602com(er+add);//er��ͷ�ļ��涨��ֵ0x80+0x40
	write_1602dat(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
	write_1602dat(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��
   write_1602dat(0xdf);//��ʾ�¶ȵ�СԲȦ���ţ�0xdf��Һ�����ַ���ĸ÷��ŵ�ַ��
  	write_1602dat(0x43);	//��ʾ"C"���ţ�0x43��Һ�����ַ������дC�ĵ�ַ��		
}

//------------------------------------
//ʱ������ʾ�Ӻ���
void write_sfm(uchar add,uchar dat)//��LCDдʱ����,����ʾλ�üӡ���ʾ���ݣ���������
{
	uchar gw,sw;
	gw=dat%10;//ȡ�ø�λ����
	sw=dat/10;//ȡ��ʮλ����
	write_1602com(er+add);//er��ͷ�ļ��涨��ֵ0x80+0x40
	write_1602dat(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
	write_1602dat(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��
				
}

//-------------------------------------
//��������ʾ�Ӻ���
void write_nyr(uchar add,uchar dat)//��LCDд�����գ�����ʾλ�ü�������ʾ���ݣ���������

{
	uchar gw,sw;
	gw=dat%10;//ȡ�ø�λ����
	sw=dat/10;//ȡ��ʮλ����
	write_1602com(yh+add);//�趨��ʾλ��Ϊ��һ��λ��+add
	write_1602dat(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
	write_1602dat(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��
	
}

//-------------------------------------------
void write_week(uchar week)//д���ں���
{
	write_1602com(yh+0x0c);//�����ַ�����ʾλ��
	switch(week)
	{
		case 1:write_1602dat('M');//������Ϊ1ʱ����ʾ
			   write_1602dat('O');
			   write_1602dat('N');
			   break;
	   
		case 2:write_1602dat('T');//��������Ϊ2ʱ��ʾ
			   write_1602dat('U');
			   write_1602dat('E');
			   break;
		
		case 3:write_1602dat('W');//��������Ϊ3ʱ��ʾ
			   write_1602dat('E');
			   write_1602dat('D');
			   break;
		
		case 4:write_1602dat('T');//��������Ϊ4����ʾ
			   write_1602dat('H');
			   write_1602dat('U');
			   break;
		
		case 5:write_1602dat('F');//��������Ϊ5ʱ��ʾ
			   write_1602dat('R');
			   write_1602dat('I');
			   break;
		
		case 6:write_1602dat('S');//��������Ϊ6ʱ��ʾ
			   write_1602dat('T');
			   write_1602dat('A');
			   break;
		
		case 7:write_1602dat('S');//��������Ϊ7ʱ��ʾ
			   write_1602dat('U');
			   write_1602dat('N');
			   break;
}
}
//****************����ɨ���йغ���**********************

void keyscan()
{
	if(key1==0)//---------------key1Ϊ���ܼ������ü���--------------------
	{
	delay(9);//��ʱ������������
	if(key1==0)//��ʱ���ٴ�ȷ�ϰ�������
	{
    buzzer=0;//����������һ��
    delay(20);
    buzzer=1;
	while(!key1);
	key1n++;
	if(key1n==9)
		key1n=1;//���ð��������롢�֡�ʱ�����ڡ��ա��¡��ꡢ���أ�8������ѭ��
	switch(key1n)
	{
	
	case 1: TR0=0;//�رն�ʱ��
			//TR1=0;
			write_1602com(er+0x09);//���ð�������һ�Σ���λ����ʾ���
		   	write_1602com(0x0f);//���ù��Ϊ��˸
		   	temp=(miao)/10*16+(miao)%10;//������д��DS1302
		   	write_1302(0x8e,0x00);
		   	write_1302(0x80,0x80|temp);//miao
		      write_1302(0x8e,0x80);
		   	break;
	case 2:  write_1602com(er+6);//��2��fenλ����ʾ���
			
		     //write_1602com(0x0f);
			break;
	case 3: write_1602com(er+3);//����3�Σ�shi
		     //write_1602com(0x0f);
			break;
	case 4: write_1602com(yh+0x0e);//����4�Σ�week
		     //write_1602com(0x0f);
			break;
	case 5: write_1602com(yh+0x0a);//����5�Σ�ri
		     //write_1602com(0x0f);
			break;
	case 6: write_1602com(yh+0x07);//����6�Σ�yue
		     //write_1602com(0x0f);
			break;
	case 7: write_1602com(yh+0x04);//����7�Σ�nian
		     //write_1602com(0x0f);
			break;
	case 8:
			write_1602com(0x0c);//��������8�Σ����ù�겻��˸
			TR0=1;//�򿪶�ʱ��
         temp=(miao)/10*16+(miao)%10;
		   write_1302(0x8e,0x00);
		   write_1302(0x80,0x00|temp);//miao����д��DS1302
		   write_1302(0x8e,0x80);
            break;															
			
	}
	}
	}
//------------------------------�Ӽ�key2----------------------------		
	if(key1n!=0)//��key1�������¡��ٰ����¼�����Ч�����������������㣩
	{

	if(key2==0)  //�ϵ���
	{
	delay(10);
	if(key2==0)
	{
    buzzer=0;//����������һ��
    delay(20);
    buzzer=1;
	while(!key2);
	switch(key1n)
	{
	case 1:miao++;//���ü�����1�Σ�����
			if(miao==60)
				miao=0;//�볬��59���ټ�1���͹���
			write_sfm(0x08,miao);//��LCD����ȷλ����ʾ"��"�趨�õ�����
			temp=(miao)/10*16+(miao)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00); //����д����ֹд���� 
		   	write_1302(0x80,temp); //��DS1302��д��Ĵ���80Hд��������������BCD��
		   	write_1302(0x8e,0x80); //��д����
			write_1602com(er+0x09);//
			//write_1602com(0x0b);
			break;
	case 2:fen++;
			if(fen==60)
				fen=0;
			write_sfm(0x05,fen);//��LCD����ȷλ����ʾ"��"�趨�õķ�����
			temp=(fen)/10*16+(fen)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд���� 
		   	write_1302(0x82,temp);//��DS1302��д�ּĴ���82Hд�������ķ�����BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(er+6);//
			break;
	case 3:shi++;
			if(shi==24)
				shi=0;
			write_sfm(2,shi);//��LCD����ȷ��λ����ʾ"��"�趨�õ�Сʱ����
			temp=(shi)/10*16+(shi)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд���� 
		   	write_1302(0x84,temp);//��DS1302��дСʱ�Ĵ���84Hд��������Сʱ����BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(er+3);//
			break;
	case 4:week++;
			if(week==8)
				week=1;
            write_1602com(yh+0x0C);//ָ��'��'�����������ʾλ��
				write_week(week);//ָ����������ʾ����
            temp=(week)/10*16+(week)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд���� 
		   	write_1302(0x8a,temp);//��DS1302��д�ܼĴ���8aHд��������������BCD��
		   	write_1302(0x8e,0x80);//��д����
			   write_1602com(yh+0x0e);//
			break;
	case 5:ri++;
			if(ri==32)
				ri=1;
			write_nyr(9,ri);//��LCD����ȷ��λ����ʾ"��"�趨�õ���������
			temp=(ri)/10*16+(ri)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд����
		   	write_1302(0x86,temp);//��DS1302��д���ڼĴ���86Hд����������������BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(yh+10);//
			break;
	case 6:yue++;
			if(yue==13)
				yue=1;
			write_nyr(6,yue);//��LCD����ȷ��λ����ʾ"��"�趨�õ��·�����
			temp=(yue)/10*16+(yue)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд����
		   	write_1302(0x88,temp);//��DS1302��д�·ݼĴ���88Hд���������·�����BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(yh+7);//
			break;
	case 7:nian++;
		 if(nian==100)
			nian=0;
			write_nyr(3,nian);//��LCD����ȷ��λ����ʾ"��"�趨�õ��������
            temp=(nian)/10*16+(nian)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд����
		   	write_1302(0x8c,temp);//��DS1302��д��ݼĴ���8cHд���������������BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(yh+4);//
			break;
	}
	}
	}
	//------------------����key3�����书�ܲ���'�Ӽ�'ע��---------------
	if(key3==0)
	{
	delay(10);//����ʱ��������
	if(key3==0)
	{
    buzzer=0;//����������һ��
    delay(20);
    buzzer=1;
	while(!key3);
	switch(key1n)
	{
		case 1:miao--;
				if(miao==-1)
					miao=59;//�����ݼ���-1ʱ�Զ����59
			write_sfm(0x08,miao);//��LCD����ȷλ����ʾ�ı���µ�����
            temp=(miao)/10*16+(miao)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00); //����д����ֹд���� 
		   	write_1302(0x80,temp); //��DS1302��д��Ĵ���80Hд��������������BCD��
		   	write_1302(0x8e,0x80); //��д����
			write_1602com(er+0x09);//
			//write_1602com(0x0b);
			break;
		case 2:fen--;
				if(fen==-1)
					fen=59;
			write_sfm(5,fen);
			temp=(fen)/10*16+(fen)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд���� 
		   	write_1302(0x82,temp);//��DS1302��д�ּĴ���82Hд�������ķ�����BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(er+6);//
			break;

		case 3:shi--;
			   if(shi==-1)
					shi=23;
			write_sfm(2,shi);
			temp=(shi)/10*16+(shi)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд���� 
		   	write_1302(0x84,temp);//��DS1302��дСʱ�Ĵ���84Hд��������Сʱ����BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(er+3);//
			break;
		case 4:week--;
				if(week==0)
					week=7;
			 
            write_1602com(yh+0x0C);//ָ��'��'�����������ʾλ��
				write_week(week);//ָ����������ʾ����
			   temp=(week)/10*16+(week)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд���� 
		   	write_1302(0x8a,temp);//��DS1302��д�ܼĴ���8aHд��������������BCD��
		   	write_1302(0x8e,0x80);//��д����
			   write_1602com(yh+0x0e);//
			break;
		case 5:ri--;
				if(ri==0)
					ri=31;
			write_nyr(9,ri);
			temp=(ri)/10*16+(ri)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд����
		   	write_1302(0x86,temp);//��DS1302��д���ڼĴ���86Hд����������������BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(yh+10);//
			break;
		case 6:yue--;
				if(yue==0)
					yue=12;
			write_nyr(6,yue);
			temp=(yue)/10*16+(yue)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд����
		   	write_1302(0x88,temp);//��DS1302��д�·ݼĴ���88Hд���������·�����BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(yh+7);//
			break;	
		case 7:nian--;
		 if(nian==-1)
			nian=99;
			write_nyr(3,nian);
         temp=(nian)/10*16+(nian)%10;//ʮ����ת����DS1302Ҫ���DCB��
		   	write_1302(0x8e,0x00);//����д����ֹд����
		   	write_1302(0x8c,temp);//��DS1302��д��ݼĴ���8cHд���������������BCD��
		   	write_1302(0x8e,0x80);//��д����
			write_1602com(yh+4);//
			break;			
	}
	}
	}
	}

}
//-------------------------------
void init() //��ʱ�������������ú���
{
	TMOD=0x11; //ָ����ʱ/�������Ĺ�����ʽΪ3
	TH0=0;  //��ʱ��T0�ĸ���λ=0
	TL0=0;  //��ʱ��T0�ĵ���λ=0
	EA=1;  //ϵͳ�����п��ŵ��ж�
	ET0=1; //����T0�ж�
	TR0=1; //�����жϣ�������ʱ��
}

//*******************������**************************
//***************************************************
void main()
{
	lcd_init();      //����Һ������ʼ���Ӻ���
	ds1302_init();   //����DS1302ʱ�ӵĳ�ʼ���Ӻ���
	init();          //���ö�ʱ�������������Ӻ���
	led=0;           //��LCD�ı����Դ
    buzzer=0;//����������һ��
    delay(80);
    buzzer=1;
	while(1)  //����ѭ���������䣺
	{		
    keyscan();      //���ü���ɨ���Ӻ���
    }
}
void timer0() interrupt 1  //ȡ�ò���ʾ������ʱ��
{
   //Init_DS18B20();//�¶ȴ�����DS18b2��ʼ���Ӻ�������ͷ�ļ���
   flag=ReadTemperature();//��18b2ͷ�ļ����з��صĺ�������͵�����FLAG�У�������ʾ

  //��ȡ��ʱ�����������߸����ݣ�DS1302�Ķ��Ĵ�����д�Ĵ�����һ������

   miao = BCD_Decimal(read_1302(0x81));
	fen = BCD_Decimal(read_1302(0x83));
	shi  = BCD_Decimal(read_1302(0x85));
	ri  = BCD_Decimal(read_1302(0x87));
	yue = BCD_Decimal(read_1302(0x89));
	nian=BCD_Decimal(read_1302(0x8d));
	week=BCD_Decimal(read_1302(0x8b));

	//��ʾ�¶ȡ��롢ʱ�������ݣ�
   
   write_temp(12,flag);//��ʾ�¶ȣ��ӵڶ��е�12���ַ���ʼ��ʾ
   write_sfm(8,miao);//�룬�ӵڶ��е�8���ֺ�ʼ��ʾ������ʱ������ʾ�Ӻ�����
	write_sfm(5,fen);//�֣��ӵڶ��е�5���ַ���ʼ��ʾ
	write_sfm(2,shi);//Сʱ���ӵڶ��е�2���ַ���ʼ��ʾ
	
	//��ʾ�ա��¡������ݣ�
	write_nyr(9,ri);//���ڣ��ӵڶ��е�9���ַ���ʼ��ʾ
   write_nyr(6,yue);//�·ݣ��ӵڶ��е�6���ַ���ʼ��ʾ
	write_nyr(3,nian);//�꣬�ӵڶ��е�3���ַ���ʼ��ʾ
	write_week(week);

}