#ifndef __SPI_H
#define __SPI_H

#define SSIG 0x80
#define SPEN 0x40
#define MSTR 0x10

#define SPIF 0x80
#define WCOL 0x40

void InitSPI();
u8 SPISwap(u8 dat);         //swap SPI data between master and slave

#endif