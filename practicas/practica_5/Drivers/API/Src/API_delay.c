#include "API_delay.h"
#include "stm32f4xx_hal.h"

void delayInit(delay_t *delay, tick_t duration) {
    if (delay == NULL) return;

    delay->duration = duration;
    delay->running = false;
	delay->startTime = 0;
}

void delayWrite(delay_t *delay, tick_t duration) {
    if (delay != NULL) {
        delay->duration = duration;
    }
}

bool_t delayRead(delay_t *delay) {
    if (delay == NULL) return false;

    tick_t current_time = HAL_GetTick();
    if (!delay->running) {
        delay->startTime = current_time;
        delay->running = true;
        return false;
    }

    if ((current_time - delay->startTime) >= delay->duration) {
        delay->running = false;
        return true;
    }

    return false;
}

bool_t delayIsRunning(delay_t * delay) {
    if (delay == NULL) return false;
    return delay->running;
}
