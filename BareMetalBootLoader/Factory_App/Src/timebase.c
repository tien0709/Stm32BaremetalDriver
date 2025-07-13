#include "timebase.h"
#include "stm32f4xx.h"


#define CTRL_ENABLE 	(1U<<0)
#define CTRL_TICKINT 	(1U<<1)
#define CTRL_CLKSOURCE  (1U<<2)
#define CTRL_COUNTFLAG  (1U<<12)

#define ONE_SEC_LOAD 	16000000//16MHz
/*systick is a 24bit countdown counter used for creating a period timer
 * => delay, time of system or tick for RTOS*/
#define TICK_FREQ 1;
#define MAX_DELAY 0xffffffff

volatile uint32_t g_cur_tick;
volatile uint32_t g_cur_tick_p;

void delay(uint32_t delay){
	uint32_t tickstart = get_tick();
	uint32_t wait = delay;

	if(wait<MAX_DELAY){
		wait += TICK_FREQ;
	}// bù sai số thời gian do thời điểm đọc tick không chính xác ngay khi vào hàm.

	while(get_tick()-tickstart<wait){}
}

uint32_t get_tick(){
	__disable_irq();
	g_cur_tick_p = g_cur_tick;
	__enable_irq();

	return g_cur_tick_p;
}
void tick_increment(){
	g_cur_tick += TICK_FREQ;
}

void timebase_init(void){

	/*Disable global Interrupts*/
	__disable_irq();
	/*Load the timer with the number of clock cycle per second */
    SysTick->LOAD = ONE_SEC_LOAD - 1;
	/*clear systick current value register */
    SysTick->VAL = 0;
	/*select internal clock source */
    SysTick->CTRL |= CTRL_CLKSOURCE;
	/*Enable Interrupts*/
    SysTick->CTRL |= CTRL_TICKINT;
	/*Enable Systick*/
    SysTick->CTRL |= CTRL_ENABLE ;
	/*Enable global Interrupts*/
	__enable_irq();

}

void SysTick_Handler(void){
	tick_increment();
}
