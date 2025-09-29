#include "API_debounce.h"
#ifdef PUNTO_2
#include "API_delay.h"
#include "stm32f4xx_hal.h"
#include "dev_gpio_cfg.h"

static debounceState_t state;
static delay_t delay;
static bool key_pressed = false; // Variable para indicar si la tecla fue presionada

/* 
 * Lee el estado del pulsador.
 * @return true si está presionado, false si no.
 */
static bool get_button_state(void) {
    return (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET);
}

/**
 * Función pública para leer si la tecla fue presionada (flanco descendente).
 * Devuelve true si fue presionada y resetea el estado.
 */
bool readKey(void) {
    if (key_pressed) {
        key_pressed = false;
        return true;
    }
    return false;
}
/* 
 * Inicializa la State Machine del antirrebote.
 * 
 * Entradas y salidas:
 *  - void
 */
void debounceFSM_init(void) {
	// Configura el state como BUTTON_UP e inicializa la estructura delay en 40 ms.
    state = BUTTON_UP;
    delayInit(&delay, DEBOUNCE_TIME_MS);
	key_pressed = false;
}

/**
 * Actualiza la máquina de estados según el estado del pulsador.
 */
void debounceFSM_update(void) {
    switch (state) {
		case BUTTON_UP: // Espera a que el botón sea presionado.
			if (get_button_state()) {
				state = BUTTON_FALLING;
			}
			break;

		case BUTTON_FALLING: // Se verifica si la pulsación es estable (antirrebote)
			if (delayRead(&delay)) {
				if (get_button_state()) {
					state = BUTTON_DOWN;
					key_pressed = true; // Indica que la tecla fue presionada
				} else {
					state = BUTTON_UP; // Lo que se detecto fue ruido.
				}
			}
			break;

		case BUTTON_DOWN: // Se espera a que el botón sea liberado
			if (!get_button_state()) {
				state = BUTTON_RAISING;
			}
			break;

		case BUTTON_RAISING: // Verifica si se libera el botón y si es estable (antirrebote)
			if (delayRead(&delay)) {
				if (!get_button_state()) {
					state = BUTTON_UP;
				} else {
					state = BUTTON_DOWN; // Lo que se detecto fue ruido.
				}
			}
			break;

		default:
			debounceFSM_init(); // Reinicia la máquina en caso de estado inválido
			break;
    }
}
#endif