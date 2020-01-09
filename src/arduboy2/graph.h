#pragma once

#include <stdint.h>
#include "screen.h"


class graph : public screen
{
private:
    unsigned cursor_x;
    unsigned cursor_y;

public:
    graph();

    void printChar(int x, int y, char ch);
    void printString(int x, int y, const char* str);
    void printString(const char* str);
    void drawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color);
    void operator<<(const char *s);

    void setCursor(int16_t x, int16_t y);
    int16_t getCursorX();
    int16_t getCursorY();
    void fillScreen(uint8_t color);
    void drawFastVLine(int16_t x, int16_t y, uint8_t h, uint8_t color);
    void drawFastHLine(int16_t x, int16_t y, uint8_t w, uint8_t color);
    void fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color);
    void drawRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color);
    void drawCircleHelper(int16_t x0, int16_t y0, uint8_t r, 
            uint8_t corners, uint8_t color);
    void fillCircleHelper(int16_t x0, int16_t y0, uint8_t r, 
            uint8_t sides, int16_t delta,uint8_t color);
    void fillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color);
    void drawRoundRect(int16_t x, int16_t y, uint8_t w, 
            uint8_t h, uint8_t r, uint8_t color);
    void fillRoundRect
        (int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t r, uint8_t color);
};