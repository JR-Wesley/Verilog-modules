#include "gpio.h"

void emio_init()
{
	gpiops_cfg_ptr=XGpioPs_LookupConfig(GPIOPS_ID);
	XGpioPs_CfgInitialize(&gpiops_inst,gpiops_cfg_ptr,gpiops_cfg_ptr->BaseAddr);

	XGpioPs_SetDirectionPin(&gpiops_inst,EMIO0,0);
	XGpioPs_SetDirectionPin(&gpiops_inst,EMIO1,0);
	XGpioPs_SetOutputEnablePin(&gpiops_inst,EMIO0,1);	//1 out
	XGpioPs_SetOutputEnablePin(&gpiops_inst,EMIO1,1);
}

void axigpio_init()
{
	XGpio_Initialize(&axi_gpio_inst,AXI_GPIO_ID);
	XGpio_SetDataDirection(&axi_gpio_inst,AXI_GPIO_CHANNEL,1);
	XGpio_InterruptEnable(&axi_gpio_inst,AXI_GPIO_MASK);
	XGpio_InterruptGlobalEnable(&axi_gpio_inst);
}

int setup_interrupt_system(XScuGic*gic_ins_ptr,XGpioPs*gpio, XGpio* axi_gpio)
{
	int status;

	//look for and init scu
	scugic_cfg_ptr = XScuGic_LookupConfig(SCUGIC_ID);
	if (NULL == scugic_cfg_ptr) {
		return XST_FAILURE;
	}
	status = XScuGic_CfgInitialize(gic_ins_ptr, scugic_cfg_ptr,
			scugic_cfg_ptr->CpuBaseAddress);
	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	//enable intr
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) XScuGic_InterruptHandler, gic_ins_ptr);
	Xil_ExceptionEnable();

	//ps io intr
	status = XScuGic_Connect(gic_ins_ptr, GPIO_INTR_ID,
			(Xil_ExceptionHandler) emio_intr_handler, (void *) gpio);
	if (status != XST_SUCCESS) {
		return status;
	}
	XGpioPs_SetIntrTypePin(gpio, EMIO0, XGPIOPS_IRQ_TYPE_EDGE_FALLING);
	XGpioPs_SetIntrTypePin(gpio, EMIO1, XGPIOPS_IRQ_TYPE_EDGE_FALLING);	//falling intr
	XGpioPs_IntrEnablePin(gpio, EMIO0);
	XGpioPs_IntrEnablePin(gpio, EMIO1);

	//enable ps_gpio scu_intr
	XScuGic_SetPriorityTriggerType(gic_ins_ptr,GPIO_INTR_ID,0xA0,0x1);
	XScuGic_Connect(gic_ins_ptr,GPIO_INTR_ID,emio_intr_handler,&gpiops_inst);
	XScuGic_Enable(gic_ins_ptr,GPIO_INTR_ID);

	//enable axi gpio intr
	XScuGic_SetPriorityTriggerType(gic_ins_ptr,AXI_GPIO_INTR,0xA0,0x1);
	XScuGic_Connect(gic_ins_ptr,AXI_GPIO_INTR,axi_gpio_handler,&axi_gpio_inst);
	XScuGic_Enable(gic_ins_ptr,AXI_GPIO_INTR);

   return XST_SUCCESS;
}

void axi_gpio_handler(void *CallbackRef)
{
	int value;
	XGpio *GpioPtr=(XGpio *)CallbackRef;

	xil_printf("axi_gpio interrupt\r\n");
	XGpio_InterruptDisable(GpioPtr,AXI_GPIO_MASK);

	value=XGpio_DiscreteRead(GpioPtr,AXI_GPIO_CHANNEL);
	if(value==1){
		xil_printf("io port high;\r\n");
	}
	sleep(1);
	XGpio_InterruptClear(GpioPtr,AXI_GPIO_MASK);
	XGpio_InterruptEnable(GpioPtr,AXI_GPIO_MASK);
}

void emio_intr_handler(void* callback_ref)
{
	XGpioPs *gpio=(XGpioPs*) callback_ref;

	//����Ƿ����жϣ�������
	if(XGpioPs_IntrGetStatusPin(gpio,EMIO0)){
		xil_printf("gpio_ps interrupt\r\n");
		XGpioPs_IntrDisablePin(gpio,EMIO0);
	}
}

