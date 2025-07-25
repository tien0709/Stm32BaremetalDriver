#ifndef STM32F411XX_H_
#define STM32F411XX_H_

#include <stdint.h>

/******************************************************************************
*           				Common Variable
*******************************************************************************/
#define ENABLE 1
#define DISABLE 0
#define FLAG_RESET 0
#define FLAG_SET 1

/******************************************************************************
*           				Stm32F411 Memory Map
*******************************************************************************/
#define SPI1_BASE_ADDRESS 0x40013000
#define SPI2_BASE_ADDRESS 0x40003800
#define SPI3_BASE_ADDRESS 0x40003C00

#define I2C1_BASE_ADDRESS 0x40005400
#define I2C2_BASE_ADDRESS 0x40005800
#define I2C3_BASE_ADDRESS 0x40005C00

#define USART1_BASE_ADDRESS 0x40011000
#define USART2_BASE_ADDRESS 0x40004400
//#define USART3_BASE_ADDRESS 0x40004800
//#define UART4_BASE_ADDRESS  0x40004C00
//#define UART5_BASE_ADDRESS  0x40005000
#define USART6_BASE_ADDRESS 0x40011400

#define GPIOA_BASE_ADDRESS 0x40020000
#define GPIOB_BASE_ADDRESS 0x40020400
#define GPIOC_BASE_ADDRESS 0x40020800
#define GPIOD_BASE_ADDRESS 0x40020C00
#define GPIOE_BASE_ADDRESS 0x40021000
#define GPIOF_BASE_ADDRESS 0x40021400
#define GPIOG_BASE_ADDRESS 0x40021800
#define GPIOH_BASE_ADDRESS 0x40021C00
//#define GPIOI_BASE_ADDRESS 0x40022000
//#define GPIOJ_BASE_ADDRESS 0x40022400
//#define GPIOK_BASE_ADDRESS 0x40022800

#define EXTI_BASE_ADDRESS 0x40013C00
#define SYSCFG_BASE_ADDRESS 0x40013800

#define RCC_BASE_ADDRESS 0x40023800

/******************************************************************************
*            Arm Cortex M Processor NVIC ISERx Register Address
*******************************************************************************/

/* Number of priority bits implemented in Priority Register. */
#define NO_PR_BITS_IMPLEMENTED 4

/*
 * NVIC ISERx Register Address
 */
#define NVIC_ISER0 (volatile uint32_t*)0xE000E100
#define NVIC_ISER1 (volatile uint32_t*)0xE000E104
#define NVIC_ISER2 (volatile uint32_t*)0xE000E108
#define NVIC_ISER3 (volatile uint32_t*)0xE000E10C

/*
 * NVIC ICERx Register Address
 */
#define NVIC_ICER0 (volatile uint32_t*)0xE000E180
#define NVIC_ICER1 (volatile uint32_t*)0xE000E184
#define NVIC_ICER2 (volatile uint32_t*)0xE000E188
#define NVIC_ICER3 (volatile uint32_t*)0xE000E18C

#define NVIC_PR_BASE_ADDRESS (volatile uint32_t*)0xE000E400
/*
 *NVIC IPRx Register Address
 */
#define NVIC_IPR0 (volatile uint32_t*)0xE000E400
#define NVIC_IPR1 (volatile uint32_t*)0xE000E404
#define NVIC_IPR2 (volatile uint32_t*)0xE000E408
#define NVIC_IPR3 (volatile uint32_t*)0xE000E40C


/*
 * Reg definition structure for exti
 */
typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
}EXTI_RegDef_t;

#define EXTI ((EXTI_RegDef_t*)EXTI_BASE_ADDRESS)

typedef struct{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
}GPIO_RegDef_t;

