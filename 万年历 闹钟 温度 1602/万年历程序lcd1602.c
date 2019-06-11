#include<reg52.h>
//#include"DS18B20_3.H"
#include <string.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define wd 1				//�����Ƿ����¶ȹ���  =0ʱ���¶ȣ�=1ʱ���¶�


#define yh 0x80 //LCD��һ�еĳ�ʼλ��,��ΪLCD1602�ַ���ַ��λD7�㶨Ϊ1��100000000=80��
#define er 0x80+0x40 //LCD�ڶ��г�ʼλ�ã���Ϊ�ڶ��е�һ���ַ�λ�õ�ַ��0x40��

//Һ��������C51֮����������Ӷ��壨��ʾ�����߽�C51��P0�ڣ�
sbit en=P2^7;
sbit rw=P2^6;   //���Ӳ����rw�ӵأ��Ͳ���д���ͺ����rw=0��
sbit rs=P2^5;


//Уʱ������C51���������Ӷ���

sbit set=P3^0;  	//���ü�
sbit add=P3^1;  	//�Ӽ�
sbit dec=P3^2;  	//����
sbit seeNL_NZ=P3^3;	//�鿴ũ��/����

sbit DQ=P2^4;		//
sbit buzzer=P2^3;	//��������ͨ��������8550�������˿ڵ͵�ƽ��

sbit led=P3^7; 		//LCD���⿪��
bit  led1=1;

unsigned char temp_miao;
unsigned char bltime;  //��������ʱ��
uchar tflag;//�¶�������־

//DS1302ʱ��оƬ��C51֮����������Ӷ���
sbit IO=P2^1;
sbit SCLK=P2^0;
sbit RST=P2^2;


uchar a,miao,shi,fen,ri,yue,nian,week,setn,temp;
uint flag;
//flag���ڶ�ȡͷ�ļ��е��¶�ֵ������ʾ�¶�ֵ
bit c_moon;

uchar nz_shi=12,nz_fen=0,nz_miao=0,setNZn;    	//�������ӱ���
uchar shangyimiao,bsn,temp_hour;			//��¼��һ��ʱ��
uchar T_NL_NZ;							//������
bit timerOn=0;							//�������ñ�־λ
bit baoshi=0;							//���㱨ʱ��־λ
bit  p_r=0;		 						//ƽ��/����  =0��ʾƽ�꣬=1��ʾ����
data uchar year_moon,month_moon,day_moon,week;



sbit ACC0=ACC^0;
sbit ACC7=ACC^7;
/************************************************************
ACC�ۼ���=A
ACC.0=E0H 

ACC.0����ACC�ĵ�0λ��Acc����λѰַ��

�ۼ���ACC��һ��8λ�Ĵ洢��Ԫ�������������ݵġ����ǣ�����洢��Ԫ��������ĵ�λ��
�ǵ�Ƭ����һ���ǳ��ؼ��ĵ�Ԫ���ܶ����㶼Ҫͨ��ACC�����С��Ժ���ѧϰָ��ʱ��
����A����ʾ�ۼ���������һЩ�ط����⣬������PUSHָ���У��ͱ�����ACC���������֡�
һ���˵����A�������ۼ����е����ݡ���ACC��������ۼ����ĵ�ַ�� 
***************************************************************/



