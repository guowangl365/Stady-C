#include "stm32f10x.h"//f103оƬͷ�ļ�
#include "delay.h"
#include "stdio.h"
char uart_rev;
//���ڳ�ʼ��
void uart_init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
    //1.��Ӳ��ʱ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO,ENABLE);
    //2.����GPIO����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
   //3.����uart����
	  USART_InitStructure.USART_BaudRate = 115200;//������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//����λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//У��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
 
    USART_Init(USART1, &USART_InitStructure);

   
    /* ѡ���жϷ��� */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    
    /* �����жϲ��� */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//�ж�ͨ�� ����1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ��
    NVIC_Init(&NVIC_InitStructure);

    //ʹ�ܴ��ڵĽ����ж�
		 USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	 //4.ʹ�ܴ���
    USART_Cmd( USART1, ENABLE);
}

//ͨ�����ڷ����ַ���
void uart_send_string(char *p)
{
     while(*p != '\0')
		{
		
		   USART_SendData(USART1,*p);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) 
			{}
		   p++;
		}
}
//printf�ض���
//�ض���fput���������printf��������õ�
int fputc(int ch,FILE *f)
{
	//��������
		   USART_SendData(USART1,ch);
	
	//����Ƿ������
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
	
	return ch;

}
//�����ʼ��
void motor_init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;   
	//ʹ��(��)�˿�B��Ӳ��ʱ�ӣ����ǶԶ˿�B����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

   //����GPIO��Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_6 | GPIO_Pin_7;//PB5 PB8 PB9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//������Ӧ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//������������������������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB, GPIO_Pin_5);//�� PB5��� �ߵ�ƽ  �򿪵������
}
//ǰ��
void car_go(void)
{

    /*���������*/
	
	
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
//ǰ��
void car_left(void)
{

	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//�� PB8��� �ߵ�ƽ  
	GPIO_SetBits(GPIOB, GPIO_Pin_8);//�� PB9��� �͵�ƽ

}
void car_stop(void)
{

    /*���������*/
	
	
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);//�� PB8��� �ߵ�ƽ  
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);//�� PB9��� �͵�ƽ
	
	//��ת
	//GPIO_ResetBits(GPIOB, GPIO_Pin_8);//�� PB8��� �͵�ƽ  
	//GPIO_SetBits(GPIOB, GPIO_Pin_9);//�� PB9��� �ߵ�ƽ
	

	GPIO_ResetBits(GPIOB, GPIO_Pin_6);//�� PB6��� �ߵ�ƽ  
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);//�� PB7��� �͵�ƽ


	
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
int main()//���
{  

	motor_init();
  delay_init(); 
  uart_init();	
	while(1)
	{
	    
		  //�ȴ����ݴ������
    if(uart_rev == 'a')
		{
		   car_go();
		   //С��ǰ��
		  
		}
    if(uart_rev == 'b')
		{
		
		   //С��ֹͣ
		  car_stop();
		}
		if(uart_rev == '3')	
    {
			car_left();
		}			
			if(uart_rev == '2')	
    {
			car_right();
		}			
		if(uart_rev == 'c')	
    {
			car_back();
		}			
			if(uart_rev == 'd')	
    {
			car_circle();
		}			
	}
   
}
//�����жϷ�����
void USART1_IRQHandler(void)
{
   //����ж��Ƿ����ڷ���
	 if(USART_GetITStatus(USART1,USART_IT_RXNE)==1)
	 {
	     //ִ���ж�������� 
	    uart_rev = USART_ReceiveData( USART1);
		   USART_SendData(USART1,uart_rev);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) ;
	 }
   
   //����жϱ�־λ �Ա��ڽ�����һ���ж�

   USART_ClearITPendingBit(USART1,USART_IT_RXNE);

}



