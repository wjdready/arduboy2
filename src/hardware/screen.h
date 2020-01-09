#include <stdint.h>


class screen
{
private:
    uint8_t *buffer;
public:
    const unsigned HEIGHT = 64;
    const unsigned WIDTH = 128;

    screen(unsigned width, unsigned height);
    screen();
    ~screen();

    void drawPixel(unsigned x, unsigned y, uint8_t color);
    void clear(uint8_t color);
    void display();
    
};
