/*
*   @Author:ZSX
*   @Date:
*   @Description:
*   @LastEditTime:
*   @LastEditors:ZSX
*   @Filepath:
*/

/********************************************************************

1.SCON寄存器
SM0   SM1   SM2   REN   TB8   RB8   TI   RI
                  1     0     0     0    0
SM0:串行工作方式定义位
SM1:串行工作方式定义位
SM2:多机通信控制位 1：多机通信 0：点对点通信
REN:允许接收控制位 1：允许接收 0：禁止接收
TB8:发送数据第九位
RB8:接收数据第九位
TI:串行通信中断请求标志
RI:串行通信中断请求标志

2.串行工作方式定义位 工作方式选择
SM0 SM1 方式            功能说明
0   0    0          8位同步移位寄存器方式（一般不用，这种方式不属于异步通信方式）
0   1    1          10位数据异步通信方式
1   0    2          11位数据异步通信方式
1   1    3          11位数据异步通信方式

3. @1 选定串行工作方式1 初始化
      代码如下：
			void SCON_init()
			{
				SCON=0x50; //0101 0000  高四位：01选择工作方式1 0选择点对点通信 1选择允许接收 
				           //低四位： 0选择禁止发送数据第九位 0选择禁止接收数据第九位 0选择TI标志位清0 0选择RI标志位清0
				
				EA=1;      //打开总中断
				ET0=1;     //打开定时器/计数器0的溢出中断允许位
				EX0=0;     //关闭外部中断0中断允许位
				ET1=0;     //关闭定时器/计数器1的溢出中断允许位
				EX1=0;     //关闭外部中断1中断允许位
				ES=1;      //打开串行通信中断允许位
			}
			
			void Timer1_INIT() //定时器1初始化
			{
				TMOD=0x20; //注：串行通信需要选择8位可重载定时器的工作方式，即工作方式2
				TH1=256-3;
				TL1=256-3;
				TR1=1;
			}

			void Service_SCON() interrupt 4 //打开串行通信中断
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











