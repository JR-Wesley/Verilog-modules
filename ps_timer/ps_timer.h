#ifndef SRC_PS_TIMER_PS_TIMER_H_
#define SRC_PS_TIMER_PS_TIMER_H_

#include "xparameters.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "xil_io.h"

//32 timer 32 watch dog--share 64bit GT
//TTC MIO//EMIO脉冲宽度,3timer
//私有定时器cpu_freq/2
#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID
#define INTC_DEVICE_ID		XPAR_SCUGIC_SINGLE_DEVICE_ID
#define TIMER_IRPT_INTR		XPAR_SCUTIMER_INTR

//0.2*1000_000_000/(1000/333)-1=3f83c3f
#define TIMER_LOAD_VALUE	0x3f83c3f

XScuTimer Timer;	/* 定时器驱动实例 */
XScuGic Intc;		/* 中断控制器驱动实例 */

int timer_init(XScuTimer *time_ptr);
void timer_intr_handler(void *CallBackRef);
void timer_intr_init(XScuGic *intc_ptr,XScuTimer *timer_ptr);

#endif /* SRC_PS_TIMER_PS_TIMER_H_ */
