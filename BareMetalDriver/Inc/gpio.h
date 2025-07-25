#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "stm32f411xx.h"

/*
 * @Generic marcos
 */

 #define SET 1
 #define RESET 0
 #define ENABLE 1
 #define DISABLE 0
 #define GPIO_PIN_SET 1
 #define GPIO_PIN_RESET 0
/*
 *@GPIO Mode
 */

#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3
//interrupt mode
#define GPIO_MODE_ITFT 4
#define GPIO_MODE_ITRT 5
#define GPIO_MODE_RFT 6

/*
 *@GPIO Output type
 */

#define GPIO_OT_PUSHPULL 0
#define GPIO_OT_OPENDRAIN 1

/*
 * @GPIO speed
 */

#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_FAST 2
#define GPIO_SPEED_HIGH 3

/*
 * @GPIO pull-up pull-down
 */

 /**********************************************************************************
 *  					Config structure of GPIO
 * *****************************************************************************/
typedef struct{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinOutputType;
    uint8_t GPIO_PullUpPullDown;
    uint8_t GPIO_AltFuncMode;
}GPIO_PinConfig_t;

/**********************************************************************************
*  						Handle structure of GPIO
* *****************************************************************************/
typedef struct{
    GPIO_RegDef_t *pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

/*******************************************************************
 *                  APIs Supported by GPIO driver
 ******************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber);
void GPIO_IRQInterruptConfiguration(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfiguration(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* GPIO_H_ */
