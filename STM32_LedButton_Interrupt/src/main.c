/**
  ******************************************************************************
  * @file    main.c
  * @author  Milind Prajapati
  * @version V1.0
  * @date    12/13/2018
  * @brief   Default main function.
  ******************************************************************************
*/

#include <string.h>
#include <stdint.h>
#include "stm32f30x.h"
#include "stm32f3xx_nucleo.h"
#include "FreeRTOS.h"
#include "task.h"

#define FALSE 0
#define TRUE 1
#define OFF FALSE
#define ON TRUE

static void prvSetupGPIO(void);
static void prvSetupUart(void);
void printmsg(char  *msg);
static void prvSetupHardware(void);

void led_task_handler(void *params);
void btn_handler(void *params);

uint8_t btn_status_flag = OFF;

int main(void)
{
	DWT -> CTRL |= (1<<0);
	RCC_DeInit();
	SystemCoreClockUpdate();
	prvSetupHardware();
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();
	xTaskCreate(led_task_handler,"LED-TASK",configMINIMAL_STACK_SIZE,NULL,3,NULL);
	vTaskStartScheduler();

	for(;;);
}

void delay(void){
	for(int i=1;i<15000;i++);
}
void led_task_handler(void *params){
	while(1){
		if(btn_status_flag == ON){
			GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_SET);
			printmsg("LED TURN ON\r \n");
			//delay();
		}else{
			GPIO_WriteBit(GPIOB, GPIO_Pin_13, Bit_RESET);
		}
	}
}

void btn_handler(void *params){
		btn_status_flag ^=1;

}

void printmsg(char  *msg){
	for(uint32_t i=0;i<strlen(msg);i++){
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)!=SET);
		USART_SendData(USART2, msg[i]);
	}
	while ( USART_GetFlagStatus(USART2,USART_FLAG_TC) != SET);
}

static void prvSetupUart(void){

	GPIO_InitTypeDef gpio_uart_pins;
	USART_InitTypeDef uart2_init;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	memset(&gpio_uart_pins,0,sizeof(gpio_uart_pins));
	gpio_uart_pins.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_uart_pins);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_7);

	memset(&uart2_init,0,sizeof(uart2_init));
	uart2_init.USART_BaudRate = 115200;
	uart2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart2_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	uart2_init.USART_Parity = USART_Parity_No;
	uart2_init.USART_StopBits = USART_StopBits_1;
	uart2_init.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2,&uart2_init);

	USART_Cmd(USART2, ENABLE);
}

static void prvSetupGPIO(void){

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef led_init,btn_init;

	led_init.GPIO_Mode =  GPIO_Mode_OUT;
	led_init.GPIO_OType = GPIO_OType_PP;
	led_init.GPIO_Pin = GPIO_Pin_13;
	led_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	led_init.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOB, &led_init);

	btn_init.GPIO_Mode =  GPIO_Mode_IN;
	btn_init.GPIO_OType = GPIO_OType_PP;
	btn_init.GPIO_Pin = GPIO_Pin_13;
	btn_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
	btn_init.GPIO_Speed = GPIO_Speed_Level_2;
	GPIO_Init(GPIOC, &btn_init);

	//Interuppt config (EXTI Connfig)
	//SYSCFG Config
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	EXTI_InitTypeDef exti_init;
	exti_init.EXTI_Line = EXTI_Line13;
	exti_init.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti_init);

	//NVIC Config
	NVIC_SetPriority(EXTI15_10_IRQn, 2);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

}
void EXTI15_10_IRQHandler(void){
	//CLEAR IPB of(EXTI 13)
	traceISR_ENTER();
	EXTI_ClearITPendingBit(EXTI_Line13);
	btn_handler(NULL);
	traceISR_EXIT();

}
static void prvSetupHardware(void){
	//Uart Call
	prvSetupGPIO();
	prvSetupUart();

}



