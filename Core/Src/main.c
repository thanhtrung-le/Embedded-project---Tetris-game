/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fonts.h"
#include "ssd1306.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
char scoreText[10];
const short MARGIN_TOP = 2;
const short MARGIN_LEFT = 1;
const short SIZE = 4;
const short TYPES = 6;
short pieceX, pieceY;
short piece[2][4];
int interval = 500, score;
/* USER CODE END Includes */
int gameplay = 1;
uint32_t timer,delayer;
uint8_t b1, b2, b3;
uint16_t currentType, nextType, rotation;
uint8_t deepSleepFlag = 0;
uint8_t grid[25][12];





const char mantex_logo [] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xc0, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff,
		0xff, 0xc0, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
		0xff, 0xff, 0xc0, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x3f, 0xff, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x07, 0xff, 0xc0, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x01, 0xff, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x1f, 0xfc, 0x7f,
		0xe3, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x0f, 0xc0, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x1f, 0xfc,
		0x7f, 0xe3, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x07, 0xc0, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x1f,
		0xfc, 0x7f, 0xe3, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x07, 0xc0, 0xfc, 0x00, 0x3f, 0xff, 0xff, 0xf8,
		0x1f, 0xfc, 0xff, 0xe7, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x03, 0xc0, 0xfc, 0x00, 0x3f, 0xff, 0xff,
		0xf8, 0x1f, 0xf8, 0x00, 0x03, 0xff, 0x1f, 0xf8, 0x00, 0x00, 0x03, 0xc0, 0xfc, 0x00, 0x00, 0x00,
		0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xfc, 0x00, 0x00,
		0x00, 0x03, 0xf8, 0x1f, 0xfc, 0xff, 0xe7, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x01, 0xc0, 0xfc, 0x00,
		0x00, 0x00, 0x03, 0xf8, 0x1f, 0xfc, 0x7f, 0xe3, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x01, 0xc0, 0xf8,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x7f, 0xe3, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x01, 0xc0,
		0xf8, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x1f, 0xfc, 0x7f, 0xe3, 0xff, 0x3f, 0xf8, 0x00, 0x00, 0x01,
		0xc0, 0xf8, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xfc, 0x7f, 0xe3, 0xff, 0x3f, 0xf8, 0x00, 0x00,
		0x01, 0xc0, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x1f, 0xfc, 0xff, 0xe7, 0xff, 0x3f, 0xf8, 0x00,
		0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0x07, 0xe3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0x01, 0xe3, 0xf8, 0x1f, 0xfc, 0x7f, 0xe3, 0xff, 0x00,
		0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0x00, 0x63, 0xf8, 0x1f, 0xfc, 0x7f, 0xe3, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0x00, 0x03, 0xf8, 0x1f, 0xfc, 0x7f, 0xe3,
		0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0x00, 0x03, 0xf8, 0x1f, 0xfc, 0xff,
		0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x1f, 0xfc,
		0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x30, 0x00, 0x03, 0xf8, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x20, 0x00, 0x03, 0xf8,
		0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x00, 0x00, 0x03,
		0xf8, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0xff,
		0xff, 0xf8, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f,
		0xff, 0xff, 0xf8, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00,
		0x3f, 0xff, 0xff, 0xf8, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8,
		0x00, 0x3f, 0xff, 0xff, 0xf8, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0,
		0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
		0xc0, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0xc0, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x00, 0x00, 0xc3, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x00, 0x03, 0xf3, 0xf8, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x10, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x1f, 0xfc,
		0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x1f,
		0xfc, 0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x0f, 0xff, 0xff, 0xf8,
		0x1f, 0xfc, 0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0xfe, 0x1f,
		0xe0, 0x1f, 0xfc, 0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x3f, 0xe0,
		0x00, 0x00, 0x1f, 0xfc, 0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8, 0x00,
		0x3f, 0xff, 0xff, 0xf8, 0x10, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0xf8,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0,
		0xf8, 0x00, 0x3f, 0x00, 0x1f, 0xe0, 0x10, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
		0xc0, 0xf8, 0x00, 0x3f, 0x00, 0x7f, 0xf8, 0x10, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x01, 0xc0, 0xfc, 0x00, 0x3f, 0x00, 0xff, 0xf8, 0x1f, 0xf8, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x01, 0xc0, 0xfc, 0x00, 0x3f, 0x07, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x01, 0xc0, 0xfc, 0x00, 0x3f, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x01, 0xc0, 0xfc, 0x00, 0x3f, 0xff, 0xf3, 0xf8, 0x1f, 0xf8, 0x7f, 0xe3, 0xff,
		0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xfc, 0x00, 0x3f, 0xff, 0x83, 0xf8, 0x10, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0xfc, 0x00, 0x3f, 0xff, 0x03, 0xf8, 0x10, 0x00, 0x00,
		0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0xfc, 0x00, 0x1f, 0xfc, 0x00, 0xf8, 0x10, 0x00,
		0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0xfe, 0x00, 0x0f, 0xf0, 0x00, 0x18, 0x10,
		0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0xff, 0xfe, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0xff, 0xff, 0x80, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xc0, 0xff, 0xff, 0xe0,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0xff, 0xff,
		0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xc0
	};

