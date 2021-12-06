#include "Includes.h"


void I2C_Wait()
{
	while (!(I2CMSST & 0x40));
	I2CMSST &= ~0x40;
}

void I2C_Init()
{
	I2CCFG = 0xe0;			//使能I2C主机模式
	I2CMSST = 0x00;
}

void I2C_Start()
{
	I2CMSCR = 0x01;			//发送START命令
	I2C_Wait();
}

void I2C_SendData(char dat)
{
	I2CTXD = dat;				//写数据到数据缓冲区
	I2CMSCR = 0x02;			//发送SEND命令
	I2C_Wait();
}

void I2C_RecvACK()
{
	I2CMSCR = 0x03;			//发送读ACK命令
	I2C_Wait();
}

u8 I2C_RecvData()
{
	I2CMSCR = 0x04;			//发送RECV命令
	I2C_Wait();
	return I2CRXD;
}

void I2C_SendACK()
{
	I2CMSST = 0x00;			//设置ACK信号
	I2CMSCR = 0x05;			//发送ACK命令
	I2C_Wait();
}

void I2C_SendNAK()
{
	I2CMSST = 0x01;			//设置NAK信号
	I2CMSCR = 0x05;			//发送ACK命令
	I2C_Wait();
}

void I2C_Stop()
{
	I2CMSCR = 0x06;			//发送STOP命令
	I2C_Wait();
}