//********����ת��������************************************
code uchar year_code[597]={
                    0x04,0xAe,0x53,    //1901 0
                    0x0A,0x57,0x48,    //1902 3
                    0x55,0x26,0xBd,    //1903 6
                    0x0d,0x26,0x50,    //1904 9
                    0x0d,0x95,0x44,    //1905 12
                    0x46,0xAA,0xB9,    //1906 15
                    0x05,0x6A,0x4d,    //1907 18
                    0x09,0xAd,0x42,    //1908 21
                    0x24,0xAe,0xB6,    //1909
                    0x04,0xAe,0x4A,    //1910
                    0x6A,0x4d,0xBe,    //1911
                    0x0A,0x4d,0x52,    //1912
                    0x0d,0x25,0x46,    //1913
                    0x5d,0x52,0xBA,    //1914
                    0x0B,0x54,0x4e,    //1915
                    0x0d,0x6A,0x43,    //1916
                    0x29,0x6d,0x37,    //1917
                    0x09,0x5B,0x4B,    //1918
                    0x74,0x9B,0xC1,    //1919
                    0x04,0x97,0x54,    //1920
                    0x0A,0x4B,0x48,    //1921
                    0x5B,0x25,0xBC,    //1922
                    0x06,0xA5,0x50,    //1923
                    0x06,0xd4,0x45,    //1924
                    0x4A,0xdA,0xB8,    //1925
                    0x02,0xB6,0x4d,    //1926
                    0x09,0x57,0x42,    //1927
                    0x24,0x97,0xB7,    //1928
                    0x04,0x97,0x4A,    //1929
                    0x66,0x4B,0x3e,    //1930
                    0x0d,0x4A,0x51,    //1931
                    0x0e,0xA5,0x46,    //1932
                    0x56,0xd4,0xBA,    //1933
                    0x05,0xAd,0x4e,    //1934
                    0x02,0xB6,0x44,    //1935
                    0x39,0x37,0x38,    //1936
                    0x09,0x2e,0x4B,    //1937
                    0x7C,0x96,0xBf,    //1938
                    0x0C,0x95,0x53,    //1939
                    0x0d,0x4A,0x48,    //1940
                    0x6d,0xA5,0x3B,    //1941
                    0x0B,0x55,0x4f,    //1942
                    0x05,0x6A,0x45,    //1943
                    0x4A,0xAd,0xB9,    //1944
                    0x02,0x5d,0x4d,    //1945
                    0x09,0x2d,0x42,    //1946
                    0x2C,0x95,0xB6,    //1947
                    0x0A,0x95,0x4A,    //1948
                    0x7B,0x4A,0xBd,    //1949
                    0x06,0xCA,0x51,    //1950
                    0x0B,0x55,0x46,    //1951
                    0x55,0x5A,0xBB,    //1952
                    0x04,0xdA,0x4e,    //1953
                    0x0A,0x5B,0x43,    //1954
                    0x35,0x2B,0xB8,    //1955
                    0x05,0x2B,0x4C,    //1956
                    0x8A,0x95,0x3f,    //1957
                    0x0e,0x95,0x52,    //1958
                    0x06,0xAA,0x48,    //1959
                    0x7A,0xd5,0x3C,    //1960
                    0x0A,0xB5,0x4f,    //1961
                    0x04,0xB6,0x45,    //1962
                    0x4A,0x57,0x39,    //1963
                    0x0A,0x57,0x4d,    //1964
                    0x05,0x26,0x42,    //1965
                    0x3e,0x93,0x35,    //1966
                    0x0d,0x95,0x49,    //1967
                    0x75,0xAA,0xBe,    //1968
                    0x05,0x6A,0x51,    //1969
                    0x09,0x6d,0x46,    //1970
                    0x54,0xAe,0xBB,    //1971
                    0x04,0xAd,0x4f,    //1972
                    0x0A,0x4d,0x43,    //1973
                    0x4d,0x26,0xB7,    //1974
                    0x0d,0x25,0x4B,    //1975
                    0x8d,0x52,0xBf,    //1976
                    0x0B,0x54,0x52,    //1977
                    0x0B,0x6A,0x47,    //1978
                    0x69,0x6d,0x3C,    //1979
                    0x09,0x5B,0x50,    //1980
                    0x04,0x9B,0x45,    //1981
                    0x4A,0x4B,0xB9,    //1982
                    0x0A,0x4B,0x4d,    //1983
                    0xAB,0x25,0xC2,    //1984
                    0x06,0xA5,0x54,    //1985
                    0x06,0xd4,0x49,    //1986
                    0x6A,0xdA,0x3d,    //1987
                    0x0A,0xB6,0x51,    //1988
                    0x09,0x37,0x46,    //1989
                    0x54,0x97,0xBB,    //1990
                    0x04,0x97,0x4f,    //1991
                    0x06,0x4B,0x44,    //1992
                    0x36,0xA5,0x37,    //1993
                    0x0e,0xA5,0x4A,    //1994
                    0x86,0xB2,0xBf,    //1995
                    0x05,0xAC,0x53,    //1996
                    0x0A,0xB6,0x47,    //1997
                    0x59,0x36,0xBC,    //1998
                    0x09,0x2e,0x50,    //1999 294
                    0x0C,0x96,0x45,    //2000 297
                    0x4d,0x4A,0xB8,    //2001
                    0x0d,0x4A,0x4C,    //2002
                    0x0d,0xA5,0x41,    //2003
                    0x25,0xAA,0xB6,    //2004
                    0x05,0x6A,0x49,    //2005
                    0x7A,0xAd,0xBd,    //2006
                    0x02,0x5d,0x52,    //2007
                    0x09,0x2d,0x47,    //2008
                    0x5C,0x95,0xBA,    //2009
                    0x0A,0x95,0x4e,    //2010
                    0x0B,0x4A,0x43,    //2011
                    0x4B,0x55,0x37,    //2012
                    0x0A,0xd5,0x4A,    //2013
                    0x95,0x5A,0xBf,    //2014
                    0x04,0xBA,0x53,    //2015
                    0x0A,0x5B,0x48,    //2016
                    0x65,0x2B,0xBC,    //2017
                    0x05,0x2B,0x50,    //2018
                    0x0A,0x93,0x45,    //2019
                    0x47,0x4A,0xB9,    //2020
                    0x06,0xAA,0x4C,    //2021
                    0x0A,0xd5,0x41,    //2022
                    0x24,0xdA,0xB6,    //2023
                    0x04,0xB6,0x4A,    //2024
                    0x69,0x57,0x3d,    //2025
                    0x0A,0x4e,0x51,    //2026
                    0x0d,0x26,0x46,    //2027
                    0x5e,0x93,0x3A,    //2028
                    0x0d,0x53,0x4d,    //2029
                    0x05,0xAA,0x43,    //2030
                    0x36,0xB5,0x37,    //2031
                    0x09,0x6d,0x4B,    //2032
                    0xB4,0xAe,0xBf,    //2033
                    0x04,0xAd,0x53,    //2034
                    0x0A,0x4d,0x48,    //2035
                    0x6d,0x25,0xBC,    //2036
                    0x0d,0x25,0x4f,    //2037
                    0x0d,0x52,0x44,    //2038
                    0x5d,0xAA,0x38,    //2039
                    0x0B,0x5A,0x4C,    //2040
                    0x05,0x6d,0x41,    //2041
                    0x24,0xAd,0xB6,    //2042
                    0x04,0x9B,0x4A,    //2043
                    0x7A,0x4B,0xBe,    //2044
                    0x0A,0x4B,0x51,    //2045
                    0x0A,0xA5,0x46,    //2046
                    0x5B,0x52,0xBA,    //2047
                    0x06,0xd2,0x4e,    //2048
                    0x0A,0xdA,0x42,    //2049
                    0x35,0x5B,0x37,    //2050
                    0x09,0x37,0x4B,    //2051
                    0x84,0x97,0xC1,    //2052
                    0x04,0x97,0x53,    //2053
                    0x06,0x4B,0x48,    //2054
                    0x66,0xA5,0x3C,    //2055
                    0x0e,0xA5,0x4f,    //2056
                    0x06,0xB2,0x44,    //2057
                    0x4A,0xB6,0x38,    //2058
                    0x0A,0xAe,0x4C,    //2059
                    0x09,0x2e,0x42,    //2060
                    0x3C,0x97,0x35,    //2061
                    0x0C,0x96,0x49,    //2062
                    0x7d,0x4A,0xBd,    //2063
                    0x0d,0x4A,0x51,    //2064
                    0x0d,0xA5,0x45,    //2065
                    0x55,0xAA,0xBA,    //2066
                    0x05,0x6A,0x4e,    //2067
                    0x0A,0x6d,0x43,    //2068
                    0x45,0x2e,0xB7,    //2069
                    0x05,0x2d,0x4B,    //2070
                    0x8A,0x95,0xBf,    //2071
                    0x0A,0x95,0x53,    //2072
                    0x0B,0x4A,0x47,    //2073
                    0x6B,0x55,0x3B,    //2074
                    0x0A,0xd5,0x4f,    //2075
                    0x05,0x5A,0x45,    //2076
                    0x4A,0x5d,0x38,    //2077
                    0x0A,0x5B,0x4C,    //2078
                    0x05,0x2B,0x42,    //2079
                    0x3A,0x93,0xB6,    //2080
                    0x06,0x93,0x49,    //2081
                    0x77,0x29,0xBd,    //2082
                    0x06,0xAA,0x51,    //2083
                    0x0A,0xd5,0x46,    //2084
                    0x54,0xdA,0xBA,    //2085
                    0x04,0xB6,0x4e,    //2086
                    0x0A,0x57,0x43,    //2087
                    0x45,0x27,0x38,    //2088
                    0x0d,0x26,0x4A,    //2089
                    0x8e,0x93,0x3e,    //2090
                    0x0d,0x52,0x52,    //2091
                    0x0d,0xAA,0x47,    //2092
                    0x66,0xB5,0x3B,    //2093
                    0x05,0x6d,0x4f,    //2094
                    0x04,0xAe,0x45,    //2095
                    0x4A,0x4e,0xB9,    //2096
                    0x0A,0x4d,0x4C,    //2097
                    0x0d,0x15,0x41,    //2098
                    0x2d,0x92,0xB5,    //2099
};

///�·����ݱ�
code uchar day_code1[9]={0x0,0x1f,0x3b,0x5a,0x78,0x97,0xb5,0xd4,0xf3};
code uint day_code2[3]={0x111,0x130,0x14e};

/*
��������:����BCD��������,���BCD��������(ֻ����1901-2099��)
���ú���ʾ��:Conversion(c_sun,year_sun,month_sun,day_sun)
��:����2004��10��16��Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun��ΪBCD����,c_sunΪ���ͱ�־λ,c_sun=0Ϊ21��
��,c_sun=1Ϊ19����
���ú�����,ԭ�����ݲ���,��c_moon,year_moon,month_moon,day_moon�ó�����BCD����
*/

