#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// Defines dos pinos

#define LED_1 12
#define LED_2 13

void vTaskLed1(void *pvParameters);
void vTaskLed2(void *pvParameters);
void setupInit(void);

int main( void ){
    sleep_ms(2000); // Aguarda 2 segundos para estabilizar a energia
    setupInit();
    printf("INICIALIZAÇÃO FEITA\n");

    xTaskCreate(vTaskLed1, "LED1" , 256 , NULL, 1 ,NULL);
    xTaskCreate(vTaskLed2, "LED2" , 256 , NULL, 1 ,NULL);

    vTaskStartScheduler(); // Inicia o scheduler do FreeRTOS
    while(1);
    return 0;
}

void setupInit(void){
    printf("INICIALIZAÇÃO FEITA\n");
    stdio_init_all();
    gpio_init(LED_1);
    gpio_init(LED_2);
    gpio_set_dir(LED_1, GPIO_OUT);
    gpio_set_dir(LED_2, GPIO_OUT);
    gpio_put(LED_1, 0);
    gpio_put(LED_2, 0); 
}

void vTaskLed1(void *pvParameters){
    for(;;){
        gpio_put(LED_1, 1); //ligando led
        vTaskDelay(300 / portTICK_PERIOD_MS);
        gpio_put(LED_1, 0); //desligando led
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

void vTaskLed2(void *pvParameters){
    for(;;){
        gpio_put(LED_2, 1); // Ligando led
        vTaskDelay(700 / portTICK_PERIOD_MS);
        gpio_put(LED_2, 0); // Desligando led
        vTaskDelay(700 / portTICK_PERIOD_MS);
    }
}