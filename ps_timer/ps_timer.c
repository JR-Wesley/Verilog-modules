
#include "ps_timer.h"

int timer_init(XScuTimer *timer_ptr)
{
    int status;

    XScuTimer_Config *timer_cfg_ptr;
    timer_cfg_ptr = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
    if (NULL == timer_cfg_ptr)
        return XST_FAILURE;
    status = XScuTimer_CfgInitialize(timer_ptr, timer_cfg_ptr,
            timer_cfg_ptr->BaseAddr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    XScuTimer_LoadTimer(timer_ptr, TIMER_LOAD_VALUE);
    XScuTimer_EnableAutoReload(timer_ptr);
    return XST_SUCCESS;
}

void timer_intr_init(XScuGic *intc_ptr,XScuTimer *timer_ptr)
{
    XScuGic_Config *intc_cfg_ptr;
    intc_cfg_ptr = XScuGic_LookupConfig(INTC_DEVICE_ID);
    XScuGic_CfgInitialize(intc_ptr, intc_cfg_ptr,
            intc_cfg_ptr->CpuBaseAddress);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
            (Xil_ExceptionHandler)XScuGic_InterruptHandler, intc_ptr);
    Xil_ExceptionEnable();
    XScuGic_Connect(intc_ptr, TIMER_IRPT_INTR,
          (Xil_ExceptionHandler)timer_intr_handler, (void *)timer_ptr);

    XScuGic_Enable(intc_ptr, TIMER_IRPT_INTR);
    XScuTimer_EnableInterrupt(timer_ptr);
}

void timer_intr_handler(void *CallBackRef)
{
    XScuTimer *timer_ptr = (XScuTimer *) CallBackRef;

    //doing task
    xil_printf("timer intr\r\n");
    XScuTimer_ClearInterruptStatus(timer_ptr);
}

//status = timer_init(&Timer);
//if (status != XST_SUCCESS) {
//    xil_printf("Timer Initial Failed\r\n");
//    return XST_FAILURE;
//}
//timer_intr_init(&Intc,&Timer);
//XScuTimer_Start(&Timer);
