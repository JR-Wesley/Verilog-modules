#include "iic.h"
#include "sleep.h"
//#include "xil_printf.h"

int GPIO_OLED_INIT()
{
    int status;
	status = XGpio_Initialize(&sdaInst, XPAR_SDA_DEVICE_ID);
	if(status != XST_SUCCESS) return XST_FAILURE;
	status = XGpio_Initialize(&sclInst, XPAR_SCL_DEVICE_ID);
	if(status != XST_SUCCESS) return XST_FAILURE;

	XGpio_DiscreteWrite(&sdaInst, 1, 0x1);
	XGpio_DiscreteWrite(&sclInst, 1, 0x1);
	return XST_SUCCESS;
}

//开始信号
void IIC_Start(void)
{
	SDA_OUT ;// set output
	SCL_OUT ; // set output

	SDA_H;//IIC_SDA=1;
    SCL_H;//IIC_SCL=1;
    usleep(2);
    SDA_L;//IIC_SDA=0;
    usleep(2);
    SCL_L;//IIC_SCL=0;
    usleep(2);
}

void IIC_Stop(void)
{
    SCL_H;//IIC_SCL=1;
    SDA_L;//IIC_SDA=0;
    usleep(2);
    SDA_H;//IIC_SDA=1;
    usleep(2);
}

/*
*   返回1--应答出错
*   返回0--应答正确
*/
unsigned char IIC_Wait_Ask(void)
{
    int count=0;

    SDA_IN ;// set output
    SCL_OUT ; // set output
			//    SDA_IN();

    SCL_H;		//IIC_SCL=1;
    usleep(2);
    while(XGpio_DiscreteRead(&sdaInst, 1)) //
    {
        count++;
        if(count>250)
        {
            IIC_Stop();
            //print("No Ack!");
            return 1;
        }
    }
    //print("ACK!");
    SCL_L;//IIC_SCL=0;
    usleep(2);
    return 0;
}

//写一个字节
void IIC_WriteByte(unsigned char  data)
{
	unsigned char  i;
    SDA_OUT;//SDA_OUT();
    for(i=0;i<8;i++)
    {
    	SCL_L;//IIC_SCL=0;
    	usleep(2);
        if(data & 0x80)     //MSB,从高位开始一位一位传输
            SDA_H;//IIC_SDA=1;
        else
            SDA_L;//IIC_SDA=0;
        SCL_H;//IIC_SCL=1;
        usleep(2);
        SCL_L;//IIC_SCL=0;
        data<<=1;

    }
}

void WriteCmd(unsigned char command)
{
    IIC_Start();
    IIC_WriteByte(0x78);//OLED地址
    IIC_Wait_Ask();
    IIC_WriteByte(0x00);//寄存器地址
    IIC_Wait_Ask();
    IIC_WriteByte(command);
    IIC_Wait_Ask();
    IIC_Stop();
}

void WriteDat(unsigned char data)
{
    IIC_Start();
    IIC_WriteByte(0x78);//OLED地址
    IIC_Wait_Ask();
    IIC_WriteByte(0x40);//寄存器地址
    IIC_Wait_Ask();
    IIC_WriteByte(data);
    IIC_Wait_Ask();
    IIC_Stop();
}
