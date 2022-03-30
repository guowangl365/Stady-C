#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"

extern u32 TimingDelay;//ע�⣺��delay.c���ж��壬��������extern���岻�ܸ���ֵ
uint16_t Channel2Pulse = 0, Channel3Pulse = 0;

void NVIC_Configuration(void);
void TIM_Config(uint16_t Channel2Pulse, uint16_t Channel3Pulse);
void PWM_IO_Config(void);

int main(void)
{
 	SysTick_Config1(SystemCoreClock/1000);
 
	PWM_IO_Config();
	TIM_Config(998/2,998*7/10);
	
  OLED_Init();
//  LED_Config();
	  OLED_P8x16Str(20,0,"TIMER DEMO");
		//OLED_P16x16Str(0+8,2,"���������ѧԺ");
	  OLED_P8x16Str(0,2," TIM2 PWM MODE ");	
		OLED_P8x16Str(0,4,"PORTA.1-PWM:50%");		
		OLED_P8x16Str(0,6,"PORTA.2-PWM:70%");		
	while(1)
	{
	
		
		
				
	}
}
 
void TIM_Config(uint16_t Channel2Pulse, uint16_t Channel3Pulse)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;  //1KHz
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM2Ԥ��Ƶ����:1MHZ,APB1��Ƶϵ��2�����뵽TIM3ʱ��Ϊ36MHzx2 = 72MHz  


	/* Channel 2 and 3 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_Pulse = Channel3Pulse;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);

	//ʹ��TIM2��ʱ������
	TIM_Cmd(TIM2, ENABLE);
	//ʹ��TIM2 PWM���ģʽ
	TIM_CtrlPWMOutputs(TIM2, ENABLE);
}

/**
  * @˵��     PWM���ģʽ PA1(TIM2-CH2)��PA2(TIM2-CH3)��������
  * @����     None 
  * @����ֵ   None
  */
void PWM_IO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}


 
 
