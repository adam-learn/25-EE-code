#ifndef __WS2812_H__
#define __WS2812_H__
 
 
#include "cover_headerfile_h.h"

#define WS2812_SPI_UNIT     hspi6
extern SPI_HandleTypeDef WS2812_SPI_UNIT;
 
 
//‘§…Ë—’…´±Ì
#define RED    0xFFFF0000
#define GREEN  0xFF00FF00
#define BLUE   0xFF0000FF
#define YELLOW 0xFFFFFF00
#define PINK   0xFFFFC0CB
#define ORANGE 0xFFDA6E00
#define PURPLE 0xFF800080
#define BLANK  0xFF000000 
 
 
void WS2812_Ctrl(uint8_t r, uint8_t g, uint8_t b);
void led_show(uint32_t aRGB);

#endif



