
#include "ui.h"
#include "../SD/sd.h"

int TouchInBar4(u16 x1, u16 y1, u16 x2, u16 y2)
{
	if(tp_dev.x[4]>x1 && tp_dev.x[4]<x2 && tp_dev.y[4]>y1 && tp_dev.y[4]<y2) return 1;
	else return 0;
}

//touch point
int TouchInBar(u16 x1, u16 y1, u16 x2, u16 y2)
{
	if(tp_dev.x[0]>x1 && tp_dev.x[0]<x2 && tp_dev.y[0]>y1 && tp_dev.y[0]<y2) return 1;
	else return 0;
}

//function config
void config()
{
	LCD_DrawLine(1,h+s,2*l,h+s);
	LCD_DrawLine(1,h+2*s,2*l,h+2*s);
	LCD_DrawLine(1,h+3*s,2*l,h+3*s);
	LCD_DrawLine(1,h+4*s,2*l,h+4*s);
	LCD_DrawLine(1,h+5*s,2*l,h+5*s);
	LCD_DrawLine(l,1,l,479);

	LCD_ShowString(10,	h+20,  "x_mode",	WHITE, 0);
	LCD_ShowString(10,  h+s+20,  "20ms/div",	WHITE, 0);
	LCD_ShowString(10,	h+2*s+20,  "2us/div",	WHITE, 0);
	LCD_ShowString(10,	h+3*s+20,  "100ns/div",	WHITE, 0);

	LCD_ShowString(l+10,	h+20,  "y_mode",	WHITE, 0);
	LCD_ShowString(l+10,	h+s+20,  "1V/div",	WHITE, 0);
	LCD_ShowString(l+10,	h+2*s+20,  "0.1V/div",	WHITE, 0);
	LCD_ShowString(l+10,	h+3*s+20,  "2mV/div",	WHITE, 0);

	LCD_ShowString(10,	h+4*s+20,  "sigle",	WHITE, 0);
	LCD_ShowString(10,	h+5*s+20,  "store",	WHITE, 0);
	LCD_ShowString(l+10,	h+4*s+20,  "square",	WHITE, 0);
	LCD_ShowString(l+10,	h+5*s+20,  "display",	WHITE, 0);
}

//graph
void graph(int* data)
{
	char mode;
	int i=0;

	touch(&mode);
	if(mode==sigle) {
		while(mode==sigle) touch(&mode);
	}

	LCD_Fill(360+1, 160+1, 760-1, 416-1,BLACK);
	LCD_DrawRectangle(360, 160, 760, 416);
	max=min=data[1]/15/sp_max;
	for(i=1;i<201;i++){
		data[i]=data[i]/15/sp_max;
		if(data[i]>max) max=data[i];
		if(data[i]<min) min=data[i];
	}

	switch(y_mode){
	case y_1v:
		min=max=(-min*3.7+max*9.1)*7.14;
		break;
	case y_01v:
		min=max=(-min*3.7+max*9.0)/2;
		break;
	case y_2mv:
		min=max=(-min*3.7+max*9.1)/50;
		break;
	default:
		break;
	}

	LCD_Fill(l+1,50,2*l-15,80,BLACK);
	LCD_Fill(2*l+15,50,3*l+15,80,BLACK);
	LCD_ShowString(l+15 , 50,"-",WHITE,0);
	LCD_ShowNum(l+25 , 50,min,4,WHITE,0);
	LCD_ShowNum(2*l+15,	50,max,4,WHITE,0);

	for(i=1;i<201;i++){
		if(data[i]>128) data[i]=128;
		if(data[i]<-128) data[i]=-128;
		LCD_DrawPoint(360+2*i,288+data[i],WHITE);
		if(i>1) LCD_DrawLine(360+2*i,288+data[i],360+2*i-2,288+data[i-1]);
	}
	for(i=1;i<201;i++) data[i]=0;
}

