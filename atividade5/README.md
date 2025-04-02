# 🎮 Atividade 05: Processamento de Eventos do Joystick com Limite

<div align="center">
  <h2>Filas e Semáforos de Contagem no FreeRTOS</h2>
  <p>
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="Joystick" src="https://img.shields.io/badge/Joystick-FF4500?style=for-the-badge&logo=game&logoColor=white" />
    <img alt="Filas" src="https://img.shields.io/badge/Filas-FF6B6B?style=for-the-badge&logo=stack-overflow&logoColor=white" />
    <img alt="Semáforos" src="https://img.shields.io/badge/Semáforos-6C3483?style=for-the-badge&logo=semaphore&logoColor=white" />
    <img alt="OLED" src="https://img.shields.io/badge/OLED-1E90FF?style=for-the-badge&logo=display&logoColor=white" />
  </p>
</div>

## 📋 Descrição do Projeto

Esta atividade implementa um sistema de processamento de eventos gerados por um joystick, com mecanismo de controle para evitar sobrecarga. Os eventos são detectados quando o joystick cruza o centro ou atinge as bordas, são armazenados em uma fila limitada e processados sequencialmente. Um semáforo de contagem controla quantos eventos podem estar pendentes, demonstrando técnicas avançadas de sincronização no FreeRTOS.

## 🔧 Funcionalidades Implementadas

- **Detecção de Eventos**: Identificação de movimentos específicos do joystick (cruzamento de centro, atingir bordas)
- **Fila Limitada**: Armazenamento temporário de eventos com capacidade máxima definida
- **Semáforo de Contagem**: Controle do número de eventos pendentes e sinalização para processamento
- **Feedback por Buzzer**: Resposta sonora diferenciada para cada tipo de evento
- **Visualização de Estado**: Display OLED mostrando informações sobre a fila e eventos processados

## 📊 Conceitos Abordados

- **Semáforos de Contagem**: Mecanismo para contar recursos disponíveis ou eventos pendentes
- **Filas com Timeout**: Gestão de situações onde a fila pode estar cheia
- **Detecção de Transições**: Monitoramento de mudanças de estado no joystick
- **Gerenciamento de Recursos**: Limitação deliberada para evitar sobrecarga do sistema
- **Acesso Concorrente**: Proteção de recursos compartilhados como o display OLED

## 📝 Detalhes da Implementação

O sistema implementa três tarefas principais:

1. **vTaskJoystickMonitor**:
   - Monitora continuamente o joystick para detectar eventos específicos
   - Quando detecta um evento, tenta adicioná-lo à fila com timeout zero
   - Se conseguir adicionar o evento, incrementa o semáforo de contagem
   - Se a fila estiver cheia, descarta o evento (evitando bloqueio)

2. **vTaskEventProcessor**:
   - Aguarda no semáforo de contagem até que haja eventos disponíveis
   - Quando um evento é sinalizado, extrai-o da fila e processa
   - Fornece feedback através do buzzer, com sons diferentes para cada tipo de evento
   - Atualiza o display com informações sobre o evento processado

3. **vTaskDisplayStatus** (opcional):
   - Atualiza periodicamente o display com informações sobre o estado da fila
   - Mostra quantos eventos estão pendentes e o último evento processado
   - Usa mutex para garantir acesso seguro ao display OLED

## 🧠 Estruturas e Mecanismos

```c
// Tipos de eventos do joystick
typedef enum {
    EVENT_CENTER_CROSS,     // Joystick cruzou o centro
    EVENT_BORDER_HIT_X,     // Joystick atingiu extremo no eixo X
    EVENT_BORDER_HIT_Y,     // Joystick atingiu extremo no eixo Y
    EVENT_NONE              // Nenhum evento detectado
} JoystickEvent;

// Handles para comunicação e sincronização
QueueHandle_t xJoystickEventQueue;          // Fila para eventos do joystick (máx. 5)
SemaphoreHandle_t xEventAvailableSemaphore; // Semáforo de contagem (máx. 5)
SemaphoreHandle_t xOledMutex;               // Mutex para proteção do display OLED
```

## 🔄 Fluxo de Processamento de Eventos

