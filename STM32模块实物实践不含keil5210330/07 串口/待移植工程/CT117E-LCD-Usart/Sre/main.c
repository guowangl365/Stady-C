/*******************************************************************************  
* �ļ����ƣ�USART����ʵ��
* ʵ��Ŀ�ģ�����STM32 USART�Ĳ��������÷���
* ����˵����1.ͨ�����ڵ��Թ�����ʾ����PC���봮�ڵ�����������������趨Ϊ19200
*           2.�����ַ���"asdasdad"+x,��LCD��7����ʾasdasdad,��'x'λ������־
* ���ڰ汾��2011-9-19/V1.0a 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay = 0;
uint8_t USART_RXBUF[20];
extern uint8_t RXOVER;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
void Delay_Ms(uint32_t nTime);
void USART_Config(void);
void USART_SendString(int8_t *str);
/* Private functions ---------------------------------------------------------*/

/**
  * @˵��     ������
  * @����     None 
  * @����ֵ   None
  */
int main(void)
{	
	uint8_t i;
    SysTick_Config(SystemCoreClock/1000);  //1ms�ж�һ��

	
	//LCD����ģʽ����
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_SetTextColor(White);
	LCD_SetBackColor(Blue);
    
	LCD_ClearLine(Line0);
	LCD_ClearLine(Line1);
	LCD_ClearLine(Line2);
	LCD_ClearLine(Line3);
	LCD_ClearLine(Line4);

	LCD_DisplayStringLine(Line1,"      USART DEMO      ");
	LCD_DisplayStringLine(Line3,"   Receive & Display  ");


	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	USART_Config();
	LCD_DisplayStringLine(Line6,"Receive:");
	
	USART_SendString("Welcome to HBEU\r\n");//�����ַ���
	
    while(1){			
		if(RXOVER == 1){
			LCD_ClearLine(Line7);
			LCD_DisplayStringLine(Line7,USART_RXBUF);
			for(i=0;i<20;i++){
				USART_RXBUF[i] =' ';  //��ս�����
			}
			RXOVER = 0;
			USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
		}
	}
}

/**
  * @˵��     USART2 ���GPIO�͹���ģʽ����
  * @����     None 
  * @����ֵ   None
  */
void USART_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	NVIC_Configuration();
    //����USART2 TX���Ź���ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //����USART2 RX���Ź���ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //����2����ģʽ����
    USART_InitStructure.USART_BaudRate = 19200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2, ENABLE);
}

/**
  * @˵��     USART2�ַ������ͺ���
  * @����     str: ָ���ַ�����ָ��
  * @����ֵ   None
  */
void USART_SendString(int8_t *str)
{
    uint8_t index = 0;
    
    do
    {
        USART_SendData(USART2,str[index]);
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
        index++;        
    }
    while(str[index] != 0);  //����ַ���������־
    
}

/**
  * @˵��     �����ж�����������
  * @����     None
  * @����ֵ   None
  */
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
/**
  * @˵��     ��ʱ����
  * @����     nTime: ��ʱʱ��
  * @����ֵ   None
  */
void Delay_Ms(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}
/******************************************END OF FILE*************************/
