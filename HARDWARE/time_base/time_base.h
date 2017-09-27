#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#include "encoder.h"


//extern u8 Time1ms_flag;
extern u8 Time10ms_flag;
extern u8 Time500ms_flag;

extern u16 Time1ms_count;
extern u16 Time10ms_count;

void TIM5_Int_Init(u16 arr,u16 psc);
void TIM5_IRQHandler(void);
#endif
