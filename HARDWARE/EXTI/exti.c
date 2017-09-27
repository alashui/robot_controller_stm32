#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "usart1.h"


//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	 
	//uart1SendChar(Cout_Lwheel01);
	
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	
/*�ⲿ�ж�2�������
void EXTI1_IRQHandler(void)
{
	
	 EXTI_ClearITPendingBit(EXTI_Line2);//���LINE1�ϵ��жϱ�־λ 
}
//�ⲿ�ж�3�������
void EXTI2_IRQHandler(void)
{
	
	 EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE2�ϵ��жϱ�־λ  
}
//�ⲿ�ж�4�������
void EXTI3_IRQHandler(void)
{
	
	 EXTI_ClearITPendingBit(EXTI_Line4);//���LINE3�ϵ��жϱ�־λ  
}

*/	


void ExtiIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //�ⲿ�ж϶�Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
 
} 

	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);//PE2 ���ӵ��ж���0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);//PE3 ���ӵ��ж���1
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource2);//PE4 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);//PA0 ���ӵ��ж���3
	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	/* ����EXTI_Line2,3,4 
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line2 | EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//�ⲿ�ж�2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
*/	   
}












