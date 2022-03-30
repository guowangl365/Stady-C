#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"

//uint32_t TimingDelay = 0; //��delay.c���Ѷ��壬����main������û���õ�
extern uint8_t leds;

void NVIC_Configuration(void);
void TIM_Config(void);
void LED_Init(void);

int main(void)
{
	uint8_t  string[20]; 
 	SysTick_Config1(SystemCoreClock/1000);
 
	TIM_Config();
	LED_Init();
	
  OLED_Init();
//  LED_Config();
	
	  OLED_P8x16Str(0,0," TIMER DEMO ");
		OLED_P8x16Str(0,2,"See The LEDs!");		
//		OLED_P8x16Str(0,4,"Computer Depart");		
	
	while(1)
	{
		

		
		//LED
		GPIO_Write(GPIOC,~(1<<(leds+7)));
			GPIO_Write(GPIOA,~(1<<(leds+7)));
		
//		GPIO_SetBits(GPIOD,GPIO_Pin_2);
//		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		//LCD
		sprintf(string,"%s%d","--LED ON:LD",leds);
//		LCD_DisplayStringLine(Line6,string);			
		OLED_P8x16Str(0,4,string);		
	}
}
 
void TIM_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//�ж���������
	NVIC_Configuration();		
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 50000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//TIM3Ԥ��Ƶ����:1MHZ,APB1��Ƶϵ��2��TIM3ʱ��Ϊ36MHzx2 = 72MHz  
	TIM_PrescalerConfig(TIM3,71, TIM_PSCReloadMode_Immediate);	
	
	//ͨ�ö�ʱ��TIM3�ж�����
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

/**
  * @˵��     �ж��������ú���
  * @����     none
  * @����ֵ   None
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Enable the TIM2 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @˵��     LED ���GPIO���Ź���ģʽ��ʱ��Դ����
  * @����     None 
  * @����ֵ   None
  */
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//

    //LED�������ã�PC08~PC15
    GPIO_InitStructure.GPIO_Pin = LED0 |LED1 | LED2 | LED3 | LED4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //74HC573�����������ã�PD2
    GPIO_InitStructure.GPIO_Pin = LED5 | LED6 | LED7;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

 
 
