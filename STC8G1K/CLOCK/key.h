#ifndef __KEY_H
#define __KEY_H

sbit KEY = P3^1;

#define N_key    0             //ÎŞ¼ü
#define S_key    1             //µ¥¼ü
#define D_key    2             //Ë«¼ü
#define L_key    3             //³¤¼ü

#define key_state_0 0
#define key_state_1 1
#define key_state_2 2
#define key_state_3 3

u8 key_driver(void);
u8 key_read(void);

#endif