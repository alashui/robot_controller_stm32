#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
 	
	
/*	
�������ӿڣ���PB3,��PB7
*/
extern	u16 LeftCode_count;				//������������
extern	u16 RightCode_count;
	

void TIM2_External_Clock_CountingMode(void);
void TIM4_External_Clock_CountingMode(void);

#endif

