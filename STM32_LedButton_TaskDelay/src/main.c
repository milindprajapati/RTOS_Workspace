/**
  ******************************************************************************
  * @file    main.c
  * @author  Milind Prajapati
  * @version V1.0
  * @date    12/13/2018
  * @brief   Default main function.
  ******************************************************************************
*/
#include <stdio.h>
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
void rtos_delay(uint32_t delay_in_ms);
static void prvSetupHardware(void);

void vTask1_handler(void *params);
void vTask2_handler(void *params);
char usr_msg[250]={0};

TaskHandle_t xTaskHandle1=NULL;
TaskHandle_t xTaskHandle2=NULL;



int main(void)
{
	DWT -> CTRL |= (1<<0);
	RCC_DeInit();
	SystemCoreClockUpdate();
	prvSetupHardware();
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	xTaskCreate(vTask1_handler,"TASK-1",400,NULL,2,&xTaskHandle1);
	xTaskCreate(vTask2_handler,"TASK-2",400,NULL,3,&xTaskHandle2);

	vTaskStartScheduler();

	for(;;);
}

void vTask1_handler(void *params)
{
	while(1){
		sprintf(usr_msg,"Status of LED is %ld \r \n", GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13));
		printmsg(usr_msg);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}

}

void vTask2_handler(void *params)
{
	while(1){
			GPIO_ToggleBits(GPIOB, GPIO_Pin_13);
			vTaskDelay(pdMS_TO_TICKS(1000));
		}

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

}

void rtos_delay(uint32_t delay_in_ms)
{
	uint32_t current_tick_count = xTaskGetTickCount();

	uint32_t delay_in_ticks = (delay_in_ms * configTICK_RATE_HZ ) /1000 ;

	while(xTaskGetTickCount() <  (current_tick_count + delay_in_ticks));

}
static void prvSetupHardware(void){
	//Uart Call
	prvSetupGPIO();
	prvSetupUart();

}



