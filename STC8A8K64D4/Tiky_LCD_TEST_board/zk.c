#include "Includes.h"

u8 xdata FontBuf[128];

/******************************************************************************
      函数说明：显示汉字
      入口数据：zk_num    1:12*12,  2:15*16,  3:24*24,  4:32*32
                x,y       坐标
                text[]    要显示的汉字
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_GB2312_String(u16 x,u16 y,u8 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 xdata i= 0;
	u8 xdata AddrHigh,AddrMid,AddrLow ; //字高、中、低地址
	u32 xdata FontAddr=0; //字地址
	u32 xdata BaseAdd=0; //字库基地址
	u8 xdata n;// 不同点阵字库的计算变量
	switch(zk_num)
	{
		// n个数d：字间距
		case 16 :	BaseAdd=0x2C9D0;	n=32;		break;	// 16*16
		case 24 :	BaseAdd=0x68190;	n=72;		break;	// 24*24
		case 32 :	BaseAdd=0xEDF00;	n=128;	break;	// 32*32
		default:	BaseAdd=0xEDF00;	n=128;	zk_num=32;	break;	// 16*16
	}
	while(text[i])
	{
		if(((text[i]>=0xA1)&&(text[i]<=0xA9))&&(text[i+1]>=0xA1))
		{
			//国标简体（GB2312）汉字在 字库IC中的地址由以下公式来计算：//
			//Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1))*n+ BaseAdd; 分三部取地址///
			FontAddr = (text[i]- 0xA1)*94;
			FontAddr += (text[i+1]-0xA1);
			FontAddr = (unsigned long)((FontAddr*zk_num)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  //地址的高8位,共24位//
			AddrMid = (FontAddr&0xff00)>>8;      //地址的中8位,共24位//
			AddrLow = FontAddr&0xff;	     //地址的低8位,共24位//
			get_n_u8s_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n );//取一个汉字的数据，存到"FontBuf[]"
			Display_GB2312(x,y,zk_num,fc,bc);//显示一个汉字到LCD上/
		}
		else if(((text[i]>=0xB0) &&(text[i]<=0xF7))&&(text[i+1]>=0xA1))
		{
			//国标简体（GB2312） 字库IC中的地址由以下公式来计算：//
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+846)*n+ BaseAdd; 分三部取地址//
			FontAddr = (text[i]- 0xB0)*94;
			FontAddr += (text[i+1]-0xA1)+846;
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  //地址的高8位,共24位//
			AddrMid = (FontAddr&0xff00)>>8;      //地址的中8位,共24位//
			AddrLow = FontAddr&0xff;	     //地址的低8位,共24位//
			get_n_u8s_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n);//取一个汉字的数据，存到"FontBuf[ ]"
			Display_GB2312(x,y,zk_num,fc,bc);//显示一个汉字到LCD上/
		}
		x+=zk_num; //下一个字坐标
		i+=2;  //下个字符
	}
}

/******************************************************************************
      函数说明：显示汉字
      入口数据：x,y      写入的坐标
                zk_num   1:12*12,  2:15*16,  3:24*24,  4:32*32
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_GB2312(u16 x,u16 y,u8 zk_num,u16 fc,u16 bc)
{
  u8 xdata i,j;
	LCD_Address_Set(x,y,x+zk_num-1,y+zk_num-1);
	for (i=0;i<(zk_num*zk_num/8);i++)
	{
		for(j=0;j<8;j++)
		{
			if(FontBuf[i]&(0x80>>j))
			{
				LCD_WR_DATA16(fc);
			} else {
				LCD_WR_DATA16(bc);
			}
		}
	}
}

/******************************************************************************
      函数说明：显示ASCII码
      入口数据：x,y      写入的坐标
                zk_num   1:5*7   2:5*8   3:6*12,  4:8*16,  5:12*24,  6:16*32
                text[]   要显示的字符串
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_Asc_String(u16 x,u16 y,u16 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 xdata i= 0;
	u8 xdata AddrHigh,AddrMid,AddrLow ; //字高、中、低地址
	u32 xdata FontAddr=0; //字地址
	u32 xdata BaseAdd=0; //字库基地址
	u8 xdata n;// 不同点阵字库的计算变量
	switch(zk_num)
	{
		case 16:  BaseAdd=0x1DD780; n=16; break;	 //  8x16 ASCII
		case 24:  BaseAdd=0x1DFF00; n=48; break;	 //  12x24 ASCII
		case 32:  BaseAdd=0x1E5A50; n=64; break;	 //  16x32 ASCII
		default:	BaseAdd=0x1E5A50; n=64;  zk_num=32; break;
	}
	while(text[i])
	{
		if((text[i] >= 0x20) &&(text[i] <= 0x7E))
		{
			FontAddr = 	text[i]-0x20;
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  /*地址的高8位,共24位*/
			AddrMid = (FontAddr&0xff00)>>8;      /*地址的中8位,共24位*/
			AddrLow = FontAddr&0xff;	     /*地址的低8位,共24位*/
			get_n_u8s_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n);/*取一个汉字的数据，存到"FontBuf[]"*/
			Display_Asc(x,y,zk_num,fc,bc);/*显示一个ascii到LCD上 */
		}
		i++;  //下个数据
		x+=zk_num/2;//下一个字坐标
	}
}

/******************************************************************************
      函数说明：显示ASCII码
      入口数据：x,y      写入的坐标
                zk_num   1:5*7   2:5*8   3:6*12,  4:8*16,  5:12*24,  6:16*32
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_Asc(u16 x,u16 y,u16 zk_num,u16 fc,u16 bc)
{
  u8 xdata i,j;
	LCD_Address_Set(x,y,x+(zk_num/2)-1,y+zk_num-1);
	for (i=0;i<(zk_num/2*zk_num/8);i++)
	{
		for(j=0;j<8;j++)
		{
			if(FontBuf[i]&(0x80>>j))
			{
				LCD_WR_DATA16(fc);
			} else {
				LCD_WR_DATA16(bc);
			}
		}
	}
}

/******************************************************************************
      函数说明：读取N个数据
      入口数据：AddrHigh  写地址高字节
                AddrMid   写地址中字节
                AddrLow   写地址低字节
                *pBuff    读取的数据
                DataLen   读取数据的长度
      返回值：  无
******************************************************************************/
void get_n_u8s_data_from_ROM(u8 AddrHigh,u8 AddrMid,u8 AddrLow,u8 *pBuff,u8 DataLen)
{
 	u8 xdata i;
	zk_cs = 0;
	SPISwap(0x03);//写指令
	SPISwap(AddrHigh);//写地址高字节
	SPISwap(AddrMid);//写地址中字节
	SPISwap(AddrLow);//写地址低字节
	for(i=0;i<DataLen;i++)
	{
		*(pBuff+i) =SPISwap(0x00);//读一个字节数据
	}

	zk_cs = 1;
}

