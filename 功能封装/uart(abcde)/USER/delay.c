#include "delay.h"
void delay_init(void)
{
        	//0.ʱ�ӷ�Ƶ  8��Ƶ  72MHZ  ----  1sִ��72000000������   9MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   

}
void delay_us(u32 nus)//2^24 = 16777216 / 9 = 1864135
{
	u32 temp;

	//1.���ó�ֵ
	SysTick->LOAD = 9*nus;

	//2.��ռ�����
	SysTick->VAL = 0;
	
	//3.��ʼ����ʱ 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	//4.�ȴ�����ʱ����
	do
	{
		temp = SysTick->CTRL;
	}while(  (temp & 0x01) && !(temp & (1<<16)) );
	
	//5.�رն�ʱ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

	//6.��ռ�����
	SysTick->VAL = 0;
}

void delay_ms(u32 nms)//1864135 /1000  1864
{
	u32 temp;

	//1.���ó�ֵ
	SysTick->LOAD = 9000*nms;

	//2.��ռ�����
	SysTick->VAL = 0;
	
	//3.��ʼ����ʱ 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	//4.�ȴ�����ʱ����
	do
	{
		temp = SysTick->CTRL;
	}while(  (temp & 0x01) && !(temp & (1<<16)) );
	
	//5.�رն�ʱ��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

	//6.��ռ�����
	SysTick->VAL = 0;
}

