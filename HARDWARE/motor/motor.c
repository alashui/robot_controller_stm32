#include "motor.h"
#include "sys.h"
#include "math.h"
#include "time_base.h"

	float LeftSpeed_read =0;     //从编码器读出的速度
	float RightSpeed_read =0;	
	
	float LeftSpeed_set =0;			//设置的速度
	float RightSpeed_set =0;
	
	u16 RightPWM_val,LeftPWM_val;	//PWM 占空比*10

//	float Proportion=100;//比例常数 Proportional Const
//	float Integral=150;//积分常数 Integral Const
//	float Derivative=10;//微分常数 Derivative Const


	float Proportion=13000;//比例常数 Proportional Const
	float Integral=1000;//积分常数 Integral Const
	float Derivative=1000;//微分常数 Derivative Const


//分别表示左轮速度当前偏差，上次偏差，上上次偏差
	float LeftSpeed_Ek=0,LeftSpeed_Ek_1=0,LeftSpeed_Ek_2=0;
//分别表示右轮速度当前偏差，上次偏差，上上次偏差
	float RightSpeed_Ek=0,RightSpeed_Ek_1=0,RightSpeed_Ek_2=0;
	
void Motor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA,GPIOC时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_15;         //I1、I2和I4对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                  //普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;             //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);                         //初始化GPIO 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	I1 = 0;
	I2 = 0;
	I3 = 0;
	I4 = 0;
	
}


//输入设置的速度值，输出PWM值和电机转动方向
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
					LeftPWM_val =(u16)(LeftSpeed * 2000);			 // 将速度换算为占空比 ,最大速度约0.55m/s	
			 }																	 								// 1000/0.55 =1818
				
		else
			 {
					I1 = 0;
					I2 = 1;
					LeftPWM_val = (u16)(LeftSpeed * 2000 * (-1));	 // 将速度换算为占空比  
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
					RightPWM_val =(u16)(RightSpeed * 2000);			 // 将速度换算为占空比 
			 }
		else
			 {
					I3 = 0;
					I4 = 1;
					RightPWM_val =(u16)(RightSpeed * 2000 * (-1));	 // 将速度换算为占空比 
				
			 }
	
		if(LeftPWM_val <= 0)
					LeftPWM_val=0;
		else if(LeftPWM_val >= 1000)
					LeftPWM_val=1000;  
		
		if(LeftPWM_val <= 0)
					LeftPWM_val=0;
		else if(RightPWM_val >= 1000)
					RightPWM_val=1000;
		
	TIM_SetCompare1(TIM3,LeftPWM_val);	 // 设置占空比 
  TIM_SetCompare2(TIM3,RightPWM_val);

}


//根据串口接收的数据（线速度和旋转速度）来控制左右轮的速度
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
//电机速度PID调节，增量式，由设置的速度值和读出的速度值产生偏差，计算得到新的PWM值
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
	//误差更新			 
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

		
		TIM_SetCompare1(TIM3,LeftPWM_val);	 // 设置占空比 
    TIM_SetCompare2(TIM3,RightPWM_val);

}

//使用串口调试助手调试
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
		
		//printf("读取的左轮速度：%f,%f,%f,%f \r\n",LeftSpeed_set,LeftSpeed_read,RightSpeed_set,RightSpeed_read);
		
		
	//	if (Time500ms_flag ==1)	
	//	{
	//		Time500ms_flag =0;
			
			//uart1SendChars(Read_Data.buf,12);
//			printf("左编码器读数：%d\r\n",LeftCode_count);
//			printf("右编码器读数：%d\r\n",RightCode_count);		
//			printf("                       \r\n");
//			printf("读取的左轮速度：%f m/s \r\n",LeftSpeed_read);
//			printf("读取的右轮速度：%f m/s \r\n",RightSpeed_read);
//			printf("                       \r\n");		
//			printf("设置的左轮速度：%f m/s \r\n",LeftSpeed_set);
//			printf("设置的右轮速度：%f m/s \r\n",RightSpeed_set);
//			printf("                       \r\n");
//			printf("设置PWM：%d  \r\n",LeftPWM_val);
//			printf("设置PWM：%d  \r\n",RightPWM_val);
//			printf("                       \r\n");
//			printf("                       \r\n");
//			printf("                       \r\n"); 
	
		//}
}





