#include "ADF4351.h"
#include "sleep.h"

void ADF_GPIOInit(void)
{
	gpiops_cfg_ptr=XGpioPs_LookupConfig(XPAR_XDMAPS_0_DEVICE_ID);
	XGpioPs_CfgInitialize(&gpiops_inst,gpiops_cfg_ptr,gpiops_cfg_ptr->BaseAddr);

	XGpioPs_SetDirectionPin(&gpiops_inst,CLK,1);
	XGpioPs_SetDirectionPin(&gpiops_inst,LD,1);
	XGpioPs_SetDirectionPin(&gpiops_inst,DATA,1);
	XGpioPs_SetDirectionPin(&gpiops_inst,MUX,1);
	XGpioPs_SetDirectionPin(&gpiops_inst,LE,1);

	XGpioPs_SetOutputEnablePin(&gpiops_inst,CLK,1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst,LD,1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst,DATA,1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst,MUX,1);
	XGpioPs_SetOutputEnablePin(&gpiops_inst,LE,1);
	LD_1;
	LE_0;
	CLK_0;
	DATA_0;
	MUX_0;
}

void WriteRegADS4351(u32 buf)
{
	u8 i;
	for(i=32;i>0;i--)
	{
		if(0x8000&buf)
			DATA_1;
		else
			DATA_0;
		CLK_1;
		buf <<= 1;
		CLK_0;
	}
	DATA_0;
	LE_1;
	LE_0;
	CLK_0;
}

void WriteToADF4351(u8 count, u8 *buf)
{
	u8 ValueToWrite = 0;
	u8 i = 0;
	u8 j = 0;

	CLK_0;
	LE_0;

	for(i = count; i>0; i--)
	{
		ValueToWrite = *(buf+i-1);
		for(j=0; j<8; j++)
		{
			if(0x80 == (ValueToWrite & 0x80))
			{
				DATA_1;
			}
			else
			{
				DATA_0;
			}
			CLK_1;
			ValueToWrite <<= 1;
			CLK_0;
		}
	}
	DATA_0;
	LE_1;
	xil_printf("clk\r\n");
	LE_0;
}

void WriteOneRegToADF4351(u32 Regster)
{
	u8 buf[4] = {0,0,0,0};
	buf[3] = (u8)((Regster>>24)&(0X000000FF));
	buf[2] = (u8)((Regster>>16)&(0X000000FF));
	buf[1] = (u8)((Regster>>8) &(0X000000FF));
	buf[0] = (u8)((Regster)&(0X000000FF));
	WriteToADF4351(4,buf);
}

void ADF4351Init(void)
{
	ADF_GPIOInit();

	WriteOneRegToADF4351(ADF4351_R5);
	WriteOneRegToADF4351(ADF4351_R4);
	WriteOneRegToADF4351(ADF4351_R3);
	WriteOneRegToADF4351(ADF4351_R2);
	WriteOneRegToADF4351(ADF4351_R1);
	WriteOneRegToADF4351(ADF4351_R0);
}

void ADF4351WriteFreq(u16 Fre)		//fre µ¥Î»100kHz
{
	u32 INT_Fre=Fre;
	u32	W_ADF4351_R0 = (INT_Fre<<15);
	WriteOneRegToADF4351(W_ADF4351_R0);
}
