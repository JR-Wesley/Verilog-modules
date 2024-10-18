#ifndef _AD9910_H_
#define _AD9910_H_
#include "xparameters.h"
#include "xgpiops.h"

#define SCLK		54 //M19
#define SDIO		55 //N17
#define IO_UD_CLK	56 //L20
#define CS			57 //M20
#define MA_RST		58 //B20
#define PF0	        59 //H16
#define PF1	        60 //L16
#define PF2	        61 //L17
#define DRCTRL      60 //M17
#define DRHOLD      61 //M18

XGpioPs gpiops_inst;
XGpioPs_Config* gpiops_cfg_ptr;
#define SCLK_Set	XGpioPs_WritePin(&gpiops_inst,SCLK,1)
#define SCLK_Clr	XGpioPs_WritePin(&gpiops_inst,SCLK,0)
#define SDIO_Set	XGpioPs_WritePin(&gpiops_inst,SDIO,1)	
#define SDIO_Clr	XGpioPs_WritePin(&gpiops_inst,SDIO,0)
#define IO_UD_Set	XGpioPs_WritePin(&gpiops_inst,IO_UD_CLK,1)
#define IO_UD_Clr	XGpioPs_WritePin(&gpiops_inst,IO_UD_CLK,0)
#define CS_Set	    XGpioPs_WritePin(&gpiops_inst,CS,1)
#define CS_Clr  	XGpioPs_WritePin(&gpiops_inst,CS,0)
#define MA_RST_Set	XGpioPs_WritePin(&gpiops_inst,MA_RST,1)
#define MA_RST_Clr	XGpioPs_WritePin(&gpiops_inst,MA_RST,0)
#define PF0_Clr		XGpioPs_WritePin(&gpiops_inst,PF0,0)
#define PF1_Clr		XGpioPs_WritePin(&gpiops_inst,PF1,0)
#define PF2_Clr		XGpioPs_WritePin(&gpiops_inst,PF2,0)
#define DRC_Clr		XGpioPs_WritePin(&gpiops_inst,DRCTRL,0)
#define DRH_Clr		XGpioPs_WritePin(&gpiops_inst,DRHOLD,0)

// AD9910 register
#define CFR1		0x00
#define CFR2		0x01
#define CFR3		0x02
#define PROFILE0	0x0e

void GPIO_AD9910_Config(void);			// AD9910 IO
void AD9910_Init(void);					// AD9910
void AD9910_WR_Byte(u8 Adata);			// byte
void Freq_convert(long Freq);			//
void Amplitude_convert(u32 amplitude);		//AD9910
void AD9910_SetSingle(u32 Freq,u32 amplitude);	//AD9910

#endif

