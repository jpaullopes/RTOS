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
    gpio_init(PINO_BUTTON); //inicializa o pino do botão
    gpio_set_dir(PINO_BUTTON, GPIO_IN); //configura o pino do botão como entrada
    gpio_pull_up(PINO_BUTTON); //ativa o pull-up no pino do botão

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

    // Lê o estado do botão
    if(gpio_get(PINO_BUTTON) == 0){ // Se o botão estiver pressionado
        joystick->button_pressed = 1; // Botão pressionado
        // sleep_ms(50); // Debounce de 50ms / Mas vou testar deixando somente o intervalod de leitura da tarefa
    } else {
        joystick->button_pressed = 0; // Botão não pressionado
    }

}