#include "Includes.h"

void delayms(u16 ms)		//1����@30MHz
{
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	for(;ms>0;ms--)
	{
		TL0 = 0xD0;		//���ö�ʱ��ʼֵ
		TH0 = 0x8A;		//���ö�ʱ��ʼֵ
		TF0 = 0;		//���TF0��־
		TR0 = 1;		//��ʱ��0��ʼ��ʱ
		while(TF0==0);
		TR0 = 0;
	}
}