bit c_moon;
data uchar year_moon,month_moon,day_moon,week;
//�Ӻ���,���ڶ�ȡ���ݱ���ũ���µĴ��»�С��,�������Ϊ�󷵻�1,ΪС����0
bit get_moon_day(uchar month_p,uint table_addr)
{
	uchar temp;
    switch (month_p){
        case 1:{temp=year_code[table_addr]&0x08;
             if (temp==0)return(0);else return(1);}
        case 2:{temp=year_code[table_addr]&0x04;
             if (temp==0)return(0);else return(1);}
        case 3:{temp=year_code[table_addr]&0x02;
             if (temp==0)return(0);else return(1);}
        case 4:{temp=year_code[table_addr]&0x01;
             if (temp==0)return(0);else return(1);}
        case 5:{temp=year_code[table_addr+1]&0x80;
             if (temp==0) return(0);else return(1);}
        case 6:{temp=year_code[table_addr+1]&0x40;
             if (temp==0)return(0);else return(1);}
        case 7:{temp=year_code[table_addr+1]&0x20;
             if (temp==0)return(0);else return(1);}
        case 8:{temp=year_code[table_addr+1]&0x10;
             if (temp==0)return(0);else return(1);}
        case 9:{temp=year_code[table_addr+1]&0x08;
             if (temp==0)return(0);else return(1);}
        case 10:{temp=year_code[table_addr+1]&0x04;
             if (temp==0)return(0);else return(1);}
        case 11:{temp=year_code[table_addr+1]&0x02;
             if (temp==0)return(0);else return(1);}
        case 12:{temp=year_code[table_addr+1]&0x01;
             if (temp==0)return(0);else return(1);}
        case 13:{temp=year_code[table_addr+2]&0x80;
             if (temp==0)return(0);else return(1);}
    }
	 return 0;
}

/*
��������:����BCD��������,���BCD��������(ֻ����1901-2099��)
���ú���ʾ��:Conversion(c_sun,year_sun,month_sun,day_sun)
��:����2004��10��16��Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun��ΪBCD����,c_sunΪ���ͱ�־λ,c_sun=0Ϊ21��
��,c_sun=1Ϊ19����
���ú�����,ԭ�����ݲ���,��c_moon,year_moon,month_moon,day_moon�ó�����BCD����
*/

void Conversion(bit c,uchar year,uchar month,uchar day)
{                         //c=0 Ϊ21����,c=1 Ϊ19���� ����������ݾ�ΪBCD����
    uchar temp1,temp2,temp3,month_p;
    uint temp4,table_addr;
    bit flag2,flag_y;
    temp1=year/16;   //BCD->hex �Ȱ�����ת��Ϊʮ������
    temp2=year%16;
   // year=temp1*10+temp2;
	year=temp1*16+temp2;
    temp1=month/16;
    temp2=month%16;
    //month=temp1*10+temp2;
	month=temp1*16+temp2;
    temp1=day/16;
    temp2=day%16;
    //day=temp1*10+temp2;
	day=temp1*16+temp2;
    //��λ���ݱ��ַ
    if(c==0){                   
        table_addr=(year+0x64-1)*0x3;
    }
    else {
        table_addr=(year-1)*0x3;
    }
    //��λ���ݱ��ַ���
    //ȡ���괺�����ڵĹ����·�
    temp1=year_code[table_addr+2]&0x60; 
    temp1=_cror_(temp1,5);
    //ȡ���괺�����ڵĹ����·����
    //ȡ���괺�����ڵĹ�����
    temp2=year_code[table_addr+2]&0x1f; 
    //ȡ���괺�����ڵĹ��������
    // ���㵱�괺���뵱��Ԫ��������,����ֻ���ڹ���1�»�2��
    if(temp1==0x1){  
        temp3=temp2-1;  
    }  
    else{
        temp3=temp2+0x1f-1;        
    }
    // ���㵱�괺���뵱��Ԫ�����������
    //���㹫�����뵱��Ԫ��������,Ϊ�˼�������,����������
    //day_code1[9],day_code2[3]
    //����������ھ��»�ǰ,����������0xff,�ñ�day_code1[9],
    //�ھ��º�,��������0xff,�ñ�day_code2[3]
    //�����빫����Ϊ8��10��,��������Ԫ������Ϊday_code1[8-1]+10-1
    //�����빫����Ϊ11��10��,��������Ԫ������Ϊday_code2[11-10]+10-1
    if (month<10){ 
        temp4=day_code1[month-1]+day-1;
    }
    else{
        temp4=day_code2[month-10]+day-1;
    }
    if ((month>0x2)&&(year%0x4==0)){  //��������´���2�²��Ҹ����2��Ϊ����,������1
        temp4+=1;
    }
    //���㹫�����뵱��Ԫ�����������
    //�жϹ������ڴ���ǰ���Ǵ��ں�
    if (temp4>=temp3){ //�������ڴ��ں����Ǵ��ڵ���ʹ����������������
        temp4-=temp3;
        month=0x1;
        month_p=0x1;  //month_pΪ�·�ָ��,�������ڴ���ǰ����Ǵ��ڵ���month_pָ������
        flag2=get_moon_day(month_p,table_addr); //����ũ����Ϊ��С����С��,���·���1,С�·���0
        flag_y=0;
        if(flag2==0)temp1=0x1d; //С��29��
        else temp1=0x1e; //��С30��
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);  //�����ݱ���ȡ����������·�,��Ϊ0�����������
        while(temp4>=temp1){
            temp4-=temp1;
            month_p+=1;
            if(month==temp2){
            flag_y=~flag_y;
            if(flag_y==0)month+=1;
            }
            else month+=1;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)temp1=0x1d;
            else temp1=0x1e;
        }
        day=temp4+1;
    }
    else{  //�������ڴ���ǰʹ����������������
        temp3-=temp4;
        if (year==0x0){year=0x63;c=1;}
        else year-=1;
        table_addr-=0x3;
        month=0xc;
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);
        if (temp2==0)
			month_p=0xc; 
        else
			month_p=0xd; //
        
       	 //month_pΪ�·�ָ��,�������������,һ����ʮ������,��ָ��13,������ָ��12
        
        flag_y=0;
        flag2=get_moon_day(month_p,table_addr);
        if(flag2==0)temp1=0x1d;
        else temp1=0x1e;
        while(temp3>temp1){
            temp3-=temp1;
            month_p-=1;
            if(flag_y==0)month-=1;
            if(month==temp2)flag_y=~flag_y;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)temp1=0x1d;
            else temp1=0x1e;
         }
        day=temp1-temp3+1;
    }
    c_moon=c;                 //HEX->BCD ,���������,������ת��ΪBCD����
    temp1=year/10;
    temp1=_crol_(temp1,4);
    temp2=year%10;
    year_moon=temp1|temp2;
    temp1=month/10;
    temp1=_crol_(temp1,4);
    temp2=month%10;
    month_moon=temp1|temp2;
    temp1=day/10;
    temp1=_crol_(temp1,4);
    temp2=day%10;
    day_moon=temp1|temp2;
}


