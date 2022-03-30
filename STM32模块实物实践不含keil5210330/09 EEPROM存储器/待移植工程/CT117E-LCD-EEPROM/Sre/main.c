/*******************************************************************************  
* �ļ����ƣ�EEPROM��дʵ��
* ʵ��Ŀ�ģ�1.����EEPROM AT24C02�Ĳ�������
*           2.����I2C����Э���ͨѶԭ��
* ����˵����1.��EEPROM 0xff��ַ��������dat,++dat������д��0xff��ַ
*           2.ͨ��LCD��ʾ0xff��ַ�洢������,ÿ�θ�λ����ֵ��1
* ���ڰ汾��2011-9-19/V1.0a 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "lcd.h"
#include "stdio.h"
#include "i2c.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t TimingDelay = 0;
/* Private function prototypes -----------------------------------------------*/
void Delay_Ms(uint32_t nTime);
uint8_t x24c02_read(uint8_t address);
void x24c02_write(uint8_t address,uint8_t info);
/* Private functions ---------------------------------------------------------*/

/**
  * @˵��     ������
  * @����     None 
  * @����ֵ   None
  */
int main(void)
{
	uint8_t temp;
	uint8_t string[20];
	
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

	LCD_DisplayStringLine(Line1,"      I2C DEMO      ");
	LCD_DisplayStringLine(Line3,"     AT24C02 R/W    ");

	LCD_SetTextColor(Blue);
	LCD_SetBackColor(White);

	i2c_init();	
	
	temp = x24c02_read(0xff);
	Delay_Ms(2);
	x24c02_write(0xff,++temp);
	Delay_Ms(2);
	
	sprintf(string,"%s%d","ADDR:0xFF,VAL:",temp);
	LCD_DisplayStringLine(Line6,string);
		
    while(1){			
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
