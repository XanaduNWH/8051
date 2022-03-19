#include "Includes.h"

void delayms(u16 ms)		//1毫秒@35MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	for(;ms>0;ms--)
	{
		TL0 = 0x48;		//设置定时初始值
		TH0 = 0x77;		//设置定时初始值
		TF0 = 0;		//清除TF0标志
		TR0 = 1;		//定时器0开始计时
		while(TF0==0);
		TR0 = 0;
	}
}