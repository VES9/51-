/**************************************************************
文件名	: 	 mian.c
作者	   : 智慧小巷
版本	   : V1.0
描述	   : 电机PWM调速
其他	   : 无
CSDN博客 	   : https://blog.csdn.net/dwh1314/article/details/106158025
微信公众号    : 智慧小巷
日志	   : 初版V1.0 2020/3/10 创建
**************************************************************/
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define motorA  0
#define motorB  1
//定义输出IN1-IN4
sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit IN3 = P2^2;
sbit IN4 = P2^3;
sbit ENA = P2^4;	//电机A使能
sbit ENB = P2^5;	//电机B使能
sbit speed_add = P1^0;	//速度加
sbit speed_mus = P1^1;	//速度减
sbit forward = P1^2;	//正转
sbit reversal = P1^3;	//反转
sbit A_OF_B = P1^4;	//选择A/B
bit flag;	

//电机初速度 0-20，20电机停转，0最快
uchar speedA = 10;
uchar speedB = 10;

/*
 * @description	: 延时函数
 * @param 		: 延时时长约1ms
 * @return 		: 无
 */
void delay(unsigned int j)
{
		unsigned int x;
		for(x=0;x<j;x++);
}

/*
 * @description	: 电机A正转
 * @param 		:无
 * @return 		: 无
 */
void motorA_forward()
{
		IN1=0;
		IN2=1;
}



/*
 * @description	: 电机A反转
 * @param 		:无
 * @return 		: 无
 */
void motorA_reversal()
{
		IN1=1;
		IN2=0;
}



/*
 * @description	: 电机B正转
 * @param 		:无
 * @return 		: 无
 */
void motorB_forward()
{
		IN3=0;
		IN4=1;
}



/*
 * @description	: 电机B正转
 * @param 		:无
 * @return 		: 无
 */
void motorB_reversal()
{
		IN3=1;
		IN4=0;
}



/*
 * @description	: 按键是扫描
 * @param 		:无
 * @return 		: 无
 */
void key_scan()
{
		//速度加
		if(speed_add==0)
		{
				//延时消抖
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
		
		//速度减
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
		
		//前进
		if(forward==0)
		{
				delay(10);
				if(forward==0)
				{	
						//根据标志位判断当前是控制的电机A还是B
						if(flag == motorA)motorA_forward();
						if(flag == motorB)motorB_forward();
				}
				while(!forward);
				return ;
		}
		
		//后退
		if(reversal==0)
		{
				delay(10);
				if(reversal==0)
				{
						//根据标志位判断当前是控制的电机A还是B
						if(flag == motorA)motorA_reversal();
						if(flag == motorB)motorB_reversal();
				}
				while(!reversal);
				return ;
		}
		
		//选择电机A或B
		if(A_OF_B==0)
		{
				delay(10);
				if(A_OF_B==0)
				{
						//切换控制的点击
						flag = flag==motorA? motorB : motorA;
				}
				while(!A_OF_B);
				return ;
		}
}


/*
 * @description	: 主函数 程序入口
 * @param 		:无
 * @return 		: 无
 */
void main()
{
		EA=1;//打开总中断	
		TMOD=0x01; //定时器工作方式
		TH0=(65535-1000)/256; //初值约1ms
		TL0=(65535-1000)%256; 
		ET0=1;	//打开定时器中断
		TR0=1;	//打开定时器
		flag=motorA;	//默认选择电机A
		while(1)
		{
				key_scan();	//按键扫描
		}
}


/*
 * @description	: 定时器中断函数,利用定时器产生PWM调速信号
 * @param 		:无
 * @return 		: 无
 */
void Time() 	interrupt 1
{
			
	
		static uchar count=0; 
		TH0=(65535-1000)/256;  //重装初值
		TL0=(65535-1000)%256;	 //重装初值
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
