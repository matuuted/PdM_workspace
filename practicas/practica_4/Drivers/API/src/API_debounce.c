#include "API_debounce.h"
#ifdef PUNTO_2
#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "dev_gpio_cfg.h"

static debounceState_t state;
static delay_t delay;

/* 
 * Lee el estado del Pulsador B1.
 * 
 * Entradas:
 *  - void
 * 
 * Salida:
 *  - Retorna el estado del GPIO.
 *  - true: si el botón está presionado.
 * - false: si el botón no está presionado. 
 */
static bool get_button_state(void) {
    return (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET);
}

/* 
 * Enciende el Led.
 * 
 * Entradas:
 *  - void
 * 
 * Salida:
 *  - void
 */
static void turn_led_on(void)  { 
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
}

/* 
 * Apaga el Led.
 * 
 * Entradas:
 *  - void
 * 
 * Salida:
 *  - void
 */
static void turn_led_off(void) { 
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
}


void debounceFSM_init(void) {
    state = BUTTON_UP;
    delayInit(&delay, DEBOUNCE_TIME_MS);
}

void debounceFSM_update(void) {
    switch (state) {
		case BUTTON_UP:
			if (get_button_state()) {
				state = BUTTON_FALLING;
				delayInit(&delay, DEBOUNCE_TIME_MS);
			}
			break;

		case BUTTON_FALLING:
			if (delayRead(&delay)) {
				if (get_button_state()) {
					state = BUTTON_DOWN;
					turn_led_on();                  // flanco descendente confirmado
				} else {
					state = BUTTON_UP;        // ruido
				}
			}
			break;

		case BUTTON_DOWN:
			if (!get_button_state()) {
				state = BUTTON_RAISING;
				delayInit(&delay, DEBOUNCE_TIME_MS);
			}
			break;

		case BUTTON_RAISING:
			if (delayRead(&delay)) {
				if (!get_button_state()) {
					state = BUTTON_UP;
					turn_led_off();
				} else {
					state = BUTTON_DOWN;
				}
			}
			break;

		default:
			debounceFSM_init(); // En caso de un error en el estado, reinicia la State Machine.
			break;
    }
}

#endif