# 🎮 Atividade 02: Interação entre Botões e LEDs com Filas FreeRTOS

<div align="center">
  <h2>Comunicação com Filas no FreeRTOS</h2>
  <p>
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="Botões" src="https://img.shields.io/badge/Botões-4169E1?style=for-the-badge&logo=input&logoColor=white" />
    <img alt="LEDs" src="https://img.shields.io/badge/LEDs-FFD700?style=for-the-badge&logo=light&logoColor=black" />
    <img alt="Filas" src="https://img.shields.io/badge/Filas-FF6B6B?style=for-the-badge&logo=stack-overflow&logoColor=white" />
  </p>
</div>

## 📋 Descrição do Projeto

Este projeto demonstra a comunicação entre tarefas no FreeRTOS usando filas (Queues). A aplicação monitora dois botões e controla três LEDs com base nas entradas do usuário, ilustrando um padrão produtor-consumidor.

## 🔧 Funcionalidades Implementadas

- **Monitoramento de Botões**: Detecção de pressionamento nos botões A e B
- **Controle de LEDs**: Ativação sequencial de LEDs baseado na entrada dos botões
- **Comunicação entre Tarefas**: Uso de filas para transmitir eventos entre tarefas
- **Debounce de Hardware**: Implementação de atraso para evitar falsos acionamentos

## 📊 Conceitos Abordados

- **Filas FreeRTOS**: Mecanismo de comunicação entre tarefas
- **Padrão Produtor-Consumidor**: Uma tarefa produz eventos, outra consome
- **Entrada de Usuário**: Leitura e processamento de entradas via botões
- **Controle de Saída**: Ativação sequencial de LEDs

## 📝 Detalhes da Implementação

O sistema implementa duas principais tarefas:

1. **vTaskButtons**:
   - Monitora os botões A e B (pinos 5 e 6)
   - Quando um botão é pressionado, envia um caractere ('A' ou 'B') para a fila
   - Implementa um debounce de 200ms para evitar leituras duplicadas

2. **vTaskTurningLed**:
   - Aguarda mensagens na fila
   - Quando recebe 'A', acende o LED 1 (pino 11)
   - Quando recebe 'B', acende o LED 2 (pino 12)
   - Mantém o LED aceso por 500ms e depois o apaga

## 🚀 Como Compilar e Executar

1. Navegue até este diretório:
   ```bash
   cd atividade2
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
6. Copie o arquivo `atividade2.uf2` para o dispositivo de armazenamento

## 📷 Diagrama de Conexão

```
        +-----------------+
        |                 |
        |  Raspberry Pi   |
        |    Pico W       |
        |                 |
        |         GPIO11 o------- LED 1
        |                 |
        |         GPIO12 o------- LED 2
        |                 |
        |         GPIO13 o------- LED 3
        |                 |
        |          GPIO5 o---[BTN A]---GND
        |                 |
        |          GPIO6 o---[BTN B]---GND
        |                 |
        +-----------------+
```

## 🎛️ Funcionamento

1. Pressione o botão A para acender o LED 1 por 500ms
2. Pressione o botão B para acender o LED 2 por 500ms
3. Observe como a comunicação entre as tarefas ocorre através da fila
4. Os botões são configurados com pull-up interno, então conecte-os ao GND quando pressionados

## 🔍 Resultado Esperado

- LED 1 acende quando o botão A é pressionado
- LED 2 acende quando o botão B é pressionado
- Mensagens de depuração são enviadas pela porta serial (UART)

---

<div align="center">
  <p>Atividade desenvolvida para aprendizado de filas do FreeRTOS no Raspberry Pi Pico W</p>
</div>