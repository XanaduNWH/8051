#ifndef __I2C_H
#define __I2C_H

sbit SDA=P3^3;
sbit SCK=P3^2;

void I2C_Init();
void I2C_Wait();
void I2C_Start();
void I2C_SendData(u8 dat);
void I2C_RecvACK();
u8 I2C_RecvData();
void I2C_SendACK();
void I2C_SendNAK();
void I2C_Stop();

#endif