/******************************************************************************
*           		      IRQ definition structure
*******************************************************************************/

 /*
  * IRQ(interrupt request) number definition
   10.1.2 Interrupt and exception vectors
  */
 #define IRQ_NO_EXTI0 6
 #define IRQ_NO_EXTI1 7
 #define IRQ_NO_EXTI2 8
 #define IRQ_NO_EXTI3 9
 #define IRQ_NO_EXTI4 10
 #define IRQ_NO_EXTI9_5 23
 #define IRQ_NO_EXTI15_10 40
 #define IRQ_NO_SPI1 35
 #define IRQ_NO_SPI2 36
 #define IRQ_NO_SPI3 51
 #define IRQ_NO_I2C1_EV 31
 #define IRQ_NO_I2C1_ER 32

/******************************************************************************
*           		      RCC definition structure
*******************************************************************************/
/*
 * peripheral register definition for RCC
 */
typedef struct{
    volatile uint32_t CR;            /* Address of offset: 0x00*/
    volatile uint32_t PLLCFGR;       /* Address of offset: 0x04*/
    volatile uint32_t CFGR;          /* Address of offset: 0x08*/
    volatile uint32_t CIR;           /* Address of offset: 0x0C*/
    volatile uint32_t AHB1RSTR;      /* Address of offset: 0x10*/
    volatile uint32_t AHB2RSTR;      /* Address of offset: 0x14*/
    volatile uint32_t AHB3RSTR;      /* Address of offset: 0x18*/
    uint32_t RESERVED0;              /* reserved: 0x1C*/
    volatile uint32_t APB1RSTR;      /* Address of offset: 0x20*/
    volatile uint32_t APB2RSTR;      /* Address of offset: 0x24*/
    uint32_t RESERVED1[2];           /* reserved: 0x28 - 0x2C*/
    volatile uint32_t AHB1ENR;       /* Address of offset: 0x30*/
    volatile uint32_t AHB2ENR;       /* Address of offset: 0x34*/
    volatile uint32_t AHB3ENR;       /* Address of offset: 0x38*/
    uint32_t RESERVED2;              /* reserved:: 0x3C*/
    volatile uint32_t APB1ENR;       /* Address of offset: 0x40*/
    volatile uint32_t APB2ENR;       /* Address of offset: 0x44*/
    uint32_t RESERVED3[2];           /* reserved:: 0x48 - 0x4C*/
    volatile uint32_t AHB1LPENR;     /* Address of offset: 0x50*/
    volatile uint32_t AHB2LPENR;     /* Address of offset: 0x54*/
    volatile uint32_t AHB3LPENR;     /* Address of offset: 0x58*/
    uint32_t RESERVED4;              /* reserved: 0x5C*/
    volatile uint32_t APB1LPENR;     /* Address of offset: 0x60*/
    volatile uint32_t APB2LPENR;     /* Address of offset: 0x64*/
    uint32_t RESERVED5[2];           /* reserved:: 0x68-0x6C*/
    volatile uint32_t BDCR;          /* Address of offset: 0x70*/
    volatile uint32_t CSR;           /* Address of offset: 0x74*/
    uint32_t RESERVED6[2];           /* reserved: 0x78 - 0x7C*/
    volatile uint32_t SSCGR;         /* Address of offset: 0x80*/
    volatile uint32_t PLLI2SCFGR;    /* Address of offset: 0x84*/

}RCC_Regdef_t;

#define RCC ((RCC_Regdef_t*)RCC_BASE_ADDRESS)

/******************************************************************************
*           		      SYSCFG definition structure
*******************************************************************************/
typedef struct{
    volatile uint32_t MEMRMP;       /*Address of offset: 0x00*/
    volatile uint32_t PMC;          /*Address of offset: 0x04*/
    volatile uint32_t EXTICR[4];      /*Address of offset: 0x08*/
    volatile uint32_t RESERVED[2];  /*Address of offset: 0x18*/
    volatile uint32_t CMPCR;        /*Address of offset: 0x20*/
}SYSCFG_RegDef_t;

#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASE_ADDRESS)

/*
 * Clock enable marco for Syscfg peripheral
 */
