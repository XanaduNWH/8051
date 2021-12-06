#include "Includes.h"


void I2C_Wait()
{
	while (!(I2CMSST & 0x40));
	I2CMSST &= ~0x40;
}

void I2C_Init()
{
	I2CCFG = 0xe0;			//ʹ��I2C����ģʽ
	I2CMSST = 0x00;
}

void I2C_Start()
{
	I2CMSCR = 0x01;			//����START����
	I2C_Wait();
}

void I2C_SendData(char dat)
{
	I2CTXD = dat;				//д���ݵ����ݻ�����
	I2CMSCR = 0x02;			//����SEND����
	I2C_Wait();
}

void I2C_RecvACK()
{
	I2CMSCR = 0x03;			//���Ͷ�ACK����
	I2C_Wait();
}

u8 I2C_RecvData()
{
	I2CMSCR = 0x04;			//����RECV����
	I2C_Wait();
	return I2CRXD;
}

void I2C_SendACK()
{
	I2CMSST = 0x00;			//����ACK�ź�
	I2CMSCR = 0x05;			//����ACK����
	I2C_Wait();
}

void I2C_SendNAK()
{
	I2CMSST = 0x01;			//����NAK�ź�
	I2CMSCR = 0x05;			//����ACK����
	I2C_Wait();
}

void I2C_Stop()
{
	I2CMSCR = 0x06;			//����STOP����
	I2C_Wait();
}