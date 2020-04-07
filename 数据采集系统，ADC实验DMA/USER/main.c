#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"
#include "stm32f10x_dma.h"

//ALIENTEK Mini STM32�����巶������15
//ADCʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
DMA_InitTypeDef DMA_InitStructure;
#define ADC1_DR_Address    ((uint32_t)0x4001244C);
__IO uint16_t AD_Value[2];

 int main(void)
 { 
	float vol1,temp,vol2;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	Adc_Init();		  		//ADC��ʼ��	 
	 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&AD_Value;   
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 2;      
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);  
	while(1)
	{
		vol1=(float)AD_Value[0]*(3.3/4096);
		printf("\rvol1:%f\n",vol1);
		
		vol2=(float)AD_Value[1]*(3.3/4096);
		temp=(1.43-vol2)/0.0043+25;
		printf("\rtmp:%f\n",temp);
		
		delay_ms(250);	
	}											    
}	
