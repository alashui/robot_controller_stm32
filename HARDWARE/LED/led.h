#ifndef _LED_H
#define _LED_H

#include "sys.h"

#define LED0 PEout(3)
#define LED1 PEout(4)
#define LED2 PGout(9)
#define LED_debug PEout(5)

void LED_Init(void);

#endif
