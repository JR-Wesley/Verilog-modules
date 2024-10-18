#ifndef _IIC_H_
#define _IIC_H_

#include  "xgpio.h"
#include"xparameters.h"

XGpio sdaInst;
XGpio sclInst;
#define SDA_IN	XGpio_SetDataDirection(&sdaInst, 1, 1) // set input
#define SDA_OUT	XGpio_SetDataDirection(&sdaInst, 1, 0)  // set output

#define SCL_IN XGpio_SetDataDirection(&sclInst, 1, 1)
#define SCL_OUT XGpio_SetDataDirection(&sclInst, 1, 0)

#define		SCL_L		XGpio_DiscreteWrite(&sclInst, 1, 0)
#define		SCL_H		XGpio_DiscreteWrite(&sclInst, 1, 1)
#define     SDA_L		XGpio_DiscreteWrite(&sdaInst, 1, 0)
#define     SDA_H		XGpio_DiscreteWrite(&sdaInst, 1, 1)

void IIC_Start(void);
void IIC_Stop(void);

/*
*   ����1--Ӧ�����
*   ����0--Ӧ����ȷ
*/
unsigned char IIC_Wait_Ask(void);
int GPIO_OLED_INIT();
void IIC_WriteByte(unsigned char data);
unsigned char IIC_ReadByte(void);
void WriteCmd(unsigned char command);
void WriteDat(unsigned char data);
#define OLED_WrCmd WriteCmd   //��д�����������
#define OLED_WrData WriteDat  //��д���ݺ���������

#endif
