
#ifndef ADF4351_ADF4351_H_
#define ADF4351_ADF4351_H_
#include "xparameters.h"
#include "xgpiops.h"

#define CLK		54//EMIO0
#define LE		55//EMIO1
#define DATA	56//EMIO2
#define MUX		57//EMIO3
#define LD		58//EMIO4

#define CLK_1	XGpioPs_WritePin(&gpiops_inst,CLK,1)
#define CLK_0	XGpioPs_WritePin(&gpiops_inst,CLK,0)
#define LE_1	XGpioPs_WritePin(&gpiops_inst,LE,1)
#define LE_0	XGpioPs_WritePin(&gpiops_inst,LE,0)
#define DATA_1	XGpioPs_WritePin(&gpiops_inst,DATA,1)
#define DATA_0	XGpioPs_WritePin(&gpiops_inst,DATA,0)
#define MUX_1	XGpioPs_WritePin(&gpiops_inst,MUX,1)
#define MUX_0	XGpioPs_WritePin(&gpiops_inst,MUX,0)
#define LD_1	XGpioPs_WritePin(&gpiops_inst,LD,1)
#define LD_0	XGpioPs_WritePin(&gpiops_inst,LD,0)

//#define
/*
#define ADF4351_R0			((u32)0x2260000)//110Mhz
#define ADF4351_R1			((u32)0x8011)
#define ADF4351_R2			((u32)0X3E8FC2)
#define ADF4351_R3			((u32)0x6004B3)
#define ADF4351_R4			((u32)0x50103C)
#define ADF4351_R5			((u32)0X580005)
*/
#define ADF4351_R0			((u32)0x2260000)//110Mhz
#define ADF4351_R1			((u32)0X11)
#define ADF4351_R2			((u32)0x3E8EC2)
#define ADF4351_R3			((u32)0x400003)
#define ADF4351_R4			((u32)0x50143C)
#define ADF4351_R5			((u32)0X580005)

#define ADF4351_R0_BASE		((u32)0X32000000)//频率输出，0hz
#define ADF4351_RF_OFF		((u32)0xD0101C)//关闭RF输出
#define ADF4351_R4_VCO_ON	((u32)0XD0103C)
#define ADF4351_R4_VCO_OFF	((u32)0XD0183C)//关闭VCO

XGpioPs gpiops_inst;
XGpioPs_Config *gpiops_cfg_ptr;

void ADF_GPIOInit(void);
void WriteRegADS4351(u32 buf);
void WriteToADF4351(u8 count, u8 *buf);
void WriteOneRegToADF4351(u32 Regster);
void ADF4351Init(void);
void ADF4351WriteFreq(u16 Fre);		//fre 单位100kHz

#endif
