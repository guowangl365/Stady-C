#include "stm32f10x.h"
#include "led.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @˵��     ������
  * @����     None 
  * @����ֵ   None
  */
int main(void)
{
    unsigned int i;
    
    LED_Init();
    LED_Control(LEDALL,0);//�ر�����LED��
	
    while(1){
        LED_Control(LED6,1);//�ѸĶ˿�C14
        for(i=0x3fffff; i>0; i--);
        LED_Control(LED6,0);
        for(i=0x3fffff; i>0; i--);
        
		LED_Control(LED7,1); //�ѸĶ˿�C15
        for(i=0x3fffff; i>0; i--);
        LED_Control(LED7,0);
        for(i=0x3fffff; i>0; i--);
    }          //LED0��LED1��������˸��
}