const char pieces_S_l[2][2][4] = {{
                                    {0, 0, 1, 1}, {0, 1, 1, 2}
                                   },
                                   {
                                    {0, 1, 1, 2}, {1, 1, 0, 0}
                                   }};
const char pieces_S_r[2][2][4]={{
                                  {1, 1, 0, 0}, {0, 1, 1, 2}
                                 },
                                 {
                                  {0, 1, 1, 2}, {0, 0, 1, 1}
                                 }};

const char pieces_L_l[4][2][4] = {{
                                  {0, 0, 0, 1}, {0, 1, 2, 2}
                                 },
                                 {
                                  {0, 1, 2, 2}, {1, 1, 1, 0}
                                 },
                                 {
                                  {0, 1, 1, 1}, {0, 0, 1, 2}
                                 },
                                 {
                                  {0, 0, 1, 2}, {1, 0, 0, 0}
                                 }};
const char pieces_Sq[1][2][4] = {{
                                  {0, 1, 0, 1}, {0, 0, 1, 1}
                                 }};
const char pieces_T[4][2][4] = {{
                                  {0, 0, 1, 0},{0, 1, 1, 2}
                                 },
                                 {
                                  {0, 1, 1, 2},{1, 0, 1, 1}
                                 },
                                 {
                                  {1, 0, 1, 1},{0, 1, 1, 2}
                                 },
                                 {
                                  {0, 1, 1, 2},{0, 0, 1, 0}
                                 }};
const char pieces_l[2][2][4] = {{
                                  {0, 1, 2, 3}, {0, 0, 0, 0}
                                 },
                                 {
                                  {0, 0, 0, 0}, {0, 1, 2, 3}
                                 }};

