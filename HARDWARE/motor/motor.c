#include "motor.h"
#include "sys.h"
#include "math.h"
#include "time_base.h"

	float LeftSpeed_read =0;     //�ӱ������������ٶ�
	float RightSpeed_read =0;	
	
	float LeftSpeed_set =0;			//���õ��ٶ�
	float RightSpeed_set =0;
	
	u16 RightPWM_val,LeftPWM_val;	//PWM ռ�ձ�*10

//	float Proportion=100;//�������� Proportional Const
//	float Integral=150;//���ֳ��� Integral Const
//	float Derivative=10;//΢�ֳ��� Derivative Const


	float Proportion=13000;//�������� Proportional Const
	float Integral=1000;//���ֳ��� Integral Const
	float Derivative=1000;//΢�ֳ��� Derivative Const


//�ֱ��ʾ�����ٶȵ�ǰƫ��ϴ�ƫ����ϴ�ƫ��
	float LeftSpeed_Ek=0,LeftSpeed_Ek_1=0,LeftSpeed_Ek_2=0;
//�ֱ��ʾ�����ٶȵ�ǰƫ��ϴ�ƫ����ϴ�ƫ��
	float RightSpeed_Ek=0,RightSpeed_Ek_1=0,RightSpeed_Ek_2=0;
	
void Motor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOA,GPIOCʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_15;         //I1��I2��I4��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                  //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;             //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //����
  GPIO_Init(GPIOA, &GPIO_InitStructure);                         //��ʼ��GPIO 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	I1 = 0;
	I2 = 0;
	I3 = 0;
	I4 = 0;
	
}


//�������õ��ٶ�ֵ�����PWMֵ�͵��ת������
void speed_set( float LeftSpeed,float RightSpeed)
{
		if (LeftSpeed_set==0)
			 {
				   I1 = 0;
				   I2 = 0;
					 LeftPWM_val=0;
			 }
		else if (LeftSpeed_set>0)
			 {
					I1 = 1;
					I2 = 0;
					LeftPWM_val =(u16)(LeftSpeed * 2000);			 // ���ٶȻ���Ϊռ�ձ� ,����ٶ�Լ0.55m/s	
			 }																	 								// 1000/0.55 =1818
				
		else
			 {
					I1 = 0;
					I2 = 1;
					LeftPWM_val = (u16)(LeftSpeed * 2000 * (-1));	 // ���ٶȻ���Ϊռ�ձ�  
			 }
			
			
		if ( RightSpeed_set==0)
			 {
					I3 = 0;
					I4 = 0;	
				  RightPWM_val = 0;
			 }
		else if (RightSpeed_set>0)
			 {
					I3 = 1;
					I4 = 0;
					RightPWM_val =(u16)(RightSpeed * 2000);			 // ���ٶȻ���Ϊռ�ձ� 
			 }
		else
			 {
					I3 = 0;
					I4 = 1;
					RightPWM_val =(u16)(RightSpeed * 2000 * (-1));	 // ���ٶȻ���Ϊռ�ձ� 
				
			 }
	
		if(LeftPWM_val <= 0)
					LeftPWM_val=0;
		else if(LeftPWM_val >= 1000)
					LeftPWM_val=1000;  
		
		if(LeftPWM_val <= 0)
					LeftPWM_val=0;
		else if(RightPWM_val >= 1000)
					RightPWM_val=1000;
		
	TIM_SetCompare1(TIM3,LeftPWM_val);	 // ����ռ�ձ� 
  TIM_SetCompare2(TIM3,RightPWM_val);

}