```
┌────────────────────┐        ┌────────────────────┐        ┌────────────────────┐
│vTaskJoystickMonitor│        │                    │        │ vTaskEventProcessor │
└─────────┬──────────┘        │    Mecanismos      │        └──────────┬─────────┘
          │                   │   de Controle      │                   │
          │                   │                    │                   │
          │    Detecta        │                    │                   │
          │    Evento         │                    │                   │
          │                   │                    │                   │
          ▼                   │                    │                   │
    ┌──────────┐              │                    │                   │
    │Tenta Add │              │  ┌─────────────┐   │                   │
    │  à Fila  │─────────────►│  │  Fila de    │   │                   │
    └──────────┘              │  │  Eventos    │   │                   │
          │                   │  │  (max: 5)   │   │                   │
          │                   │  └─────────────┘   │                   │
          │ Se sucesso        │         ▲          │                   │
          ▼                   │         │          │                   │
    ┌──────────┐              │         │          │    ┌──────────┐   │
    │Incrementa│              │         └──────────┼────┤Decrementa│   │
    │Semáforo  │────────────►│  ┌─────────────┐   │    │Semáforo  │◄──┘
    └──────────┘              │  │ Semáforo de │   │    └──────────┘
                              │  │ Contagem    │   │          ▲
                              │  │ (max: 5)    │   │          │
                              │  └─────────────┘   │          │
                              │         │          │          │
                              └─────────┼──────────┘          │
                                        │                     │
                                        └─────────────────────┘
                                         Sinalização de evento
```

## 🚀 Como Compilar e Executar

1. Navegue até este diretório:
   ```bash
   cd atividade5
   ```

2. Crie e entre no diretório de build:
   ```bash
   mkdir -p build && cd build
   ```

3. Configure o projeto com CMake:
   ```bash
   cmake ..
   ```

4. Compile o projeto:
   ```bash
   make
   ```

5. Conecte o Raspberry Pi Pico W enquanto pressiona o botão BOOTSEL
6. Copie o arquivo `atividade5.uf2` para o dispositivo de armazenamento

## 📷 Diagrama de Conexão

```
          +-------------------+
          |                   |
          |   Raspberry Pi    |
          |      Pico W       |
          |                   |
          | ADC0(26) o--------+------ Joystick X
          |                   |
          | ADC1(27) o--------+------ Joystick Y
          |                   |
          | GPIO16   o--------+------ Buzzer
          |                   |
          | I2C_SDA(4) o------+------ OLED SDA
          |                   |
          | I2C_SCL(5) o------+------ OLED SCL
          |                   |
          +-------------------+
```

## 🎛️ Funcionamento

### Tarefa de Monitoramento (vTaskJoystickMonitor)

```c
void vTaskJoystickMonitor(void *pvParameters) {
    uint16_t last_x = 0, last_y = 0;
    uint16_t current_x, current_y;
    JoystickEvent event;
    
    while (1) {
        // Lê valores do joystick
        current_x = adc_read(0);  // ADC0 para X
        current_y = adc_read(1);  // ADC1 para Y
        
        event = EVENT_NONE;
        
        // Detecta cruzamento do centro (valor ~2048)
        if ((last_x < 2048 && current_x >= 2048) || 
            (last_x >= 2048 && current_x < 2048) ||
            (last_y < 2048 && current_y >= 2048) ||
            (last_y >= 2048 && current_y < 2048)) {
            event = EVENT_CENTER_CROSS;
        }
        // Detecta se atingiu borda X
        else if ((last_x > 100 && current_x <= 100) || 
                 (last_x < 3900 && current_x >= 3900)) {
            event = EVENT_BORDER_HIT_X;
        }
        // Detecta se atingiu borda Y
        else if ((last_y > 100 && current_y <= 100) || 
                 (last_y < 3900 && current_y >= 3900)) {
            event = EVENT_BORDER_HIT_Y;
        }
        
        // Se detectou evento, tenta adicionar à fila
        if (event != EVENT_NONE) {
            if (xQueueSend(xJoystickEventQueue, &event, 0) == pdPASS) {
                // Se conseguiu adicionar, incrementa o semáforo
                xSemaphoreGive(xEventAvailableSemaphore);
            } else {
                // Fila cheia, evento descartado
                // Opcional: Indicar descarte no display
            }
        }
        
        // Atualiza valores anteriores
        last_x = current_x;
        last_y = current_y;
        
        // Pequeno atraso para evitar detecção muito rápida
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
```

