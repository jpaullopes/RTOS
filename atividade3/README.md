# 🔊 Atividade 03: Controle de Buzzer com Semáforos FreeRTOS

<div align="center">
  <h2>Sincronização com Semáforos no FreeRTOS</h2>
  <p>
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="Semáforos" src="https://img.shields.io/badge/Semáforos-6C3483?style=for-the-badge&logo=semaphore&logoColor=white" />
    <img alt="Buzzer" src="https://img.shields.io/badge/Buzzer-FF5733?style=for-the-badge&logo=speaker&logoColor=white" />
    <img alt="GPIO" src="https://img.shields.io/badge/GPIO-ED1C24?style=for-the-badge&logo=raspberry-pi&logoColor=white" />
  </p>
</div>

## 📋 Descrição do Projeto

Esta atividade explora o uso de semáforos binários do FreeRTOS para sincronizar tarefas. O projeto implementa um sistema onde o pressionamento de um botão aciona um buzzer utilizando um semáforo como mecanismo de sincronização.

## 🔧 Funcionalidades Implementadas

- **Semáforo Binário**: Utilização de semáforo para sincronização entre tarefas
- **Detecção de Botões**: Monitoramento de botões para acionar eventos
- **Controle de Buzzer**: Acionamento temporizado de um buzzer
- **Sistema de Eventos**: O sistema reage a eventos externos (pressionamento de botão)

## 📊 Conceitos Abordados

- **Semáforos FreeRTOS**: Mecanismo de sincronização entre tarefas
- **Padrão Produtor-Consumidor**: Uma tarefa libera o semáforo, outra o consome
- **Sinalização de Eventos**: Uso de semáforo para sinalizar eventos entre tarefas
- **Temporização**: Controle preciso de tempos de acionamento

## 📝 Detalhes da Implementação

O sistema implementa duas tarefas principais:

1. **vTaskButtonA**:
   - Monitora o botão A conectado ao pino 5
   - Quando o botão é pressionado, libera o semáforo (xSemaphoreGive)
   - Implementa um pequeno debounce de 300ms

2. **vTaskBuzzer**:
   - Aguarda a liberação do semáforo (xSemaphoreTake)
   - Quando o semáforo é recebido, aciona o buzzer por 1 segundo
   - Após 1 segundo, desativa o buzzer

## 🚀 Como Compilar e Executar

1. Navegue até este diretório:
   ```bash
   cd atividade3
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
6. Copie o arquivo `atividade3.uf2` para o dispositivo de armazenamento

## 📷 Diagrama de Conexão

```
        +-----------------+
        |                 |
        |  Raspberry Pi   |
        |    Pico W       |
        |                 |
        |         GPIO21 o------- Buzzer ---+
        |                 |                 |
        |                 |                GND
        |                 |
        |          GPIO5 o---[BTN A]---GND
        |                 |
        |          GPIO6 o---[BTN B]---GND
        |                 |
        +-----------------+
```

## 🎛️ Funcionamento

1. Pressione o botão A
2. O semáforo é liberado pela tarefa vTaskButtonA
3. A tarefa vTaskBuzzer recebe o semáforo e aciona o buzzer
4. O buzzer permanece ativo por 1 segundo
5. O buzzer é desativado, e o ciclo pode se repetir

## 🔍 Resultado Esperado

- Quando o botão A é pressionado, o buzzer é ativado por 1 segundo
- Mensagens de debug são enviadas pela porta serial (UART)
- O semáforo garante a sincronização correta entre as tarefas

## 📚 Recursos Adicionais

- [Documentação sobre Semáforos Binários no FreeRTOS](https://www.freertos.org/Embedded-RTOS-Binary-Semaphores.html)
- [Tutorial sobre Buzzer no Raspberry Pi Pico](https://microcontrollerslab.com/raspberry-pi-pico-buzzer-tutorial/)

---

<div align="center">
  <p>Atividade desenvolvida para aprendizado de semáforos do FreeRTOS no Raspberry Pi Pico W</p>
</div>