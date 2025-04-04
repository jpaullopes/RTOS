# 🔄 Atividade Multicore 1: Processamento Paralelo no Raspberry Pi Pico W

<div align="center">
  <h2>Explorando as Capacidades Multicore do RP2040</h2>
  <p>
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="Multicore" src="https://img.shields.io/badge/Multicore-FF6347?style=for-the-badge&logo=chip&logoColor=white" />
    <img alt="Paralelismo" src="https://img.shields.io/badge/Paralelismo-1E90FF?style=for-the-badge&logo=parallel&logoColor=white" />
    <img alt="Raspberry Pi" src="https://img.shields.io/badge/Raspberry%20Pi-C51A4A?style=for-the-badge&logo=Raspberry-Pi&logoColor=white" />
    <img alt="Wi-Fi" src="https://img.shields.io/badge/Wi--Fi-4285F4?style=for-the-badge&logo=wifi&logoColor=white" />
  </p>
</div>

## 📋 Descrição do Projeto

Esta atividade implementa um sistema multicore no Raspberry Pi Pico W, explorando o potencial dos dois núcleos ARM Cortex-M0+ do RP2040. O projeto demonstra como distribuir tarefas entre os núcleos, com o Core 0 lidando com a leitura do joystick e o Core 1 encarregado da exibição de dados no display OLED.

## 🔧 Funcionalidades Implementadas

- **Divisão de Responsabilidades**: Cada núcleo com funções específicas e otimizadas
- **FreeRTOS em Ambos os Núcleos**: Gerenciamento independente de tarefas em cada processador
- **Leitura de Joystick**: Core 0 captura dados do joystick analógico
- **Exibição no Display**: Core 1 processa e atualiza o display OLED com os valores do joystick
- **Comunicação via Fila**: Troca de dados entre os núcleos usando filas do FreeRTOS

## 🔮 Funcionalidades Futuras

- **Comunicação Wi-Fi pelo Core 0**: Implementação de envio de dados para servidor remoto
- **Processamento em Tempo Real no Core 1**: Enquanto o Core 0 gerencia a comunicação Wi-Fi
- **Processamento de Sensores**: Leitura e processamento de múltiplos sensores distribuídos entre os núcleos

## 📊 Conceitos Abordados

- **Programação Multicore**: Divisão de trabalho entre múltiplos processadores
- **Comunicação Interprocessador**: Mecanismos seguros para troca de dados entre núcleos
- **Filas Compartilhadas**: Uso de filas do FreeRTOS para transferência de dados entre núcleos
- **Escalonamento Independente**: Cada núcleo executa seu próprio escalonador do FreeRTOS
- **Balanceamento de Carga**: Distribuição adequada do trabalho entre os processadores

## 📝 Implementação e Distribuição de Tarefas

1. **Core 0**:
   - Inicialização de todos os módulos do sistema
   - Tarefa `xTaskJoystick`: Leitura periódica do joystick analógico
   - Envio dos dados do joystick para uma fila compartilhada
   - Gerenciamento do FreeRTOS para o Core 0

2. **Core 1**:
   - Tarefa `xTaskExibition`: Recebe dados da fila compartilhada
   - Processa e formata os valores do joystick
   - Atualiza o display OLED com as informações formatadas
   - Gerenciamento do FreeRTOS para o Core 1

## 🔄 Mecanismos de Comunicação Intercore

```c
// Criação da fila compartilhada entre os núcleos
QueueHandle_t xQueueJoytick = xQueueCreate(15, sizeof(Joystick));

// Envio de dados do joystick pelo Core 0
if(xQueueSend(xQueueJoytick, &joystick_data, 10 / portMAX_DELAY) != pdPASS){
    printf("Erro ao criar ao enviar os dados apra a fila\n");
}

// Recebimento dos dados no Core 1
if(xQueueReceive(xQueueJoytick, &joystick_data_recive, 10 / portMAX_DELAY) == pdPASS){
    // Processamento dos dados recebidos
    // Atualização do display
}
```

## 🚀 Como Compilar e Executar

1. Navegue até este diretório:
   ```bash
   cd multicore/atividade-Multicore1
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
6. Copie o arquivo `atividade-Multicore1.uf2` para o dispositivo de armazenamento

## 📊 Arquitetura do Sistema

```
  Core 0 (FreeRTOS)                   Core 1 (FreeRTOS)
┌─────────────────────┐            ┌─────────────────────┐
│                     │            │                     │
│  ┌───────────────┐  │            │  ┌───────────────┐  │
│  │ xTaskJoystick │  │  Fila      │  │ xTaskExibition│  │
│  │               │  │  de        │  │               │  │
│  │ - Lê joystick │  │  dados     │  │ - Atualiza    │  │
│  │ - Envia dados │──┼──────────► │  │  display OLED │  │
│  └───────────────┘  │            │  └───────────────┘  │
│                     │            │                     │
└─────────────────────┘            └─────────────────────┘
        │                                     │
        │                                     │
        ▼                                     ▼
┌─────────────────────────────────────────────────────┐
│                 Hardware Compartilhado              │
│      (Joystick, Display OLED, Memória, GPIO)        │
└─────────────────────────────────────────────────────┘
```

## 🌐 Implementação Futura de Comunicação Wi-Fi

```
┌─────────────────┐     ┌─────────────────┐
│                 │     │                 │
│  Raspberry Pi   │     │    Servidor     │
│  Pico W         │     │    Remoto       │
│  (Core 0)       │◄───►│                 │
│                 │     │                 │
└─────────────────┘     └─────────────────┘
        ▲
        │
        │
┌─────────────────┐
│                 │
│  Processamento  │
│  (Core 1)       │
│                 │
└─────────────────┘
```

## 🔍 Desafios e Considerações

1. **Sincronização de Filas**:
   - Garantir que o envio e recebimento de dados entre núcleos seja seguro
   - Evitar estouros de fila ou perda de dados

2. **Balanceamento de Carga**:
   - Distribuição adequada de tarefas entre os núcleos
   - Evitar que um núcleo fique sobrecarregado enquanto o outro está ocioso

3. **Gerenciamento de Recursos**:
   - Acesso adequado a recursos compartilhados como I2C para o display
   - Priorização correta das tarefas em cada núcleo

4. **Implementação Futura do Wi-Fi**:
   - Isolamento das operações Wi-Fi no Core 0 para não interferir no processamento do Core 1
   - Gerenciamento eficiente do consumo de energia durante transmissões

## 📚 Recursos Adicionais

- [Documentação Oficial do RP2040 sobre Multicore](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
- [SDK da Raspberry Pi Pico - Programação Multicore](https://raspberrypi.github.io/pico-sdk-doxygen/group__pico__multicore.html)
- [FreeRTOS e Multiprocessamento](https://www.freertos.org/symmetric-multiprocessing-introduction.html)
- [SDK do Raspberry Pi Pico W para Wi-Fi](https://datasheets.raspberrypi.com/picow/connecting-to-the-internet-with-pico-w.pdf)

---

<div align="center">
  <p>Atividade desenvolvida para aprendizado de programação multicore combinada com FreeRTOS no Raspberry Pi Pico W</p>
</div>