#define SYSCFG_CLK_ENABLE() RCC->APB2ENR |= (1<<14)


/******************************************************************************
*           				GPIO Definition
*******************************************************************************/

/*
 * GPIO base address macro
 */
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)
#define GPIOI ((GPIO_RegDef_t*)GPIOI_BASE_ADDRESS)
#define GPIOJ ((GPIO_RegDef_t*)GPIOJ_BASE_ADDRESS)
#define GPIOK ((GPIO_RegDef_t*)GPIOK_BASE_ADDRESS)

/*
 * clock enable and disable macro for GPIOx peripheral
 */

 #define GPIOA_CLK_ENABLE() RCC->AHB1ENR |= (1<<0)
 #define GPIOB_CLK_ENABLE() RCC->AHB1ENR |= (1<<1)
 #define GPIOC_CLK_ENABLE() RCC->AHB1ENR |= (1<<2)
 #define GPIOD_CLK_ENABLE() RCC->AHB1ENR |= (1<<3)
 #define GPIOE_CLK_ENABLE() RCC->AHB1ENR |= (1<<4)
 #define GPIOF_CLK_ENABLE() RCC->AHB1ENR |= (1<<5)
 #define GPIOG_CLK_ENABLE() RCC->AHB1ENR |= (1<<6)
 #define GPIOH_CLK_ENABLE() RCC->AHB1ENR |= (1<<7)

 #define GPIOA_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<0)
 #define GPIOB_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<1)
 #define GPIOC_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<2)
 #define GPIOD_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<3)
 #define GPIOE_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<4)
 #define GPIOF_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<5)
 #define GPIOG_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<6)
 #define GPIOH_CLK_DISABLE() RCC->AHB1ENR &= ~(1<<7)

 /*
  * Reset state for GPIOx peripheral
  */
 #define GPIOA_RESET() do {RCC->AHB1RSTR |= (1<<0); RCC->AHB1RSTR &= ~(1<<0);}while(0)
 #define GPIOB_RESET() do {RCC->AHB1RSTR |= (1<<1); RCC->AHB1RSTR &= ~(1<<1);}while(0)
 #define GPIOC_RESET() do {RCC->AHB1RSTR |= (1<<2); RCC->AHB1RSTR &= ~(1<<2);}while(0)
 #define GPIOD_RESET() do {RCC->AHB1RSTR |= (1<<3); RCC->AHB1RSTR &= ~(1<<3);}while(0)
 #define GPIOE_RESET() do {RCC->AHB1RSTR |= (1<<4); RCC->AHB1RSTR &= ~(1<<4);}while(0)
 #define GPIOF_RESET() do {RCC->AHB1RSTR |= (1<<5); RCC->AHB1RSTR &= ~(1<<5);}while(0)
 #define GPIOG_RESET() do {RCC->AHB1RSTR |= (1<<6); RCC->AHB1RSTR &= ~(1<<6);}while(0)
 #define GPIOH_RESET() do {RCC->AHB1RSTR |= (1<<7); RCC->AHB1RSTR &= ~(1<<7);}while(0)

/*
 *
 */
#define GPIOB_BASE_ADDRESS_TO_CODE(x)   ((x==GPIOA)?0:\
                                        (x==GPIOB)?1:\
                                        (x==GPIOC)?2:\
                                        (x==GPIOD)?3:\
                                        (x==GPIOE)?4:\
                                        (x==GPIOF)?5:\
                                        (x==GPIOG)?6:\
                                        (x==GPIOH)?7:0)


/******************************************************************************
*           		  SPI  register definition structure
*******************************************************************************/
/*
 *  Base address of SPIx peripheral
 */
