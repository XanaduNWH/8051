#ifndef __LCD_H
#define __LCD_H

 //����LCD�ĳߴ�
#define LCD_W 480
#define LCD_H 854

#define Bus_16
#define Bit_16
// #define Bit_18
// #define Bit_24

#define  USR_LCM_IF     1			//1: use LCM Interface; 0: use IO mode

//IO����
#define  LCD_DataPortH P2			//��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ
#define  LCD_DataPortL P0			//��8λ���ݿ�	,8λģʽ�µ�8λ���Բ�����,��ȷ��P0���Ѿ�����10K����,����̫С����С4.7K,�Ƽ�10K.
sbit LCD_RS = P4^1;						//����/�����л�
sbit LCD_WR = P4^3;						//д����
sbit LCD_RD = P4^4;						//������
sbit LCD_CS = P7^4;						//Ƭѡ
sbit LCD_REST = P7^5;					//��λ
sbit LCD_BL = P1^0;

//========================================================================
//                              �ⲿ����
//========================================================================

//void LCM_Inilize(LCM_InitTypeDef *LCM);
//void DMA_LCM_Inilize(DMA_LCM_InitTypeDef *DMA);
//u8 NVIC_DMA_LCM_Init(u8 State, u8 Priority, u8 Bus_Priority);
//u8 NVIC_LCM_Init(u8 State, u8 Priority);

void LCM_config(void);
void DMA_config(void);
void LCD_ILI9806G_Init(void);
void LCD_WR_REG(u8 da);
void LCD_WR_DATA(u8 da);
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_WR_DATA16(u16 dat);
void LCD_Clear(u16 color);
#if USR_LCM_IF == 1

void LCD_Writ_Bus(u8 VH,u8 VL);

#endif

/*
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode);
void LCD_ShowString(u16 x,u16 y,const u8 *p);
void LCD_DrawPoint(u16 x,u16 y);
*/

#define WHITE				0xFFFF
#define BLACK				0x0000
#define BLUE				0x001F
#define BRED				0XF81F
#define GRED				0XFFE0
#define GBLUE				0X07FF
#define RED					0xF800
#define MAGENTA			0xF81F
#define GREEN				0x07E0
#define CYAN				0x7FFF
#define YELLOW			0xFFE0
#define BROWN				0XBC40
#define BRRED				0XFC07
#define GRAY				0X8430

#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458

#define LIGHTGREEN     	 0X841F
#define LGRAY 			 0XC618

#define LGRAYBLUE        0XA651
#define LBBLUE           0X2B12

#endif