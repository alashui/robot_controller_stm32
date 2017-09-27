#ifndef _MOTOR_H
#define _MOTOR_H
#include "sys.h"
 
#include "usart1.h"
#include "pwm.h"
#include "motor.h" 
#include "encoder.h"





//电机驱动控制（L298N）逻辑端口
#define I1 PAout(15)
#define I2 PAout(5)
#define I3 PGout(3)
#define I4 PGout(4)


#define WIDTH_LR   0.193   //两轮间距离193mm
#define R_WHEEL    0.08    //轮子直径80mm
#define C_WHEEL    0.25    //轮子周长250mm

extern	float LeftSpeed_read ;     //从编码器读出的速度
extern	float RightSpeed_read ;	
	
extern	float LeftSpeed_set ;			//设置的速度
extern	float RightSpeed_set ;


extern	u16 RightPWM_val,LeftPWM_val;	//PWM 占空比*10


extern float LeftSpeed_Ek,LeftSpeed_Ek_1,LeftSpeed_Ek_2;


void Motor_Init(void);
void speed_set( float LeftSpeed,float RightSpeed);
void speed_PIDcontrol(void);
void instruction_control(void);

void Serial_debugging(void);

#endif