void copyPiece(short piece[2][4], short type, short rotation){
  switch(type){
  case 0: //L_l
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_L_l[rotation][0][i];
      piece[1][i] = pieces_L_l[rotation][1][i];
    }
    break;
   case 1: //S_l
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_S_l[rotation][0][i];
      piece[1][i] = pieces_S_l[rotation][1][i];
    }
    break;
   case 2: //S_r
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_S_r[rotation][0][i];
      piece[1][i] = pieces_S_r[rotation][1][i];
    }
    break;
   case 3: //Sq
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_Sq[0][0][i];
      piece[1][i] = pieces_Sq[0][1][i];
    }
    break;
    case 4: //T
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_T[rotation][0][i];
      piece[1][i] = pieces_T[rotation][1][i];
    }
    break;
    case 5: //l
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_l[rotation][0][i];
      piece[1][i] = pieces_l[rotation][1][i];
    }
    break;
  }
}
void drawLayout(){
	SSD1306_DrawLine(110, 0, 110, SSD1306_HEIGHT, SSD1306_COLOR_WHITE);
	SSD1306_DrawRectangle(0, 0, SSD1306_WIDTH, SSD1306_HEIGHT, SSD1306_COLOR_WHITE);
	drawNextPiece();

}
void drawPiece(short type, short rotation, short x, short y){
  for(short i = 0; i < 4; i++)
	  SSD1306_DrawFilledRectangle(MARGIN_LEFT + (SIZE + 1)*(x + piece[0][i]), MARGIN_TOP + (SIZE + 1)*(y + piece[1][i]), SIZE, SIZE, SSD1306_COLOR_WHITE);
}
void drawGrid(){
  for(short x = 0; x < 25; x++)
    for(short y = 0; y < 12; y++)
      if(grid[x][y])
    	  SSD1306_DrawFilledRectangle(MARGIN_LEFT + (SIZE + 1)*x, MARGIN_TOP + (SIZE + 1)*y, SIZE, SIZE, SSD1306_COLOR_WHITE);
}
void drawNextPiece(){
  short nPiece[2][4];
  copyPiece(nPiece, nextType, 0);
  for(short i = 0; i < 4; i++)
	  SSD1306_DrawFilledRectangle(112 + 3*nPiece[0][i], 8 + 3*nPiece[1][i], 3, 3, SSD1306_COLOR_WHITE);
}
void refresh(){
	SSD1306_Fill(0);
    drawLayout();
    drawGrid();
    drawPiece(currentType, 0, pieceX, pieceY);
    SSD1306_UpdateScreen();
}
void generate(){
  currentType = nextType;
  nextType = customRandom();
  if(currentType != 5)
    pieceY = customRandomd();
  else
	  pieceY = customRandomd();
  pieceX = 18;
  rotation = 0;
  copyPiece(piece, currentType, rotation);
}
int customRandom() {
    uint32_t tick = HAL_GetTick();
    return (uint16_t)((tick / 1000) % 6);
}
int customRandomd() {
    uint32_t tick = HAL_GetTick();
    return (uint16_t)((tick / 1000) % 9);
}
int nextHorizontalCollision(short piece[2][4], int amount){
  for(short i = 0; i < 4; i++){
    short newX = pieceX + piece[0][i] + amount;
    short newY = pieceY + piece[1][i];
    if(grid[newX][newY]|| newY<=-1)
      return 1;
  }
  return 0;
}
int nextCollision() {
  for (short i = 0; i < 4; i++) {
    short y = pieceY + piece[1][i];
    short x =  pieceX + piece[0][i]-1;
    if (x < 0 || grid[x][y]) {
      return 1; // true
    }
  }
  return 0; // false
}
short getMaxRotation(short type){
  if(type == 1 || type == 2 || type == 5)
    return 2;
  else if(type == 0 || type == 4)
    return 4;
  else if(type == 3)
    return 1;
  else
    return 0;
}
int canRotate(short rotation){
  short piece[2][4];
  copyPiece(piece, currentType, rotation);
  return !nextHorizontalCollision(piece, 0);
}
void checkLines(){
  int full;
  for(short x = 19; x >= 0; x--){
    full = 1;
    for(short y = 0; y < 12; y++){
      full = full && grid[x][y];
    }
    if(full==1){
		breakLine(x);
		x--;
    }
  }
}
void hiendiem (int number) {
		SSD1306_Clear();
		SSD1306_GotoXY (0,20);
		SSD1306_Puts ("Score: ", &Font_11x18, 1);
		SSD1306_GotoXY (70, 20);
		char string[20];
		snprintf(string, sizeof(string), "%d", number);
		SSD1306_Puts (string, &Font_11x18, 1);
		SSD1306_GotoXY (0,0);
		SSD1306_Puts ("GAME", &Font_11x18, 1);
		SSD1306_GotoXY (50, 0);
		SSD1306_Puts ("OVER ", &Font_11x18, 1);
		SSD1306_UpdateScreen();
}

void breakLine(short line){
	for(short y = 0; y < 12; y++)
	{
		grid[y][0] = 0;
	}
	for (int x = line + 1; x < 20; x++)
	{
		for (char y = 2; y < 12; y++)
		{
		 if (grid[x][y]) grid[x-1][y] = 1;
		   else grid[x-1][y] = 0;
		}
	}
	  SSD1306_InvertDisplay(1);
	  SSD1306_InvertDisplay(0);
	  score = score + 10;
}
int checkCollision() {
	  for (int y = 0; y < 12; y++) {
	    if (grid[18][y] == 1) {
	      // Phát hiện một khối chạm lưới ở trên
	      return 1;
	    }
	  }
	  return 0;
	}
