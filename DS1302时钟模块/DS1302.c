#include "ds1302.h"

unsigned char time[8] = {0x00,0x45,0x19,0x18,0x10,0x01,0x21,0x20};//���ʱ ������ ��

/*DS1302���ֽڶ����ݺ���*/
unsigned char ds1302_readByte(unsigned char dat)
{
	unsigned char i = 0;
	for(i=0;i<8;i++)  
	{
		dat = dat >> 1;	 //����һ�� ��λ��ʼ ����Ч����7��
		if(DAT == 1) 		
			dat = dat | 0x80;	 //��λ��1
		else
			dat = dat & 0x7F;	 //��λ��0	
		CLK = 1; //ʱ�����߱�ʾ��λ�Ѿ�����
		CLK = 0; //ʱ�����Ϳ�ʼ�����µ�����λ
	}	
	return dat;

}

/*DS1302���ֽ�д��ַ�������ݺ���*/
void ds1302_writeByte(unsigned char addrOrData)
{
	unsigned char i = 0;
	for(i=0;i<8;i++)   
	{
		DAT = addrOrData & 0x01;	//��ʼ�����λ 
		addrOrData = addrOrData >> 1;//����һλ
		CLK = 1;					 //����ʱ�ӱ�ʾ�Ѿ�����
		CLK = 0;					 //����ʱ��׼���������µ�����λ
	}
					
}

/*DS1302ʱ��ģ��д�����*/
void ds1302_writeCom(unsigned char addr,unsigned char dat)
{
 	RST = 0; //����RST
	CLK = 0; //����ʱ��
	RST = 1; //ʹ�ܴ�
	ds1302_writeByte(addr);	 //д��Ҫд�ĵ�ַ
	ds1302_writeByte(dat);	 //д���ַ������
	RST = 0; //�ر� ��ʾ����
}

/*DS1302ʱ��ģ������ݺ���*/
unsigned char ds1302_readData(unsigned char addr)
{
	unsigned char dat = 0;
	RST = 0; //����RST
	CLK = 0; //����ʱ��
	RST = 1; //��ʹ��
	ds1302_writeByte(addr);		//д��Ҫ���ĵ�ַ
	dat = ds1302_readByte(dat);	//��ȡ��ַ������
	RST = 0; //�ر� ��ʾ����
	
	return dat; //���ض�ȡ��������
}

/*DS1302ʱ��ģ���ȡ���ں�ʱ�亯��*/
void ds1302_read_DateAndTime()
{
	time[0] = ds1302_readData(DS1302_READ_YEAR);  //��ȡ��
	time[1] = ds1302_readData(DS1302_READ_MONTH); //��ȡ��
	time[2] = ds1302_readData(DS1302_READ_DAY);   //��ȡ��
	time[3] = ds1302_readData(DS1302_READ_HOUR);  //��ȡʱ
	time[4] = ds1302_readData(DS1302_READ_MINUTE);//��ȡ��
	time[5] = ds1302_readData(DS1302_READ_SECOND);//��ȡ��
	time[6] = ds1302_readData(DS1302_READ_WEEK);  //��ȡ��		
}

/*DS1302ʱ��ģ���ʼ������*/
void ds1302_init()
{
	RST = 0; //�ر�RST
	CLK = 0; //����ʱ��
	ds1302_writeCom(DS1302_WRITE_PROTECT,0x00); //�ر�д���� �������ܽ���д����
	ds1302_burst_write(DS1302_WRITE_TIME);	//��ʼ��ȫ��ʱ��
	//ds1302_initTime(); //��ʼʱ�䣺2021��10��18�� 19��45��00�� ��һ	
	ds1302_writeCom(DS1302_WRITE_PROTECT,0x80); //����д���� ֻ��ģʽ
		
}

