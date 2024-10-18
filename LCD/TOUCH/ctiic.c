#include "ctiic.h"
#include <xgpio.h>
#include <xparameters.h>
#include "../DELAY/delay.h"
#include "stdlib.h"
#include "stdio.h"

void CT_SDA_IN(void)
{
	XGpio_SetDataDirection (&gpio_sda, 1, 1);
}
void CT_SDA_OUT(void)
{
	XGpio_SetDataDirection (&gpio_sda, 1, 0);
}//����gpio_sda�ķ���

//����I2C�ٶȵ���ʱ
void CT_Delay(void)
{
	delay_us(5);
} 

void GPIO_Init(void)
{
	int sts;
    sts = XGpio_Initialize (&gpio_sda, XPAR_TFT_LCD_GPIO_SDA_DEVICE_ID);
	if(sts!=XST_SUCCESS) xil_printf("gpio sda init err!\n");
    sts = XGpio_Initialize (&gpio_intc, XPAR_TFT_LCD_GPIO_INTC_DEVICE_ID);
	if(sts!=XST_SUCCESS) xil_printf("gpio intc init err!\n");
    sts = XGpio_Initialize (&gpio_rst, XPAR_TFT_LCD_GPIO_RST_DEVICE_ID);
	if(sts!=XST_SUCCESS) xil_printf("gpio rst init err!\n");
    sts = XGpio_Initialize (&gpio_scl, XPAR_TFT_LCD_GPIO_SCL_DEVICE_ID);
	if(sts!=XST_SUCCESS) xil_printf("gpio scl init err!\n");
}//��ʼ���ĸ�gpio

//���ݴ���оƬIIC�ӿڳ�ʼ��
void CT_IIC_Init(void)
{					     
	XGpio_SetDataDirection (&gpio_sda, 1, 0);
	XGpio_SetDataDirection (&gpio_scl, 1, 0);
	XGpio_DiscreteWrite (&gpio_scl, 1, 1);//CT_IIC_SCL_1
	XGpio_DiscreteWrite (&gpio_sda, 1, 1);//CT_IIC_SDA_1
}
//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda�����
	CT_IIC_SDA_1;
	CT_IIC_SCL_1;
	delay_us(30);
 	CT_IIC_SDA_0;//START:when CLK is high,DATA change form high to low
	CT_Delay();
	CT_IIC_SCL_0;//ǯסI2C���ߣ�׼�����ͻ��������
}	  
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda�����
	CT_IIC_SCL_1;
	delay_us(30);
	CT_IIC_SDA_0;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA_1;//����I2C���߽����ź�
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	CT_SDA_IN();      //SDA����Ϊ����  
	CT_IIC_SDA_1;
	CT_IIC_SCL_1;
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	CT_IIC_SCL_0;//ʱ�����0
	return 0;  
} 
//����ACKӦ��
void CT_IIC_Ack(void)
{
	CT_IIC_SCL_0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA_0;
	CT_Delay();
	CT_IIC_SCL_1;
	CT_Delay();
	CT_IIC_SCL_0;
}
//������ACKӦ��		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL_0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA_1;
	CT_Delay();
	CT_IIC_SCL_1;
	CT_Delay();
	CT_IIC_SCL_0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CT_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL_0;//����ʱ�ӿ�ʼ���ݴ���
	CT_Delay();
	for(t=0;t<8;t++)
    {              
		XGpio_DiscreteWrite(&gpio_sda, 1, (txd&0x80)>>7);
        txd<<=1; 	      
		CT_IIC_SCL_1;
		CT_Delay();
		CT_IIC_SCL_0;
		CT_Delay();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CT_SDA_IN();//SDA����Ϊ����
	delay_us(30);
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL_0;
		CT_Delay();
		CT_IIC_SCL_1;
		receive<<=1;
		if(CT_READ_SDA)receive++;   
	}	  				 
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK   
 	return receive;
}




























