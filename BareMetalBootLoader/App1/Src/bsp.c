#include "bsp.h"
#include "stm32f4xx.h"
#define GPIOAEN (1U<<0)
#define GPIOCEN (1U<<2)
#define PIN5 (1U<<5)
#define LED_PIN PIN5
#define PIN13 (1U<<13)
#define BTN_PIN PIN13
void led_init(void){
	//enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//set PA5 mode to Output mode
	GPIOA->MODER |= (1<<10);
	GPIOA->MODER &= ~(1<<11); //MODER5 01 = set output mode to PA5 pin
}
void led_on(void){
	GPIOA->ODR |= LED_PIN;
}
void led_off(void){
	GPIOA->ODR &= ~LED_PIN;
}

void button_init(void){
	//enable clock access to GPIOC
	RCC->AHB1ENR |= GPIOCEN;
	//set PC13 mode to input mode
	GPIOC->MODER &= ~(1<<26);
	GPIOC->MODER &= ~(1<<27); //MODER13 00 = set input mode to PC13 pin
}

bool get_btn_state(void){
	//Note: button is active Low
	return (GPIOC->IDR & BTN_PIN) == 0;
}
