#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// Defines dos pinos
#define BUTTON_PIN_A 5
#define BUTTON_PIN_B 6
#define PIN_BUZZER_A 21

SemaphoreHandle_t xSemaphoreA;

void setupInit(void);
void vTaskButtonA(void *pdParameters);
void vTaskBuzzer(void *pdParameters);   

int main(void){
    setupInit();

    xSemaphoreA =  xSemaphoreCreateBinary();
    if ( xSemaphoreA == NULL){
        printf("Falha ao criar o semáforo A\n");
        return 1;
    }

    // Craindo as tasks
    xTaskCreate(vTaskButtonA, "Task button A", 500 , NULL, 1 , NULL);
    xTaskCreate(vTaskBuzzer, "Task Buzzer", 500 , NULL, 1 , NULL);

    // Iniciando o scheduler
    vTaskStartScheduler();
    while(1);
}

// Função que inicializa os pinos e o sistema
void setupInit(void){
    stdio_init_all();
    gpio_init(BUTTON_PIN_A);
    gpio_init(BUTTON_PIN_B);    
    gpio_init(PIN_BUZZER_A);
    gpio_set_dir(BUTTON_PIN_A, GPIO_IN);
    gpio_set_dir(BUTTON_PIN_B, GPIO_IN);
    gpio_set_dir(PIN_BUZZER_A, GPIO_OUT);
    gpio_pull_up(BUTTON_PIN_A);
    gpio_pull_up(BUTTON_PIN_B);

}

// Função que verifica o botão A para liberar o semafóro
void vTaskButtonA(void *pdParameters){
    while(1){
        if(gpio_get(BUTTON_PIN_A) == 0){
            xSemaphoreGive(xSemaphoreA);
            printf("Botão A pressionado\n");
            vTaskDelay(300 / portTICK_PERIOD_MS);
        }
    }
}

// Função que verifica o semáforo e ativa o buzzer

void vTaskBuzzer(void *pdParameters){
    while(1){
        if(xSemaphoreTake(xSemaphoreA, portMAX_DELAY) == pdTRUE){
            printf("Buzzer ativado\n");
            gpio_put(PIN_BUZZER_A, 1);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            gpio_put(PIN_BUZZER_A, 0);
            printf("Buzzer desativado\n");
        }
    }
}