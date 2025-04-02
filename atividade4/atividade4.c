#include <stdio.h>
#include "pico/stdlib.h"
#include "include/leds/leds.h"
#include "include/display/display.h"
#include "include/joystick/joystick.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

void setup_init_all(void);
void vTaskJoystickRead(void *pdParameters);
void vTaskMatrixControl(void *pdParameters);
void vTaskDisplayUpdate(void *pdParameters);

QueueHandle_t xJoystickQueue;   // Fila para dados do joystick
SemaphoreHandle_t xOledMutex;   // Mutex para acesso ao display OLED
SemaphoreHandle_t xDataMutex;   // Mutex para acesso a dados compartilhados

int main(void){

    setup_init_all();

    // Criação da fila apra os dados do joystick
    xJoystickQueue = xQueueCreate(15, sizeof(Joystick));
    if(xJoystickQueue == NULL){
        printf("Erro na criação da fila do joystick\n");
        return -1;
    }

    // Criação do mutex para o display OLED
    xOledMutex = xSemaphoreCreateMutex();
    xDataMutex = xSemaphoreCreateMutex();
    if(xOledMutex == NULL || xDataMutex == NULL){
        printf("Erro na criação do mutex\n");
        return -1;
    }

    // Criação das tarefas - removidas as chamadas duplicadas
    if(xTaskCreate(vTaskJoystickRead, "Joystick Read", 256, NULL, 1, NULL) != pdPASS){
        printf("Erro na criação da tarefa de leitura do joystick\n");
        return -1;
    }
    
    if(xTaskCreate(vTaskMatrixControl, "Matrix Control", 256, NULL, 2, NULL) != pdPASS){
        printf("Erro na criação da tarefa de controle da matriz\n");
        return -1;
    }
    
    // Descomente essas linhas se precisar ativar a tarefa do display
    if(xTaskCreate(vTaskDisplayUpdate, "Display Update", 256, NULL, 2, NULL) != pdPASS){
       printf("Erro na criação da tarefa de atualização do display\n");
       return -1;
    }

    vTaskStartScheduler(); // Inicia o escalonador do FreeRTOS
    while(1);
    return 0;
}


/* Função de inicialização de todos os componentes
* Inicializa o display, joystick e LEDs
*/
void setup_init_all(void){
    stdio_init_all();
    sleep_ms(1000);
    display_init();
    joystick_init();
    npInit(LED_PIN);
    npClear();
    display_clear();
}

void vTaskJoystickRead(void *pdParameters){
    Joystick joystick_data;
    while(1){
        read_joystick(&joystick_data); // Leitura dos dados do joystick
        int x_value = joystick_data.x_position / 20 < 4 ?  joystick_data.x_position / 20 : 4; // Limita o valor máximo a 4
        int y_value = joystick_data.y_position / 20 < 4 ?  joystick_data.y_position / 20 : 4; // Limita o valor máximo a 4
        joystick_data.x_position = x_value;
        joystick_data.y_position = y_value;
        
        // Enviar duas cópias para a fila (uma para cada tarefa consumidora)
        if(xQueueSend(xJoystickQueue, &joystick_data, 0) != pdTRUE){
            printf("Erro ao enviar dados do joystick para a fila\n");
        }
        
        printf("Joystick X: %d, Y: %d\n", joystick_data.x_position, joystick_data.y_position);
        vTaskDelay(100 / portTICK_PERIOD_MS); // Delay de 100ms
    }
}

void vTaskMatrixControl(void *pdParameters){
    Joystick joystick_data_recive;
    while(1){
        if(xQueueReceive(xJoystickQueue, &joystick_data_recive, portMAX_DELAY) == pdTRUE){
            // Atualiza os LEDs com base na posição do joystick
            
            xSemaphoreTake(xDataMutex, portMAX_DELAY); // Toma o mutex para acesso seguro aos dados

            uint8_t index_matriz;
            if((joystick_data_recive.y_position % 2) == 0){
                index_matriz = joystick_data_recive.y_position * 5 + (4 - joystick_data_recive.x_position); 
            }
            else{
                index_matriz = joystick_data_recive.y_position * 5 + (joystick_data_recive.x_position);
            }

            xSemaphoreGive(xDataMutex); // Libera o mutex   

            // Limpando o led anterior
            npClear();
            // Acende o LED correspondente
            npSetLED(index_matriz, 3, 0, 0); // Acende o LED na posição correspondente
            npWrite(); // Atualiza os LEDs
            vTaskDelay(100 / portTICK_PERIOD_MS); // Delay de 100ms
        }
    }
}

void vTaskDisplayUpdate(void *pdParameters){
    Joystick joystick_data_recive;
    while(1){
        // Usar um timeout menor para esperar por dados, sem bloquear indefinidamente
        if(xQueueReceive(xJoystickQueue, &joystick_data_recive, 100 / portTICK_PERIOD_MS) == pdTRUE){
            // Tomar o mutex de dados antes de processar
            if(xSemaphoreTake(xDataMutex, 10 / portTICK_PERIOD_MS) == pdTRUE) {
                // Processamento aqui com semáforo adquirido
                int x_pos = joystick_data_recive.x_position;
                int y_pos = joystick_data_recive.y_position;
                xSemaphoreGive(xDataMutex); // Libera o mutex
                
                // Tomar o mutex do display com timeout para evitar bloqueios
                if(xSemaphoreTake(xOledMutex, 10 / portTICK_PERIOD_MS) == pdTRUE) {
                    display_clear();
                    char buffer_x_value[20];
                    sprintf(buffer_x_value, "Val. Eixo X: (%d)", x_pos);
                    char buffer_y_value[20];
                    sprintf(buffer_y_value, "Val. Eixo Y: (%d)", y_pos);
                    char *text[] = {buffer_x_value, buffer_y_value};
                    display_draw_text_lines(text, 2, 0); // Desenha o texto no display
                    display_update(); // Atualiza o display
                    xSemaphoreGive(xOledMutex); // Libera o mutex
                }
            }
        }
        // Adicionar um delay entre atualizações para evitar sobrecarga do sistema
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}