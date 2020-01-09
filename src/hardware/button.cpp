#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "button.h"
#include <thread>
#include <iostream>
#include <unistd.h>

#define LEFT_BUTTON  0B01000000
#define RIGHT_BUTTON 0B00100000
#define UP_BUTTON    0B00010000
#define DOWN_BUTTON  0B00001000
#define A_BUTTON     0B00000100
#define B_BUTTON     0B00000010


struct button::btn {
    std::thread buttonThread;
};

char button::buttonChar = -1;

uint8_t button::buttonsState;


bool button::pressed(uint8_t buttons)
{
    uint8_t state = buttonsState;
    buttonsState &= ~buttons;
    return (state & buttons) == buttons;
}

bool button::notPressed(uint8_t buttons)
{
  return (buttonsState & buttons) == 0;
}


void button::buttonHandler()
{
    while(1) {
        buttonChar = getchar_unlocked();
        switch (buttonChar)
        {
        case 'w':
            buttonsState |= UP_BUTTON;
            break;
        case 's':
            buttonsState |= DOWN_BUTTON;
            break;
        case 'a':
            buttonsState |= LEFT_BUTTON;
            break;
        case 'd':
            buttonsState |= RIGHT_BUTTON;
            break;
        case 'j':
            buttonsState |= A_BUTTON;
            break;
        case 'k':
            buttonsState |= B_BUTTON;
            break;
        default:
            break;
        }
    }
}


button::button()
{
    // unix termios
    struct termios term;
    tcgetattr(0,&term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW,&term);

    // int flags = fcntl(0, F_GETFL, 0);
    // fcntl(0, F_SETFL, flags | O_NONBLOCK);

    btHandle = new btn;
    btHandle->buttonThread = std::thread(buttonHandler);
}


char button::readbutton()
{
    char tmp = buttonChar;
    buttonChar = -1;
    return tmp;
}