#include "uart.h"
#include<stdint.h>

#define GPIOAEN (1U<<0)
#define USART2EN (1U<<17)
#define DBG_UART_BAUDRATE 115200//popular baudrate, refer online
#define SYS_FREQ 16000000
/*refer clocks and startup in datasheet
 = FREQ of HSI(FREQ of internal clock)*/
#define APB1_CLK SYS_FREQ
#define CR1_TE (1U<<3)
#define CR1_RE (1U<<2)
#define CR1_UE (1U<<13)
#define SR_TXE (1U<<7)

static void usart_set_baudrate(uint32_t periph_clk, uint32_t baudrate);
static void uart_write(int ch);
int __io_putchar(int ch) {
	uart_write(ch);
	return ch;
}

void system_uart_init(void) {
	/* Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;
	/* Set the mode of PA2 and PA3 to Alternate function mode*/
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 7);
	/* Set alternate function type of PA2 to AF7(UsART_TX2)*/
	//refer alternation mapping in datasheet
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);
	/*Set alternate function type of PA3 to AF7(UsART_RX2)*/
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] |= (1U << 11);
	GPIOA->AFR[0] &= ~(1U << 12);
	/* Enable clock access to UsART2 */
	RCC->APB1ENR |= USART2EN;
	/* setting baudrate */
	usart_set_baudrate(APB1_CLK, DBG_UART_BAUDRATE);
	/* config transfer direction */
	USART2->CR1 |= CR1_TE;
	USART2->CR1 |= CR1_RE;
	/* Enable Uart module */
	USART2->CR1 |= CR1_UE;
}

static void uart_write(int ch) {
	/* make sure transmit data reg is empty*/
	while (!(USART2->SR & SR_TXE)) {
	}
	/* write to transmit data register */
	USART2->DR |= ch & 0xff;
}
//Note: this code applied only when dont use Oversampling
static uint16_t compute_usart_baudrate(uint32_t periph_clk, uint32_t baudrate) {
	return ((periph_clk + (baudrate / 2U)) / baudrate);
}

static void usart_set_baudrate(uint32_t periph_clk, uint32_t baudrate) {
	USART2->BRR = compute_usart_baudrate(periph_clk, baudrate);
}
