#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include "stm32f411xx.h"

/*
 * SPI Application State
 */
#define SPI_READY 0
#define SPI_BUSY_IN_TX 1
#define SPI_BUSY_IN_RX 2

/*
 * SPI Application Event
*/
#define SPI_EVENT_TX_CMPLT 1
#define SPI_EVENT_RX_CMPLT 2
#define SPI_EVENT_OVR_ERROR 3


/*
 * SPI status flags definition
*/
#define SPI_TXE_FLAG (1<<SPI_SR_TXE)
#define SPI_RXNE_FLAG (1<<SPI_SR_RXNE)
#define SPI_BUSY_FLAG (1<<SPI_SR_BSY)

/*
 * @SPI_DeviceMode
 */

#define SPI_MODE_MASTER 0
#define SPI_MODE_SLAVE 1

/*
 * @SPI_BusConfig
 */

#define SPI_BUS_CONFIG_FD 0 //full duplex
#define SPI_BUS_CONFIG_HD 1 //half duplex
#define SPI_BUS_CONFIG_SIMPLEX_TXONLY 2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY 3

/*
 * @SPI_SclkSpeed
 */

#define SPI_SCLK_SPEED_DIV2 0
#define SPI_SCLK_SPEED_DIV4 1
#define SPI_SCLK_SPEED_DIV8 2
#define SPI_SCLK_SPEED_DIV16 3

/*
 * @SPI_DFF
 */

#define SPI_DFF_8BIT 0
#define SPI_DFF_16BIT 1

/*
 * @SPI_CPOL
 */

#define SPI_CPOL_LOW 0
#define SPI_CPOL_HIGH 1

/*
 * @SPI_CPHA
 */

#define SPI_CPHA_LOW 0
#define SPI_CPHA_HIGH 1

/*
 * @SPI_SSM
 */

#define SPI_SSM_DISABLE 0
#define SPI_SSM_ENABLE 1

 /**********************************************************************************
 *  					config structure of SPI
 * *****************************************************************************/
//refer protocol control register  to select field of SPI config
typedef struct {
    uint32_t SPI_DeviceMode;
    uint32_t SPI_BusConfig;
    uint32_t SPI_SclkSpeed;
    uint32_t SPI_DFF;
    uint32_t SPI_CPOL;
    uint32_t SPI_CPHA;
    uint32_t SPI_SSM;
}SPI_Config_t;

/**********************************************************************************
*  					    Handle structure of USART
* *****************************************************************************/

typedef struct {
    SPI_RegDef_t *pSPIx; /*this hold the base address of SPIx peripheral*/
    SPI_Config_t SPI_Config;
    uint8_t* pTxBuffer;
    uint8_t* pRxBuffer;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxState;
    uint8_t RxState;
}SPI_Handle_t;


/**********************************************************************************
*  					    API Supported by USART driver
* *****************************************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_Init(SPI_Handle_t *pSPIx);
void SPI_DeInit(SPI_Handle_t *pSPIx);

/*
 * SPI send ànd receive
*/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len);

uint8_t SPI_SendDataIT(SPI_Handle_t *pPSIHandler, uint8_t *pTxBuffer, uint32_t len);

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandler, uint8_t *pRxBuffer, uint32_t len);

/*
 * IRQ Configuration and ISR handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandler(SPI_Handle_t *pHandle);

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandler);
void SPI_CloseReception(SPI_Handle_t *pSPIHandler);

/*
 * Application callbacks
*/
__attribute((weak)) void SPI_ApplicationEventCallback(SPI_Handle_t *pHandle, uint8_t AppEv);
//weak to allow application writer to override the default weak implementation


#endif /* SPI_H_ */
