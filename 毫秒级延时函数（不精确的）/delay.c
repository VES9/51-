/*
*毫秒级延时函数模块
*/
#include <REGX51.H>
typedef unsigned char uchar;
typedef unsigned int uint;
void delay(uint n)
{
	uint i=0;
	uint j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}
}

