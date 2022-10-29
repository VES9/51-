/*
*   @Author:ZSX
*   @Date:
*   @Description:
*   @LastEditTime:
*   @LastEditors:ZSX
*   @Filepath:
*/

/********************************************************************

1.SCON�Ĵ���
SM0   SM1   SM2   REN   TB8   RB8   TI   RI
                  1     0     0     0    0
SM0:���й�����ʽ����λ
SM1:���й�����ʽ����λ
SM2:���ͨ�ſ���λ 1�����ͨ�� 0����Ե�ͨ��
REN:������տ���λ 1��������� 0����ֹ����
TB8:�������ݵھ�λ
RB8:�������ݵھ�λ
TI:����ͨ���ж������־
RI:����ͨ���ж������־

2.���й�����ʽ����λ ������ʽѡ��
SM0 SM1 ��ʽ            ����˵��
0   0    0          8λͬ����λ�Ĵ�����ʽ��һ�㲻�ã����ַ�ʽ�������첽ͨ�ŷ�ʽ��
0   1    1          10λ�����첽ͨ�ŷ�ʽ
1   0    2          11λ�����첽ͨ�ŷ�ʽ
1   1    3          11λ�����첽ͨ�ŷ�ʽ

3. @1 ѡ�����й�����ʽ1 ��ʼ��
      �������£�
			void SCON_init()
			{
				SCON=0x50; //0101 0000  ����λ��01ѡ������ʽ1 0ѡ���Ե�ͨ�� 1ѡ��������� 
				           //����λ�� 0ѡ���ֹ�������ݵھ�λ 0ѡ���ֹ�������ݵھ�λ 0ѡ��TI��־λ��0 0ѡ��RI��־λ��0
				
				EA=1;      //�����ж�
				ET0=1;     //�򿪶�ʱ��/������0������ж�����λ
				EX0=0;     //�ر��ⲿ�ж�0�ж�����λ
				ET1=0;     //�رն�ʱ��/������1������ж�����λ
				EX1=0;     //�ر��ⲿ�ж�1�ж�����λ
				ES=1;      //�򿪴���ͨ���ж�����λ
			}
			
			void Timer1_INIT() //��ʱ��1��ʼ��
			{
				TMOD=0x20; //ע������ͨ����Ҫѡ��8λ�����ض�ʱ���Ĺ�����ʽ����������ʽ2
				TH1=256-3;
				TL1=256-3;
				TR1=1;
			}

			void Service_SCON() interrupt 4 //�򿪴���ͨ���ж�
			{
				//FUNCTION
			}

********************************************************************/



#include <REGX51.H>
#include <INTRINS.H>
#include <MATH.H>
#define uchar unsigned char
#define uint unsigned int
#define schar static char
typedef int i8;
typedef char c8;
typedef float f8;

uchar flag=0;
uchar recdat=0;

void SCON_init()
{
	SCON=0x50;
	EA=1;
	ET0=1;
	EX0=0;
	ET1=0;
	EX1=0;
	ES=1;
}

void Timer1_INIT()
{
	TMOD=0x20;
	TH1=256-3;
	TL1=256-3;
	TR1=1;
}

void Service_SCON() interrupt 4
{
	recdat=SBUF;
	RI=0;
	flag=~flag;
}

void Senddat()
{
	SBUF=recdat;
	while(!TI)
		TI=0;
}

void main()
{
	SCON_init();
	Timer1_INIT();
	Senddat();
	while(1)
	{
		if(flag==1)
		{
				Senddat();
		}
		else
		{
		
		}
	}
}











