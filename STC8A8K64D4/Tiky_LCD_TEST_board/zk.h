#ifndef __ZK_H
#define __ZK_H

sbit zk_cs = P1^7;
//sbit zk_di = P1^3;
//sbit zk_do = P1^4;
//sbit zk_clk = P1^5;

void ZK_command(u8 cmd);
void Display_GB2312_String(u16 x,u16 y,u8 zk_num,u8 text[],u16 fc,u16 bc);
void Display_GB2312(u16 x,u16 y,u8 zk_num,u16 fc,u16 bc);
void get_n_u8s_data_from_ROM(u8 AddrHigh,u8 AddrMid,u8 AddrLow,u8 *pBuff,u8 DataLen);
void Display_Asc_String(u16 x,u16 y,u16 zk_num,u8 text[],u16 fc,u16 bc);
void Display_Asc(u16 x,u16 y,u16 zk_num,u16 fc,u16 bc);

#endif