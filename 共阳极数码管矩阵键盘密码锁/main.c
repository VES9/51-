#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar old1=6,old2=6,old3=6,old4=6,old5=6,old6=6; //ԭʼ����666666
uchar new1,new2,new3,new4,new5,new6;  //ÿ�ε�Ƭ���ɼ���������
uchar a=10,b=10,c=10,d=10,e=10,f=10; //�����������ʾ�ı��� ��ʼ״̬����ʾ
uchar wei,key,temp;	  //λ���� ������ֵ ����������б��� 

bit allow,gai,ok,wanbi,retry,close;	 //����״̬����
//  ����  ������  ��ȷ  ���  �������� �ر� 

sbit buzz=P1^7;//�������ӿ�
sbit relay=P1^3;//�̵����ӿ�

uchar dd[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff,0xbf};
//����������ܶ����										// 10 11
void delay(unsigned char i)
{
	uchar j,k;
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void keyscan(uchar a,uchar b,uchar c,uchar d,uchar e,uchar f)
{
	{	
    P3=0xfe; //P3��	��һ��
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {	
        temp=P3;
        switch(temp)//�жϱ���
        {
          case 0xee:   //����0 
               key=0;
			   wei++;  //�����λ
               break;

          case 0xde:  //1
               key=1;
			   wei++;
               break;

          case 0xbe:  //2
               key=2;
			   wei++;
               break;

          case 0x7e:  //3
               key=3;
			   wei++;
               break;
         }
         while(temp!=0xf0) 
        {
           temp=P3;
           temp=temp&0xf0;
           buzz=1;	//������ʱ��������
         }
         buzz=0;   //�������� �ر�
      }
    }
    P3=0xfd;	  //�ڶ���
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xed: //4
               key=4;
			   wei++;
               break;

          case 0xdd:  //5
               key=5;
			   wei++;
               break;

          case 0xbd: //6
               key=6;
			   wei++;
               break;

          case 0x7d:   //7
               key=7;
			   wei++;
               break;
         }
         while(temp!=0xf0)
         {
           temp=P3;	   
           temp=temp&0xf0;
           buzz=1;
         }
         buzz=0;
      }
      }
    P3=0xfb;	  //������
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xeb:   //8
               key=8;
			   wei++;
               break;

          case 0xdb:   //9
               key=9;
			   wei++;
               break;
			   
          case 0xbb:	//��������
               gai=1;
			   wei=0;
               break;

          case 0x7b:	 //ȷ������
		  	   if(allow)
               ok=1;
               break;
         }
        while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           buzz=1;
         }
         buzz=0;
      }
      }
	  P3=0xf7;		//������
    temp=P3;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      delay(10);
      if(temp!=0xf0)
      {
        temp=P3;
        switch(temp)
        {
          case 0xe7:  //��������
		  	   retry=1;
               break;

          case 0xd7:	//�ر�������
		  	   close=1;
               break;
         }
        while(temp!=0xf0)
         {
           temp=P3;
           temp=temp&0xf0;
           buzz=1;
         }
         buzz=0;
      }
      }
}
	}
		
	
	
	
	
	
	
	
	













































	
	
	
	
	
	
	
void main()
{
	while(1)
	{
	
	}
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
















