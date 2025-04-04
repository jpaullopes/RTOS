#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "joystick.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Inicializa o joystick
 */
void joystick_init(void){
    adc_init(); //inicializa o ADC
    adc_gpio_init(PINO_JOY_X); //inicializa o pino do eixo X
    adc_gpio_init(PINO_JOY_Y); //inicializa o pino do eixo Y
}

/**
 * @brief Lê os valores do joystick
 * @param joystick Ponteiro para a estrutura do joystick
 */
void read_joystick(Joystick *joystick){
    // Lê os valores do joystick
    adc_select_input(ADC_CHANNEL_Y); // Seleciona o canal ADC para o eixo X
    uint16_t x_value = adc_read(); 
    adc_select_input(ADC_CHANNEL_X); // Seleciona o canal ADC para o eixo Y
    uint16_t y_value = adc_read();

    // Converte os valores lidos para a faixa de 0 a 100
    joystick->x_position = (x_value * 100) / 4095; 
    joystick->y_position = (y_value * 100) / 4095;

}