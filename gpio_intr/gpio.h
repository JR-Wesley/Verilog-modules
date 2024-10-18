
#ifndef SRC_GPIO_GPIO_H_
#define SRC_GPIO_GPIO_H_

#include "xparameters.h"
#include "xgpiops.h"
#include "xgpio.h"
#include "xscugic.h"

#define GPIO_INT_ID XPAR_FABRIC_GPIO_0_VEC_ID	//PS gpio ID
#define GPIOPS_ID	XPAR_XGPIOPS_0_DEVICE_ID	//PS gpio
#define GPIO_INTR_ID XPAR_XGPIOPS_0_INTR		//PS gpio intr
#define EMIO0				54					//connect IO
#define EMIO1				55
XGpioPs			gpiops_inst;
XGpioPs_Config *gpiops_cfg_ptr;

#define AXI_GPIO_ID			XPAR_AXI_GPIO_0_DEVICE_ID
#define AXI_GPIO_INTR		XPAR_FABRIC_GPIO_0_VEC_ID
#define AXI_GPIO_CHANNEL	1					//PL axi gpio
#define AXI_GPIO_MASK		XGPIO_IR_CH1_MASK	//
XGpio 			axi_gpio_inst;

#define SCUGIC_ID	XPAR_SCUGIC_0_DEVICE_ID
XScuGic			scugic_inst;
XScuGic_Config *scugic_cfg_ptr;

void emio_init();
void axigpio_init();
int setup_interrupt_system(XScuGic*gic_ins_ptr,XGpioPs*gpio, XGpio* axi_gpio);
void axi_gpio_handler(void *CallbackRef);
void emio_intr_handler(void *callback_ref);

#endif /* SRC_GPIO_GPIO_H_ */