//���ݴ��ڽ��յ����ݣ����ٶȺ���ת�ٶȣ������������ֵ��ٶ�
void instruction_control(void)
{
	if(USART_RX_STA&0x8000)
	{		
			if (Read_Data.Float_RAM.hander == (float)15.5)
			{
				
				LeftSpeed_set = (Read_Data.Float_RAM.v - 0.5* WIDTH_LR * Read_Data.Float_RAM.w);  //  m/s
				RightSpeed_set =(Read_Data.Float_RAM.v + 0.5* WIDTH_LR * Read_Data.Float_RAM.w);  //  m/s
				speed_set( LeftSpeed_set,RightSpeed_set);
			
			}
			USART_RX_STA=0;
	}
}
//����ٶ�PID���ڣ�����ʽ�������õ��ٶ�ֵ�Ͷ������ٶ�ֵ����ƫ�����õ��µ�PWMֵ
void speed_PIDcontrol()
{
	  float temp_lspeed_read,temp_rspeed_read,temp_lspeed_set,temp_rspeed_set;
	
	  temp_lspeed_read = (LeftSpeed_read  < 0) ? LeftSpeed_read * (-1) : LeftSpeed_read;
	  temp_rspeed_read = (RightSpeed_read  < 0) ? RightSpeed_read * (-1) : RightSpeed_read;
	  temp_lspeed_set = (LeftSpeed_set  < 0) ? LeftSpeed_set * (-1) : LeftSpeed_set;
	  temp_rspeed_set = (RightSpeed_set  < 0) ? RightSpeed_set * (-1) : RightSpeed_set;
	
	  LeftSpeed_Ek = temp_lspeed_set - temp_lspeed_read;	
	  RightSpeed_Ek = temp_rspeed_set - temp_rspeed_read;

	
	  LeftPWM_val =(u16)(LeftPWM_val +

         Proportion*(LeftSpeed_Ek-LeftSpeed_Ek_1)+

         Integral*LeftSpeed_Ek+

         Derivative*(LeftSpeed_Ek  -  2 * LeftSpeed_Ek_1  +  LeftSpeed_Ek_2));
	
		RightPWM_val =(u16)(RightPWM_val +

         Proportion*(RightSpeed_Ek-RightSpeed_Ek_1)+

         Integral*RightSpeed_Ek+

         Derivative*(RightSpeed_Ek  -  2 * RightSpeed_Ek_1  +  RightSpeed_Ek_2));
	//������			 
		LeftSpeed_Ek_2 = LeftSpeed_Ek_1;
		LeftSpeed_Ek_1 = LeftSpeed_Ek;
		
		RightSpeed_Ek_2 = RightSpeed_Ek_1;
		RightSpeed_Ek_1 = RightSpeed_Ek;
		
		if(LeftPWM_val <= 0)
					LeftPWM_val=0;
		else if(LeftPWM_val >= 1000)
					LeftPWM_val=1000;
		
		if(RightPWM_val <= 0)
					RightPWM_val=0;
		else if(RightPWM_val >= 1000)
					RightPWM_val=1000;

		
		TIM_SetCompare1(TIM3,LeftPWM_val);	 // ����ռ�ձ� 
    TIM_SetCompare2(TIM3,RightPWM_val);

}

//ʹ�ô��ڵ������ֵ���
void Serial_debugging(void)
{		
		
		if(USART_RX_STA&0x8000)
		{		
			if (USART1_Receive("go"))
			{
				LeftSpeed_set = 0.25;
				RightSpeed_set = 0.25;

			}
			
			if (USART1_Receive("add"))
			{
				LeftSpeed_set += 0.02;
				RightSpeed_set += 0.02;
				if(LeftSpeed_set>=0.55) LeftSpeed_set=0.55;
				if(RightSpeed_set>=0.55) RightSpeed_set=0.55;
							
			}
			
			if (USART1_Receive("sub"))
			{
				LeftSpeed_set  -=0.02;
				RightSpeed_set -=0.02;
				if(RightSpeed_set<=-0.55) RightSpeed_set=-0.55;	
				if(LeftSpeed_set<=-0.55) LeftSpeed_set=-0.55;
			}
			if (USART1_Receive("stop"))
			{
				LeftSpeed_set = 0;
				RightSpeed_set = 0;			
			}
			speed_set(LeftSpeed_set,RightSpeed_set);
			USART_RX_STA=0;
		}								
		
		//printf("��ȡ�������ٶȣ�%f,%f,%f,%f \r\n",LeftSpeed_set,LeftSpeed_read,RightSpeed_set,RightSpeed_read);
		
		
	//	if (Time500ms_flag ==1)	
	//	{
	//		Time500ms_flag =0;
			
			//uart1SendChars(Read_Data.buf,12);
//			printf("�������������%d\r\n",LeftCode_count);
//			printf("�ұ�����������%d\r\n",RightCode_count);		
//			printf("                       \r\n");
//			printf("��ȡ�������ٶȣ�%f m/s \r\n",LeftSpeed_read);
//			printf("��ȡ�������ٶȣ�%f m/s \r\n",RightSpeed_read);
//			printf("                       \r\n");		
//			printf("���õ������ٶȣ�%f m/s \r\n",LeftSpeed_set);
//			printf("���õ������ٶȣ�%f m/s \r\n",RightSpeed_set);
//			printf("                       \r\n");
//			printf("����PWM��%d  \r\n",LeftPWM_val);
//			printf("����PWM��%d  \r\n",RightPWM_val);
//			printf("                       \r\n");
//			printf("                       \r\n");
//			printf("                       \r\n"); 
	
		//}
}





