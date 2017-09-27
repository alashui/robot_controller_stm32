#ifndef _MOTOR_H
#define _MOTOR_H
#include "sys.h"
 
#include "usart1.h"
#include "pwm.h"
#include "motor.h" 
#include "encoder.h"





//����������ƣ�L298N���߼��˿�
#define I1 PAout(15)
#define I2 PAout(5)
#define I3 PGout(3)
#define I4 PGout(4)


#define WIDTH_LR   0.193   //���ּ����193mm
#define R_WHEEL    0.08    //����ֱ��80mm
#define C_WHEEL    0.25    //�����ܳ�250mm

extern	float LeftSpeed_read ;     //�ӱ������������ٶ�
extern	float RightSpeed_read ;	
	
extern	float LeftSpeed_set ;			//���õ��ٶ�
extern	float RightSpeed_set ;


extern	u16 RightPWM_val,LeftPWM_val;	//PWM ռ�ձ�*10


extern float LeftSpeed_Ek,LeftSpeed_Ek_1,LeftSpeed_Ek_2;


void Motor_Init(void);
void speed_set( float LeftSpeed,float RightSpeed);
void speed_PIDcontrol(void);
void instruction_control(void);

void Serial_debugging(void);

#endif
