#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f411xx.h"
#include "rcc_driver.h"



/*
 *@USART_Mode
 */
#define USART_TX_ONLY 0
#define USART_RX_ONLY 1
#define USART_TX_RX 2

/*
 * @USART Event
 */
#define USART_EVENT_TX_CMPLT 0
#define USART_EVENT_RX_CMPLT 1
#define USART_EVENT_CTS 2
#define USART_EVENT_IDLE 3
#define USART_EVENT_ORE 4
#define USART_ERREVENT_FE 5
#define USART_ERREVENT_NE 5
#define USART_ERREVENT_ORE 6

/*
 * @USART_Baud
*/
#define USART_BAUD_1200 1200
#define USART_BAUD_2400 2400
#define USART_BAUD_4800 4800
#define USART_BAUD_9600 9600
#define USART_BAUD_19200 19200
#define USART_BAUD_38400 38400
#define USART_BAUD_57600 57600
#define USART_BAUD_115200 115200
#define USART_BAUD_230400 230400
#define USART_BAUD_460800 460800
#define USART_BAUD_921600 921600

/*
 * @USART_ParityControl
 */
#define USART_NO_PARITY 0
#define USART_EVEN_PARITY 1
#define USART_ODD_PARITY 2

/*
 * @USART_WorldLenght
 */
#define USART_DATA_5 5
#define USART_DATA_6 6
#define USART_DATA_7 7
#define USART_DATA_8 8
#define USART_DATA_9 9

/*
 * @USART_NoOfStopBits
 */
#define USART_STOPBITS_1 0
#define USART_STOPBITS_0_5 1
#define USART_STOPBITS_2 2
#define USART_STOPBITS_1_5 3

/*
 * @USART_HardwareFlowControl
 */
#define USART_HWCONTROL_NONE 0
#define USART_HWCONTROL_RTS 1
#define USART_HWCONTROL_CTS 2
#define USART_HWCONTROL_CTS_RTS 3

/*
 * USART related status flags
 */
#define USART_FLAG_PE (1<<USART_SR_PE)
#define USART_FLAG_FE (1<<USART_SR_FE)
#define USART_FLAG_NF (1<<USART_SR_NF)
#define USART_FLAG_ORE (1<<USART_SR_ORE)
#define USART_FLAG_IDLE (1<<USART_SR_IDLE)
#define USART_FLAG_RXNE (1<<USART_SR_RXNE)
#define USART_FLAG_TC (1<<USART_SR_TC)
#define USART_FLAG_TXE (1<<USART_SR_TXE)
#define USART_FLAG_LBD (1<<USART_SR_LBD)
#define USART_FLAG_CTS (1<<USART_SR_CTS)

/*
 * USART state
 */
#define USART_READY 0
#define USART_BUSY_IN_TX 1
#define USART_BUSY_IN_RX 2

 /**********************************************************************************
 *  					config structure of USART
 * *****************************************************************************/
typedef struct {
    uint32_t USART_Mode; /* */
    uint32_t USART_Baud;
    uint32_t USART_NoOfStopBits;
    uint32_t USART_WorlLenght;
    uint32_t USART_ParityControl;
    uint32_t USART_HardwareFlowControl;
}USART_Config_t;

 /**********************************************************************************
 *  					handle structure of USART
 * *****************************************************************************/

typedef struct {
    USART_RegDef_t *pUSARTx;        /*this hold the base address of USARTx peripheral*/
    USART_Config_t USART_Config;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxState;
    uint8_t RxState;
    uint8_t* pTxBuffer;
    uint8_t* pRxBuffer;
}USART_Handle_t;



 /*******************************************************************************************
 *                              API supported by USART driver
 * ******************************************************************************************/

/*
 * Clock Setup
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/*
 * Init and Deinit
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_Handle_t *pUSARTHandle);

/*
 * USART send ànd receive
*/
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t len);

uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t len);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

void USART_IRQHandling(USART_Handle_t *pUSARTHandle);

/*
 * Other Peripheral Control APIs
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx , uint32_t FlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);


/*
 * Application callbacks
*/
__attribute((weak)) void USART_ApplicationEventCallback(USART_Handle_t *pHandle, uint8_t AppEv);
//weak to allow application writer to override the default weak implementation
#endif /* UART_H_ */
