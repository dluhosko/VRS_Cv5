/*
 * VRS_Cv5.c
 *
 *  Created on: 18. 10. 2016
 *      Author: Viktor
 */


#include "VRS_Cv5.h"
#include <stddef.h>
#include "stm32l1xx.h"

extern uint16_t value;



void adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_384Cycles);


	ADC_ITConfig(ADC1,ADC_IT_EOC, ENABLE);
	ADC_ITConfig(ADC1, ADC_IT_OVR , ENABLE);
	ADC_Cmd(ADC1, ENABLE);




	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
	{
	}
	ADC_SoftwareStartConv(ADC1);

}
void NVIC_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void ADC1_IRQHandler (void)
{

	if(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC))
	{
		value =ADC_GetConversionValue(ADC1);
	}
	ADC_ClearFlag(ADC1, ADC_FLAG_OVR);


}
void USART_init(void)
{

	  GPIO_InitTypeDef GPIOInitStruct;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	  GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF;
	  GPIOInitStruct.GPIO_OType = GPIO_OType_PP ;
	  GPIOInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIOInitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	  GPIOInitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	  GPIO_Init(GPIOA,&GPIOInitStruct);

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
      GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	  USART_InitStructure.USART_BaudRate = 9600; //9600
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	  USART_Init(USART2, &USART_InitStructure);
	  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	  //toto prehodit....
	  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);


	  USART_Cmd(USART2, ENABLE);
}










