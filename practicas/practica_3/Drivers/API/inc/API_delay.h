#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;
typedef uint32_t tick_t;


/* ============================================================================
 * Estructuras
 * ==========================================================================*/

/*
 * Estructura para manejar un delay no bloqueante definida para la actividad.
 *
 * - startTime: marca de tiempo cuando se inicia el delay.
 * - duration: duración que debe transcurrir para que el delay se cumpla (ms).
 * - running: indica si el delay está activo (true) o esperando ser iniciado (false).
 */
typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;

// Public Functions  ------------------------------------------------------------
void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void delayWrite(delay_t *delay, tick_t duration);
bool_t delayIsRunning(delay_t * delay);

#endif // API_DELAY_H