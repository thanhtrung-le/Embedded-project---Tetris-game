#ifndef TETRIS_H_
#define TETRIS_H_
#include "stm32f1xx_hal.h"
#include "fonts.h"
#include "ssd1306.h"
#include "stdlib.h"
#include "string.h"
#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 128
#endif
/* SSD1306 LCD height in pixels */
#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 64
#endif
#ifndef START_X
#define START_X  120
#endif
#ifndef START_Y
#define START_Y  29
#endif
#ifndef BLOCK_WIDTH
#define BLOCK_WIDTH 12
#endif
#ifndef squareSize
#define squareSize 8
#endif
#ifndef BLOCK_HEIGHT
#define BLOCK_HEIGHT 12
#endif
// Kích thước khối
	void drawBlock(void);
	void drawSquare(void);
	void moveTBlockLeft(void);


#endif
