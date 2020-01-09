#pragma once

#include <stdint.h>

#define LEFT_BUTTON  0B01000000
#define RIGHT_BUTTON 0B00100000
#define UP_BUTTON    0B00010000
#define DOWN_BUTTON  0B00001000
#define A_BUTTON     0B00000100
#define B_BUTTON     0B00000010

class button {
private:
    struct btn;
    btn *btHandle;
    static void buttonHandler();
    static char buttonChar;
    static uint8_t buttonsState;
    static uint8_t previousButtonState;
    static uint8_t currentButtonState;
    
public:
    button();
    // void pollButtons();
    char readbutton();
    bool pressed(uint8_t buttons);
    bool notPressed(uint8_t buttons);
    
};