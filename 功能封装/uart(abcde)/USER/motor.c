#include "motor.h"


//GPIO �ṹ���ʼ��
//static GPIO_InitTypeDef GPIO_InitStructure;
//�����ʼ��
void motor_init(void)
	
{
	static GPIO_InitTypeDef GPIO_InitStructure;
	
   	//ʹ��(��)�˿�B��Ӳ��ʱ�ӣ����ǶԶ˿�B����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

   //����GPIO��Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_6 | GPIO_Pin_7;//PB5 PB8 PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//������Ӧ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//������������������������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
/*���������*/
	GPIO_SetBits(GPIOB, GPIO_Pin_5);//�� PB5��� �ߵ�ƽ  �򿪵������
}
//ǰ��
void car_go(void)
{

    
	
	//��ת
	GPIO_SetBits(GPIOB, GPIO_Pin_8);//�� PB8��� �ߵ�ƽ  
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//�� PB9��� �͵�ƽ
	
	//��ת
	//GPIO_ResetBits(GPIOB, GPIO_Pin_8);//�� PB8��� �͵�ƽ  
	//GPIO_SetBits(GPIOB, GPIO_Pin_9);//�� PB9��� �ߵ�ƽ
	
  	
	//��ת
	GPIO_SetBits(GPIOB, GPIO_Pin_6);//�� PB6��� �ߵ�ƽ  
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//�� PB7��� �͵�ƽ


}
void car_back(void)
{
      /*���������*/
//	GPIO_SetBits(GPIOB, GPIO_Pin_5);//�� PB5��� �ߵ�ƽ  �򿪵������
  //��ת
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);//�� PB8��� �͵�ƽ  
	GPIO_SetBits(GPIOB, GPIO_Pin_9);//�� PB9��� �ߵ�ƽ
	
	  //��ת
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//�� PB6��� �͵�ƽ  
	GPIO_SetBits(GPIOB, GPIO_Pin_7);//�� PB7��� �ߵ�ƽ

}
void car_left(void)
{
                GPIO_SetBits(GPIOB, GPIO_Pin_8);
                GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}

void car_right(void)
{
                GPIO_SetBits(GPIOB, GPIO_Pin_6);	
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);


}
void car_circle(void)
{
    
                GPIO_SetBits(GPIOB, GPIO_Pin_8);
                GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);

}
void car_stop(void)
{
   GPIO_ResetBits(GPIOB, GPIO_Pin_8);//�� PB8��� �͵�ƽ  
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//�� PB9��� �ߵ�ƽ
	
	  //��ת
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//�� PB6��� �͵�ƽ  
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//�� PB7��� �ߵ�ƽ


}

