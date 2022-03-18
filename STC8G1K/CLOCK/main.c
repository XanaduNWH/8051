#include "Includes.h"

#define ENI2C 0x80
#define MSSL 0x40
#define MSSPEED 0x02
#define ET2         0x04

u8 xdata cnt=0,num=0,rtc_buf[2],rtc_tmp[2],rtc_ctrl[2],PageIndex=0;
char xdata temp[2];
bit idata dot,time_10ms_ok,wakeup,lcdon = 1;
extern u8 code matrix[10];

void tm1_isr() interrupt 3		// 定时器10ms中断服务
{
	time_10ms_ok = 1;
	cnt++;
	switch(PageIndex)
	{
		case 0:
			Read_Bytes_From_DS3231_RTC(0x01, &rtc_buf, 2);
			break;
		case 1:
			Read_Bytes_From_DS3231_RTC(0x11, &temp, 2);
			break;
		default:
			break;
	}
}

void exint4() interrupt 16
{
	INTCLKO &= 0xBF;           //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
	wakeup=1;
	INTCLKO |= 0x40;           //然后再开中断即可
}

void main()
{
	u8 xdata key,key_buf=0,SettingIndex=0,dig[4];

	P3M0=0x00;
	P3M1=0x00;
	P5M0=0x00;
	P5M1=0x00;

//	P5PU=0x30;

	P_SW2 = 0x80;
	P3PU = 0x0C;

	delayms(100);

	I2C_Init();
	TM1650_Initialize();

/*
	rtc_tmp[0] = 0x01;
	rtc_tmp[1] = 0x16;
	Write_Bytes_To_DS3231_RTC(0x01, rtc_tmp, 2);
*/

	INTCLKO |= 0x40;		//(EX4 = 1)使能INT4下降沿中断
	ET1 = 1;		//使能定时器1中断
	EA = 1;
	Timer10ms();

	while(1)
	{
//		PCON = 0x02;
//		_nop_();
//		_nop_();
		if (time_10ms_ok){
			time_10ms_ok =0;
			key = key_read();
		}

		if(key){
			key_buf=key;
		}

		if(PageIndex==0)					// 时间页面
		{
			if(SettingIndex == 0)		// 显示页面
			{
				if(key_buf==L_key)
				{
					SettingIndex = 1;
				}
				if(key_buf==D_key)
				{
					PageIndex++;
				}
				if(key_buf==S_key)
				{
					lcdon = !lcdon;		// 关显示
					TM1650_write_data(0x48,(0x10 | lcdon));
					//PCON = 0x02;
				}
				key_buf = 0;
				if(cnt>50)
				{
					dot=!dot;					// 秒点
					TM1650_show_clock(rtc_buf,dot);
					dig[3] = 0x0F&rtc_buf[0];
					dig[2] = rtc_buf[0]>>4;
					dig[1] = 0x0F&rtc_buf[1];
					dig[0] = rtc_buf[1]>>4;
					cnt=0;
				}
			} else {				// 设置页面
				if(key_buf==L_key)
				{
					rtc_tmp[2] = (dig[0]<<4) + dig[1];
					rtc_tmp[1] = (dig[2]<<4) + dig[3];
					if(((rtc_tmp[0]>>4) > 5) || ((rtc_tmp[0]&0x0F) > 9))
						rtc_tmp[0] = 0x00;
					Write_Bytes_To_DS3231_RTC(0x00, rtc_tmp, 3);
					SettingIndex = 0;
					key_buf = 0;
				}
				if(key_buf==D_key) {
					SettingIndex++;
					if(SettingIndex>4){
						SettingIndex=1;
					}
					key_buf = 0;
				}
				if(key_buf==S_key) {
					if(SettingIndex == 1){
						dig[0]++;
						if(dig[0] > 2) {
							dig[0] = 0;
						}
					}
					if(SettingIndex == 2) {
						dig[1]++;
						if((dig[0] == 2) && (dig[1] > 3)) {
							dig[1] = 0;
						}
						if(dig[1] > 9) {
							dig[1] = 0;
						}
					}
					if(SettingIndex == 3){
						dig[2]++;
						if(dig[2] > 5) {
							dig[2] = 0;
						}
					}
					if(SettingIndex == 4){
						dig[3]++;
						if(dig[3] > 9) {
							dig[3] = 0;
						}
					}
					key_buf = 0;
				}

				TM1650_write_data(0x68, (((SettingIndex == 1) && (cnt>50))?0x00:matrix[dig[0]]));
				TM1650_write_data(0x6A, (((SettingIndex == 2) && (cnt>50))?0x00:matrix[dig[1]]));
				TM1650_write_data(0x6C, (((SettingIndex == 3) && (cnt>50))?0x00:matrix[dig[2]]));
				TM1650_write_data(0x6E, (((SettingIndex == 4) && (cnt>50))?0x00:matrix[dig[3]]));

				if(cnt>100) cnt=0;
			}
		}

		if(PageIndex==1)  // 温度页面
		{
			if(key_buf==D_key)
			{
				PageIndex = 0;
				key_buf = 0;
			}
			
			if(cnt>50)
			{
				TM1650_show_temp(temp);
				dig[3] = 0x0F&rtc_buf[0];
				dig[2] = rtc_buf[0]>>4;
				dig[1] = 0x0F&rtc_buf[1];
				dig[0] = rtc_buf[1]>>4;
				cnt=0;
			}
		}

		delayms(25);
	}
}