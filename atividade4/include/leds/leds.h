// A biblioteca leds.h foi baseada totalmente no codigo exemplo da BITDogLab-C

#ifndef LEDS_H
#define LEDS_H

#include "hardware/pio.h"  // Adicionando a inclusão para o tipo PIO

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

// Definição de pixel GRB
struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; 

// Declaração do buffer de pixels que formam a matriz.
extern npLED_t leds[LED_COUNT];  // Modificado para extern

// Declaração das variáveis globais como extern
extern PIO np_pio;
extern uint sm;  

/**
 * @brief Inicializa o PIO para controle de LEDs WS2812B.
 * @param pin Pino de controle dos LEDs.
 * @note O número de LEDs é definido na constante LED_COUNT.
 */
void npInit(uint pin);

/**
 * @brief Define a cor de um LED específico.
 * @param index Índice do LED (0 a LED_COUNT-1).
 * @param r Valor do componente vermelho (0-255).
 * @param g Valor do componente verde (0-255).
 * @param b Valor do componente azul (0-255).
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b);

/**
 * @brief Apaga todos os LEDs, definindo-os como apagados (0, 0, 0).
 */
void npClear(void);

/**
 * @brief Escreve os dados dos LEDs no buffer da máquina PIO, em resumo, ele envia os dados para os LEDs.
 */
void npWrite(void);


#endif