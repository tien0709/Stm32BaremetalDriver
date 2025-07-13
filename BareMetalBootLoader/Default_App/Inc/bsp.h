#ifndef BSP_H_
#define BSP_H_
#include <stdint.h>
#include <stdbool.h>

void led_init();
void led_on();
void led_off();
void button_init(void);
bool get_btn_state(void);

#endif /* BSP_H_ */
