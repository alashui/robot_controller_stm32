#include "iwdg.h"
#include "time_base.h"
#include "delay.h"
#include "led.h"
#include "usart1.h"
#include "pwm.h"
#include "motor.h" 
#include "encoder.h"




int main(void)
{
	
	IWDG_Init(4,500); //与分频数为64,重载值为500,溢出时间为1s
	
	My_USART1_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	delay_init(168);
	Motor_Init();
	
	
//产生PWM波	
	TIM3_PWM_Init(999,20); //84M/21=4Mhz的计数频率,重装载值1000，所以PWM频率为 4M/1000=4Khz.
//用作任务控制的时基	
	TIM5_Int_Init(1000-1,84-1); //定时器时钟84M，分频系数84，所以84M/84=1MKhz的计数频率，计数1000次为1ms 
	
	//ExtiIO_Init();
	//EXTIX_Init();
 
	
//利用定时器计数模式对编码器脉冲计数//
	TIM2_External_Clock_CountingMode(); //左编码器计数 
	TIM4_External_Clock_CountingMode(); //又编码器计数	

	speed_set(LeftSpeed_set,RightSpeed_set);
	
	while(1)
	{	
		
		IWDG_ReloadCounter();//看门口计数器重载
		
		
		instruction_control();	//根据串口接收的数据（线速度和旋转速度）来控制左右轮的速度
		
		//Serial_debugging();
		
		
		
		
		if (Time10ms_flag ==1)
		 {
				Time10ms_flag =0;
			
				LED1=!LED1; //DS1翻转
				LED_debug = !LED_debug;
			 
			// 从编码器读出的速度(码盘100格，减速比45:1，轮子周长250mm)
			// speed = count/(100*45)  * 250mm /0.01s=count*5.556mm/s					 			  
				LeftSpeed_read =LeftCode_count*0.005556;    //m/s  
				RightSpeed_read =RightCode_count*0.005556;  //m/s 	
				 
				if(LeftSpeed_set < 0) LeftSpeed_read = (-1)* LeftSpeed_read;
				if(RightSpeed_set < 0) RightSpeed_read = (-1)* RightSpeed_read;
			 
				speed_PIDcontrol();
			
			
				Send_Data.Float_RAM.hander = (float)15.5;
				Send_Data.Float_RAM.v = 0.5 * (LeftSpeed_read  + RightSpeed_read );
				Send_Data.Float_RAM.w = (RightSpeed_read  - LeftSpeed_read) * 10.363; //WIDTH_LR =  0.193; 2* (1/0.193)=10.363
				uart1SendChars(Send_Data.buf,12);
				
			  //printf("%f,%f,%f,%f,%d,%f,%f,%f \r\n",LeftSpeed_set,LeftSpeed_read,RightSpeed_set,RightSpeed_read,LeftPWM_val,LeftSpeed_Ek,LeftSpeed_Ek_1,LeftSpeed_Ek_2);
		 }
		

	
	}
	
}