typedef struct{
    volatile uint32_t CR1;           /* Address of offset: 0x00*/
    volatile uint32_t CR2;           /* Address of offset: 0x04*/
    volatile uint32_t SR;            /* Address of offset: 0x08*/
    volatile uint32_t DR;            /* Address of offset: 0x0C*/
    volatile uint32_t CRCPR;         /* Address of offset: 0x10*/
    volatile uint32_t RXCRCR;        /* Address of offset: 0x14*/
    volatile uint32_t TXCRCR;        /* Address of offset: 0x18*/
    volatile uint32_t I2SCFGR;       /* Address of offset: 0x1C*/
    volatile uint32_t I2SPR;         /* Address of offset: 0x20*/
}SPI_RegDef_t;

/*
 * peripheral definition
 */

#define SPI1  ((SPI_RegDef_t*)SPI1_BASE_ADDRESS)//note: dont ignore () and define not have ";"
#define SPI2  ((SPI_RegDef_t*)SPI2_BASE_ADDRESS)
#define SPI3  ((SPI_RegDef_t*)SPI3_BASE_ADDRESS)
// #define SPI4  (SPI_Regdef_t*)SPI4_BASE_ADDRESS;

/*
 * clock enable macro for SPIx peripheral
*/

// #define SPI1_CLK_ENABLE() __HAL_RCC_SPI1_CLK_ENABLE()
// #define SPI2_CLK_ENABLE() __HAL_RCC_SPI2_CLK_ENABLE()
// #define SPI3_CLK_ENABLE() __HAL_RCC_SPI3_CLK_ENABLE()
// #define SPI4_CLK_ENABLE() __HAL_RCC_SPI4_CLK_ENABLE()
#define SPI1_CLK_ENABLE() RCC->APB2ENR |= (1<<12)
#define SPI2_CLK_ENABLE() RCC->APB1ENR |= (1<<14)
#define SPI3_CLK_ENABLE() RCC->APB1ENR |= (1<<15)
// #define SPI4_CLK_ENABLE() RCC->APB2ENR |= (1<<13)

/*
 * clock disable macro for SPIx peripheral
*/

#define SPI1_CLK_DISABLE() RCC->APB2ENR &= ~(1<<12)
#define SPI2_CLK_DISABLE() RCC->APB1ENR &= ~(1<<14)
#define SPI3_CLK_DISABLE() RCC->APB1ENR &= ~(1<<15)

/*
 * bits position definition for SPI_CR1
 */
#define SPI_CR1_CPHA 0
#define SPI_CR1_CPOL 1
#define SPI_CR1_MSTR 2
#define SPI_CR1_BR 3
#define SPI_CR1_SPE 6
#define SPI_CR1_LSBFIRST 7
#define SPI_CR1_SSI 8
#define SPI_CR1_SSM 9
#define SPI_CR1_RXONLY 10
#define SPI_CR1_DFF 11
#define SPI_CR1_CRCNEXT 12
#define SPI_CR1_CRCEN 13
#define SPI_CR1_BIDIOE 14
#define SPI_CR1_BIDIMODE 15

/*
 * bits position definition for SPI_CR2
 */
#define SPI_CR2_RXDMAEN 0
#define SPI_CR2_TXDMAEN 1
#define SPI_CR2_SSOE 2
#define SPI_CR2_FRF 4
#define SPI_CR2_ERRIE 5
#define SPI_CR2_RXNEIE 6
#define SPI_CR2_TXEIE 7

/*
 * bits position definition for SPI_SR
 */

 #define SPI_SR_RXNE 0
 #define SPI_SR_TXE 1
 #define SPI_SR_CHSIDE 2
 #define SPI_SR_UDR 3
 #define SPI_SR_CRCERR 4
 #define SPI_SR_MODF 5
 #define SPI_SR_OVR 6
 #define SPI_SR_BSY 7
 #define SPI_SR_FRE 8


 /**********************************************************************************
 *  				I2c register definition structure
 * *****************************************************************************/
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
    volatile uint32_t FLTR;
}I2C_RegDef_t;


/*
 *  basse address macro
 */
#define I2C1 ((I2C_RegDef_t*)I2C1_BASE_ADDRESS)
#define I2C2 ((I2C_RegDef_t*)I2C1_BASE_ADDRESS)
#define I2C3 ((I2C_RegDef_t*)I2C1_BASE_ADDRESS)


