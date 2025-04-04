# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(atividade-Multicore1 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(atividade-Multicore1
atividade-Multicore1.c 
include/joystick/joystick.c
include/display/display.c
include/leds/leds.c
include/oled/ssd1306_i2c.c)

pico_set_program_name(atividade-Multicore1 "atividade-Multicore1")
pico_set_program_version(atividade-Multicore1 "0.1")


include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(atividade-Multicore1 0)
pico_enable_stdio_usb(atividade-Multicore1 1)

pico_generate_pio_header(atividade-Multicore1 ${CMAKE_CURRENT_LIST_DIR}/ws2818b.pio)

# Add the standard library to the build
target_link_libraries(atividade-Multicore1
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(atividade-Multicore1 PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(atividade-Multicore1 
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        pico_stdlib
        pico_multicore 
        FreeRTOS-Kernel 
        FreeRTOS-Kernel-Heap4
        hardware_pwm
        hardware_adc
        )

pico_add_extra_outputs(atividade-Multicore1)

