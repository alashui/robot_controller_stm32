/***************************************************************************

��Ŀ���ƣ������˵ײ�������

�汾��Ϣ��V01

���ڣ�2017.3.30

���ܣ�����λ�����д���ͨѶ��������λ����ָ����Ƶ�����ٶȣ�����ٶȲ���PID����

Ӳ����Ϣ��


 1.����������ƣ�L298N���߼��˿�
	#define I1 PAout(15)
	#define I2 PAout(5)
	#define I3 PGout(3)
	#define I4 PGout(4)
 2.PWM�����	
	���֣�PB4
	���֣�PB5
 3.���ӳߴ�
	#define WIDTH_LR   0.193   //���ּ����193mm
	#define R_WHEEL    0.08    //����ֱ��80mm
	#define C_WHEEL    0.25    //�����ܳ�250mm
 4.������
	���� �� PB7
	���� �� PB3
 5.����
    A9��A10
 6.led�ƣ������ã�
	#define LED0 PEout(3)
	#define LED1 PEout(4)
	#define LED2 PGout(9)



�����Ϣ��
 
    �ļ�			����								��������			
	
	main.c 		    main(void)							����������ʼ�������Ź����жϷ��飬ʱ�ӣ�LED��
														����˿ڣ�PWM��ʱ�����������������������ٶ����㣩
														����ѭ������λ���Ź�����ȡ�ٶ�ֵ��10msһ�Σ�������ָ�PID����
	
	led.c			LED_Init()							��ʼ��LED�˿�
	
	usart1.c		My_USART1_Init()					��ʼ�����ڣ������ʣ��˿ڣ�У���
					USART1_IRQHandler()					���ڽ����ж�
					uart1SendChar()						���͵����ַ�
					uart1SendChars()					�����ַ���
					USART1_Receive()					�Ƚ��ַ���
	
	pwm.c			TIM3_PWM_Init()						��ʼ��PWMƵ�ʣ�����˿�
	
	motor.c			Motor_Init()						����˿ڳ�ʼ��
					speed_set( )						�������õ��ٶ�ֵ�����PWMֵ�͵��ת������
					speed_PIDcontrol()					����ٶ�PID���ڣ�����ʽ
					instruction_control()				���ݴ��ڽ��յ����ݣ����ٶȺ���ת�ٶȣ������������ֵ��ٶ�
					Serial_debugging()					ʹ�ô��ڵ������ֵ��ԵĲ��Գ���
	
	time_base.c     TIM5_Int_Init()						ͨ�ö�ʱ��5�жϳ�ʼ��������������Ƶ�ʱ��	
					TIM5_IRQHandler()					��ʱ��5�жϷ�����,1ms�ж�һ��

	encoder.c		TIM2_External_Clock_CountingMode()	��TIM2����ģʽ�����ֱ�������������������أ�PB7	
					TIM4_External_Clock_CountingMode()	��TIM4����ģʽ�����ֱ�������������������أ�PB3
					
	iwdg.c			IWDG_Init()							�������Ź���ʼ��


*****************************************************************************/