//overall ui
void uidesign()
{
	LCD_DrawRectangle(1, 1, 799, 479);
	LCD_DrawRectangle(1, 1, l, h);
	LCD_DrawRectangle(l, 1, 2*l, h);
	LCD_DrawRectangle(2*l, 1, 3*l, h);
	LCD_DrawRectangle(3*l, 1, 4*l, h);
	LCD_DrawRectangle(4*l, 1, 799,	h);

	LCD_ShowString(15,		10,	 "07_C",	WHITE, 0);
	LCD_ShowString(15,		50,	 "dig_osc",	WHITE, 0);
	LCD_ShowString(l+15,	10,  "V_min /mV",	WHITE, 0);
	LCD_ShowString(2*l+15,	10,	 "V_max /mV",	WHITE, 0);
	LCD_ShowString(3*l+15,	10,  "freq /hz",	WHITE, 0);
	LCD_ShowString(4*l+15,	10,  "perio/ns",	WHITE, 0);

	LCD_DrawLine(1, h, 799, h);
	LCD_DrawLine(2*l, h, 2*l, 479);

	LCD_DrawRectangle(360, 160, 760, 416);

	LCD_DrawLine(360, 160, 360, 150);
	LCD_DrawLine(360+40, 160, 360+40, 150);
	LCD_DrawLine(360+40*2, 160, 360+40*2, 150);
	LCD_DrawLine(360+40*3, 160, 360+40*3, 150);
	LCD_DrawLine(360+40*4, 160, 360+40*4, 150);
	LCD_DrawLine(360+40*5, 160, 360+40*5, 140);
	LCD_DrawLine(360+40*6, 160, 360+40*6, 150);
	LCD_DrawLine(360+40*7, 160, 360+40*7, 150);
	LCD_DrawLine(360+40*8, 160, 360+40*8, 150);
	LCD_DrawLine(360+40*9, 160, 360+40*9, 150);

	LCD_DrawLine(350, 160, 360, 160);
	LCD_DrawLine(350, 160+32, 360, 160+32);
	LCD_DrawLine(350, 160+32*2, 360, 160+32*2);
	LCD_DrawLine(350, 160+32*3, 360, 160+32*3);
	LCD_DrawLine(340, 160+32*4, 360, 160+32*4);
	LCD_DrawLine(350, 160+32*5, 360, 160+32*5);
	LCD_DrawLine(350, 160+32*6, 360, 160+32*6);
	LCD_DrawLine(350, 160+32*7, 360, 160+32*7);
}

//wait for touch and detect
void touchdetect(char *expression)
{
	char tempLCD;
	sp_num=0;
	while((tp_dev.sta) == '@'||(tp_dev.sta) == 0)
    {
    	tp_dev.scan(0);
    	delay_ms(10);
    }
	if(tp_dev.sta)
	{
		if(TouchInBar(20+4*s, 1, 20+5*s, l))
		{
			tempLCD = x_20ms;
			*expression = tempLCD;
			x20ms;
			x_mode=x_20ms;
			LCD_Fill(320+10,100+10,480-10,160-10,BLACK);
			LCD_ShowString(360,120,"20ms/div",WHITE, 0);
		}
		if(TouchInBar(20+3*s, 1, 20+4*s, l))
		{
			tempLCD = x_2us;
			*expression = tempLCD;
			x2us;
			x_mode=x_2us;
			LCD_Fill(320+10,100+10,480-10,160-10,BLACK);
			LCD_ShowString(360,120,"2us/div",WHITE, 0);
		}
		if(TouchInBar(20+2*s, 1, 20+3*s, l))
		{
			tempLCD = x_100n;
			*expression = tempLCD;
			x100ns;
			x_mode=x_100n;
			LCD_Fill(320+10,100+10,480-10,160-10,BLACK);
			LCD_ShowString(360,120,"100ns/div",WHITE, 0);
		}
		if(TouchInBar(20+s, 1, 20+2*s, l))
		{
			tempLCD = sigle;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"single",WHITE, 0);
		}
		if(TouchInBar(20, 1, 20+s, l))
		{
			tempLCD = store;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"store",WHITE, 0);
			sd_write_data(FILE_NAME,(u32)data,256);
		}
		if(TouchInBar(20+4*s, l, 20+5*s, 2*l))
		{
			tempLCD = y_1v;
			*expression = tempLCD;
			y1v;
			y_mode=y_1v;
			LCD_Fill(660+10,100+10,790-10,160-10,BLACK);
			LCD_ShowString(660,120,"1V/div",WHITE, 0);
		}
		if(TouchInBar(20+3*s, l, 20+4*s, 2*l))
		{
			tempLCD = y_01v;
			*expression = tempLCD;
			y01V;
			y_mode=y_01v;
			LCD_Fill(660+10,100+10,790-10,160-10,BLACK);
			LCD_ShowString(660,120,"0.1V/div",WHITE, 0);
		}
		if(TouchInBar(20+2*s, l, 20+3*s, 2*l))
		{
			tempLCD = y_2mv;
			*expression = tempLCD;
			y2mV;
			y_mode=y_2mv;
			LCD_Fill(660+10,100+10,790-10,160-10,BLACK);
			LCD_ShowString(660,120,"2mV/div",WHITE, 0);
		}

		if(TouchInBar(20+s, l, 20+2*s, 2*l))
		{
			tempLCD = square;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"square",WHITE, 0);
		}
		if(TouchInBar(20, l, 20+s, 2*l))
		{
			tempLCD = display;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"display",WHITE, 0);
			sd_read_data(FILE_NAME,(u32)data,256);
			graph(data);
		}
		if(TouchInBar(480-416, 760, 360, 779))
		{
			LCD_Fill( 760, 480-416,  779,360,BLACK);
			v_temp=(tp_dev.y[0]-64);
			LCD_Fill(760, 480-416,  779,64+v_temp,WHITE);
			LCD_ShowNum(780 , 370,v_temp,5,WHITE,0);
		}
	}
	while((tp_dev.sta)!= '@')
	{
	    tp_dev.scan(0);
	    delay_ms(10);
	}
}

