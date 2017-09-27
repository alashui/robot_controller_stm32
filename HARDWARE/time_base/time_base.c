#include "time_base.h"
#include "motor.h"
#include "led.h"

//u8 Time1ms_flag=0;
u8 Time10ms_flag=0;
u8 Time500ms_flag=0;

u16 Time1ms_count=0;
u16 Time10ms_count=0;


//通用定时器5中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器5!

void TIM5_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM5,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//定时器5中断服务函数,1ms中断一次
void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET) //溢出中断
	{
		//Time1ms_flag =1; 

		Time1ms_count++;
		if (Time1ms_count==10)
			{
				Time1ms_count=0;
					
				LeftCode_count=TIM2->CNT;
				RightCode_count=TIM4->CNT; 
				TIM_SetCounter(TIM2, 0);
				TIM_SetCounter(TIM4, 0);			
					
				Time10ms_flag=1;
				
				Time10ms_count++;
				if (Time10ms_count==50)
						{
							Time10ms_count=0;
							Time500ms_flag=1;	
						}
			}

	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //清除中断标志位
}


