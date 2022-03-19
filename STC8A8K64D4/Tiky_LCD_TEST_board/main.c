#include "Includes.h"

#define CYCLE			0x1000

void PWM_Isr() interrupt 22
{
	static bit dir = 1;
	static int val = 0;

	if (PWMCFG & 0x08)
	{
		PWMCFG &= ~0x08;				//清中断标志
		if (dir)
		{
			val++;
			if (val >= CYCLE) dir = 0;
		}
		else
		{
			val--;
			if (val <= 1) dir = 1;
		}

		_push_(P_SW2);
		P_SW2 |= 0x80;
		PWM1T2 = val;
		_pop_(P_SW2);
	}
}

void main()
{
	u16 xdata Color = BRRED;

	P0M0 = 0x00;
	P0M1 = 0x00;
	P1M0 = 0x01;
	P1M1 = 0x00;
	P2M0 = 0x00;
	P2M1 = 0x00;
	P3M0 = 0x00;
	P3M1 = 0x00;
	P4M0 = 0x00;
	P4M1 = 0x00;
	P7M0 = 0x00;
	P7M1 = 0x00;

	P0PU = 0xFF;
	P2PU = 0xFF;

	P0SR = 0x00;
	P2SR = 0x00;
	P4SR = 0x1A;

// PWM呼吸灯@P11

	PWMSET = 0x01;
	P_SW2 = 0x80;
	PWM1CR = 0x08;				//PWM1_2/P1.1
	PWMCKS = 0x00;				// PWM时钟为系统时钟
	PWMC = CYCLE;					//设置PWM周期为
	PWM1T1= 0x0000;
	PWM1T2= 0x0001;
	PWM1CR= 0x88;					//使能PWM1输出
	P_SW2 = 0x00;
	PWMCFG = 0x05;				//启动PWM模块
	EA = 1;

//	P7 = 0x00;
//	P34 = 1;
//	LCD_BL = 1;

	InitSPI();
	LCM_config();
	DMA_config();
	EA = 1;
 	LCD_ILI9806G_Init();
//	LCD_ST7789_Init();

	while (1)
	{
		LCD_Clear(Color);
		// delayms(500);
		Display_GB2312_String(0,0,32, "中文测试",~Color,Color);
		Display_Asc_String(0,48,32, "ASCII_16x32 string", ~Color,Color);
		Color = ~Color;
		delayms(500);
	}
}

