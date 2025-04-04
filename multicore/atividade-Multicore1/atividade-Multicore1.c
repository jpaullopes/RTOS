#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "pico/multicore.h"
#include "include/joystick/joystick.h"
#include "include/leds/leds.h"
#include "include/display/display.h"


QueueHandle_t xQueueJoytick;

void setup_init_all(void);
void xTaskJoystick(void *pdParamenters);
void xTaskExibition(void *pdParamenters);
void core1_entry(void);


int main(void){
    setup_init_all(); // Inicializa todos os módulos

    // Criação da Fila que ficará na memória compartilhada entre os núcleos
    xQueueJoytick = xQueueCreate(15, sizeof(Joystick));
    if( xQueueJoytick == NULL ){
        printf("Erro ao criar a fila\n");
        return 1;
    }

    if(xTaskCreate(xTaskJoystick, "Joystick", 500, NULL, 1, NULL) !=pdPASS){
        printf("Erro ao criar a tarefa do Joystick\n");
        return 1;
    }

    // Criação da tarefa no core 1
    multicore_launch_core1(core1_entry);
    
    // Inicia o scheduler do FreeRTOS
    vTaskStartScheduler();
    while(1);
    return 0;
}

// Função para a inicialização de todos os módulos
void setup_init_all(void){
    stdio_init_all();
    joystick_init();
    npInit(LED_PIN);
    npClear();
    display_init();
    display_clear();
}

void xTaskJoystick(void *pdParamenters){
    Joystick joystick_data;
    while(1){
        read_joystick(&joystick_data); // Leitura dos dadas do Joystick

        if(xQueueSend(xQueueJoytick, &joystick_data, 10 / portMAX_DELAY) != pdPASS){
            printf("Erro ao criar ao enviar os dados apra a fila\n");
        }

        printf("X: %d, Y: %d\n", joystick_data.x_position, joystick_data.y_position);
        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay de 100ms
    }
}

void xTaskExibition(void *pdParamenters){
    Joystick joystick_data_recive;
    while(1){
        if(xQueueReceive(xQueueJoytick, &joystick_data_recive, 10 / portMAX_DELAY) == pdPASS){

            display_clear();
            char buffer_x[20];
            char buffer_y[20];
            snprintf(buffer_x, sizeof(buffer_x), "Val X: %d", joystick_data_recive.x_position);
            snprintf(buffer_y, sizeof(buffer_y), "Val Y: %d", joystick_data_recive.y_position);
            char *text[] = {buffer_x, buffer_y};
            display_draw_text_lines(text, 2, 0);
            display_update();

            vTaskDelay(100 / portTICK_PERIOD_MS); // Delay de 100ms
        }
    }
}

void core1_entry(void){
    // Criação da tarefa de exibição no core 1
    if(xTaskCreate(xTaskExibition, "Exibition", 500, NULL, 1, NULL) != pdPASS){
        printf("Erro ao criar a tarefa de exibição\n");
    }

    // Inicia o scheduler do FreeRTOS
    vTaskStartScheduler();
}