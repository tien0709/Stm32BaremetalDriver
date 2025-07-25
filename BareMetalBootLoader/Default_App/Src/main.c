#include "stm32f4xx.h"
#include "fpu.h"
#include <stdio.h>
#include "timebase.h"
#include "bsp.h"


#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_PIN PIN5

#define FLASH_BASE_ADRRESS 0x08000000
#define VECTOR_TABLE_BASE_ADDRESS FLASH_BASE_ADRRESS
#define VECTOR_TABLE_OFFSET 0x4000

typedef void(*func_ptr)(void);

//callback of reset handler, Automatically call
void SystemInit(void){
	SCB->VTOR = VECTOR_TABLE_BASE_ADDRESS|VECTOR_TABLE_OFFSET;
}


int main(){

	//enable Floating point
	fpu_enable();


	//enable timebase
	timebase_init();

	//enable led
	led_init();

	//enable button
	button_init();

	while(1){
		printf("default applicaion is running\n");
		delay(1000);
	}


}

