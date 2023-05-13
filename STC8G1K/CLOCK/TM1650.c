#include "Includes.h"

u8 code matrix[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x27, // 7
    0x7F, // 8
    0x6F // 9
};

WORD init_dig = 0xFF;

void TM1650_Start(void)
{
	CLK=1;
	DIO=1;
	delay5us();delay5us();
	DIO=0;
	delay5us();delay5us();
}

void TM1650_Stop(void)
{
	 CLK=1;	
	 DIO=0; delay5us();delay5us();
	 DIO=1; delay5us();	delay5us();
}

void TM1650_ACK(void)
{
	// while(DIO);
	CLK=1; delay5us();
//	DIO=1; delay5us();delay5us();
	CLK=0; delay5us();
	
}

bit TM1650_send_data(u8 dat)
{
	u8 i;

	CLK=0;
	for(i=0;i<8;i++)
	{
		DIO = ((dat&0x80) == 0x80);
		CLK=0; delay5us();
		CLK=1; delay5us();
		CLK=0; delay5us();

		dat<<=1;
	}
	return DIO;
}

void TM1650_write_data(u8 add, u8 dat)
{
	TM1650_Start();
	TM1650_send_data(add);
	TM1650_ACK();
	TM1650_send_data(dat);
	TM1650_ACK();
	TM1650_Stop();
}

void TM1650_Initialize()
{
	TM1650_write_data(0x48,0x11);

	while(init_dig>0){
		TM1650_write_data(0x68,~init_dig);
		TM1650_write_data(0x6A,~init_dig);
		TM1650_write_data(0x6C,~init_dig);
		TM1650_write_data(0x6E,~init_dig);
		init_dig <<= 1;
		delayms(50);
	}
}

void TM1650_show_clock(u8* rtc_buf,bit dot)
{
	u8 idata min_l,min_h,hour_l,hour_h;

	min_l = 0x0F&rtc_buf[0];
	min_h = rtc_buf[0]>>4;
	hour_l = 0x0F&rtc_buf[1];
	hour_h = rtc_buf[1]>>4;

	TM1650_write_data(0x68, (hour_h ? matrix[hour_h] : 0x00));
	TM1650_write_data(0x6A, (matrix[hour_l] | (dot?0x80:0x00)));
	TM1650_write_data(0x6C, matrix[min_h]);
	TM1650_write_data(0x6E, matrix[min_l]);
}

void TM1650_show_temp(u8* temp)
{
	u8 idata temp_1;	// ����λ
	u8 idata temp_2;	// �¶�ʮλ
	u8 idata temp_3;	// �¶ȸ�λ
	u8 idata temp_4;	// С��λ

	temp_1 = 0x80&temp[0];
	temp_2 = 0;
	temp_3 = 0x7F&temp[0];

	// ��ʮλ�͸�λ���¶��������������Ҫ����
	while(temp_3 >= 10)
	{
		temp_2++;
		temp_3 -= 10;
	}

	/*--------------------------------------------------------------------*/
	/* --- DS3231��12h�Ĵ�����bit7��bit6������¶�С��λ��bit0��bit5��Ч --- */
	/* --- 12h������ֻ��2bit��Ч���ݣ����Ա�ʾ0.25�Ŀ̶� --------------------*/
	/* --- �����ֻ��һλ����С��λ������ֱ�ӳ�3���Ա�ʾ0��0.3��0.6��0.9 ---- */
	/*--------------------------------------------------------------------*/
	temp_4 = (temp[1]>>6)*3;

	TM1650_write_data(0x68, (temp_1 ? 0x40 : 0x00));
	TM1650_write_data(0x6A, matrix[temp_2]);
	TM1650_write_data(0x6C, matrix[temp_3] | 0x80);
	TM1650_write_data(0x6E, matrix[(temp_4)]);
}