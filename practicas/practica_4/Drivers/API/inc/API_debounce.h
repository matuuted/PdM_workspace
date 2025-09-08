#ifndef API_DEBOUNCE_H
#define API_DEBOUNCE_H

#ifdef PUNTO_2
typedef enum {
    BUTTON_UP = 0,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING
} debounceState_t;
#define DEBOUNCE_TIME_MS 40

void debounceFSM_init(void);    // carga estado inicial
void debounceFSM_update(void);  // lógica de transición + eventos
void buttonPressed(void);       // enciende LED
void buttonReleased(void);      // apaga LED
/* USER CODE END Private defines */
#endif
#endif // API_DEBOUNCE_H