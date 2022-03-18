sbit CLK=P5^4;
sbit DIO=P5^5;

void TM1650_Start(void);
void TM1650_Stop(void);
void TM1650_ACK(void);
bit TM1650_send_data(u8 dat);
void TM1650_write_data(u8 add, u8 dat);
void TM1650_Initialize();
void TM1650_show_clock(u8* rtc_buf,bit dot);
void TM1650_show_temp(u8* temp);