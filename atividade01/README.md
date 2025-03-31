# 🔆 Atividade 01: Controle de LEDs com FreeRTOS

<div align="center">
  <h2>Piscar LEDs com FreeRTOS</h2>
  <p>
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="GPIO" src="https://img.shields.io/badge/GPIO-ED1C24?style=for-the-badge&logo=raspberry-pi&logoColor=white" />
    <img alt="LEDs" src="https://img.shields.io/badge/LEDs-FFD700?style=for-the-badge&logo=light&logoColor=black" />
  </p>
</div>

## 📋 Descrição do Projeto

Esta atividade demonstra o uso básico do FreeRTOS com o Raspberry Pi Pico W para controlar LEDs. O objetivo principal é criar duas tarefas independentes que controlam dois LEDs diferentes, cada um com seu próprio padrão de intermitência.

## 🔧 Funcionalidades Implementadas

- **Inicialização do Sistema**: Configuração dos pinos GPIO e da UART
- **Tarefa LED 1**: Pisca o LED conectado ao pino 12 a cada 300ms
- **Tarefa LED 2**: Pisca o LED conectado ao pino 13 a cada 700ms
- **Escalonamento FreeRTOS**: Demonstração do escalonador cooperativo

## 📊 Conceitos Abordados

- **Multitarefa**: Execução de múltiplas tarefas concorrentes
- **Temporização**: Uso do vTaskDelay para controle preciso de tempos
- **Inicialização de Hardware**: Configuração de pinos GPIO
- **FreeRTOS**: Fundamentos de criação e gerenciamento de tarefas

## 📝 Detalhes da Implementação

O código implementa duas tarefas:

1. **vTaskLed1**: 
   - Controla o LED no pino 12
   - Ciclo de trabalho: 300ms ligado, 300ms desligado

2. **vTaskLed2**: 
   - Controla o LED no pino 13
   - Ciclo de trabalho: 700ms ligado, 700ms desligado

Essas tarefas rodam de forma independente graças ao escalonador do FreeRTOS.

## 🚀 Como Compilar e Executar

1. Navegue até este diretório:
   ```bash
   cd atividade01
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

5. Conecte o Raspberry Pi Pico W ao seu computador enquanto mantém pressionado o botão BOOTSEL
6. Copie o arquivo `atividade01.uf2` para o dispositivo de armazenamento que aparecer

## 📷 Diagrama de Conexão

```
        +-----------------+
        |                 |
        |  Raspberry Pi   |
        |    Pico W       |
        |                 |
        |                 |
        |         GPIO12 o------- LED 1
        |                 |
        |         GPIO13 o------- LED 2
        |                 |
        +-----------------+
```

## 🔍 Resultado Esperado

Quando executado corretamente, você verá:
- LED 1 piscando em intervalos de 300ms
- LED 2 piscando em intervalos de 700ms
- Ambos os LEDs operando de forma independente

---

<div align="center">
  <p>Atividade desenvolvida para aprendizado do Raspberry Pi Pico W com FreeRTOS</p>
</div>