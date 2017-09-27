#include "encoder.h"
#include "sys.h"


	u16 LeftCode_count=0;				//������������
	u16 RightCode_count=0;
	

/*�����ֱ�������������������أ�PB7*/
void TIM4_External_Clock_CountingMode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 //   TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_TIM4); //PB7����λ��ʱ��5
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_DeInit(TIM4);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; /*��ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
                                                                            ʹ�õĲ���Ƶ��֮��ķ�Ƶ��Ϊ1*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM4, &TIM_TimeBaseStructure); // Time base configuration 
   

                            
		TIM_TIxExternalClockConfig(TIM4,TIM_TIxExternalCLK1Source_TI2,TIM_ICPolarity_Rising,0);
		TIM_SetCounter(TIM4, 0);   // ���������CNT
		TIM_Cmd(TIM4,ENABLE); 
}

/*�����ֱ�������������������أ�PB3*/
void TIM2_External_Clock_CountingMode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 //   TIM_ICInitTypeDef  TIM_ICInitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2); //PB7����λ��ʱ��5
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
    TIM_TimeBaseStructure.TIM_Prescaler = 0x00;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; /*��ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
                                                                            ʹ�õĲ���Ƶ��֮��ķ�Ƶ��Ϊ1*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM2, &TIM_TimeBaseStructure); // Time base configuration 
   
                            
		TIM_TIxExternalClockConfig(TIM2,TIM_TIxExternalCLK1Source_TI2,TIM_ICPolarity_Rising,0);
		TIM_SetCounter(TIM2, 0);   // ���������CNT
		TIM_Cmd(TIM2,ENABLE); 
}



