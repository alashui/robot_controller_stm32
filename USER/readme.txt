/***************************************************************************

项目名称：机器人底层电机控制

版本信息：V01

日期：2017.3.30

功能：和上位机进行串口通讯，根据上位机的指令，控制电机的速度，电机速度采用PID调节

硬件信息：


 1.电机驱动控制（L298N）逻辑端口
	#define I1 PAout(15)
	#define I2 PAout(5)
	#define I3 PGout(3)
	#define I4 PGout(4)
 2.PWM输出端	
	左轮：PB4
	右轮：PB5
 3.轮子尺寸
	#define WIDTH_LR   0.193   //两轮间距离193mm
	#define R_WHEEL    0.08    //轮子直径80mm
	#define C_WHEEL    0.25    //轮子周长250mm
 4.编码器
	左轮 ： PB7
	右轮 ： PB3
 5.串口
    A9，A10
 6.led灯（调试用）
	#define LED0 PEout(3)
	#define LED1 PEout(4)
	#define LED2 PGout(9)



软件信息：
 
    文件			函数								函数描述			
	
	main.c 		    main(void)							主函数，初始化（看门狗，中断分组，时钟，LED，
														电机端口，PWM，时基函数，编码器计数器，速度置零）
														无限循环：复位看门狗，读取速度值（10ms一次），接收指令，PID调速
	
	led.c			LED_Init()							初始化LED端口
	
	usart1.c		My_USART1_Init()					初始化串口，波特率，端口，校验等
					USART1_IRQHandler()					串口接受中断
					uart1SendChar()						发送单个字符
					uart1SendChars()					发送字符串
					USART1_Receive()					比较字符串
	
	pwm.c			TIM3_PWM_Init()						初始化PWM频率，输出端口
	
	motor.c			Motor_Init()						电机端口初始化
					speed_set( )						输入设置的速度值，输出PWM值和电机转动方向
					speed_PIDcontrol()					电机速度PID调节，增量式
					instruction_control()				根据串口接收的数据（线速度和旋转速度）来控制左右轮的速度
					Serial_debugging()					使用串口调试助手调试的测试程序
	
	time_base.c     TIM5_Int_Init()						通用定时器5中断初始化，用作任务控制的时基	
					TIM5_IRQHandler()					定时器5中断服务函数,1ms中断一次

	encoder.c		TIM2_External_Clock_CountingMode()	用TIM2计数模式对左轮编码器脉冲计数，上升沿，PB7	
					TIM4_External_Clock_CountingMode()	用TIM4计数模式对右轮编码器脉冲计数，上升沿，PB3
					
	iwdg.c			IWDG_Init()							独立看门狗初始化


*****************************************************************************/