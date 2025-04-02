# 🎮 Atividade 04: Joystick Controla Matriz, Display Mostra Estado

<div align="center">
  <h2>Comunicação com Filas e Mutex no FreeRTOS</h2>
  <p>
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="Joystick" src="https://img.shields.io/badge/Joystick-FF4500?style=for-the-badge&logo=game&logoColor=white" />
    <img alt="LED Matrix" src="https://img.shields.io/badge/LED%20Matrix-00FFFF?style=for-the-badge&logo=led&logoColor=black" />
    <img alt="OLED" src="https://img.shields.io/badge/OLED-1E90FF?style=for-the-badge&logo=display&logoColor=white" />
    <img alt="Mutex" src="https://img.shields.io/badge/Mutex-9370DB?style=for-the-badge&logo=lock&logoColor=white" />
  </p>
</div>

## 📋 Descrição do Projeto

Esta atividade implementa um sistema interativo onde um joystick controla um ponto luminoso em uma matriz de LEDs RGB, enquanto um display OLED exibe as coordenadas atuais e a cor selecionada. O projeto demonstra o uso de filas para transmissão de dados entre tarefas e mutex para acesso seguro a recursos compartilhados.

## 🔧 Funcionalidades Implementadas

- **Controle via Joystick**: Leitura de ADCs para as coordenadas X/Y e um botão digital
- **Matriz de LEDs RGB**: Exibição de um ponto colorido que se move de acordo com o joystick
- **Display OLED**: Apresentação das coordenadas atuais e cor selecionada
- **Fila FreeRTOS**: Transmissão de dados do joystick entre tarefas
- **Mutex FreeRTOS**: Proteção do acesso ao display OLED e variáveis compartilhadas

## 📊 Conceitos Abordados

- **Comunicação entre Tarefas**: Uso de filas para transmitir dados do joystick
- **Sincronização**: Uso de mutex para acesso seguro a recursos compartilhados
- **Hardware Periférico**: Configuração de ADC, PIO para WS2812, I2C para OLED
- **Mapeamento de Coordenadas**: Conversão de leituras analógicas para coordenadas discretas
- **Race Conditions**: Prevenção de condições de corrida em acesso a dados compartilhados

## 📝 Detalhes da Implementação

O sistema implementa três tarefas principais:

1. **vTaskJoystickRead**:
   - Lê periodicamente os valores X e Y do joystick via ADC
   - Mapeia valores analógicos para coordenadas discretas da matriz
   - Detecta o estado do botão (pressionado/não pressionado)
   - Envia os dados para uma fila (`xJoystickQueue`)

2. **vTaskMatrixControl**:
   - Recebe dados do joystick da fila
   - Atualiza a posição e cor do pixel na matriz
   - Apaga o pixel antigo e acende o novo
   - Alterna a cor quando o botão é pressionado
   - Atualiza a matriz de LEDs RGB física

3. **vTaskDisplayUpdate**:
   - Adquire mutex para acessar dados compartilhados
   - Lê as coordenadas atuais e cor
   - Adquire mutex para acessar o display OLED
   - Formata e exibe as informações no display
   - Libera os mutex após o uso

## 🧠 Estruturas de Dados

```c
// Estrutura para os dados do joystick
typedef struct {
    int x_position;     // Coordenada X mapeada (0-4)
    int y_position;     // Coordenada Y mapeada (0-4)
} Joystick;

// Handles para comunicação e sincronização
QueueHandle_t xJoystickQueue;   // Fila para dados do joystick
SemaphoreHandle_t xOledMutex;   // Mutex para acesso ao display OLED/matriz LED
SemaphoreHandle_t xDataMutex;   // Mutex para acesso a dados compartilhados
```

## 🚀 Como Compilar e Executar

1. Navegue até este diretório:
   ```bash
   cd atividade4
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
   ninja
   ```

5. Conecte o Raspberry Pi Pico W enquanto pressiona o botão BOOTSEL
6. Copie o arquivo `atividade4.uf2` para o dispositivo de armazenamento

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
          | GPIO22   o--------+------ Joystick Button
          |                   |
          | GPIO28   o--------+------ WS2812 Data In
          |                   |
          | I2C_SDA(4) o------+------ OLED SDA
          |                   |
          | I2C_SCL(5) o------+------ OLED SCL
          |                   |
          +-------------------+
```

## 🔄 Fluxo de Dados e Sincronização

```
┌───────────────────┐     ┌───────────────────┐     ┌───────────────────┐
│ vTaskJoystickRead │     │ vTaskMatrixControl│     │ vTaskDisplayUpdate│
└─────────┬─────────┘     └────────┬──────────┘     └────────┬──────────┘
          │                         │                         │
          │  ┌──────────────┐       │                         │
          ├─▶│JoystickQueue │───────▶│                         │
          │  └──────────────┘       │                         │
          │                         │   ┌──────────┐          │
          │                         ├──▶│ DataMutex│◀─────────┤
          │                         │   └──────────┘          │
          │                         │                         │
          │                         │                         │
          │                         │                    ┌──────────┐
          │                         │                    │OledMutex │◀─┐
          │                         │                    └──────────┘  │
          │                         │                         │        │
          │                         │                         ├────────┘
          │                         │                         │
          │                         │                         │
┌─────────┴─────────┐     ┌────────┴──────────┐     ┌────────┴──────────┐
│   Ler Joystick    │     │   Atualizar LED   │     │  Atualizar OLED   │
└───────────────────┘     └───────────────────┘     └───────────────────┘
```

## 🎛️ Funcionamento

1. Mova o joystick para controlar a posição do ponto luminoso na matriz de LEDs
2. Pressione o botão do joystick para alternar entre as cores (Vermelho, Verde, Azul)
3. Observe o display OLED mostrando as coordenadas atuais e a cor selecionada
4. Experimente movimentos rápidos para ver o sistema respondendo em tempo real

## 🔍 Resultado Esperado

- O ponto na matriz de LEDs se move de acordo com o joystick
- A cor do ponto muda ao pressionar o botão do joystick
- O display OLED mostra as coordenadas (X,Y) atuais e a cor
- As operações são thread-safe, sem corrupção de dados ou interferência

## 🛠️ Solução para Race Conditions

O projeto implementa duas camadas de proteção contra race conditions:

1. **Dados do Joystick**: Transmitidos de forma segura através da fila (`xJoystickQueue`)
2. **Variáveis Compartilhadas**: Protegidas pelo mutex de dados (`xDataMutex`)
3. **Acesso ao Display**: Protegido pelo mutex do OLED (`xOledMutex`)

Isso garante que os dados não serão corrompidos mesmo com múltiplas tarefas operando em frequências diferentes.

## 📚 Recursos Adicionais

- [Documentação sobre Mutex no FreeRTOS](https://www.freertos.org/Real-time-embedded-RTOS-mutexes.html)
- [Guia para WS2812 LEDs com Raspberry Pi Pico](https://learn.adafruit.com/getting-started-with-raspberry-pi-pico-circuitpython/neopixel-leds)
- [Tutorial para Display OLED com Raspberry Pi Pico](https://how2electronics.com/interfacing-ssd1306-oled-display-with-raspberry-pi-pico/)

---

<div align="center">
  <p>Atividade desenvolvida para aprendizado de comunicação entre tarefas com FreeRTOS no Raspberry Pi Pico W</p>
</div>