#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "pico/stdlib.h"
#include "../oled/ssd1306.h"

// Definições de pinos para o I2C
#define DISPLAY_I2C_SDA 14
#define DISPLAY_I2C_SCL 15

/**
 * @brief Estrutura para área de renderização do display
 */
typedef struct render_area render_area_t;

/**
 * @brief Inicializa o display OLED
 * @return 1 se a inicialização foi bem-sucedida, 0 caso contrário
 */
int display_init(void);

/**
 * @brief Limpa o conteúdo do display
 */
void display_clear(void);

/**
 * @brief Desenha um texto no display
 * @param x Posição X do texto (coluna)
 * @param y Posição Y do texto (linha)
 * @param text Texto a ser desenhado
 */
void display_draw_text(uint8_t x, uint8_t y, const char *text);

/**
 * @brief Desenha múltiplas linhas de texto no display
 * @param text Array de strings a serem desenhadas
 * @param count Número de linhas de texto
 * @param y_start Posição Y inicial (linha)
 */
void display_draw_text_lines(char **text, uint8_t count, uint8_t y_start);

/**
 * @brief Desenha uma linha no display usando o algoritmo de Bresenham
 * @param x0 Coordenada X inicial
 * @param y0 Coordenada Y inicial
 * @param x1 Coordenada X final
 * @param y1 Coordenada Y final
 * @param color Cor da linha (true = ligado, false = desligado)
 */
void display_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);

/**
 * @brief Desenha um bitmap no display
 * @param bitmap Array de bytes contendo o bitmap
 */
void display_draw_bitmap(const uint8_t *bitmap);

/**
 * @brief Atualiza o conteúdo do display
 */
void display_update(void);

#endif /* DISPLAY_H */