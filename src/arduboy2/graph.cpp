#include <iostream>
#include <cstring>
#include "graph.h"
#include "font.h"


#define  max(x,y)    ((x) > (y) ? (x) : (y))
#define  min(x,y)    ((x) < (y) ? (x) : (y))


/* -------------- graph class -----------------*/

/**
 * 构造函数
 */ 
graph::graph()
{
    cursor_x = 0;
    cursor_y = 0;
}

/**
 * 设置光标位置
 */ 
void graph::setCursor(int16_t x, int16_t y)
{
  cursor_x = x;
  cursor_y = y;
}

/**
 * 获取光标的 x 轴位置
 */ 
int16_t graph::getCursorX()
{
  return cursor_x;
}

/**
 * 获取光标的 y 轴位置
 */ 
int16_t graph::getCursorY()
{
  return cursor_y;
}


/**
 * 在指定坐标打印一个字符
 */ 
void graph::printChar(int x, int y, char ch)
{
    unsigned char temp = (ch - 32), col;
    for(int i=0; i<6; i++) {
        col = ASCII_6X8[temp][i];
        for(int j=0; j<8; j++)
            drawPixel(x+i,y+j, col & (1<<j));
    }
}


/**
 * 直接在当前坐标打印字符串
 * 
 * 如果到达屏幕边界，则字符自动换行
 * 如果屏幕输出满了，则自动清屏
 */ 
void graph::printString(const char* str)
{
    while(*str){
        if(*str == '\r'){ str++; continue; }
        if(*str == '\n'){
            cursor_x = 0; cursor_y += 8;
            str++; continue;
        }
        if(cursor_x > WIDTH-6) { cursor_x = 0; cursor_y += 8; }
        if(cursor_y > HEIGHT-8) { clear(0); cursor_y = cursor_x = 0; }
        printChar(cursor_x, cursor_y, *str++);
        cursor_x += 6;
    }
}


/**
 * 在指定坐标打印字符串
 */ 
void graph::printString(int x, int y, const char* str)
{
    setCursor(x, y);
    printString(str);
}


/**
 * 在指定坐标上画一个圆
 */ 
void graph::drawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    drawPixel(x0, y0+r, color);
    drawPixel(x0, y0-r, color);
    drawPixel(x0+r, y0, color);
    drawPixel(x0-r, y0, color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }

        x++;
        ddF_x += 2;
        f += ddF_x;

        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 - x, y0 + y, color);
        drawPixel(x0 + x, y0 - y, color);
        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 + y, y0 - x, color);
        drawPixel(x0 - y, y0 - x, color);
    }
}

/**
 * 打印字符串重载
 */ 
void graph::operator<<(const char *s)
{
    printString(s);
}


/**
 * 画一条竖线
 * 
 * x,y 竖线的起点位置，h 竖线的高度
 */
void graph::drawFastVLine(int16_t x, int16_t y, uint8_t h, uint8_t color)
{
    for(int i=0; i<h; i++)
        drawPixel(x,i+y,color);
}

/**
 * 画一条横线
 * 
 * x,y 横线的起点位置，w 横线的宽度
 */
void graph::drawFastHLine(int16_t x, int16_t y, uint8_t w, uint8_t color)
{
    for(int i=0; i<w; i++)
        drawPixel(x+i, y, color);
}


/**
 * 画一个充填的一个长方形
 * 
 * x, y 长方形的起点位置
 * w, h 长方形的宽和高
 */ 
void graph::fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color)
{
    for (int16_t i=x; i<x+w; i++) {
        drawFastVLine(i, y, h, color);
    }
}


/**
 * 画一个空的长方形
 */ 
void graph::drawRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color)
{
    drawFastHLine(x, y, w, color);
    drawFastHLine(x, y+h-1, w, color);
    drawFastVLine(x, y, h, color);
    drawFastVLine(x+w-1, y, h, color);
}


/**
 * 画空圆辅助函数
 */ 
void graph::drawCircleHelper(int16_t x0, int16_t y0, uint8_t r, uint8_t corners, uint8_t color)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  while (x<y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    if (corners & 0x4) // lower right
    {
      drawPixel(x0 + x, y0 + y, color);
      drawPixel(x0 + y, y0 + x, color);
    }
    if (corners & 0x2) // upper right
    {
      drawPixel(x0 + x, y0 - y, color);
      drawPixel(x0 + y, y0 - x, color);
    }
    if (corners & 0x8) // lower left
    {
      drawPixel(x0 - y, y0 + x, color);
      drawPixel(x0 - x, y0 + y, color);
    }
    if (corners & 0x1) // upper left
    {
      drawPixel(x0 - y, y0 - x, color);
      drawPixel(x0 - x, y0 - y, color);
    }
  }
}


/**
 * 画实心圆辅助函数
 */ 
void graph::fillCircleHelper
(int16_t x0, int16_t y0, uint8_t r, uint8_t sides, int16_t delta,uint8_t color)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  while (x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    if (sides & 0x1) // right side
    {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }

    if (sides & 0x2) // left side
    {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}


/**
 * 画一个实心圆
 */ 
void graph::fillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color)
{
  drawFastVLine(x0, y0-r, 2*r+1, color);
  fillCircleHelper(x0, y0, r, 3, 0, color);
}


/**
 * 画一个空心的边角圆滑的四边形
 * 
 * x, y 四边形起点，在左上角位置
 * w, h 四边形的宽度和高度 
 * r 边角圆的半径
 */ 
void graph::drawRoundRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t r, uint8_t color)
{
  // smarter version
  drawFastHLine(x+r, y, w-2*r, color); // Top
  drawFastHLine(x+r, y+h-1, w-2*r, color); // Bottom
  drawFastVLine(x, y+r, h-2*r, color); // Left
  drawFastVLine(x+w-1, y+r, h-2*r, color); // Right
  // draw four corners
  drawCircleHelper(x+r, y+r, r, 1, color);
  drawCircleHelper(x+w-r-1, y+r, r, 2, color);
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
  drawCircleHelper(x+r, y+h-r-1, r, 8, color);
}

/**
 * 画一个实心的边角圆滑的四边形
 * 
 * x, y 四边形起点，在左上角位置
 * w, h 四边形的宽度和高度 
 * r 边角圆的半径
 */ 
void graph::fillRoundRect
(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t r, uint8_t color)
{
  // smarter version
  fillRect(x+r, y, w-2*r, h, color);

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
  fillCircleHelper(x+r, y+r, r, 2, h-2*r-1, color);
}

/**
 * 充满屏幕
 */ 
void graph::fillScreen(uint8_t color)
{
    clear(color);
}



