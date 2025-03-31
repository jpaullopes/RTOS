# 🚀 Projeto de Desenvolvimento com Raspberry Pi Pico W

<div align="center">
  <h1>Raspberry Pi Pico W</h1>
  <p>
    <img alt="Linguagem C" src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" />
    <img alt="FreeRTOS" src="https://img.shields.io/badge/FreeRTOS-8CC84B?style=for-the-badge&logo=freertos&logoColor=white" />
    <img alt="Raspberry Pi" src="https://img.shields.io/badge/Raspberry%20Pi-C51A4A?style=for-the-badge&logo=Raspberry-Pi&logoColor=white" />
    <img alt="Microcontroladores" src="https://img.shields.io/badge/Microcontroladores-217346?style=for-the-badge&logo=chip&logoColor=white" />
  </p>
</div>

## 📋 Sobre o Repositório

Este repositório contém uma série de tarefas e projetos desenvolvidos para o Raspberry Pi Pico W, com o objetivo de aprofundar meus conhecimentos em sistemas embarcados, FreeRTOS e programação de microcontroladores.

Cada atividade aborda diferentes conceitos e funcionalidades do Raspberry Pi Pico W, permitindo explorar suas capacidades e aplicações práticas no desenvolvimento de sistemas embarcados.

## 🛠️ Tecnologias Utilizadas

- **Raspberry Pi Pico W**: Microcontrolador baseado no RP2040
- **FreeRTOS**: Sistema operacional de tempo real
- **C/C++**: Linguagem de programação principal
- **CMake**: Sistema de construção dos projetos
- **PIO (Programmable I/O)**: Interface programável de entrada/saída do RP2040

## 📂 Estrutura do Projeto

O repositório está organizado em diferentes pastas, cada uma correspondendo a uma atividade específica:

- **[Atividade 01](./atividade01)**: Controle básico de LEDs usando tarefas do FreeRTOS
- **[Atividade 02](./atividade2)**: Interação entre botões e LEDs usando filas do FreeRTOS
- **[Atividade 03](./atividade3)**: Controle de buzzer utilizando semáforos do FreeRTOS

Cada pasta contém seu próprio README com informações detalhadas sobre a atividade.

## 🚦 Como Executar os Projetos

Cada projeto pode ser compilado e carregado no Raspberry Pi Pico W seguindo estas etapas:

1. Navegue até o diretório da atividade desejada
2. Execute o comando `mkdir -p build && cd build`
3. Configure o projeto com `cmake ..`
4. Compile com `make`
5. Conecte o Raspberry Pi Pico W ao computador enquanto pressiona o botão BOOTSEL
6. Carregue o arquivo `.uf2` na unidade de armazenamento que aparecerá

## 📚 Recursos Adicionais

- [Documentação Oficial do Raspberry Pi Pico W](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html)
- [Documentação do FreeRTOS](https://www.freertos.org/Documentation/RTOS_book.html)
- [SDK do Raspberry Pi Pico](https://github.com/raspberrypi/pico-sdk)

## 📝 Licença

Este projeto está sob a licença MIT.

---
<div align="center">
  <p>Desenvolvido com ❤️ para aprendizado e exploração do Raspberry Pi Pico W</p>
</div>