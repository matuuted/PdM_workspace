# Programación de Microcontroladores - Práctica 3

## Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2.

## Punto 1 – Definición de funciones para retardos no bloqueantes

### Objetivo
Implementar las funciones para usar **retardos no bloqueantes** en `API_delay.c` y `API_delay.h`.

### Definiciones en `API_delay.h`
```c
#include <stdint.h>
#include <stdbool.h> 

typedef uint32_t tick_t;
typedef bool     bool_t;

typedef struct {
  tick_t startTime;
  tick_t duration;
  bool_t running;
} delay_t;

void   delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay);
void   delayWrite(delay_t *delay, tick_t duration);

```

### Definiciones en `API_delay.c`
```c
#include "API_delay.h"

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
```
---
## Punto 2 – Parpadeo periódico utilizando una secuencia definida.

### Objetivo
Implementar un programa que utilice retardos no bloqueantes y haga titilar el Led en la secuencia predeterminada:
```c
const uint32_t TIEMPOS[] = {500, 100, 100, 1000};
```

### Descripción
- El LED debe encenderse y apagarse con la secuencia de tiempos definida en TIEMPOS[].
- Utilizar la función `delayWrite()` y una única variable tipo `delay_t` para cambiar el tiempo de encendido del led. 
- Duty cycle fijo = **50%**.  
- Parpadeo indefinido (ciclo continuo).  
---
## Punto 3 – Verificacion de `delay` implementando `delayIsRunning()`

### Objetivo
Implementar la función `delayIsRunning()` en `API_delay.c`

```c
bool_t delayIsRunning(delay_t * delay);
```
### Defines utilizados en el Punto 3
```c
#define NUM_TIMES    4

typedef enum {
    LED_PERIOD_100_MS  = 100,
    LED_PERIOD_200_MS  = 200,
    LED_PERIOD_500_MS  = 500,
    LED_PERIOD_1000_MS = 1000
} led_period_t;

typedef enum {
    DUTY_CYCLE_25 = 25,
    DUTY_CYCLE_50 = 50,
    DUTY_CYCLE_75 = 75,
    DUTY_CYCLE_100 = 100
} duty_cycle_t;

typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;
```
### Definicion de la funcion `delayIsRunning(delay_t * delay)` agregada en `API_delay.c`
```c
bool_t delayIsRunning(delay_t * delay) {
    if (delay == NULL) return false;
    return delay->running;
}
```