void touch(char *expression )
{
	char tempLCD;
	sp_num=0;
	if((tp_dev.sta) == '@'||(tp_dev.sta) == 0)
    {
    	tp_dev.scan(0);
    	delay_ms(10);
    }
	if(tp_dev.sta)
	{
		if(TouchInBar(20+4*s, 1, 20+5*s, l))
		{
			tempLCD = x_20ms;
			*expression = tempLCD;
			x20ms;
			LCD_Fill(320+10,100+10,480-10,160-10,BLACK);
			LCD_ShowString(360,120,"20ms/div",WHITE, 0);
		}
		if(TouchInBar(20+3*s, 1, 20+4*s, l))
		{
			tempLCD = x_2us;
			*expression = tempLCD;
			x2us;
			LCD_Fill(320+10,100+10,480-10,160-10,BLACK);
			LCD_ShowString(360,120,"2us/div",WHITE, 0);
		}
		if(TouchInBar(20+2*s, 1, 20+3*s, l))
		{
			tempLCD = x_100n;
			*expression = tempLCD;
			x100ns;
			LCD_Fill(320+10,100+10,480-10,160-10,BLACK);
			LCD_ShowString(360,120,"100ns/div",WHITE, 0);
		}
		if(TouchInBar(20+s, 1, 20+2*s, l))
		{
			tempLCD = sigle;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"single",WHITE, 0);
		}
		if(TouchInBar(20, 1, 20+s, l))
		{
			tempLCD = store;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"store",WHITE, 0);
			sd_write_data(FILE_NAME,(u32)data,256);
		}
		if(TouchInBar(20+4*s, l, 20+5*s, 2*l))
		{
			tempLCD = y_1v;
			*expression = tempLCD;
			y1v;
			y_mode=y_1v;
			LCD_Fill(660+10,100+10,790-10,160-10,BLACK);
			LCD_ShowString(660,120,"1V/div",WHITE, 0);
		}
		if(TouchInBar(20+3*s, l, 20+4*s, 2*l))
		{
			tempLCD = y_01v;
			*expression = tempLCD;
			y01V;
			y_mode=y_01v;
			LCD_Fill(660+10,100+10,790-10,160-10,BLACK);
			LCD_ShowString(660,120,"0.1V/div",WHITE, 0);
		}
		if(TouchInBar(20+2*s, l, 20+3*s, 2*l))
		{
			tempLCD = y_2mv;
			*expression = tempLCD;
			y2mV;
			y_mode=y_2mv;
			LCD_Fill(660+10,100+10,790-10,160-10,BLACK);
			LCD_ShowString(660,120,"2mV/div",WHITE, 0);
		}
		if(TouchInBar(20+s, l, 20+2*s, 2*l))
		{
			tempLCD = square;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"square",WHITE, 0);
		}
		if(TouchInBar(20, l, 20+s, 2*l))
		{
			tempLCD = display;
			*expression = tempLCD;
			LCD_Fill(320+10,420+10,480-10,479-10,BLACK);
			LCD_ShowString(360,440,"display",WHITE, 0);
			sd_read_data(FILE_NAME,(u32)data,256);
			graph(data);
		}
		if(TouchInBar(480-416, 760, 360, 779))
		{
			LCD_Fill( 760, 480-416,  779,360,BLACK);
			v_temp=(tp_dev.x[0]-64);
			LCD_Fill(760, 480-416,  779,64+v_temp,WHITE);
			LCD_ShowNum(780 , 370,v_temp,5,WHITE,0);
		}
	}
	if((tp_dev.sta)!= '@')
	{
	    tp_dev.scan(0);
	    delay_ms(10);
	}
}

