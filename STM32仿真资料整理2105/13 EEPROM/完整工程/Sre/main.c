#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "lcd1602.h"

#include "i2c.h"
 
#define KEY_ON	1
#define KEY_OFF	0
 
uint8_t x24c02_read(uint8_t address);
void x24c02_write(uint8_t address,uint8_t info);

int main(void)
{
	uint8_t temp;
	uint8_t string[20];
	
 	SysTick_Config(SystemCoreClock/1000);
 GPIO_Configuration();
  LCD1602_Init();
//  LED_Config();
//	  LCD1602_Show_Str(0,0,"   I2C DEMO  ");
		LCD1602_Show_Str(0,0,"  AT24C02 R/W");		
		//OLED_P8x16Str(0,6,"Computer Depart");	
	
	i2c_init();	
	temp = x24c02_read(0xff);
	delay_ms(2);
	//x24c02_write(0xff,++temp);
	//delay_ms(2);
	
	sprintf(string,"%s%d","ADDR:0xFF,VAL:",temp);
	LCD1602_Show_Str(0,2,string);
	while(1)
	{
		
		if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))//�жϰ�������
		{
			delay_ms(2);
			if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15))
			{
				x24c02_write(0xff,++temp);
			                delay_ms(2);
				
				temp = x24c02_read(0xff);
				delay_ms(2);
				sprintf(string,"%s%d","ADDR:0xFF,VAL:",temp);
				LCD1602_Show_Str(0,2,string);
				while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15));//�ȴ������ɿ�
			}
		}
		

	}
}
 

/**
  * @˵��     ��AT24C02ָ����ַ����һ���ֽ�����
  * @����     address:AT24C02�ڲ��洢��ַ
  * @����ֵ   val:��������
  */
uint8_t x24c02_read(uint8_t address)
{
	unsigned char val;
	
	I2CStart(); 
	I2CSendByte(0xa0);
	I2CWaitAck(); 
	
	I2CSendByte(address);
	I2CWaitAck(); 
	
	I2CStart();
	I2CSendByte(0xa1); 
	I2CWaitAck();
	val = I2CReceiveByte(); 
	I2CWaitAck();
	I2CStop();
	
	return(val);
}

/**
  * @˵��     ��AT24C02ָ����ַд��һ���ֽ�����
  * @����     address:AT24C02�ڲ��洢��ַ
  * @����     info:д������
  * @����ֵ   None
  */
void x24c02_write(unsigned char address,unsigned char info)
{
	I2CStart(); 
	I2CSendByte(0xa0); 
	I2CWaitAck(); 
	I2CSendByte(address);	
	I2CWaitAck(); 
	I2CSendByte(info); 
	I2CWaitAck(); 
	I2CStop();
}
 
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);       
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;                      
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //������û�а���ʱ��IO�ڼ��Ϊ�ߵ�ƽ��Ϊ��������ģʽ������IO��������ӣ�Ϊ�͵�ƽ   
//  GPIO_InitStructure.GPIO_Speed =    GPIO_Speed_50MHz; //�밴��������IO��Ϊ���룬����Ҫ���ýӿ��ٶȣ�ֻ���������
	GPIO_Init(GPIOB,&GPIO_InitStructure) ; 

}


