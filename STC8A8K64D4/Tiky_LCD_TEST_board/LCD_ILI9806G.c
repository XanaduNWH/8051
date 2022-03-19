#include "Includes.h"

u32 index;
u16 xdata Color[256];

void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(x1>>8);
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2>>8);
	LCD_WR_DATA(x2);
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(y1>>8);
	LCD_WR_DATA(y1);
	LCD_WR_DATA(y2>>8);
	LCD_WR_DATA(y2);
	LCD_WR_REG(0x2C);
}

void LCD_Clear(u16 color)
{
#if USR_LCM_IF == 1
	u16 i;

	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
	for(i=0;i<256;i++)
	{
		Color[i] = color;
	}
	index = 1602;
	LCD_CS=0;
	DMA_LCM_CR = 0xa0;	//Write dat
	while(index);
#else
	u16 xdata x,y;
	LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
	for(x=0;x<LCD_W;x++)
	{
		for (y=0;y<LCD_H;y++)
		{
			LCD_WR_DATA16(Color);
		}
	}
#endif
}


void LCD_ILI9806G_Init(void)
{
	LCD_WR=1;
	LCD_REST=0;
	delayms(100);
	LCD_REST=1;
	delayms(100);
	LCD_BL = 1;
	LCD_WR_REG(0xFF); // EXTC Command Set enable register
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x98);
	LCD_WR_DATA(0x06);

	LCD_WR_REG(0xBA); // SPI Interface Setting
	LCD_WR_DATA(0xE0);

	LCD_WR_REG(0xBC); // GIP 1
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x63);
	LCD_WR_DATA(0x69);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x11);
	LCD_WR_DATA(0x70);
	LCD_WR_DATA(0x73);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0xFF);
	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x05);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xEE);
	LCD_WR_DATA(0xE2);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xC1);

	LCD_WR_REG(0xBD); // GIP 2
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x23);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x67);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x23);
	LCD_WR_DATA(0x45);
	LCD_WR_DATA(0x67);

	LCD_WR_REG(0xBE); // GIP 3
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x22);
	LCD_WR_DATA(0x27);
	LCD_WR_DATA(0x6A);
	LCD_WR_DATA(0xBC);
	LCD_WR_DATA(0xD8);
	LCD_WR_DATA(0x92);
	LCD_WR_DATA(0x22);
	LCD_WR_DATA(0x22);

	LCD_WR_REG(0xC7); // Vcom
	LCD_WR_DATA(0x1E);

	LCD_WR_REG(0xED); // EN_volt_reg
	LCD_WR_DATA(0x7F);
	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xC0); // Power Control 1
	LCD_WR_DATA(0xE3);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xFC);
	LCD_WR_DATA(0x08);

	LCD_WR_REG(0xDF); // Engineering Setting
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x02);

	LCD_WR_REG(0xF3); // DVDD Voltage Setting
	LCD_WR_DATA(0x74);

	LCD_WR_REG(0xB4); // Display Inversion Control
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);


	LCD_WR_REG(0xB1); // Frame Rate
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x10);
	LCD_WR_DATA(0x14);

	LCD_WR_REG(0xF1); // Panel Timing Control
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0x07);

	LCD_WR_REG(0xF2); //Panel Timing Control
	LCD_WR_DATA(0x40);
	LCD_WR_DATA(0xD2);
	LCD_WR_DATA(0x50);
	LCD_WR_DATA(0x28);

	LCD_WR_REG(0xC1); // Power Control 2
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0X85);
	LCD_WR_DATA(0x85);
	LCD_WR_DATA(0x20);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0x00); //P1
	LCD_WR_DATA(0x0C); //P2
	LCD_WR_DATA(0x15); //P3
	LCD_WR_DATA(0x0D); //P4
	LCD_WR_DATA(0x0F); //P5
	LCD_WR_DATA(0x0C); //P6
	LCD_WR_DATA(0x07); //P7
	LCD_WR_DATA(0x05); //P8
	LCD_WR_DATA(0x07); //P9
	LCD_WR_DATA(0x0B); //P10
	LCD_WR_DATA(0x10); //P11
	LCD_WR_DATA(0x10); //P12
	LCD_WR_DATA(0x0D); //P13
	LCD_WR_DATA(0x17); //P14
	LCD_WR_DATA(0x0F); //P15
	LCD_WR_DATA(0x00); //P16

	LCD_WR_REG(0xE1);
	LCD_WR_DATA(0x00); //P1
	LCD_WR_DATA(0x0D); //P2
	LCD_WR_DATA(0x15); //P3
	LCD_WR_DATA(0x0E); //P4
	LCD_WR_DATA(0x10); //P5
	LCD_WR_DATA(0x0D); //P6
	LCD_WR_DATA(0x08); //P7
	LCD_WR_DATA(0x06); //P8
	LCD_WR_DATA(0x07); //P9
	LCD_WR_DATA(0x0C); //P10
	LCD_WR_DATA(0x11); //P11
	LCD_WR_DATA(0x11); //P12
	LCD_WR_DATA(0x0E); //P13
	LCD_WR_DATA(0x17); //P14
	LCD_WR_DATA(0x0F); //P15
	LCD_WR_DATA(0x00); //P16

	LCD_WR_REG(0x35); //Tearing Effect ON
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0xF7);
	LCD_WR_DATA(0x81); // 854 x 480

	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x55);

	LCD_WR_REG(0x53);
	LCD_WR_DATA(0x24);
	LCD_WR_REG(0xC8);
	LCD_WR_DATA(0x00);

	LCD_WR_REG(0x11); //Exit Sleep
	delayms(200);
	LCD_WR_REG(0x29); // Display On
}