/*
��������:����BCD��������,���BCD��������(ֻ����1901-2099��)
���ú���ʾ��:Conver_week(c_sun,year_sun,month_sun,day_sun)
��:����2004��10��16��Conversion(0,0x4,0x10,0x16);
c_sun,year_sun,month_sun,day_sun��ΪBCD����,c_sunΪ���ͱ�־λ,c_sun=0Ϊ21��
��,c_sun=1Ϊ19����
���ú�����,ԭ�����ݲ���,��week�ó�����BCD����
*/
code uchar table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�
/*
�㷨:����+���+����������+�½�����֮�ͳ�7 �������������ڵ��������
�����ֲ���3 �·�����֮��Ҫ��һ���ٳ�7
������Ϊ0
*/
void Conver_week(uchar year,uchar month,uchar day)
{//c=0 Ϊ21����,c=1 Ϊ19���� ����������ݾ�ΪBCD����
    uchar p1,p2;
    year+=0x64;  //���Ϊ21����,�������100
    p1=year/0x4;  //����������ֻ��1900��֮���
    p2=year+p1;
    p2=p2%0x7;  //Ϊ��ʡ��Դ,�Ƚ���һ��ȡ��,����������0xff,����ʹ����������
    p2=p2+day+table_week[month-1];
    if (year%0x4==0&&month<3)p2-=1;
    week=p2%0x7;
}


/**************************************************************/

uchar code tab1[]={"20  -  -   "}; 	//����ʾ�Ĺ̶��ַ�
uchar code tab2[]={"  :  :  "};		//ʱ����ʾ�Ĺ̶��ַ�
uchar code nlp[]={"NL:  -  -   PING"};	//ũ��ƽ����ʾ
uchar code nlr[]={"NL:  -  -   RUN "};	//ũ��������ʾ
uchar code NZd[]={"timer:    -  -  "};	//��ʾ���ӹ̶���
uchar code qk[]= {"                "};	//�����ʾ
uchar code tm[]= {"time"};



//=====================DS18B20=============================================
//******************************************************************************
void Delayns(int num)//��ʱ����
{
	while(num--);
}	


//******************************************************************************
void Init_DS18B20(void)//��ʼ��ds1820
{
	unsigned char x=0;
	DQ = 1;    //DQ��λ
	Delayns(8);  //������ʱ
	DQ = 0;    //��Ƭ����DQ����
	Delayns(80); //��ȷ��ʱ ���� 480us
	DQ = 1;    //��������
	Delayns(14);
	x=DQ;      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
	Delayns(20);
}
//******************************************************************************
unsigned char ReadOneChar(void)//��һ���ֽ�
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ = 0; // �������ź�
		dat>>=1;
		DQ = 1; // �������ź�
		if(DQ)
		dat|=0x80;
		Delayns(4);
	}
	return(dat);
}

//******************************************************************************
void WriteOneChar(unsigned char dat)//дһ���ֽ�
{
	unsigned char i=0;
	for (i=8; i>0; i--)
	{
		DQ = 0;
		DQ = dat&0x01;
		Delayns(5);
		DQ = 1;
		dat>>=1;
	}
}
//******************************************************************************
unsigned int ReadTemperature(void)//��ȡ�¶�
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned int t=0;
	float tt=0;
	Init_DS18B20();
	WriteOneChar(0xCC); // ����������кŵĲ���
	WriteOneChar(0x44); // �����¶�ת��
	Init_DS18B20();
	WriteOneChar(0xCC); //����������кŵĲ���
	WriteOneChar(0xBE); //��ȡ�¶ȼĴ���
	a=ReadOneChar();  //����8λ
	b=ReadOneChar(); //����8λ
	t=b;
	t<<=8;
	t=t|a;
   
   if(t<0x0fff)   tflag=0;
   else   {t=~t+2;tflag=1;}
	t=t*(0.625)+5;//�¶�ֵ����10������ȷ��1λС��
	//CurrentT=tvalue;
	//return(tvalue);
   
	//tt=t*0.625;
	//t= (unsigned int)(tt*10+0.5); //�Ŵ�10���������������
	return(t);
}
//*****************************************************************************



//��ʱ���������澭������
void delay(uint xms)//��ʱ�������вκ���
{
	uint x,y;
	for(x=xms;x>0;x--)
	 for(y=110;y>0;y--);
}

/********Һ��д��ָ�����д�����ݺ������Ժ�ɵ���**************/

/*����������У�Һ��д���йغ�������DS1302�ĺ����е��ã�����Һ������Ҫ����ǰ��*/

void write_1602com(uchar com)//****Һ��д��ָ���****
{
	rs=0;//����/ָ��ѡ����Ϊָ��
	rw=0; //��дѡ����Ϊд
	P0=com;//��������
	delay(1);
	en=1;//����ʹ�ܶˣ�Ϊ������Ч���½�����׼��
	delay(1);
	en=0;//en�ɸ߱�ͣ������½��أ�Һ��ִ������
}


void write_1602dat(uchar dat)//***Һ��д�����ݺ���****
{
	rs=1;//����/ָ��ѡ����Ϊ����
	rw=0; //��дѡ����Ϊд
	P0=dat;//��������
	delay(1);
	en=1; //en�øߵ�ƽ��Ϊ�����½�����׼��
	delay(1);
	en=0; //en�ɸ߱�ͣ������½��أ�Һ��ִ������
}


