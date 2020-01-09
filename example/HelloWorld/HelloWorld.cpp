#include <iostream>
#include <string>
#include <unistd.h>
#include "arduboy2.h"


int main()
{
    arduboy2 arduboy;
    arduboy.drawFastHLine(50, 5, 20, 1);
    arduboy.drawRect(20, 0, 50, 50, 1);
    arduboy.display();
    usleep(30*1000);
    arduboy.clear(0);
    
}