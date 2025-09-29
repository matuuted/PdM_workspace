
# Programación de Microcontroladores - Práctica 5

## Objetivo
Implementar un módulo de software que permita trabajar con **UART**, utilizando la **HAL** de STM32 en **modo polling**.  
- El módulo debe permitir inicializar la UART, enviar y recibir datos.

---

## Punto 1 – Módulo UART

### Archivos requeridos
- `API_uart.c`.
- `API_uart.h`.

---
## Estructura de Archivos
- `Core/Src/main.c`: While loop que envia `Hola Mundo! 👋` por la UART.
- `Drivers/API/Src/API_uart.c`: Implementación del módulo UART con las funciones públicas requeridas por la consigna.
- `Drivers/API/Inc/API_uart.h`: Prototipos y definiciones públicas del módulo UART.

---

### Funciones públicas
Declaradas en `API_uart.h`:

```c
bool uartInit();
bool uartDeInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
```

---