void lcd_init(void)//***Һ����ʼ������****
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
	write_1602com(er);//ʱ����ʾ�̶�����д��λ�ã��ӵ�2��λ�ú�ʼ��ʾ
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
void write_temp(uchar add,uint dat)//��LCDд�¶�����,��ָ����ʾλ��
{
	uchar gw,sw,bw,qw;
	//bw=dat/100;//ȡ�ð�λ
	//sw=dat%100/10;//ȡ��ʮλ����
	//gw=dat%10;//ȡ�ø�λ����
   
   qw=dat/1000;//��λ��
   bw=dat%1000/100;//ʮλ��
   sw=dat%100/10;//��λ��
   gw=dat%10;//С��λ
   if(tflag==1)
   {
      write_1602com(er+add);//er��ͷ�ļ��涨��ֵ0x80+0x40
      write_1602dat(0x2d);  //���ű�־
      write_1602dat(0x30+bw);
      write_1602dat(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
      write_1602dat('.');
      write_1602dat(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��
      write_1602dat(0xdf);//��ʾ�¶ȵ�СԲȦ���ţ�0xdf��Һ�����ַ���ĸ÷��ŵ�ַ��
      write_1602dat(0x43);	//��ʾ"C"���ţ�0x43��Һ�����ַ������дC�ĵ�ַ��	
   }
   else
   {
      write_1602com(er+add);//er��ͷ�ļ��涨��ֵ0x80+0x40
      write_1602dat(0x30+qw);
      write_1602dat(0x30+bw);
      write_1602dat(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
      write_1602dat('.');
      write_1602dat(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��
      write_1602dat(0xdf);//��ʾ�¶ȵ�СԲȦ���ţ�0xdf��Һ�����ַ���ĸ÷��ŵ�ַ��
      write_1602dat(0x43);	//��ʾ"C"���ţ�0x43��Һ�����ַ������дC�ĵ�ַ��	
   }
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


//------------------------------------
//ũ����ʾ�Ӻ���
void write_nl(uchar add,uchar dat)//��LCDдʱ����,����ʾλ�üӡ���ʾ���ݣ���������
{
	
	uchar gw,sw;
	//gw=dat%10;//ȡ�ø�λ����
	//sw=dat/10;//ȡ��ʮλ����
	gw=dat%16;//ȡ�ø�λ����
	sw=dat/16;//ȡ��ʮλ����
	write_1602com(er+add);//er��ͷ�ļ��涨��ֵ0x80+0x40
//	write_1602dat(0x30+sw);//����+30�õ������ֵ�LCD1602��ʾ��
//	write_1602dat(0x30+gw);//����+30�õ������ֵ�LCD1602��ʾ��	
	write_1602dat('0'+sw);//����+30�õ������ֵ�LCD1602��ʾ��
	write_1602dat('0'+gw);//����+30�õ������ֵ�LCD1602��ʾ��		
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
		
		case 0:write_1602dat('S');//��������Ϊ7ʱ��ʾ
			   write_1602dat('U');
			   write_1602dat('N');
			   break;
	}
}


//****************����ɨ���йغ���**********************
void keyscan()
{
	if(seeNL_NZ==0)
	{
		delay(9);
		if(seeNL_NZ==0)
		{
			led1=0;
			bltime=0;
			if((setn==0)&&(setNZn==0))								//��û�н����ʱģʽʱ�ſɰ���
			{
				buzzer=0;//����������һ��
	    		delay(20);
	    		buzzer=1;
	
				if(TR1==1)
				{
					TR1=0;		
				}
				else
				{			
					T_NL_NZ++;
					if(T_NL_NZ==3)
					{
						setn=0;
						setNZn=0;
						T_NL_NZ=0;	
					}
				}			
			}
			while(seeNL_NZ==0);
		}
	}
			

	if(set==0)//---------------setΪ���ܼ������ü���--------------------
	{
		delay(9);//��ʱ������������
		if(set==0)//��ʱ���ٴ�ȷ�ϰ�������
		{
			led1=0;
			bltime=0;

    		buzzer=0;//����������һ��
    		delay(20);
    		buzzer=1;
			while(!set);
			if(T_NL_NZ==0x02)			//֤���Ƕ����ӽ�������
			{
				setNZn++;
				if(setNZn==4)			//�����趨�ɹ����˻ص�������ʾ����������
				{
					setNZn=0;
					setn=0;
					timerOn=1;				
				}
				switch(setNZn)
				{
					case 0:						//������ʾ����ʱ��
						write_1602com(0x0c);	//����ù�겻���?
						write_1602com(er);		//ʱ����ʾ�̶�����д��λ��?
						for(a=0;a<16;a++)
						write_1602dat(NZd[a]);	//д��ʾʱ��̶����ţ�����ð��
						
						write_sfm(8,nz_shi);	//���� ʱ
						write_sfm(11,nz_fen);	//���� ��
						write_sfm(14,nz_miao);	//���� ��
						break;
					case 1:				   		//����������˸		
						write_1602com(er+15);	//���ð�������һ�Σ���λ����ʾ���   //er+0x09;
				  	 	write_1602com(0x0f);	//���ù��Ϊ��˸
						break;
					case 2:						//���ӷֹ����˸	
						write_1602com(er+12);	//���ð�������һ�Σ���λ����ʾ���   //er+0x09;
				  	 	write_1602com(0x0f);	//���ù��Ϊ��˸
						break;
					case 3:						//����ʱ�����˸	
						write_1602com(er+9);	//���ð�������һ�Σ���λ����ʾ���   //er+0x09;
				  	 	write_1602com(0x0f);	//���ù��Ϊ��˸
						break;	
				}	
			}

			else								//֤���Ƕ�ʱ�估���ڽ�������
			{
				if(T_NL_NZ==0)
				{
					setn++;
					if(setn==7)
						setn=0;			//���ð��������롢�֡�ʱ�����ڡ��ա��¡��ꡢ���أ�8������ѭ��
					switch(setn)
					{
			
						case 1: TR0=0;//�رն�ʱ��
						//TR1=0;
						write_1602com(er+7);//���ð�������һ�Σ���λ����ʾ���   //er+0x09;
				  	 	write_1602com(0x0f);//���ù��Ϊ��˸
				  	 	temp=(miao)/10*16+(miao)%10;//������д��DS1302
				  	 	write_1302(0x8e,0x00);
				  	 	write_1302(0x80,0x80|temp);//miao
				  	    write_1302(0x8e,0x80);
				  	 	break;
						case 2:  
						write_1602com(er+4);  //��2��fenλ����ʾ���   //er+0x06	
				   	 	 //write_1602com(0x0f);
						break;
						case 3: 
						write_1602com(er+1);   //����3�Σ�shi
				     	//write_1602com(0x0f);
						break;
					//	case 4: write_1602com(yh+0x0e);//����4�Σ�week
				 	    //write_1602com(0x0f);
					//	break;
						case 4: write_1602com(yh+0x0a);//����4�Σ�ri
					     //write_1602com(0x0f);
						break;
						case 5: write_1602com(yh+0x07);//����5�Σ�yue
					     //write_1602com(0x0f);
						break;
						case 6: write_1602com(yh+0x04);//����6�Σ�nian
				  	   //write_1602com(0x0f);
						break;
						case 0:
						write_1602com(0x0c);//��������7�Σ����ù�겻��˸
						TR0=1;//�򿪶�ʱ��
		        	 	temp=(miao)/10*16+(miao)%10;
					   	write_1302(0x8e,0x00);
				   		write_1302(0x80,0x00|temp);//miao����д��DS1302
				   		write_1302(0x8e,0x80);
		            	break;	
					}													
				}
			}
		}
	}
//------------------------------�Ӽ�add----------------------------		
	if((setn!=0)&&(setNZn==0))//��set�������¡��ٰ����¼�����Ч�����������������㣩
	{
		if(add==0)  //�ϵ���
		{
			delay(10);
			if(add==0)
			{
				led1=0;
				bltime=0;

			    buzzer=0;//����������һ��
			    delay(20);
			    buzzer=1;
				while(!add);
				switch(setn)
				{
					case 1:miao++;//���ü�����1�Σ�����
							if(miao==60)
								miao=0;//�볬��59���ټ�1���͹���
							write_sfm(0x06,miao);//��LCD����ȷλ����ʾ"��"�趨�õ�����
							temp=(miao)/10*16+(miao)%10;//ʮ����ת����DS1302Ҫ���DCB��
						   	write_1302(0x8e,0x00); //����д����ֹд���� 
						   	write_1302(0x80,temp); //��DS1302��д��Ĵ���80Hд��������������BCD��
						   	write_1302(0x8e,0x80); //��д����
							write_1602com(er+7);//��Ϊ����Һ����ģʽ��д�����ݺ󣬹���Զ����ƣ�����Ҫָ������
							//write_1602com(0x0b);
							break;
					case 2:fen++;
							if(fen==60)
								fen=0;
							write_sfm(0x03,fen);//��LCD����ȷλ����ʾ"��"�趨�õķ�����
							temp=(fen)/10*16+(fen)%10;//ʮ����ת����DS1302Ҫ���DCB��
						   	write_1302(0x8e,0x00);//����д����ֹд���� 
						   	write_1302(0x82,temp);//��DS1302��д�ּĴ���82Hд�������ķ�����BCD��
						   	write_1302(0x8e,0x80);//��д����
							write_1602com(er+4);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ����������д��ԭ����λ��
							break;
					case 3:shi++;
							if(shi==24)
								shi=0;
							write_sfm(0x00,shi);//��LCD����ȷ��λ����ʾ"��"�趨�õ�Сʱ����
							temp=(shi)/10*16+(shi)%10;//ʮ����ת����DS1302Ҫ���DCB��
						   	write_1302(0x8e,0x00);//����д����ֹд���� 
						   	write_1302(0x84,temp);//��DS1302��дСʱ�Ĵ���84Hд��������Сʱ����BCD��
						   	write_1302(0x8e,0x80);//��д����
							write_1602com(er+1);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
							break;
					/*
					case 4:week++;
							if(week==8)
								week=1;
				            write_1602com(yh+0x0C);//ָ��'��'�����������ʾλ��
								write_week(week);//ָ����������ʾ����
				            temp=(week)/10*16+(week)%10;//ʮ����ת����DS1302Ҫ���DCB��
						   	write_1302(0x8e,0x00);//����д����ֹд���� 
						   	write_1302(0x8a,temp);//��DS1302��д�ܼĴ���8aHд��������������BCD��
						   	write_1302(0x8e,0x80);//��д����
							   write_1602com(yh+0x0e);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
							break;
					*/
					case 4:ri++;
							if((yue==12)||(yue==10)||(yue==8)||(yue==7)||(yue==5)||(yue==3)||(yue==1))
                  {
                     if(ri>=32)  ri=1;
                  }  
                  else if(yue!=2)
                  {
                     if(ri>=31)  ri=1;
                  }
						else
                  {
                     if(((nian%4)==0))
							{
                        if(nian%100==0)
                        {
                           if((nian%400)==0) if(ri==30)  ri=1;
                           else if(ri>=29)  ri=1;
                        }
                        else if(ri>29)  ri=1;
                     }
                     else if(ri>=29)  ri=1;
                  }
							Conver_week(nian,yue,ri);
							write_week(week);
							write_nyr(9,ri);//��LCD����ȷ��λ����ʾ"��"�趨�õ���������
							temp=(ri)/10*16+(ri)%10;//ʮ����ת����DS1302Ҫ���DCB��
						   	write_1302(0x8e,0x00);//����д����ֹд����
						   	write_1302(0x86,temp);//��DS1302��д���ڼĴ���86Hд����������������BCD��
						   	write_1302(0x8e,0x80);//��д����
							write_1602com(yh+10);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
				
							break;
					case 5:yue++;
							if(yue==13)	yue=1;
                     if((yue==11)||(yue==9)||(yue==6)||(yue==4))
                     {
                        if(ri>30)  {ri=30;write_nyr(9,ri);}//��LCD����ȷ��λ����ʾ"��"�趨�õ���������
                     }  
                     else if(yue==2)
                     {
                        if(((nian%4)==0))
                        {
                           if(nian%100==0)
                           {
                              if((nian%400)==0) 
                              {
                                 if(ri>29)
                                 {ri=29;write_nyr(9,ri);}
                              }
                           }
                           else if(ri>29) {ri=29;write_nyr(9,ri);}
                        }
                        else if(ri>28)  {ri=28;write_nyr(9,ri);}
                        
                     }
							Conver_week(nian,yue,ri);
							write_week(week);
							write_nyr(6,yue);//��LCD����ȷ��λ����ʾ"��"�趨�õ��·�����
							temp=(yue)/10*16+(yue)%10;//ʮ����ת����DS1302Ҫ���DCB��
						   	write_1302(0x8e,0x00);//����д����ֹд����
						   	write_1302(0x88,temp);//��DS1302��д�·ݼĴ���88Hд���������·�����BCD��
						   	write_1302(0x8e,0x80);//��д����
							write_1602com(yh+7);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
				
							break;
					case 6:nian++;
						 if(nian==100)
							nian=0;
                     if(yue==2)
                     {
                        if(((nian%4)==0))
                        {
                           if(nian%100==0)
                           {
                              if((nian%400)==0) 
                              {
                                 if(ri>29)
                                 {ri=29;write_nyr(9,ri);}
                              }
                           }
                           else if(ri>29) {ri=29;write_nyr(9,ri);}
                        }
                        else if(ri>28)  {ri=28;write_nyr(9,ri);}
                        
                     }
							Conver_week(nian,yue,ri);
							write_week(week);
							write_nyr(3,nian);//��LCD����ȷ��λ����ʾ"��"�趨�õ��������
				            temp=(nian)/10*16+(nian)%10;//ʮ����ת����DS1302Ҫ���DCB��
						   	write_1302(0x8e,0x00);//����д����ֹд����
						   	write_1302(0x8c,temp);//��DS1302��д��ݼĴ���8cHд���������������BCD��
						   	write_1302(0x8e,0x80);//��д����
							write_1602com(yh+4);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
				
							break;
				}
			}
	
		}
		//------------------����dec�����书�ܲ���'�Ӽ�'ע��---------------
		if(dec==0)
		{
			delay(10);//����ʱ��������
			if(dec==0)
			{
				led1=0;
				bltime=0;

		    	buzzer=0;//����������һ��
			    delay(20);
			    buzzer=1;
				while(!dec);
				switch(setn)
				{
					case 1:
						miao--;
						if(miao==-1)
							miao=59;//�����ݼ���-1ʱ�Զ����59
						write_sfm(0x06,miao);//��LCD����ȷλ����ʾ�ı���µ�����
			            temp=(miao)/10*16+(miao)%10;//ʮ����ת����DS1302Ҫ���DCB��
					   	write_1302(0x8e,0x00); //����д����ֹд���� 
					   	write_1302(0x80,temp); //��DS1302��д��Ĵ���80Hд��������������BCD��
					   	write_1302(0x8e,0x80); //��д����
						write_1602com(er+7);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ����������д��ԭ����λ��
						//write_1602com(0x0b);
						break;
					case 2:
						fen--;
						if(fen==-1)
						fen=59;
						write_sfm(3,fen);
						temp=(fen)/10*16+(fen)%10;//ʮ����ת����DS1302Ҫ���DCB��
					   	write_1302(0x8e,0x00);//����д����ֹд���� 
					   	write_1302(0x82,temp);//��DS1302��д�ּĴ���82Hд�������ķ�����BCD��
					   	write_1302(0x8e,0x80);//��д����
						write_1602com(er+4);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ����������д��ԭ����λ��
						break;
	
					case 3:
						shi--;
				  		if(shi==-1)
						shi=23;
						write_sfm(0,shi);
						temp=(shi)/10*16+(shi)%10;//ʮ����ת����DS1302Ҫ���DCB��
					   	write_1302(0x8e,0x00);//����д����ֹд���� 
					   	write_1302(0x84,temp);//��DS1302��дСʱ�Ĵ���84Hд��������Сʱ����BCD��
					   	write_1302(0x8e,0x80);//��д����
						write_1602com(er+1);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
						break;
			/*
			case 4:week--;
					if(week==0)
						week=7;
				 
	            write_1602com(yh+0x0C);//ָ��'��'�����������ʾλ��
					write_week(week);//ָ����������ʾ����
				   temp=(week)/10*16+(week)%10;//ʮ����ת����DS1302Ҫ���DCB��
			   	write_1302(0x8e,0x00);//����д����ֹд���� 
			   	write_1302(0x8a,temp);//��DS1302��д�ܼĴ���8aHд��������������BCD��
			   	write_1302(0x8e,0x80);//��д����
				   write_1602com(yh+0x0e);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
				break;
			*/
					case 4:
						ri--;
						if((yue==12)||(yue==10)||(yue==8)||(yue==7)||(yue==5)||(yue==3)||(yue==1))
                  {
                     if(ri==0)  ri=31;
                  }  
                  else if(yue!=2)
                  {
                     if(ri==0)  ri=30;
                  }
						else
                  {
                     if(((nian%4)==0))
							{
                        if(nian%100==0)
                        {
                           if((nian%400)==0) if(ri==0)  ri=29;
                           else if(ri==0)  ri=28;
                        }
                        else if(ri==0)  ri=29;
                     }
                     else if(ri==0)  ri=28;
                  }
						Conver_week(nian,yue,ri);
						write_week(week);
						write_nyr(9,ri);
						temp=(ri)/10*16+(ri)%10;//ʮ����ת����DS1302Ҫ���DCB��
					   	write_1302(0x8e,0x00);//����д����ֹд����
					   	write_1302(0x86,temp);//��DS1302��д���ڼĴ���86Hд����������������BCD��
					   	write_1302(0x8e,0x80);//��д����
						write_1602com(yh+10);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ		
						break;
					case 5:
						yue--;
                  if(yue==0)
						yue=12;

                  if((yue==11)||(yue==9)||(yue==6)||(yue==4))
                     {
                        if(ri>30)  {ri=30;write_nyr(9,ri);}//��LCD����ȷ��λ����ʾ"��"�趨�õ���������
                     }  
                     else if(yue==2)
                     {
                        if(((nian%4)==0))
                        {
                           if(nian%100==0)
                           {
                              if((nian%400)==0) 
                              {
                                 if(ri>29)
                                 {ri=29;write_nyr(9,ri);}
                              }
                           }
                           else if(ri>29) {ri=29;write_nyr(9,ri);}
                        }
                        else if(ri>28)  {ri=28;write_nyr(9,ri);}
                        
                     }
						Conver_week(nian,yue,ri);
						write_week(week);
						write_nyr(6,yue);
						temp=(yue)/10*16+(yue)%10;//ʮ����ת����DS1302Ҫ���DCB��
					   	write_1302(0x8e,0x00);//����д����ֹд����
					   	write_1302(0x88,temp);//��DS1302��д�·ݼĴ���88Hд���������·�����BCD��
					   	write_1302(0x8e,0x80);//��д����
						write_1602com(yh+7);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
			
						break;	
					case 6:
						nian--;
			 			if(nian==-1)
						nian=99;
                  if(nian==100)
							nian=0;
                     if(yue==2)
                     {
                        if(((nian%4)==0))
                        {
                           if(nian%100==0)
                           {
                              if((nian%400)==0) 
                              {
                                 if(ri>29)
                                 {ri=29;write_nyr(9,ri);}
                              }
                           }
                           else if(ri>29) {ri=29;write_nyr(9,ri);}
                        }
                        else if(ri>28)  {ri=28;write_nyr(9,ri);}
                        
                     }
						Conver_week(nian,yue,ri);
						write_week(week);
						write_nyr(3,nian);
			         	temp=(nian)/10*16+(nian)%10;//ʮ����ת����DS1302Ҫ���DCB��
					   	write_1302(0x8e,0x00);//����д����ֹд����
					   	write_1302(0x8c,temp);//��DS1302��д��ݼĴ���8cHд���������������BCD��
					   	write_1302(0x8e,0x80);//��д����
						write_1602com(yh+4);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
						break;
								
				}
			}
		}
	}
	if((setNZn!=0)&&(setn==0))
	{
		if(add==0)  //�ϵ���
		{
			delay(10);
			if(add==0)
			{
				led1=0;
				bltime=0;

			    buzzer=0;//����������һ��
			    delay(20);
			    buzzer=1;
				while(!add);
				switch(setNZn)
				{
					case 1:
						nz_miao++;				//���ü�����1�Σ�����
						if(nz_miao==60)
							nz_miao=0;//�볬��59���ټ�1���͹���
						write_sfm(14,nz_miao);//��LCD����ȷλ����ʾ"��"�趨�õ�����
						write_1602com(er+15);//��Ϊ����Һ����ģʽ��д�����ݺ󣬹���Զ����ƣ�����Ҫָ������
						break;
					case 2:
						nz_fen++;
						if(nz_fen==60)
							nz_fen=0;
						write_sfm(11,nz_fen);//��LCD����ȷλ����ʾ"��"�趨�õķ�����
						write_1602com(er+12);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ����������д��ԭ����λ��
						break;
					case 3:
						nz_shi++;
						if(nz_shi==24)
							nz_shi=0;
						write_sfm(8,nz_shi);//��LCD����ȷ��λ����ʾ"��"�趨�õ�Сʱ����
						write_1602com(er+9);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
						break;
				}
			}
	
		}
		//------------------����dec�����书�ܲ���'�Ӽ�'ע��---------------
		if(dec==0)
		{
			delay(10);//����ʱ��������
			if(dec==0)
			{
				led1=0;
				bltime=0;

		    	buzzer=0;//����������һ��
			    delay(20);
			    buzzer=1;
				while(!dec);
				switch(setNZn)
				{
					case 1:
						nz_miao--;
						if(nz_miao==-1)
							nz_miao=59;//�����ݼ���-1ʱ�Զ����59
						write_sfm(14,nz_miao);//��LCD����ȷλ����ʾ�ı���µ�����
						write_1602com(er+15);
						break;
					case 2:
						nz_fen--;
						if(nz_fen==-1)
							nz_fen=59;
						write_sfm(11,nz_fen);
						write_1602com(er+12);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ����������д��ԭ����λ��
						break;
	
					case 3:
						nz_shi--;
				  		if(nz_shi==-1)
						nz_shi=23;
						write_sfm(8,nz_shi);
						write_1602com(er+9);//��Ϊ����Һ����ģʽ��д�����ݺ�ָ���Զ���һ��������Ҫ����λ
						break;
								
				}
			}
		}
	}	
}

//-------------------------------
void init(void)   //��ʱ�������������ú���
{
	TMOD=0x11; 		//ָ����ʱ/�������Ĺ�����ʽΪ3
	TH0=0; 			//��ʱ��T0�ĸ���λ=0
	TL0=0;  		//��ʱ��T0�ĵ���λ=0
	TH1=0x3C;
	TL1=0xB0;
	EA=1;  			//ϵͳ�����п��ŵ��ж�
	ET0=1; 			//����T0�ж�
	ET1=1;
	IT1=1;
	IT0=0;
	TR0=1; 			//�����жϣ�������ʱ��
	TR1=0;
}


void alarm(void)
{
	if((shi==nz_shi)&&(fen==nz_fen)&&(miao==0))
	{
	    TR1=1;
	}
	if((shi==nz_shi)&&(fen==(nz_fen+1)))
	{
		TR1=0;
		buzzer=1;
	}
}


void ZD_baoshi(void)
{
	buzzer=0;
	delay(5);
	buzzer=1;
	bsn++;
	if(bsn==temp_hour)
	{
		baoshi=0;
	}
}

//*******************������**************************
//***************************************************
void main()
{
	P1=0xff;
	lcd_init();      //����Һ������ʼ���Ӻ���
	ds1302_init();   //����DS1302ʱ�ӵĳ�ʼ���Ӻ���
	init();          //���ö�ʱ�������������Ӻ���
	led=1;           //��LCD�ı����Դ
    buzzer=0;		 //����������һ��
    delay(80);
    buzzer=1;
	while(1)  //����ѭ���������䣺
	{		
   	 	keyscan();      //���ü���ɨ���Ӻ���
		led=led1;		
		if(timerOn==1)
			alarm();	//�������
		if((fen==0)&&(miao==0))
		{
			if(shi>12)
				temp_hour=shi-12;
			else
			{
				if(shi==0)
					temp_hour=12;
				else
					temp_hour=shi;
			}
			shangyimiao=miao;
			baoshi=1;
		}
		if(baoshi==1)
		{
			ZD_baoshi();
			do 
				keyscan();
			while(shangyimiao==miao);	
			shangyimiao=miao;
		}
    }
}


void timer0() interrupt 1  //ȡ�ò���ʾ������ʱ��
{
	
   //Init_DS18B20();//�¶ȴ�����DS18b2��ʼ���Ӻ�������ͷ�ļ���
   //flag=ReadTemperature();//��18b2ͷ�ļ����з��صĺ�������͵�����FLAG�У�������ʾ

  //��ȡ��ʱ�����������߸����ݣ�DS1302�Ķ��Ĵ�����д�Ĵ�����һ������
	
    miao = BCD_Decimal(read_1302(0x81));
	fen = BCD_Decimal(read_1302(0x83));
	shi  = BCD_Decimal(read_1302(0x85));
	ri  = BCD_Decimal(read_1302(0x87));
	yue = BCD_Decimal(read_1302(0x89));
	nian=BCD_Decimal(read_1302(0x8d));
	//week=BCD_Decimal(read_1302(0x8b));     //����ȡ��ֱ��ͨ�����ڼ���õ�
	if((led1==0))
	{
		if(temp_miao!=miao)
		{
			temp_miao=miao;
			bltime++;
		}
		if(bltime==10)
		{
			led1=1;
			bltime=0;
		}
	}


    if(T_NL_NZ==1)							//��ʾũ��
	{
		uint nian_temp,temp;
		temp=nian;
		nian_temp=2000+(temp&0xF0)*10+temp&0x0F;
		if((nian_temp%400==0)||((nian_temp%100!=0)&&(nian_temp%4==0)))  //�ж��Ƿ�Ϊ����
			p_r=1;
		else
			p_r=0;
		Conversion(0,nian,yue,ri);
		write_1602com(er);//ʱ����ʾ�̶�����д��λ��?
		for(a=0;a<16;a++)
		{
			if(p_r==0)
				write_1602dat(nlp[a]);//д��ʾʱ��̶����ţ�����ð��
			else 
				write_1602dat(nlr[a]);
		}

	  	write_nl(3,year_moon);//ũ�� ��
		write_nl(6,month_moon);//ũ�� ��
		write_nl(9,day_moon);//ũ�� ��

		do
			keyscan();
		while(T_NL_NZ==1);

		write_1602com(er);//ʱ����ʾ�̶�����д��λ�ã��ӵ�2��λ�ú�ʼ��ʾ
		for(a=0;a<16;a++)
		{
			write_1602dat(qk[a]);//д��ʾʱ��̶����ţ�����ð��
		}

		write_1602com(er);//ʱ����ʾ�̶�����д��λ�ã��ӵ�2��λ�ú�ʼ��ʾ
		for(a=0;a<8;a++)
		{
			write_1602dat(tab2[a]);//д��ʾʱ��̶����ţ�����ð��
		}
	}

	if(T_NL_NZ==2)								//��ʾ����ʱ�䣬
	{
		write_1602com(er);//ʱ����ʾ�̶�����д��λ��?
		for(a=0;a<16;a++)
			write_1602dat(NZd[a]);//д��ʾʱ��̶����ţ�����ð��

	  	write_sfm(8,nz_shi);//ũ�� ��
		write_sfm(11,nz_fen);//ũ�� ��
		write_sfm(14,nz_miao);//ũ�� ��

		do
			keyscan();
		while(T_NL_NZ==2);

		write_1602com(er);//ʱ����ʾ�̶�����д��λ�ã��ӵ�2��λ�ú�ʼ��ʾ
		for(a=0;a<16;a++)
		{
			write_1602dat(qk[a]);//д��ʾʱ��̶����ţ�����ð��
		}

		write_1602com(er);//ʱ����ʾ�̶�����д��λ�ã��ӵ�2��λ�ú�ʼ��ʾ
		for(a=0;a<8;a++)
		{
			write_1602dat(tab2[a]);//д��ʾʱ��̶����ţ�����ð��
		}
	}
	

	else
	{	
		//��ʾ�¶ȡ��롢ʱ�������ݣ� 
		if(wd)
		{ 
			flag=ReadTemperature()-5;
	  		write_temp(9,flag);//��ʾ�¶ȣ��ӵڶ��е�11���ַ���ʼ��ʾ
		}
		else
		{
			write_1602com(er+12);
			for(a=0;a<4;a++)
			{
				write_1602dat(tm[a]);
			}
		}
	  	write_sfm(6,miao);//�룬�ӵڶ��е�8���ֺ�ʼ��ʾ������ʱ������ʾ�Ӻ�����
		write_sfm(3,fen);//�֣��ӵڶ��е�5���ַ���ʼ��ʾ
		write_sfm(0,shi);//Сʱ���ӵڶ��е�2���ַ���ʼ��ʾ
	}	
		//��ʾ�ա��¡������ݣ�
		write_nyr(9,ri);//���ڣ��ӵڶ��е�9���ַ���ʼ��ʾ
	   	write_nyr(6,yue);//�·ݣ��ӵڶ��е�6���ַ���ʼ��ʾ
		write_nyr(3,nian);//�꣬�ӵڶ��е�3���ַ���ʼ��ʾ
		Conver_week(nian,yue,ri);
		write_week(week);
}


unsigned char count1;

void timer1() interrupt 3  //ȡ�ò���ʾ������ʱ��
{
	TH1=0x3C;
	TL1=0xB0;
	TR1=1;
	count1++;
	if(count1==10)
	{
		count1=0;
		buzzer=!buzzer;
	}
}
