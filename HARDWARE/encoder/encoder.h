#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"
 	
	
/*	
±àÂëÆ÷½Ó¿Ú£º×óPB3,ÓÒPB7
*/
extern	u16 LeftCode_count;				//±àÂëÆ÷Âö³åÊı
extern	u16 RightCode_count;
	

void TIM2_External_Clock_CountingMode(void);
void TIM4_External_Clock_CountingMode(void);

#endif

