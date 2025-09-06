#include "API_delay.h"
#include "stm32f4xx_hal.h"

/* 
 * Inicializa la estructura delay.
 * 
 * Entradas:
 *  - delay: puntero a la estructura delay_t que se quiere inicializar.
 *  - duration: tiempo de duración del delay en ms.
 * 
 * Salida:
 *  - No devuelve valor. 
 */
void delayInit(delay_t *delay, tick_t duration) {
    if (delay == NULL || duration == 0) {
        return; // El puntero o la duracion no son válidos.
    }
    delay->duration = duration;
    delay->running = false;
	delay->startTime = 0;
}

/* 
 * Actualiza la duración configurada en el delay.
 * 
 * Entradas:
 *  - delay: puntero a la estructura delay_t que se quiere actualizar.
 *  - duration: nuevo tiempo de duración en ms.
 * 
 * Salida:
 *  - No devuelve valor.
 */
void delayWrite(delay_t *delay, tick_t duration) {
    if (delay == NULL || duration == 0) {
        return; // El puntero o la duracion no son válidos.
    }
    delay->duration = duration;
}

/* 
 * Verifica si el delay ha finalizado.
 * 
 * Entradas:
 *  - delay: puntero a la estructura delay_t a verificar.
 * 
 * Salida (bool_t):
 *  - true: el tiempo definido en la estructura se cumplió.
 *  - false: el tiempo todavía no se cumplio.
 * 
 */
bool_t delayRead(delay_t *delay) {

    if (delay == NULL || delay->duration == 0) {
        return false; // El puntero o la duracion no son válidos.
    }
    tick_t current_time = HAL_GetTick(); // Tiempo actual en ms

    // Si no estaba actualmente corriendo, inicia la estructura delay
    if (!delay->running) { 
        delay->startTime = current_time;
        delay->running = true;
        return false;
    }

    // Verifica si el tiempo definido se cumplió
    if ((current_time - delay->startTime) >= delay->duration) { 
        delay->running = false;
        return true;
    }

    return false; // Todavía no llegó a cumplir el tiempo definido
}

/*
 * Punto 3: Función auxiliar pública delayIsRunning().
 */

/* 
 * Consulta si el delay está corriendo.
 * 
 * Entradas:
 *  - delay: puntero a la estructura delay_t .
 * 
 * Salida (bool_t):
 *  - true: el delay está corriendo.
 *  - false: el delay no está corriendo.
 * 
 */
bool_t delayIsRunning(delay_t * delay) {
    if (delay == NULL) return false; // El puntero delay no es valido.

    return delay->running; // Retorna el estado actual del delay
}
