#include "Includes.h"

void delay5us(void)		//5微秒@6.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xE2;			//设置定时初值
	TH0 = 0xFF;			//设置定时初值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	while(TF0==0);	//等待计时器结束
	TR0 = 0;				//停止计时器
}

void delayms(WORD ms)		//1毫秒@6.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	for(;ms>0;ms--)
	{
		TL0 = 0x90;		//设置定时初值
		TH0 = 0xE8;		//设置定时初值
		TF0 = 0;		//清除TF0标志
		TR0 = 1;		//定时器0开始计时
		while(TF0==0);
		TR0 = 0;
	}
}

void Timer10ms(void)		//10毫秒@6.000MHz
{
	AUXR |= 0x40;		//定时器时钟1T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xA0;		//设置定时初始值
	TH1 = 0x15;		//设置定时初始值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
}