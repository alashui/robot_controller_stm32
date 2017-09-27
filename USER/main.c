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
	
	IWDG_Init(4,500); //���Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s
	
	My_USART1_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	delay_init(168);
	Motor_Init();
	
	
//����PWM��	
	TIM3_PWM_Init(999,20); //84M/21=4Mhz�ļ���Ƶ��,��װ��ֵ1000������PWMƵ��Ϊ 4M/1000=4Khz.
//����������Ƶ�ʱ��	
	TIM5_Int_Init(1000-1,84-1); //��ʱ��ʱ��84M����Ƶϵ��84������84M/84=1MKhz�ļ���Ƶ�ʣ�����1000��Ϊ1ms 
	
	//ExtiIO_Init();
	//EXTIX_Init();
 
	
//���ö�ʱ������ģʽ�Ա������������//
	TIM2_External_Clock_CountingMode(); //����������� 
	TIM4_External_Clock_CountingMode(); //�ֱ���������	

	speed_set(LeftSpeed_set,RightSpeed_set);
	
	while(1)
	{	
		
		IWDG_ReloadCounter();//���ſڼ���������
		
		
		instruction_control();	//���ݴ��ڽ��յ����ݣ����ٶȺ���ת�ٶȣ������������ֵ��ٶ�
		
		//Serial_debugging();
		
		
		
		
		if (Time10ms_flag ==1)
		 {
				Time10ms_flag =0;
			
				LED1=!LED1; //DS1��ת
				LED_debug = !LED_debug;
			 
			// �ӱ������������ٶ�(����100�񣬼��ٱ�45:1�������ܳ�250mm)
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

