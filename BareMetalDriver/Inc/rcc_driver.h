#ifndef RCC_DRIVER_H_
#define RCC_DRIVER_H_
#include<stdint.h>
#include "stm32f411xx.h"

extern uint16_t AHB_Prescaler[8];
extern uint16_t APB1_Prescaler[4];
uint32_t RCC_GetPLLOutputClock(void);
uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);
#endif /* RCC_DRIVER_H_ */
