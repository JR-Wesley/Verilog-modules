#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "gt9147.h"
#include "xil_types.h"

#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 
#define CT_MAX_TOUCH  5    //������֧�ֵĵ���,�̶�Ϊ5��

//������������
typedef struct
{
	u8 (*init)(void);			//��ʼ��������������
	u8 (*scan)(u8);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
	void (*adjust)(void);		//������У׼ 
	u16 x[CT_MAX_TOUCH]; 		//��ǰ����
	u16 y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������. 
	u8  sta;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������. 
								//b5:����
								//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
/////////////////////������У׼����(����������ҪУ׼)//////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
//b1~6:����.
//b7:0,������
//   1,������ 
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//������оƬ��������	   
/*#define PEN  		PBin(1)  	//T_PEN
#define DOUT 		PBin(2)   	//T_MISO
#define TDIN 		PFout(11)  	//T_MOSI
#define TCLK 		PBout(0)  	//T_SCK
#define TCS  		PCout(13)  	//T_CS  */

void Load_Drow_Dialog(void);   //�����Ļ�������Ͻ���ʾ"RST"
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color); //��ˮƽ��  x0,y0:����  len:�߳���  color:��ɫ
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color); //��ʵ��Բ  x0,y0:����  r:�뾶  color:��ɫ
u16 my_abs(u16 x1,u16 x2); //������֮��ľ���ֵ  x1,x2����ȡ��ֵ��������  ����ֵ��|x1-x2|
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color);//��һ������  (x1,y1),(x2,y2):��������ʼ����  size�������Ĵ�ϸ�̶�  color����������ɫ
void ctp_test(void);//���ݴ��������Ժ���
//������/������ ���ú���
u8 TP_Scan(u8 tp);								//ɨ��
u8 TP_Init(void);								//��ʼ��
 
#endif

















