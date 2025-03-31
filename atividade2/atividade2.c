#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Defines de todos os pinos utilizados na placa
#define LED_PIN_1 11
#define LED_PIN_2 12
#define LED_PIN_3 13
#define BUTTON_PIN_A 5
#define BUTTON_PIN_B 6

// Criando as filas para comunicação entre as tarefas
QueueHandle_t xQueueButtons;

void setupInit();
void vTaskButtons(void *pdParamenters);
void vTaskTurningLed(void *pdParamenters);

int main(void){
    // Inicializa o sistema
    setupInit();
    
    // Cria a fila para comunicação entre as tarefas
    xQueueButtons = xQueueCreate(10, sizeof(char));

    // Criando Tarefas
    xTaskCreate(vTaskButtons, "Buttons", 900, NULL , 1 , NULL);
    xTaskCreate(vTaskTurningLed, "Turning the LEDs", 900, NULL , 2 , NULL);

    // Inicia o scheduler
    vTaskStartScheduler();
    while(1);
    return 0;
}

/* Função que inicializa todo os pinos da placa 
*/
void setupInit(){
    stdio_init_all();
    // Inicializa o LED
    gpio_init(LED_PIN_1);
    gpio_init(LED_PIN_2);
    gpio_init(LED_PIN_3);
    gpio_set_dir(LED_PIN_1, GPIO_OUT);
    gpio_set_dir(LED_PIN_2, GPIO_OUT);
    gpio_set_dir(LED_PIN_3, GPIO_OUT);
    // Inicializa o botão
    gpio_init(BUTTON_PIN_A);
    gpio_init(BUTTON_PIN_B);
    gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
    gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
    gpio_pull_up(BUTTON_PIN_A);
    gpio_pull_up(BUTTON_PIN_B);
    // Inicializa o sistema de tempo
    sleep_ms(1000);
    printf("SISTEMA INICIALIZADO COM SUCESSO\n");
}

// Função da Tarefa que verifica se o botão foi pressionado
void vTaskButtons(void *pdParamenters){
    char buttonPressed = 0;
    while(1){
        // Verifica se o botão A foi pressionado
        if(gpio_get(BUTTON_PIN_A) == 0){
            buttonPressed = 'A';
            xQueueSend(xQueueButtons, &buttonPressed, portMAX_DELAY);
            printf("Botão A foi precionado\n");
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        // Verifica se o botão B foi pressionado
        if(gpio_get(BUTTON_PIN_B) == 0){
            buttonPressed = 'B';
            xQueueSend(xQueueButtons, &buttonPressed, portMAX_DELAY);
            printf("Botão B foi precionado\n");
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

// Função da Tarefa que controla os LEDs de acordo com o botão pressionado
void vTaskTurningLed(void *pdParamenters){
    char buttonPressed = 0;
    while(1){
        // Verifica se há algum botão pressionado na fila
        if(xQueueReceive(xQueueButtons, &buttonPressed, portMAX_DELAY) == pdTRUE){
            
            if(buttonPressed == 'A'){
                gpio_put(LED_PIN_1, 1);
                gpio_put(LED_PIN_2, 0);
                gpio_put(LED_PIN_3, 0);
                printf("LED 1 aceso\n");
                vTaskDelay(500 / portTICK_PERIOD_MS);
                gpio_put(LED_PIN_1, 0);
            }else if(buttonPressed == 'B'){
                gpio_put(LED_PIN_1, 0);
                gpio_put(LED_PIN_2, 1);
                gpio_put(LED_PIN_3, 0);
                printf("LED 2 aceso\n");
                vTaskDelay(500 / portTICK_PERIOD_MS);
                gpio_put(LED_PIN_2, 0);
            }
        }
    }
}