/*
 *  MArco to enable or disable i2c peripheral clock
 */

#define I2C1_CLK_ENABLE() RCC->APB1ENR |= (1<<21)
#define I2C2_CLK_ENABLE() RCC->APB1ENR |= (1<<22)
#define I2C3_CLK_ENABLE() RCC->APB1ENR |= (1<<23)

#define I2C1_CLK_DISABLE()  RCC->APB1ENR &= ~(1<<21)
#define I2C2_CLK_DISABLE()  RCC->APB1ENR &= ~(1<<22)
#define I2C3_CLK_DISABLE()  RCC->APB1ENR &= ~(1<<23)

/*
 *bit position definition of I2C_CR1
 */
#define I2C_CR1_PE 0
#define I2C_CR1_SMBUS 1
#define I2C_CR1_SMBTYPE 3
#define I2C_CR1_ENARP 4
#define I2C_CR1_ENPEC 5
#define I2C_CR1_ENGC 6
#define I2C_CR1_NOSTRETCH 7
#define I2C_CR1_START 8
#define I2C_CR1_STOP 9
#define I2C_CR1_ACK 10
#define I2C_CR1_POS 11
#define I2C_CR1_PEC 12
#define I2C_CR1_ALERT 13
#define I2C_CR1_SWRST 15

/*
 *bit position definition of I2C_
 */
#define I2C_CR2_FREQ 0
#define I2C_CR2_ITERREN 8
#define I2C_CR2_ITEVTEN 9
#define I2C_CR2_ITBUFEN 10
#define I2C_CR2_DMAEN 11
#define I2C_CR2_LAST 12

/*
 *bit position definition of I2C_OAR1
 */
#define I2C_OAR1_ADD0 0
#define I2C_OAR1_ADD71 1
#define I2C_OAR1_ADD98 8
#define I2C_OAR1_ADDMODE 15

/*
 *bit position definition of I2C_OAR2
 */
#define I2C_OAR2_ENDUAL 0
#define I2C_OAR2_ADD 1

/*
 *bit position definition of I2C_DR
 */
#define I2C_DR_DR 0

/*
 *bit position definition of I2C_SR1
 */
#define I2C_SR1_SB 0
#define I2C_SR1_ADDR 1
#define I2C_SR1_BTF 2
#define I2C_SR1_ADD10 3
#define I2C_SR1_STOPF 4
#define I2C_SR1_RXNE 6
#define I2C_SR1_TXE 7
#define I2C_SR1_BERR 8
#define I2C_SR1_ARLO 9
#define I2C_SR1_AF 10
#define I2C_SR1_OVR 11
#define I2C_SR1_PECERR 12
#define I2C_SR1_TIMEOUT 14
#define I2C_SR1_SMBALERT 15

/*
 *bit position definition of I2C_SR2
 */
#define I2C_SR2_MSL 0
#define I2C_SR2_BUSY 1
#define I2C_SR2_TRA 2
#define I2C_SR2_GENCALL 4
#define I2C_SR2_SMBDEFAULT 5
#define I2C_SR2_SMBHOST 6
#define I2C_SR2_DUALF 7
#define I2C_SR2_PEC 8

/*
 *bit position definition of I2C_CCR
 */
#define I2C_CCR_CCR 0
#define I2C_CCR_DUTY 14
#define I2C_CCR_FS 15

/*
 *bit position definition of I2C_TRISE
 */
#define I2C_TRISE_TRISE 0

/*
 *bit position definition of I2C_FLTR
 */
#define I2C_FLTR_DNF 0
#define I2C_FLTR_ANOFF 4


/**********************************************************************************
*  				USART register definition structure
* *****************************************************************************/

/*
 *  Base address of USARTx peripheral
 */
