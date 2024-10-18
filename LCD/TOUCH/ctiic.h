#ifndef __MYCT_IIC_H
#define __MYCT_IIC_H
#include "xbasic_types.h"
#include <xgpio.h>

//IO��������
void CT_SDA_IN(void) ;	//PF11����ģʽ
void CT_SDA_OUT(void) ; 	//PF11���ģʽ

XGpio gpio_sda;
XGpio gpio_intc;
XGpio gpio_rst;
XGpio gpio_scl;
//IO��������	 
#define CT_IIC_SCL_1    XGpio_DiscreteWrite (&gpio_scl, 1, 1)
#define CT_IIC_SCL_0    XGpio_DiscreteWrite (&gpio_scl, 1, 0)
#define CT_IIC_SDA_1    XGpio_DiscreteWrite (&gpio_sda, 1, 1)
#define CT_IIC_SDA_0    XGpio_DiscreteWrite (&gpio_sda, 1, 0)
#define CT_READ_SDA     XGpio_DiscreteRead (&gpio_sda, 1)   //����SDA
void GPIO_Init(void);

//IIC���в�������
void CT_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void CT_IIC_Start(void);				//����IIC��ʼ�ź�
void CT_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CT_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CT_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 CT_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CT_IIC_Ack(void);					//IIC����ACK�ź�
void CT_IIC_NAck(void);					//IIC������ACK�ź�

#endif







