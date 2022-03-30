#include "stm32f10x.h"
#include "stdio.h"
#include "delay.h"
#include "lcd1602.h"


 int main(void)
 { int b;
	 float temp;
	 u8 string[20];
	 
	 void ADC1_GPIO_Config(void);
   void ADC_Config(void);
	SysTick_Config(SystemCoreClock/1000);

	GPIO_Configuration();   	 
	LCD1602_Init();	 
	LCD1602_Show_Str(1, 0, "PA1-ADC chnl 1");
	  
	ADC1_GPIO_Config();
  ADC_Config(); 
	 	 
	while(1)
	  {
			b=ADC_GetConversionValue(ADC1);
			temp=(float)b*(3.30/4095);//4095=2^12-1
			sprintf(string,"%s%.3f%s","ADC Value:",temp,"v");
			LCD1602_Show_Str(0, 2, string);
		}
				
	}

	
void ADC1_GPIO_Config(void)
	{
    GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE);	//ʹ��ADC1��GPIOCʱ��
 	  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//Ϊʲôû�����������������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	//ģ������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PC4
  }


void ADC_Config(void)
{
  ADC_InitTypeDef ADC_InitStructure;//ADC�ṹ�����//ע����һ�������ڱ���������Ҫ���ڿ�ִ������ǰ�棬����������Ҫ����ADC1_GPIO_Config();ǰ��
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1��ADC2�����ڶ���ģʽ
  ADC_InitStructure.ADC_ScanConvMode =	DISABLE; //ʹ��ɨ��
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADCת������������ģʽ
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���������ת��,��ʹ���ⲿ����
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ת�������Ҷ���
  ADC_InitStructure.ADC_NbrOfChannel = 1;//ת��ͨ��Ϊ1
  ADC_Init(ADC1, &ADC_InitStructure); //��ʼ��ADC
	
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
  //ADC1ѡ���ŵ�14,�ȼ�1,����ʱ��55.5������
  //ADC_DMACmd(ADC1, ENABLE);//ʹ��ADC1ģ��DMA
  ADC_Cmd(ADC1, ENABLE);//ʹ��ADC1
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//  ADC_ResetCalibration(ADC1); //����.����λ��.ADC1У׼�Ĵ���
//  while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
//  ADC_StartCalibration(ADC1);//��ʼADC1У׼
//  while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���
//  ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ��ADC1�����ʼת��
}
	
	
 
