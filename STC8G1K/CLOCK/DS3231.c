#include "Includes.h"

void Read_Bytes_From_DS3231_RTC(u8 Address, u8* pData, u8 NoOfBytes)
{
	u8 xdata i;
	I2C_Start();
	I2C_SendData(Device_Address_DS3231_EEPROM);
	I2C_RecvACK();
	I2C_SendData(Address);
	I2C_RecvACK();
	I2C_Start();
	I2C_SendData(Device_Address_DS3231_EEPROM + 1);
	I2C_RecvACK();

	pData[0] = I2C_RecvData();
	for(i=1;i<NoOfBytes;i++)
	{
		I2C_SendACK();
		pData[i] = I2C_RecvData();
	}
	I2C_SendNAK();
	I2C_Stop();
}

void Write_Bytes_To_DS3231_RTC(u8 Address,u8* pData,u8 NoOfBytes)
{
	u8 xdata i;
	I2C_Start();
	I2C_SendData(Device_Address_DS3231_EEPROM);
	I2C_RecvACK();
	I2C_SendData(Address);
	I2C_RecvACK();

	for(i=0;i<NoOfBytes;i++)
	{
		I2C_SendData(pData[i]);
		I2C_RecvACK();
	}
	I2C_Stop();
}