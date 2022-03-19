#include "Includes.h"

u8 xdata FontBuf[128];

/******************************************************************************
      ����˵������ʾ����
      ������ݣ�zk_num    1:12*12,  2:15*16,  3:24*24,  4:32*32
                x,y       ����
                text[]    Ҫ��ʾ�ĺ���
                fc ������ɫ
                bc ������ɫ
      ����ֵ��  ��
******************************************************************************/
void Display_GB2312_String(u16 x,u16 y,u8 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 xdata i= 0;
	u8 xdata AddrHigh,AddrMid,AddrLow ; //�ָߡ��С��͵�ַ
	u32 xdata FontAddr=0; //�ֵ�ַ
	u32 xdata BaseAdd=0; //�ֿ����ַ
	u8 xdata n;// ��ͬ�����ֿ�ļ������
	switch(zk_num)
	{
		// n����d���ּ��
		case 16 :	BaseAdd=0x2C9D0;	n=32;		break;	// 16*16
		case 24 :	BaseAdd=0x68190;	n=72;		break;	// 24*24
		case 32 :	BaseAdd=0xEDF00;	n=128;	break;	// 32*32
		default:	BaseAdd=0xEDF00;	n=128;	zk_num=32;	break;	// 16*16
	}
	while(text[i])
	{
		if(((text[i]>=0xA1)&&(text[i]<=0xA9))&&(text[i+1]>=0xA1))
		{
			//������壨GB2312�������� �ֿ�IC�еĵ�ַ�����¹�ʽ�����㣺//
			//Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1))*n+ BaseAdd; ������ȡ��ַ///
			FontAddr = (text[i]- 0xA1)*94;
			FontAddr += (text[i+1]-0xA1);
			FontAddr = (unsigned long)((FontAddr*zk_num)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  //��ַ�ĸ�8λ,��24λ//
			AddrMid = (FontAddr&0xff00)>>8;      //��ַ����8λ,��24λ//
			AddrLow = FontAddr&0xff;	     //��ַ�ĵ�8λ,��24λ//
			get_n_u8s_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n );//ȡһ�����ֵ����ݣ��浽"FontBuf[]"
			Display_GB2312(x,y,zk_num,fc,bc);//��ʾһ�����ֵ�LCD��/
		}
		else if(((text[i]>=0xB0) &&(text[i]<=0xF7))&&(text[i+1]>=0xA1))
		{
			//������壨GB2312�� �ֿ�IC�еĵ�ַ�����¹�ʽ�����㣺//
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+846)*n+ BaseAdd; ������ȡ��ַ//
			FontAddr = (text[i]- 0xB0)*94;
			FontAddr += (text[i+1]-0xA1)+846;
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  //��ַ�ĸ�8λ,��24λ//
			AddrMid = (FontAddr&0xff00)>>8;      //��ַ����8λ,��24λ//
			AddrLow = FontAddr&0xff;	     //��ַ�ĵ�8λ,��24λ//
			get_n_u8s_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n);//ȡһ�����ֵ����ݣ��浽"FontBuf[ ]"
			Display_GB2312(x,y,zk_num,fc,bc);//��ʾһ�����ֵ�LCD��/
		}
		x+=zk_num; //��һ��������
		i+=2;  //�¸��ַ�
	}
}

/******************************************************************************
      ����˵������ʾ����
      ������ݣ�x,y      д�������
                zk_num   1:12*12,  2:15*16,  3:24*24,  4:32*32
                fc ������ɫ
                bc ������ɫ
      ����ֵ��  ��
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
      ����˵������ʾASCII��
      ������ݣ�x,y      д�������
                zk_num   1:5*7   2:5*8   3:6*12,  4:8*16,  5:12*24,  6:16*32
                text[]   Ҫ��ʾ���ַ���
                fc ������ɫ
                bc ������ɫ
      ����ֵ��  ��
******************************************************************************/
void Display_Asc_String(u16 x,u16 y,u16 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 xdata i= 0;
	u8 xdata AddrHigh,AddrMid,AddrLow ; //�ָߡ��С��͵�ַ
	u32 xdata FontAddr=0; //�ֵ�ַ
	u32 xdata BaseAdd=0; //�ֿ����ַ
	u8 xdata n;// ��ͬ�����ֿ�ļ������
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

			AddrHigh = (FontAddr&0xff0000)>>16;  /*��ַ�ĸ�8λ,��24λ*/
			AddrMid = (FontAddr&0xff00)>>8;      /*��ַ����8λ,��24λ*/
			AddrLow = FontAddr&0xff;	     /*��ַ�ĵ�8λ,��24λ*/
			get_n_u8s_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n);/*ȡһ�����ֵ����ݣ��浽"FontBuf[]"*/
			Display_Asc(x,y,zk_num,fc,bc);/*��ʾһ��ascii��LCD�� */
		}
		i++;  //�¸�����
		x+=zk_num/2;//��һ��������
	}
}

/******************************************************************************
      ����˵������ʾASCII��
      ������ݣ�x,y      д�������
                zk_num   1:5*7   2:5*8   3:6*12,  4:8*16,  5:12*24,  6:16*32
                fc ������ɫ
                bc ������ɫ
      ����ֵ��  ��
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
      ����˵������ȡN������
      ������ݣ�AddrHigh  д��ַ���ֽ�
                AddrMid   д��ַ���ֽ�
                AddrLow   д��ַ���ֽ�
                *pBuff    ��ȡ������
                DataLen   ��ȡ���ݵĳ���
      ����ֵ��  ��
******************************************************************************/
void get_n_u8s_data_from_ROM(u8 AddrHigh,u8 AddrMid,u8 AddrLow,u8 *pBuff,u8 DataLen)
{
 	u8 xdata i;
	zk_cs = 0;
	SPISwap(0x03);//дָ��
	SPISwap(AddrHigh);//д��ַ���ֽ�
	SPISwap(AddrMid);//д��ַ���ֽ�
	SPISwap(AddrLow);//д��ַ���ֽ�
	for(i=0;i<DataLen;i++)
	{
		*(pBuff+i) =SPISwap(0x00);//��һ���ֽ�����
	}

	zk_cs = 1;
}