typedef struct{
    volatile uint32_t SR;            /* Address of offset: 0x00*/
    volatile uint32_t DR;            /* Address of offset: 0x04*/
    volatile uint32_t BRR;           /* Address of offset: 0x08*/
    volatile uint32_t CR1;           /* Address of offset: 0x0C*/
    volatile uint32_t CR2;           /* Address of offset: 0x10*/
    volatile uint32_t CR3;           /* Address of offset: 0x14*/
    volatile uint32_t GTPR;           /* Address of offset: 0x18*/
}USART_RegDef_t;

/*
 * USART peripheral definition
 */

#define USART1  ((USART_RegDef_t*)USART1_BASE_ADDRESS)//note: dont ignore () and define not have ";"
#define USART2  ((USART_RegDef_t*)USART2_BASE_ADDRESS)
//#define USART3  ((USART_RegDef_t*)USART3_BASE_ADDRESS)
//#define UART4  ((USART_RegDef_t*)UART4_BASE_ADDRESS)
//#define UART5  ((USART_RegDef_t*)UART5_BASE_ADDRESS)
#define USART6  ((USART_RegDef_t*)USART6_BASE_ADDRESS)
// #define SPI4  (SPI_Regdef_t*)SPI4_BASE_ADDRESS;

/*
 * clock enable macro for USARTx peripheral
*/

#define USART1_CLK_ENABLE() RCC->APB2ENR |= (1<<4)
#define USART2_CLK_ENABLE() RCC->APB1ENR |= (1<<17)
//#define USART3_CLK_ENABLE() RCC->APB1ENR |= (1<<18)
// #define SPI4_CLK_ENABLE() RCC->APB2ENR |= (1<<13)

/*
 * clock disable macro for USARTx peripheral
*/

#define USART1_CLK_DISABLE() RCC->APB2ENR &= ~(1<<4)
#define USART2_CLK_DISABLE() RCC->APB1ENR &= ~(1<<17)
//#define USART3_CLK_DISABLE() RCC->APB1ENR &= ~(1<<18)

/*
 *bit position definition of USART_CR1
 */
#define USART_CR1_SBK 0
#define USART_CR1_RWU 1
#define USART_CR1_RE 2
#define USART_CR1_TE 3
#define USART_CR1_IDLEIE 4
#define USART_CR1_RXNEIE 5
#define USART_CR1_TCIE 6
#define USART_CR1_TXEIE 7
#define USART_CR1_PEIE 8
#define USART_CR1_PS 9
#define USART_CR1_PCE 10
#define USART_CR1_WAKE 11
#define USART_CR1_M 12
#define USART_CR1_UE 13
#define USART_CR1_OVER8 15

/*
 * bit position definition of USART_CR2
 */
#define USART_CR2_ADD 0
#define USART_CR2_LBDL 5
#define USART_CR2_LBDIE 6
#define USART_CR2_LBCL 8
#define USART_CR2_CPHA 9
#define USART_CR2_CPOL 10
#define USART_CR2_CLKEN 11
#define USART_CR2_STOP 12
#define USART_CR2_LINEN 14

/*
 * bit position definition of USART_CR3
 */
#define USART_CR3_EIE 0
#define USART_CR3_IREN 1
#define USART_CR3_IRLP 2
#define USART_CR3_HDSEL 3
#define USART_CR3_NACK 4
#define USART_CR3_SCEN 5
#define USART_CR3_DMAR 6
#define USART_CR3_DMAT 7
#define USART_CR3_RTSE 8
#define USART_CR3_CTSE 9
#define USART_CR3_CTSIE 10
#define USART_CR3_ONEBIT 11

/*
 * bit position definition of USART_SR
 */
#define USART_SR_PE 0
#define USART_SR_FE 1
#define USART_SR_NF 2
#define USART_SR_ORE 3
#define USART_SR_IDLE 4
#define USART_SR_RXNE 5
#define USART_SR_TC 6
#define USART_SR_TXE 7
#define USART_SR_LBD 8
#define USART_SR_CTS 9

#endif /* STM32F411XX_H_ */
