#include "stm32f4xx.h"
#include "fpu.h"
#include <stdio.h>
#include "uart.h"
#include "timebase.h"
#include "bsp.h"
#define GPIOAEN (1U<<0)
#define PIN5 (1U<<5)
#define LED_PIN PIN5

#define SECTOR0_BASE_ADDRESS 0x08000000/*BootLoader sector*/
#define SECTOR1_BASE_ADDRESS 0x08004000/*Default APP sector*/
#define SECTOR2_BASE_ADDRESS 0x08008000/* APP1 sector*/
#define SECTOR3_BASE_ADDRESS 0x0800C000/*Factory APP sector*/

#define DEFAULT_APP_ADDRESS SECTOR1_BASE_ADDRESS
#define APP1_ADDRESS SECTOR2_BASE_ADDRESS
#define FACTORY_APP_ADDRESS SECTOR3_BASE_ADDRESS

#define APPLICATION_BASE_ADRRESS 0x08008000
#define FLASH_BASE_ADRRESS 0x08000000
#define MSP_VERIFY_MASK 0x2FFE0000
#define EMPTY_MEM 0xffffffff

typedef void(*func_ptr)(void);
volatile char g_key;
volatile uint8_t g_un_key;


//0x20020000: value stored at 0x08008000=> reset handler of application

//struct blt_common_apis{
//	void (*led_init)(void);
//	void (*led_on)(void);
//	void (*led_off)(void);
//	void (system_uart_init)(void);
//	void (*button_init)(void);
//	bool (*get_btn_state)(void);
//	void (*fpu_enable)(void);
//	void (*timebase_init)(void);
//};
//
//struct blt_common_apis blt_common_apis __attribute__((section(".COMMON_APIS"))) = {
//	led_init,
//	led_on,
//	led_off,
//	led_init,
//	system_uart_init,
//	button_init,
//	get_btn_state,
//	fpu_enable,
//	timebase_init
//};

typedef enum{
	APP1 = 1,
	FACTORY_APP
}SYS_APPS;

static void process_btldr_cmds(SYS_APPS curr_app);

void jump_to_app(uint32_t addr_value){
	uint32_t app_start_address;
	func_ptr jump_to_app_ptr;
	printf("Boot loader started. \n");
	delay(300);

    // --- Application Validity Check ---
#ifdef MEM_CHECK_V1
    // Kiểm tra Stack Pointer có nằm trong vùng SRAM hợp lệ
    if (((*(uint32_t *)addr_value) & 0x2FFE0000U) == 0x20000000U)
#elif MEM_CHECK_V2
    // Kiểm tra vùng nhớ không trống
    if (*(uint32_t *)addr_value != EMPTY_MEM)
#else
    if (1)
#endif
    {
        printf("Bootloader: Valid application found. Jumping...\n");

        // Lấy địa chỉ hàm reset handler (tại addr_value + 4)
        app_start_address = *(volatile uint32_t *)(addr_value + 4);
        jump_to_app_ptr = (func_ptr)app_start_address;

        // Set lại MSP (Main Stack Pointer)
        __disable_irq();                         // Ngăn ngắt trước khi chuyển
        __set_MSP(*(volatile uint32_t *)addr_value);
        __enable_irq();                          // (optional) bật lại nếu app cần ngắt

        jump_to_app_ptr();                       // Nhảy vào ứng dụng
    }
    else
    {
        printf("Bootloader: No valid application at 0x%08lX\n", addr_value);
    }
}
int main(){

	//enable Floating point
	fpu_enable();

	//enable Floating point
	system_uart_init();

	//enable Floating point
	timebase_init();

	//enable Floating point
	led_init();

	//enable Floating point
	button_init();

	//enable Floating point
//	jump_to_default_app();

	if( get_btn_state()){
		//button is pressed
		printf("DBG: button is pressed");

		printf("===========================\n");
		printf("===========================\n");
		printf("===========================\n");
		printf("===========================\n");

		printf("===========================\n");
		printf("\n");
		printf("BootLoader Menu\n");
		printf("\n");
		printf("===========================\n");
		printf("===========================\n");
		printf("===========================\n");

		printf("Available commands: \n");
		printf("1 ==> run app 1");
		printf("f ==> Factory App");
		printf("Any Key ==> run Default App");

		while(1){
			process_btldr_cmds(g_un_key);
		}
	}else{
		//button is not pressed
		jump_to_app(DEFAULT_APP_ADDRESS);
	}

	while(1){

	}


}
static void process_btldr_cmds(SYS_APPS curr_app){
	switch(curr_app){
		case APP1:
			printf("App 1 selected\n");
			jump_to_app(APP1_ADDRESS);
			break;
		case FACTORY_APP:
			printf("Factory App selected\n");
			jump_to_app(FACTORY_APP_ADDRESS);
			break;
		default:
			break;
	}
}

static void uart_callback(){
	g_key = USART2->DR;

	if(g_key == '1') {
		printf("Key press: 1\n");
		g_un_key = 1;
	}
	else if((g_key == 'f')||(g_key == 'F')){
		g_un_key = 2;
		printf("Key press: f\n");
	}
}

void USART2_IRQHandler(void){
	/* check if RXNE is set*/
	if(USART2->SR & (1 << 5)){
		uart_callback();
	}
}