void restartGame() {
    // Khởi tạo lại các biến cần thiết
    score = 0;
    for (short x = 0; x < 25; x++)
        for (short y = 0; y < 13; y++)
            grid[x][y] = 0;
    generate();
    gameplay = 1;
}


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  timer = HAL_GetTick();
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  SSD1306_Clear();
  SSD1306_Init();
  SSD1306_DrawBitmap(0,0,mantex_logo, 130, 65,SSD1306_COLOR_WHITE);
  SSD1306_UpdateScreen();
  HAL_Delay(10000);
  SSD1306_Clear();
  drawLayout();
  nextType = customRandom();
  generate();
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if(HAL_GetTick()-timer>interval)
	  {
		__HAL_TIM_SET_AUTORELOAD(&htim2, 0);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
		if (checkCollision())
		{
		    int x;
		    for(x = 6; x < 8; x = x + 1)
		    {
		        __HAL_TIM_SET_AUTORELOAD(&htim2, x * 70);
		        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, x * 60);
		        HAL_Delay(300);
		    }
		// Kết thúc trò chơi
		      hiendiem(score) ;
		      HAL_Delay (5000);
		      restartGame();
		      SSD1306_Clear();
		      SSD1306_DrawBitmap(0,0,mantex_logo, 130, 65,SSD1306_COLOR_WHITE);
		      SSD1306_UpdateScreen();
		      HAL_Delay(2000);
		      SSD1306_Clear();
		}
		else
		{
			checkLines();
			refresh();
			if(nextCollision()==1)
			{
			for(short i = 0; i < 4; i++)
			grid[pieceX + piece[0][i]][pieceY + piece[1][i]] = 1;
			generate();
			}
			else
			pieceX--;
			timer = HAL_GetTick();
		}
	  }
	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
	  {
		  if (deepSleepFlag == 0)
		  {
			SSD1306_Clear();
			// Chuyển vào chế độ deep sleep
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
			HAL_SuspendTick();
			HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
			HAL_ResumeTick();
			deepSleepFlag = 1;
		  }
		  else
		  {
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
			deepSleepFlag = 0;
		  }
	  }

	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)==GPIO_PIN_SET)
	  {
		if(b1==1)
		{
			if(!nextHorizontalCollision(piece, -1))
			{
			    int x;
			    for(x = 4; x < 5; x = x + 1)
			    {
			        __HAL_TIM_SET_AUTORELOAD(&htim2, x * 70);
			        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, x * 60);
			        HAL_Delay(10);
			    }
				if (pieceY>0){
					pieceY--;
				refresh();
				}
				else
					refresh();
			}
		b1 = 0;
		}
	  }
	  else
	  {
		b1 = 1;
	  }

	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)==GPIO_PIN_SET)
	  {
		if(b2==1)
		{
			if(!nextHorizontalCollision(piece, 1))
			{
			    int x;
			    for(x = 4; x < 5; x = x + 1)
			    {
			        __HAL_TIM_SET_AUTORELOAD(&htim2, x * 70);
			        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, x * 60);
			        HAL_Delay(10);
			    }
				if (pieceY<11){
				pieceY++;
				refresh();
				}
				else
				refresh();
			}
		b2 = 0;
		}
	  }
	  else
	  {
		b2 = 1;
	  }
//	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==GPIO_PIN_SET)
//	  {
//	    int x;
//	    for(x = 4; x < 5; x = x + 1)
//	    {
//	        __HAL_TIM_SET_AUTORELOAD(&htim2, x * 70);
//	        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, x * 60);
//	        HAL_Delay(10);
//	    }
//	    interval = 20;
//	  }
//	  else
//	  {
//	    interval = 500;
//	  }
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==GPIO_PIN_SET){
	    if(b3==1){
		    int x;
		    for(x = 4; x < 5; x = x + 1)
		    {
		        __HAL_TIM_SET_AUTORELOAD(&htim2, x * 70);
		        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, x * 60);
		        HAL_Delay(10);
		    }
	      if(rotation == getMaxRotation(currentType) - 1 && canRotate(0)){
	        rotation = 0;
	      }else if(canRotate(rotation + 1)){
	        rotation++;
	      }
	      copyPiece(piece, currentType, rotation);
	      refresh();
	      b3 = 0;
	      timer = HAL_GetTick();
	    }
	  }else if(HAL_GetTick() - delayer > 50){
	    b3 = 1;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV8;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 429;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 254;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
