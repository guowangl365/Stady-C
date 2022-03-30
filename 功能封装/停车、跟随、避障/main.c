#include "stm32f10x.h"//f103оƬͷ�ļ�
#include "delay.h"
#include "stdio.h"
char uart_rev;
//���ڳ�ʼ��
//#include "motor.h"


//GPIO �ṹ���ʼ��
static GPIO_InitTypeDef GPIO_InitStructure;
//�����ʼ��
void motor_init(void)
	
{
	//static GPIO_InitTypeDef GPIO_InitStructure;
	
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

//��ʼ��������ģ��
void sr04_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
	  //1.��Ӳ��ʱ��
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    //2.����GPIO����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
     GPIO_ResetBits( GPIOB, GPIO_Pin_11);	
}
//��ȡ������������
int get_distance(void)
{
    int n=0;
   //1.PB11���������ź� ����10us�ĸߵ�ƽ�ź�
	  GPIO_SetBits( GPIOB, GPIO_Pin_11);
	  delay_us(15);
    GPIO_ResetBits( GPIOB, GPIO_Pin_11);	

   //2.������뵽PB12������ģʽ���ĵ�ƽ�ź� 
		while(GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_12)!=1);
	
	 //3.��ȡecho�ߵ�ƽ������ʱ��
    while(GPIO_ReadInputDataBit( GPIOB, GPIO_Pin_12)!=0)
		{
		
		   delay_us(9);
        			
		   n++;
		    
		}

   // 4.�������
   return    3*n/2;


}
int main()//���
{  
  int distance;
	delay_init();
	sr04_init();
	uart_init();
	motor_init();
	 printf("sr04 test\n");
  	//car_go();//----------------------------------------------�Զ�ͣ��or�Զ�����
	while(1)
	{
	  
				distance =  get_distance();
				printf("sr04 get distance is  %d mm\n",distance);	
				delay_ms(1000);
		if(0<distance&&distance<90) {car_back();delay_ms(1000);}//--------------------------------�Զ�����car_left();delay_ms(1000);car_stop();
		else if(90<distance&&distance<100){ car_stop();}//------------------------------------�Զ�����
		else if(100<distance){ car_go();delay_ms(1000);car_stop();}//---------------------------�Զ�����
   /* if(distance<=100) c=0;
				else if(100<=distance<=200) c=1;
	      else c=2;
		switch(c){
				case'0':car_back();break;
				.case'1':car_stop();break;
				case'2':car_go();break;
	           }*/	  
		//if(distance<300){ car_stop();}//-------------------------�Զ�ͣ��
	 // if(distance<300){ car_stop();delay_ms(1000);car_back();delay_ms(1000);car_left();delay_ms(1000);delay_ms(1000);car_go();}//---�Զ�����
		//else if(100<distance){ car_go();delay_ms(1000);car_stop();}
		//else if(90<distance&&distance<100){ car_stop();}
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

