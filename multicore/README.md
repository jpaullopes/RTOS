# 🔄 Multicore: FreeRTOS com Processamento Paralelo

<div align="center">
  <h2>Combinando FreeRTOS com Multicore no Raspberry Pi Pico W</h2>
  <p>
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="Multicore" src="https://img.shields.io/badge/Multicore-FF6347?style=for-the-badge&logo=chip&logoColor=white" />
    <img alt="Paralelismo" src="https://img.shields.io/badge/Paralelismo-1E90FF?style=for-the-badge&logo=parallel&logoColor=white" />
    <img alt="Raspberry Pi" src="https://img.shields.io/badge/Raspberry%20Pi-C51A4A?style=for-the-badge&logo=Raspberry-Pi&logoColor=white" />
  </p>
</div>

## 📋 Descrição do Projeto

Esta atividade explora o uso das capacidades multicore do Raspberry Pi Pico W em conjunto com o FreeRTOS. O RP2040 possui dois núcleos ARM Cortex-M0+ idênticos, e neste projeto exploramos como executar tarefas em paralelo distribuindo-as entre os dois núcleos para maximizar o desempenho e a eficiência do sistema.

## 🔧 Funcionalidades Implementadas

- **Processamento Paralelo**: Executar tarefas em dois núcleos simultaneamente
- **FreeRTOS no Core 0**: Gerenciamento de múltiplas tarefas no primeiro núcleo
- **Comunicação Intercore**: Troca de dados entre núcleos usando filas e spinlocks
- **Processamento Dedicado no Core 1**: Tarefas de tempo crítico isoladas no segundo núcleo
- **Sincronização**: Coordenação de operações entre os núcleos

## 📊 Conceitos Abordados

- **Programação Multicore**: Divisão de trabalho entre múltiplos processadores
- **Comunicação Interprocessador**: Mecanismos seguros para troca de dados entre núcleos
- **Spinlocks**: Primitivas de sincronização para acesso a recursos compartilhados
- **FIFOs de Hardware**: Comunicação eficiente entre núcleos usando hardware dedicado
- **Balanceamento de Carga**: Distribuição adequada do trabalho entre os processadores

## 📝 Detalhes da Implementação

O sistema implementa uma abordagem híbrida:

1. **Core 0**:
   - Executa o FreeRTOS com múltiplas tarefas gerenciadas pelo escalonador
   - Lida com comunicação, interface do usuário e operações não críticas
   - Envia comandos e dados para o Core 1 conforme necessário

2. **Core 1**:
   - Opera em um loop de execução dedicado sem overhead de escalonamento
   - Realiza operações de tempo crítico ou computacionalmente intensivas
   - Responde a comandos e solicitações vindas do Core 0

## 🔄 Estratégias de Comunicação Intercore

Existem várias estratégias para comunicação entre os núcleos:

1. **Hardware FIFO**: Canal dedicado de comunicação simples
2. **Memória compartilhada com spinlocks**: Acesso exclusivo a dados compartilhados
3. **Mailbox**: Estrutura dedicada para troca de mensagens
4. **Semáforos multicore**: Para sincronização entre núcleos

## 🚀 Como Compilar e Executar

1. Navegue até este diretório:
   ```bash
   cd multicore
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
6. Copie o arquivo `multicore.uf2` para o dispositivo de armazenamento

## 📊 Comparação entre Abordagens

| Aspecto                    | FreeRTOS Single Core                 | FreeRTOS + Core Dedicado             |
|----------------------------|--------------------------------------|--------------------------------------|
| Latência de tarefas        | Afetada pelo escalonamento           | Reduzida para tarefas críticas       |
| Previsibilidade            | Dependente da priorização            | Garantida no core dedicado           |
| Complexidade do código     | Média                                | Alta (comunicação intercore)         |
| Throughput                 | Limitado a um núcleo                 | Potencialmente dobrado               |
| Gerenciamento de recursos  | Centralizado                         | Distribuído                          |
| Debugging                  | Mais simples                         | Mais complexo                        |

## 📷 Diagrama de Funcionamento

```
  Core 0 (FreeRTOS)                     Core 1 (Dedicado)
┌─────────────────────┐              ┌─────────────────────┐
│                     │              │                     │
│  ┌───────────────┐  │  Comandos    │  ┌───────────────┐  │
│  │ Tarefa 1      │  │  ─────────►  │  │ Loop Principal│  │
│  └───────────────┘  │              │  └───────┬───────┘  │
│                     │              │          │          │
│  ┌───────────────┐  │              │  ┌───────▼───────┐  │
│  │ Tarefa 2      │  │              │  │ Processamento │  │
│  └───────────────┘  │              │  └───────┬───────┘  │
│                     │              │          │          │
│  ┌───────────────┐  │  Respostas   │  ┌───────▼───────┐  │
│  │ Tarefa 3      │  │  ◄─────────  │  │ Envio Resposta│  │
│  └───────────────┘  │              │  └───────────────┘  │
│                     │              │                     │
└─────────────────────┘              └─────────────────────┘
        │                                     │
        │                                     │
        ▼                                     ▼
┌─────────────────────────────────────────────────────┐
│                  Hardware Compartilhado              │
│   (Memória, GPIO, Periféricos, Spinlocks, FIFOs)    │
└─────────────────────────────────────────────────────┘
```

## 🔍 Desafios e Considerações

1. **Race Conditions**:
   - Uso adequado de spinlocks para proteger recursos compartilhados
   - Evitar deadlocks entre os núcleos

2. **Comunicação Eficiente**:
   - Minimizar a troca de dados entre núcleos
   - Uso de estruturas de dados lock-free quando possível

3. **Balanceamento de Carga**:
   - Distribuição adequada de tarefas entre os núcleos
   - Evitar que um núcleo fique sobrecarregado enquanto o outro está ocioso

4. **Debug**:
   - Técnicas para depurar sistemas multicore
   - Uso de ferramentas como Segger SystemView para visualizar a execução

## 📚 Recursos Adicionais

- [Documentação Oficial do RP2040 sobre Multicore](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
- [SDK da Raspberry Pi Pico - Programação Multicore](https://raspberrypi.github.io/pico-sdk-doxygen/group__pico__multicore.html)
- [FreeRTOS e Multiprocessamento](https://www.freertos.org/symmetric-multiprocessing-introduction.html)
- [Padrões de Design para Sistemas Multicore](https://www.embedded.com/design-patterns-for-multicore-systems/)

---

<div align="center">
  <p>Atividade desenvolvida para aprendizado de programação multicore combinada com FreeRTOS no Raspberry Pi Pico W</p>
</div>