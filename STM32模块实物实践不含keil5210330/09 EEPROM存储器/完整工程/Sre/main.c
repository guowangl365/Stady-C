#include "stm32f10x.h"
#include "stdio.h"
//#include "led.h"
#include "delay.h"
#include "oled.h"
#include "User_Oled.h"
#include "bmp.h"
#include "i2c.h"
 
uint8_t x24c02_read(uint8_t address);
void x24c02_write(uint8_t address,uint8_t info);

int main(void)
{
	uint8_t temp;
	uint8_t string[20];
	
 	SysTick_Config1(SystemCoreClock/1000);
 
  OLED_Init();
//  LED_Config();
	  OLED_P8x16Str(0,0,"   I2C DEMO  ");
		OLED_P8x16Str(0,2,"  AT24C02 R/W");		
		//OLED_P8x16Str(0,6,"Computer Depart");	
	
	i2c_init();	
	temp = x24c02_read(0xff);
	delay_ms(2);
	x24c02_write(0xff,++temp);
	delay_ms(2);
	
	sprintf(string,"%s%d","ADDR:0xFF,VAL:",temp);
	OLED_P8x16Str(0,4,string);
	while(1)
	{
		
	
		

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
 
 
