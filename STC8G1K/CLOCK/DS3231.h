#ifndef __DS3231_H
#define __DS3231_H

#define Device_Address_DS3231_EEPROM	0xD0

void Write_Bytes_To_DS3231_RTC(u8 Address,u8* pData,u8 NoOfBytes);
void Read_Bytes_From_DS3231_RTC(u8 Address,u8* pData,u8 NoOfBytes);

#endif