void LCD_WR_DATA16(u16 dat)
{
#if USR_LCM_IF == 1

	LCMIFDATH = (dat>>8)&0xFF;
	LCMIFDATL = dat&0xFF;
	LCD_CS=0;
	LCMIFCR = 0x85;		//Enable interface, write data out
	_nop_();
	LCD_CS=1;

#else

	LCD_RS=1;
	LCD_Writ_Bus(dat>>8,dat);

#endif
}


void LCD_WR_REG(u8 da)
{
#if USR_LCM_IF == 1

	LCMIFDATH = 0x00;
	LCMIFDATL = da;
	LCD_CS=0;
	LCMIFCR = 0x84;		//Enable interface, write command out
	_nop_();
	LCD_CS=1;

#else

	LCD_RS=0;
	LCD_Writ_Bus(0x00,da);

#endif
}

void LCD_WR_DATA(u8 da)
{
#if USR_LCM_IF == 1

	LCMIFDATH = 0x00;
	LCMIFDATL = da;
	LCD_CS=0;
	LCMIFCR = 0x85;		//Enable interface, write data out
	_nop_();
	LCD_CS=1;

#else

	LCD_RS=1;
	LCD_Writ_Bus(0x00,da);

#endif
}

#if USR_LCM_IF == 0

void LCD_Writ_Bus(u8 VH,u8 VL)
{
	LCD_CS = 0;
	LCD_RD = 1;
	LCD_DataPortH=VH;
	LCD_DataPortL=VL;
	LCD_WR = 0;
	LCD_WR = 1;
	LCD_CS = 1;
}

#endif

/******************** LCM ≈‰÷√ ********************/
void LCM_config(void)
{
	P_SW2 = 0x80;
	LCMIFCFG = 0x02;	//bit7 1:Enable Interrupt, bit1 1:16bit mode; bit0 0:8080,1:6800
	LCMIFCFG2 = 0x09;		//RS:P41,RD:P44,WR:P43; Setup Time=2,HOLD Time=1
	LCMIFSTA = 0x00;
}

/******************** DMA ≈‰÷√ ********************/
void DMA_config(void)
{
	P_SW2 = 0x80;
	DMA_LCM_AMT = 0xFF;		//Exe 256(n+1) bytes
	DMA_LCM_TXA = &Color;
//	DMA_LCM_RXA = &Buffer;
	DMA_LCM_STA = 0x00;
	DMA_LCM_CFG = 0x82;
	DMA_LCM_CR = 0x80;
}

/*****************************************************************************
 * @name       :void LCM_Interrupt(void)
 * @date       :2018-11-13 
 * @function   :None
 * @parameters :None
 * @retvalue   :
******************************************************************************/ 
void LCMIF_DMA_Interrupt(void) interrupt 13
{
//	LCMIFSTA = 0x00;
//	LCD_CS=1;

	DMA_LCM_STA = 0;
	index--;
	if(index == 0)
	{
		DMA_LCM_CR = 0;
		LCD_CS=1;
//		P40 = 1;
	}
	else
	{
		DMA_LCM_CR = 0xa0;	//Write dat
	}
}