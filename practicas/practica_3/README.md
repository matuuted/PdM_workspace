# Programación de Microcontroladores - Práctica 3

## Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes a partir de las funciones creadas en la práctica 2.

## 🎯 Punto 1 – Definición de funciones para retardos no bloqueantes

### Objetivo
Implementar funciones auxiliares para usar **retardos no bloqueantes** en `API_delay.c` y `API_delay.h`.

### Definiciones en `API_delay.h`
```c
#include <stdint.h>   // para uint32_t
#include <stdbool.h>  // para bool
#include "stm32f4xx_hal.h"

typedef uint32_t tick_t;
typedef bool     bool_t;

typedef struct {
  tick_t startTime;
  tick_t duration;
  bool_t running;
} delay_t;

// Inicializa la estructura de delay, configurando la duracion del timer.
void   delayInit(delay_t *delay, tick_t duration);

// Retorna true si el delay ha terminado
bool_t delayRead(delay_t *delay);

// Actualiza el valor de duración del timer
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
## 🎯 Punto 2 – Parpadeo periódico utilizando una secuencia definida.

### Objetivo
Implementar un programa que utilice retardos no bloqueantes y haga titilar en forma periódica un led de la placa NUCLEO-F4xx de acuerdo a una secuencia predeterminada:
```c
const uint32_t TIEMPOS[] = {500, 100, 100, 1000};
```

### Descripción
- El LED debe encenderse y apagarse con la secuencia de tiempos definida en TIEMPOS[].
- Utilizar la función `delayWrite()` y una única variable tipo `delay_t` para cambiar el tiempo de encendido del led. 
- Duty cycle fijo = **50%**.  
- Parpadeo indefinido (ciclo continuo).  

### Lógica de funcionamiento
1. Se inicializa la estructura `led_delay` con un retardo de **250ms (LED_PERIOD_500_MS * 0.5)** con `delayInit`.  
2. En el `while`, cada vez que `delayRead` devuelve `true` → se conmuta el estado del LED.  
3. Se vuelve a actualizar el retardo correspondiente con `delayWrite()`.  
---
## 🎯 Punto 3 – Verificacion de `delay`

### Objetivo
Implementar la siguiente función auxiliar pública en `API_delay.c`

```c
bool_t delayIsRunning(delay_t * delay);
```
### Defines principales
```c
#define NUM_TIMES    4
```

### Enum principales 
```c
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
```

### Estructuras principales
```c
typedef struct {
    tick_t startTime;
    tick_t duration;
    bool_t running;
} delay_t;
```
### Definicion de `delayIsRunning(delay_t * delay)`
```c
bool_t delayIsRunning(delay_t * delay) {
    if (delay == NULL) return false;
    return delay->running;
}
```

### Descripción del funcionamiento
1. Se calculan los tiempos de encendido y apagado (`time_on` y `time_off`) a partir del período actual y un duty cycle fijo del **50%**.  
2. `delayRead()` verifica cuándo alternar el estado del LED.  
3. Se implementó `bool_t delayIsRunning(delay_t *delay)` para consultar si el delay está corriendo. En caso de retornar **false**, actualiza el delay con el tiempo correspondiente.
4. Cada ciclo completo (ON + OFF) avanza al siguiente período definido en `TIEMPOS`.  
5. Cuando se llega al final de la lista, la secuencia se reinicia desde el primer período.