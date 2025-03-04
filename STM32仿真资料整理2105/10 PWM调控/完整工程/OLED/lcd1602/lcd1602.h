#ifndef __LCD1602_H
#define __LCD1602_H	 
#include "sys.h"

//1602Һ��ָ��/����ѡ������
#define	LCD_RS_Set()	GPIO_SetBits(GPIOC, GPIO_Pin_10)
#define	LCD_RS_Clr()	GPIO_ResetBits(GPIOC, GPIO_Pin_10)

//1602Һ����д����
#define	LCD_RW_Set()	GPIO_SetBits(GPIOC, GPIO_Pin_11)
#define	LCD_RW_Clr()	GPIO_ResetBits(GPIOC, GPIO_Pin_11)

//1602Һ��ʹ������
#define	LCD_EN_Set()	GPIO_SetBits(GPIOC, GPIO_Pin_12)
#define	LCD_EN_Clr()	GPIO_ResetBits(GPIOC, GPIO_Pin_12)

//1602Һ�����ݶ˿�	PA0~7
#define	DATAOUT(x)	GPIO_Write(GPIOC, x)

void GPIO_Configuration(void);
void LCD1602_Wait_Ready(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void LCD1602_ClearScreen(void);
void LCD1602_Set_Cursor(u8 x, u8 y);
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);

#endif

