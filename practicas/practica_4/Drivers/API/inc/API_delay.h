#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdint.h>
#include <stdbool.h>

typedef bool bool_t;
typedef uint32_t tick_t;

// Defines  ---------------------------------------------------------------
#define NUM_TIMES    4

// Types and Enums ---------------------------------------------------------
typedef enum {
    LED_PERIOD_100_MS  = 100,
    LED_PERIOD_200_MS  = 200,
    LED_PERIOD_500_MS  = 500,
    LED_PERIOD_1000_MS = 1000
} led_period_t;

typedef enum {
    DUTY_CYCLE_25  = 25,
    DUTY_CYCLE_50  = 50,
    DUTY_CYCLE_75  = 75,
    DUTY_CYCLE_100 = 100
} duty_cycle_t;

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