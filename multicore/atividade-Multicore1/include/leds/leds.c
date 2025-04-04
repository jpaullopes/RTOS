#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2818b.pio.h"
#include "leds.h"

// Definição das variáveis globais
npLED_t leds[LED_COUNT];
PIO np_pio;
uint sm;


/**
 * @brief Inicializa o PIO para controle de LEDs WS2812B.
 * @param pin Pino de controle dos LEDs.
 * @note O número de LEDs é definido na constante LED_COUNT.
 */
void npInit(uint pin) {

    // Cria programa PIO.
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
  
    // Toma posse de uma máquina PIO.
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0) {
      np_pio = pio1;
      sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
    }
  
    // Inicia programa na máquina PIO obtida.
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);
  
    // Limpa buffer de pixels.
    for (uint i = 0; i < LED_COUNT; ++i) {
      leds[i].R = 0;
      leds[i].G = 0;
      leds[i].B = 0;
    }
}

/**
 * @brief Define a cor de um LED específico.
 * @param index Índice do LED (0 a LED_COUNT-1).
 * @param r Valor do componente vermelho (0-255).
 * @param g Valor do componente verde (0-255).
 * @param b Valor do componente azul (0-255).
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}
  
/**
 * * @brief Apaga todos os LEDs, definindo-os como apagados (0, 0, 0).
 */
void npClear() {
    for (uint i = 0; i < LED_COUNT; ++i)
      npSetLED(i, 0, 0, 0);
}
  
/**
 * @brief Escreve os dados dos LEDs no buffer da máquina PIO, em resumo, ele envia os dados para os LEDs.
 * 
 */
void npWrite() {
    // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
    for (uint i = 0; i < LED_COUNT; ++i) {
      pio_sm_put_blocking(np_pio, sm, leds[i].G);
      pio_sm_put_blocking(np_pio, sm, leds[i].R);
      pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}