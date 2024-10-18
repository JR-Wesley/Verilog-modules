#include "ad9910.h"
#include "sleep.h"

const u8 cfr1[] = { 0x00,0x40,0x00,0x00 };       //cfr1
const u8 cfr2[] = { 0x01,0x00,0x00,0x00 };       //cfr2
const u8 cfr3[] = { 0x05,0x0F,0x41,0x32 };       //cfr3  40M VC0=101   ICP=001;
u8 profile0[] = { 0x3f,0xff,0x00,0x00,0x25,0x09,0x7b,0x42 };
//profile1 0x25,0x09,0x7b,0x42
//01-amplitude 23-phase 4567-frequency

void GPIO_AD9910_Config()
{
	gpiops_cfg_ptr = XGpioPs_LookupConfig(XPAR_XDMAPS_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&gpiops_inst, gpiops_cfg_ptr, gpiops_cfg_ptr->BaseAddr);

	XGpioPs_SetDirectionPin(&gpiops_inst, SCLK, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, SDIO, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, IO_UD_CLK, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, CS, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, MA_RST, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, PF0, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, PF1, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, PF2, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, DRCTRL, 1);
	XGpioPs_SetDirectionPin(&gpiops_inst, DRHOLD, 1);

	XGpioPs_SetOutputEnablePin(&gpiops_inst, SCLK, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, SDIO, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, IO_UD_CLK, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, CS, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, MA_RST, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, PF0, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, PF1, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, PF2, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, DRCTRL, 1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst, DRHOLD, 1);
}

void AD9910_Init(void)
{
	u8 i;
	GPIO_AD9910_Config();
	PF0_Clr;
	PF1_Clr;
	PF2_Clr;
	SCLK_Clr;
	IO_UD_Clr;
	SDIO_Clr;
	DRC_Clr;
	DRH_Clr;
	CS_Clr;

	MA_RST_Set;
	usleep(1000);
	MA_RST_Clr;

	AD9910_WR_Byte(CFR1);
	for (i = 0; i < 4; i++)
		AD9910_WR_Byte(cfr1[i]);
	IO_UD_Set;
	IO_UD_Clr;

	AD9910_WR_Byte(CFR2);
	for (i = 0; i < 4; i++)
		AD9910_WR_Byte(cfr2[i]);
	IO_UD_Set;
	IO_UD_Clr;

	AD9910_WR_Byte(CFR3);
	for (i = 0; i < 4; i++)
		AD9910_WR_Byte(cfr3[i]);
	IO_UD_Set;
	IO_UD_Clr;
}

void AD9910_WR_Byte(u8 Adata)
{
	u8 i;
	u8 sbt=0x80;
	SCLK_Clr;
	for (i=0;i<8;i++)
	{
		if((Adata & sbt)==0) SDIO_Clr;
		else SDIO_Set;
	    SCLK_Set;
		sbt=sbt>>1;
		SCLK_Clr;
	}
}

void Freq_convert(long Freq)
{
	u32 Temp;
	Temp = (u32)Freq * 4.294967296;	   // 4.294967296=(2^32)/1000_000_000 sclk:1GHz max:429Mhz
	profile0[7] = (u8)Temp;
	profile0[6] = (u8)(Temp >> 8);
	profile0[5] = (u8)(Temp >> 16);
	profile0[4] = (u8)(Temp >> 24);
}

// max 576 am(unit mv)
void Amplitude_convert(u32 amplitude)
{
	u16 Temp = amplitude * 16383/576;
	profile0[1] = Temp;
	profile0[0] = Temp>>8;
}

void AD9910_SetSingle(u32 Freq,u32 amplitude)
{
	u8 count;
	Amplitude_convert(amplitude);
	Freq_convert(Freq);

	AD9910_WR_Byte(PROFILE0);
	for (count = 0; count < 8; count++)
		AD9910_WR_Byte(profile0[count]);
	IO_UD_Set;
	IO_UD_Clr;
}
