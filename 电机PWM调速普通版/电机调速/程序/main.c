/**************************************************************
�ļ���	: 	 mian.c
����	   : �ǻ�С��
�汾	   : V1.0
����	   : ���PWM����
����	   : ��
CSDN���� 	   : https://blog.csdn.net/dwh1314/article/details/106158025
΢�Ź��ں�    : �ǻ�С��
��־	   : ����V1.0 2020/3/10 ����
**************************************************************/
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define motorA  0
#define motorB  1
//�������IN1-IN4
sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit IN3 = P2^2;
sbit IN4 = P2^3;
sbit ENA = P2^4;	//���Aʹ��
sbit ENB = P2^5;	//���Bʹ��
sbit speed_add = P1^0;	//�ٶȼ�
sbit speed_mus = P1^1;	//�ٶȼ�
sbit forward = P1^2;	//��ת
sbit reversal = P1^3;	//��ת
sbit A_OF_B = P1^4;	//ѡ��A/B
bit flag;	

//������ٶ� 0-20��20���ͣת��0���
uchar speedA = 10;
uchar speedB = 10;

/*
 * @description	: ��ʱ����
 * @param 		: ��ʱʱ��Լ1ms
 * @return 		: ��
 */
void delay(unsigned int j)
{
		unsigned int x;
		for(x=0;x<j;x++);
}

/*
 * @description	: ���A��ת
 * @param 		:��
 * @return 		: ��
 */
void motorA_forward()
{
		IN1=0;
		IN2=1;
}



/*
 * @description	: ���A��ת
 * @param 		:��
 * @return 		: ��
 */
void motorA_reversal()
{
		IN1=1;
		IN2=0;
}



/*
 * @description	: ���B��ת
 * @param 		:��
 * @return 		: ��
 */
void motorB_forward()
{
		IN3=0;
		IN4=1;
}



/*
 * @description	: ���B��ת
 * @param 		:��
 * @return 		: ��
 */
void motorB_reversal()
{
		IN3=1;
		IN4=0;
}



/*
 * @description	: ������ɨ��
 * @param 		:��
 * @return 		: ��
 */
void key_scan()
{
		//�ٶȼ�
		if(speed_add==0)
		{
				//��ʱ����
				delay(10);
				if(speed_add==0)
				{
						if(flag == motorA)
						{
								if(speedA>0)speedA-=2;
						}
						if(flag == motorB)
						{
								if(speedB>0)speedB-=2;
						}
						while(!speed_add);
						return ;
				}
		}
		
		//�ٶȼ�
		if(speed_mus==0)
		{
			delay(10);
			if(speed_mus==0)
				{
						if(flag == motorA)
						{
								if(speedA<=20)speedA+=2;
						}
						if(flag == motorB)
						{
								if(speedB<=20)speedB+=2;
						}
				}
				while(!speed_mus);
				return ;
		}
		
		//ǰ��
		if(forward==0)
		{
				delay(10);
				if(forward==0)
				{	
						//���ݱ�־λ�жϵ�ǰ�ǿ��Ƶĵ��A����B
						if(flag == motorA)motorA_forward();
						if(flag == motorB)motorB_forward();
				}
				while(!forward);
				return ;
		}
		
		//����
		if(reversal==0)
		{
				delay(10);
				if(reversal==0)
				{
						//���ݱ�־λ�жϵ�ǰ�ǿ��Ƶĵ��A����B
						if(flag == motorA)motorA_reversal();
						if(flag == motorB)motorB_reversal();
				}
				while(!reversal);
				return ;
		}
		
		//ѡ����A��B
		if(A_OF_B==0)
		{
				delay(10);
				if(A_OF_B==0)
				{
						//�л����Ƶĵ��
						flag = flag==motorA? motorB : motorA;
				}
				while(!A_OF_B);
				return ;
		}
}


/*
 * @description	: ������ �������
 * @param 		:��
 * @return 		: ��
 */
void main()
{
		EA=1;//�����ж�	
		TMOD=0x01; //��ʱ��������ʽ
		TH0=(65535-1000)/256; //��ֵԼ1ms
		TL0=(65535-1000)%256; 
		ET0=1;	//�򿪶�ʱ���ж�
		TR0=1;	//�򿪶�ʱ��
		flag=motorA;	//Ĭ��ѡ����A
		while(1)
		{
				key_scan();	//����ɨ��
		}
}


/*
 * @description	: ��ʱ���жϺ���,���ö�ʱ������PWM�����ź�
 * @param 		:��
 * @return 		: ��
 */
void Time() 	interrupt 1
{
			
	
		static uchar count=0; 
		TH0=(65535-1000)/256;  //��װ��ֵ
		TL0=(65535-1000)%256;	 //��װ��ֵ
		count++;
		if(count==20)count=0;
		if(count>=speedA)
		{
				ENA=1;
		}
		else{
				ENA=0;
		}
		if(count>=speedB)
		{
				ENB=1;
		}
		else{
				ENB=0;
		}

}
