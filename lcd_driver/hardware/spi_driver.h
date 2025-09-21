#ifndef __SPI_DRIVER_H
#define __SPI_DRIVER_H


//BLK<->PA2
//CSX<->PA3
//DC <->PA4
//RST<->PA5
//SDA<-->PA7
//SCL<-->PA6
#include "gpio.h"
#include "lcd_font.h"
#define LCD_GPIO GPIOA
#define LCD_PIN_BL   GPIO_PIN_2
#define LCD_PIN_CSX  GPIO_PIN_3
#define LCD_PIN_DC   GPIO_PIN_4
#define LCD_PIN_RST  GPIO_PIN_5
#define LCD_PIN_SDA  GPIO_PIN_6
#define LCD_PIN_SCK  GPIO_PIN_7

#define SET_LCD_RST    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_RST,GPIO_PIN_SET);
#define SET_LCD_SDA    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_SDA,GPIO_PIN_SET);
#define SET_LCD_CSX    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_CSX,GPIO_PIN_SET);
#define SET_LCD_SCK    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_SCK,GPIO_PIN_SET);
#define SET_LCD_DC     HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_DC,GPIO_PIN_SET);
#define SET_LCD_BL     HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_BL,GPIO_PIN_SET);

#define CLR_LCD_RST    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_RST,GPIO_PIN_RESET);
#define CLR_LCD_SDA    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_SDA,GPIO_PIN_RESET);
#define CLR_LCD_CSX    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_CSX,GPIO_PIN_RESET);
#define CLR_LCD_SCK    HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_SCK,GPIO_PIN_RESET);
#define CLR_LCD_DC     HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_DC,GPIO_PIN_RESET);
#define CLR_LCD_BL     HAL_GPIO_WritePin(LCD_GPIO,LCD_PIN_BL,GPIO_PIN_RESET);

//RGB565
//R R R R R  G G G G G G  B B B B B 
//1 1 1 1 1  1 1 1 1 1 1  1 1 1 1 1  =white
//0 0 0 0 0  0 0 0 0 0 0  0 0 0 0 0  =black
//1 1 1 1 1  0 0 0 0 0 0  0 0 0 0 0  =red
//0 0 0 0 0  1 1 1 1 1 1  0 0 0 0 0  =green
//0 0 0 0 0  0 0 0 0 0 0  1 1 1 1 1  =blue
#define white 0xFFFF
#define black 0x0000
#define red   0xF800
#define green 0x07D0
#define blue  0x001F
void LCD_Init(void);
void LCD_clear(uint16_t color);
void LCD_Fill(uint8_t x_start,uint8_t y_start,uint8_t x_end,uint8_t y_end,uint16_t color);
void LCD_DrawPoint(uint8_t x,uint8_t y,uint16_t color);
void saber(void);
#endif