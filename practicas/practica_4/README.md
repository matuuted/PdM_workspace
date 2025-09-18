
# Programación de Microcontroladores - Práctica 4

## Objetivo
Implementar una Máquina de Estados Finitos (MEF) para trabajar con anti-rebotes por software.

---
## 🎯 Punto 1 – Implementación de MEF anti-rebote

### Objetivo
Crear un nuevo proyecto como copia del realizado en la práctica 3 e implementar una MEF anti-rebote para leer el estado del pulsador y generar eventos ante flancos ascendentes y descendentes.

### Requerimientos
- Estado inicial de la MEF: `BUTTON_UP`.
- Implementar en `main.c` las funciones:
    - `void debounceFSM_init();`  // Carga el estado inicial
    - `void debounceFSM_update();` // Lógica de transición y actualización de salidas
    - `void buttonPressed();`      // Enciende el LED
    - `void buttonReleased();`     // Apaga el LED
- Tiempo de anti-rebote: **40 ms** (retardo no bloqueante).
- Llamar periódicamente a `debounceFSM_update()` dentro de main.c.
- Definición de estados para la MEF:
```c
typedef enum{
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING,
} debounceState_t;
```

---
## 🎯 Punto 2 – Módulo API_debounce y cambio de frecuencia de parpadeo

### Objetivo
Implementar el módulo de software en `API_debounce.c` y `API_debounce.h` en las carpetas `/Drivers/API/src` y `/Drivers/API/inc` para controlar la MEF del anti-rebote. Luego, realizar un programa que cambie la frecuencia de parpadeo del LED entre **100 ms** y **500 ms** cada vez que se presione la tecla.

### Requerimientos
- En `API_debounce.h`:
    - Agregar las siguientes funciones públicas:
        - `void debounceFSM_init();`
        - `void debounceFSM_update();`
        - `bool_t readKey();`
- En `API_debounce.c`:
    - Declarar de manera privada `debounceState_t` y variable de estado global privada (static).
    - Variable global privada tipo `bool_t` que se cambia a true cuando se detecta un flanco descendente y en false al llamar a `readKey()`.

---
## Estructura de Archivos
- `Core/Src/main.c`: Implementación principal de la MEF para el Punto 1.
- `Drivers/API/inc/API_debounce.h`: Prototipos y declaraciones públicas del módulo anti-rebote (Punto 2).
- `Drivers/API/src/API_debounce.c`: Implementación del módulo anti-rebote (Punto 2).
- `Drivers/API/inc/API_delay.h` y `Drivers/API/src/API_delay.c`: Módulo de retardos no bloqueantes.

---
## Detalles a tener en cuenta al momento de compilación.
Para poder desarrollar ambos puntos, se agregaron `#ifdef` que permiten la ejecucion de codigo diferenciado.
Para compilarlo correctamente, hace falta agregar la definicion `PUNTO_1` o `PUNTO_2` en el MCU GCC Compiler.
- A continuación se detallan los pasos para agregarlo: 
1. Click derecho sobre el proyecto `practica_4`.
2. Propiedades.
3. Dentro de la pestaña `C/C++ Build`, clickear en `Settings`.
4. Dentro de la pestaña `MCU GCC Compiler`, clickear en `Preproccesor`.
5. En `Define symbols (-D)`, clickear en `Add..` y agregar el correspondiente -> `PUNTO_1` o `PUNTO_2`.

---