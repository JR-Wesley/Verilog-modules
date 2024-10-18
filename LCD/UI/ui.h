
#ifndef SRC_LCD_UI_H_
#define SRC_LCD_UI_H_

#include "lcd.h"
#include "xparameters.h"
#include "../TOUCH/touch.h"
#include "../DELAY/delay.h"
#include "../FUNC/func.h"

#define l 160
#define h 100
#define s 60
#define x_20ms	0x00
#define x_2us	0x01
#define x_100n	0x02
#define y_1v	0x03
#define y_01v	0x04
#define y_2mv	0x05
#define sigle 	0x06
#define store	0x07
#define square	0x08
#define display	0x09

int TouchInBar4(u16 x1, u16 y1, u16 x2, u16 y2);
int TouchInBar(u16 x1, u16 y1, u16 x2, u16 y2);
void config();
void graph(int* data);
void uidesign();
void touchdetect(char *expression);
void touch(char *expression );

 u32 fs_cnt_n,fs_cnt_p,fx_cnt;
 u32 fs_cnt,fx_freq,duty_cycle,period;
 u32 v_temp;
 u32 x_mode,y_mode;

#endif /* SRC_LCD_UI_H_ */