### Tarefa de Processamento (vTaskEventProcessor)

```c
void vTaskEventProcessor(void *pvParameters) {
    JoystickEvent event;
    
    while (1) {
        // Aguarda sinal do semáforo (há evento na fila)
        if (xSemaphoreTake(xEventAvailableSemaphore, portMAX_DELAY) == pdTRUE) {
            
            // Lê o evento da fila
            if (xQueueReceive(xJoystickEventQueue, &event, 0) == pdPASS) {
                // Processa o evento
                switch (event) {
                    case EVENT_CENTER_CROSS:
                        // Beep curto
                        gpio_put(BUZZER_PIN, 1);
                        vTaskDelay(pdMS_TO_TICKS(100));
                        gpio_put(BUZZER_PIN, 0);
                        break;
                        
                    case EVENT_BORDER_HIT_X:
                    case EVENT_BORDER_HIT_Y:
                        // Beep longo
                        gpio_put(BUZZER_PIN, 1);
                        vTaskDelay(pdMS_TO_TICKS(300));
                        gpio_put(BUZZER_PIN, 0);
                        break;
                        
                    default:
                        break;
                }
                
                // Atualiza display com o evento processado
                if (xSemaphoreTake(xOledMutex, portMAX_DELAY) == pdTRUE) {
                    // Atualizar display com o evento
                    display_clear();
                    display_text(0, 0, "Ultimo evento:");
                    display_text(0, 16, event_to_string(event));
                    display_update();
                    xSemaphoreGive(xOledMutex);
                }
            }
        }
    }
}
```

## 🔍 Resultados Esperados

- **Estado Inicial**: Display mostra "Eventos na Fila: 0"
- **Movimentos do Joystick**: 
  - Quando cruza o centro: gera EVENT_CENTER_CROSS
  - Quando atinge borda em X: gera EVENT_BORDER_HIT_X
  - Quando atinge borda em Y: gera EVENT_BORDER_HIT_Y
- **Feedback do Buzzer**:
  - Beep curto para cruzamento do centro
  - Beep longo para atingir as bordas
- **Comportamento da Fila**: 
  - Se eventos rápidos forem gerados, a fila atinge o limite (5)
  - Eventos adicionais são descartados até que haja espaço na fila
- **Display**: Mostra o último evento processado e o número de eventos pendentes

## 📐 Pontos de Atenção Técnica

1. **Sincronização Fila-Semáforo**:
   - O semáforo é incrementado somente se o evento foi adicionado à fila com sucesso
   - Isso mantém o semáforo sincronizado com o número real de eventos na fila

2. **Ordem de Operações**:
   - vTaskEventProcessor primeiro aguarda o semáforo e depois tenta ler da fila
   - Esta ordem é crucial para evitar leituras da fila quando não há itens

3. **Prevenção de Deadlock**:
   - O timeout zero em xQueueSend evita bloqueio da tarefa se a fila estiver cheia
   - O mutex para OLED é sempre adquirido e liberado na mesma tarefa

4. **Detecção de Transições**:
   - Eventos são gerados apenas nas transições de estado do joystick
   - Armazenamento de valores anteriores permite detectar apenas mudanças

## 📚 Recursos Adicionais

- [FreeRTOS Semáforo de Contagem](https://www.freertos.org/Real-time-embedded-RTOS-Counting-Semaphores.html)
- [FreeRTOS Filas](https://www.freertos.org/Embedded-RTOS-Queues.html)
- [Configuração do ADC no Raspberry Pi Pico](https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__adc.html)
- [Joysticks com Raspberry Pi Pico](https://microcontrollerslab.com/analog-joystick-raspberry-pi-pico/)

---

<div align="center">
  <p>Atividade desenvolvida para aprendizado de sistemas de controle de fluxo usando filas e semáforos no FreeRTOS</p>
</div>