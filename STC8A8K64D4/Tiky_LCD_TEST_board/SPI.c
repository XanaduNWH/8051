#include "Includes.h"

void InitSPI()
{
	P_SW1 = 0x00;			//SS/P1.2, MOSI/P1.3, MISO/P1.4, SCLK/P1.5
//	P_SW1 = 0x04;		//SS_2/P2.2, MOSI_2/P2.3, MISO_2/P2.4, SCLK_2/P2.5
//	P_SW1 = 0x08;		//SS_3/P7.4, MOSI_3/P7.5, MISO_3/P7.6, SCLK_3/P7.7
//	P_SW1 = 0x0c;		//SS_4/P3.5, MOSI_4/P3.4, MISO_4/P3.3, SCLK_4/P3.2
	SPDAT = 0;				//initial SPI data
	SPCTL = SSIG | SPEN | MSTR;		//master mode
	SPSTAT = SPIF | WCOL;					//clear SPI status
}

u8 SPISwap(u8 dat)
{
	SPDAT = dat;								//trigger SPI send
	while (!(SPSTAT & SPIF));		//wait send complete
	SPSTAT = SPIF | WCOL;				//clear SPI status
	return SPDAT;								//return received SPI data
}