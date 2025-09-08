# Programación de Microcontroladores - Práctica 2

## Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes. 

## Punto 1 – Definición de funciones para retardos no bloqueantes

### Objetivo
Implementar funciones auxiliares para usar **retardos no bloqueantes** en `main.c` y `main.h`.

### Definiciones en `main.h`
```c
#include <stdint.h>   // para uint32_t
#include <stdbool.h>  // para bool

typedef uint32_t tick_t;
typedef bool     bool_t;

typedef struct {
  tick_t startTime;
  tick_t duration;
  bool_t running;
} delay_t;

void   delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void   delayWrite( delay_t * delay, tick_t duration );

```
---
## Punto 2 – Parpadeo periódico

### Objetivo
Usar la API de retardos no bloqueantes (Punto 1) para hacer parpadear el LED.

### Descripción
- El LED debe encenderse 100 ms y apagarse 100 ms.  
- Duty cycle fijo = **50%**.  
- Parpadeo indefinido (ciclo continuo).  

>⚠️ **NOTA:** Para poder probar este ejercicio hay que agregar el `#define PUNTO_2` al comienzo de `main.c`.

---
## Punto 3 – Secuencia de patrones 

### Objetivo
Hacer parpadear el LED en una secuencia de **patrones configurables de 1 seg, 200ms y 100ms**.

### Defines agregados para el Punto 3
```c
#define NUM_PERIOD 3
#define REPETITIONS 5

typedef enum {
    LED_PERIOD_100_MS  = 100,
    LED_PERIOD_200_MS  = 200,
    LED_PERIOD_1000_MS = 1000
} led_period_t;

typedef enum {
    DUTY_CYCLE_25 = 25,
    DUTY_CYCLE_50 = 50,
    DUTY_CYCLE_75 = 75,
    DUTY_CYCLE_100 = 100
} duty_cycle_t;

typedef struct {
  uint8_t repetitions;
  tick_t  period;
  uint8_t duty_cycle;
} blink_pattern;

const blink_pattern blink[NUM_PERIOD] = {
  {REPETITIONS, LED_PERIOD_1000_MS, DUTY_CYCLE_50},
  {REPETITIONS, LED_PERIOD_200_MS,  DUTY_CYCLE_50},
  {REPETITIONS, LED_PERIOD_100_MS,  DUTY_CYCLE_50}
};
```

### Descripción del funcionamiento
La implementación del código utilizando la estructura `blink_pattern` busca que los parámetros de ejecución puedan modificarse fácilmente, permitiendo probar distintos patrones de repeticiones/periodos/duty cycle.

- Cada patrón se ejecuta el número de repeticiones definidas (`#define REPETITIONS 5`).
- Una vez completadas, se pasa al siguiente patrón.
- Cuando todos los patrones finalizan, se reinicia el ciclo.
- El código recalcula los tiempos de encendido y apagado en función del período y del duty cycle.

>⚠️ **NOTA:** Para poder probar este ejercicio, **NO** debe estar definido `#define PUNTO_2` al comienzo de `main.c`.

---
