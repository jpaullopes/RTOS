#include "display.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "../oled/ssd1306.h"
#include "../oled/ssd1306_i2c.h"

// Buffer global para o display
static uint8_t display_buffer[ssd1306_buffer_length];

// Área de renderização global
static struct render_area display_frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};

// Variável para o bitmap
static ssd1306_t bitmap_display;

/**
 * @brief Inicializa o display OLED
 * @return 1 se a inicialização foi bem-sucedida, 0 caso contrário
 */
int display_init(void) {
    // Inicialização do i2c
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(DISPLAY_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(DISPLAY_I2C_SDA);
    gpio_pull_up(DISPLAY_I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Calcula o comprimento do buffer para a área de renderização
    calculate_render_area_buffer_length(&display_frame_area);
    
    // Limpa o display inicialmente
    display_clear();
    
    // Inicializa a estrutura do bitmap
    ssd1306_init_bm(&bitmap_display, 128, 64, false, 0x3C, i2c1);
    
    return 1; // Inicialização bem-sucedida
}


/**
 * @brief Limpa o conteúdo do display
 */
void display_clear(void) {
    // Zera todo o buffer do display
    memset(display_buffer, 0, ssd1306_buffer_length);
    render_on_display(display_buffer, &display_frame_area);
}

/**
 * @brief Desenha um texto no display
 * @param x Posição X do texto (coluna)
 * @param y Posição Y do texto (linha)
 * @param text Texto a ser desenhado
 */
void display_draw_text(uint8_t x, uint8_t y, const char *text) {
    ssd1306_draw_string(display_buffer, x, y, (char *)text); // Cast para corrigir o aviso
}

/**
 * @brief Desenha múltiplas linhas de texto no display
 * @param text Array de strings a serem desenhadas
 * @param count Número de linhas de texto
 * @param y_start Posição Y inicial (linha)
 */
void display_draw_text_lines(char **text, uint8_t count, uint8_t y_start) {
    int y = y_start;
    for (uint i = 0; i < count; i++) {
        ssd1306_draw_string(display_buffer, 5, y, text[i]);
        y += 8; // Avança para a próxima linha (cada caractere tem 8 pixels de altura)
    }
}

/**
 * @brief Desenha uma linha no display usando o algoritmo de Bresenham
 * @param x0 Coordenada X inicial
 * @param y0 Coordenada Y inicial
 * @param x1 Coordenada X final
 * @param y1 Coordenada Y final
 * @param color Cor da linha (true = ligado, false = desligado)
 */
void display_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color) {
    ssd1306_draw_line(display_buffer, x0, y0, x1, y1, color);
}

/**
 * @brief Desenha um bitmap no display
 * @param bitmap Array de bytes contendo o bitmap
 */
void display_draw_bitmap(const uint8_t *bitmap) {
    // Configura o display para o bitmap
    ssd1306_config(&bitmap_display);
    
    // Desenha o bitmap
    ssd1306_draw_bitmap(&bitmap_display, bitmap);
}

/**
 * @brief Atualiza o conteúdo do display
 */
void display_update(void) {
    // Atualiza o conteúdo do display com o buffer atual
    render_on_display(display_buffer, &display_frame_area);
}