#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "xbasic_types.h"
#include <xgpio.h>

//IO方向设置
void CT_SDA_IN(void) ;	//PF11输入模式
void CT_SDA_OUT(void) ; 	//PF11输出模式

XGpio gpio_sda;
XGpio gpio_intc;
XGpio gpio_rst;
XGpio gpio_scl;
//IO操作函数	 
#define CT_IIC_SCL_1    XGpio_DiscreteWrite (&gpio_scl, 1, 1)
#define CT_IIC_SCL_0    XGpio_DiscreteWrite (&gpio_scl, 1, 0)
#define CT_IIC_SDA_1    XGpio_DiscreteWrite (&gpio_sda, 1, 1)
#define CT_IIC_SDA_0    XGpio_DiscreteWrite (&gpio_sda, 1, 0)
#define CT_READ_SDA     XGpio_DiscreteRead (&gpio_sda, 1)   //输入SDA
void GPIO_Init(void);

//IIC所有操作函数
void CT_IIC_Init(void);                	//初始化IIC的IO口				 
void CT_IIC_Start(void);				//发送IIC开始信号
void CT_IIC_Stop(void);	  				//发送IIC停止信号
void CT_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC读取一个字节
u8 CT_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void CT_IIC_Ack(void);					//IIC发送ACK信号
void CT_IIC_NAck(void);					//IIC不发送ACK信号

#endif







