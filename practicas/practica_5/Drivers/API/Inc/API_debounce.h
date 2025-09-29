/**
 * @file API_debounce.h
 * @brief En este archivo se encuentra la implementación del antirrebote del pulsador LD2.
 *
 * Este archivo contiene los enums y funciones necesarias para implementar
 *  la máquina de estados de antirrebote requerido en la práctica 4.
 */

#ifndef API_DEBOUNCE_H
#define API_DEBOUNCE_H

#ifdef PUNTO_2
#include <stdbool.h>
typedef enum {
    BUTTON_UP = 0,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RAISING
} debounceState_t;
#define DEBOUNCE_TIME_MS 40

void debounceFSM_init(void);    // carga estado inicial
void debounceFSM_update(void);  // lógica de transición + eventos
bool readKey(void);             // Funcion global para verificar si la tecla fue presionada.
/* USER CODE END Private defines */
#endif
#endif // API_DEBOUNCE_H