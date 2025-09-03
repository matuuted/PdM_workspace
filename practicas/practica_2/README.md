# Programación de Microcontroladores - Práctica 2

## Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes. 

## 🎯 Punto 1 – Definición de funciones para retardos no bloqueantes

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
## 🎯 Punto 2 – Parpadeo periódico

### Objetivo
Usar la API de retardos no bloqueantes (Punto 1) para hacer parpadear el LED de la placa.

### Descripción
- El LED debe encenderse 100 ms y apagarse 100 ms.  
- Duty cycle fijo = **50%**.  
- Parpadeo indefinido (ciclo continuo).  

### Lógica de funcionamiento
1. Se inicializa la estructura `led_delay` con un retardo de **100ms (LED_PERIOD_200_MS * 0.5)** con `delayInit`.  
2. En el `while`, cada vez que `delayRead` devuelve `true` → se conmuta el estado del LED.  
3. Se vuelve a cargar el mismo retardo con `delayWrite()`.  

>⚠️ **NOTA:** Para poder probar este ejercicio se debe agregar el `#define PUNTO_2` al comienzo de `main.c`.

---
## 🎯 Punto 3 – Secuencia de patrones 

### Objetivo
Hacer parpadear el LED en una secuencia de **patrones configurables de 1 seg, 200ms y 100ms**, la cual se implemento mediante un arreglo.

### Defines principales
```c
#define NUM_PERIOD 3
#define REPETITIONS 5
```

### Enum principales 
```c
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
```

### Estructuras principales
```c
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
La implementación del código utilizando la estructura `blink_pattern` busca que los parámetros de ejecución puedan modificarse fácilmente, manteniendo una organización clara y sencilla de verificar desde el **Debugger** en el IDE.

- Cada patrón se ejecuta el número de repeticiones definidas (`#define REPETITIONS 5`).
- Una vez completadas, se pasa al siguiente patrón.
- Cuando todos los patrones finalizan, se reinicia el ciclo.
- El código recalcula los tiempos de encendido y apagado en función del período y del duty cycle.

>⚠️ **NOTA:** Para poder probar este ejercicio, **NO** debe estar definido `#define PUNTO_2` al comienzo de `main.c`.

---
## ✅ Checklist

### Punto 1
- [x] Inclusión de `<stdint.h>` y `<stdbool.h>`.
- [x] Definición de `tick_t`, `bool_t` y `delay_t`.
- [x]  Prototipos en main.h y main.c.

### Punto 2
- [x] Reutilización de `delayInit`, `delayRead`, `delayWrite`.  
- [x] LED ON 100 ms.  
- [x] LED OFF 100 ms.  

### Punto 3
- [x] Secuencia: 1000 ms → 200 ms → 100 ms. 
- [x] Duty fijo del 50%.
