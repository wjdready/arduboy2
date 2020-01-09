#include "screen.h"
#include <cstring>
#include <iostream>

/**
 * screen 类的构造函数
 * 
 * 会根据显示器的宽高来创建显示缓冲区的大小
 */ 
screen::screen(unsigned width, unsigned height)
        : HEIGHT{height}, WIDTH{width} 
{
    buffer = new unsigned char[HEIGHT*WIDTH];
}


/**
 * screen 类的默认构造函数
 * 默认显示范围 128*64 
 */ 
screen::screen() : HEIGHT{64}, WIDTH{128} 
{
    buffer = new unsigned char[HEIGHT*WIDTH];
}


/**
 * screen 析构函数
 * 
 * 对缓冲区的内存进行释放
 */ 
screen::~screen() {
    if(buffer != nullptr)
        delete buffer;
}


/**
 * 在指定坐标画一个点
 */ 
void screen::drawPixel(unsigned x, unsigned y, uint8_t color) 
{
    if(x < WIDTH && y < HEIGHT)
        buffer[y*WIDTH + x] = color;
}


/**
 * 清空显示缓冲区，使其只有单一的颜色
 */ 
void screen::clear(unsigned char color) 
{
    memset(buffer, color, WIDTH*HEIGHT);
}


/**
 * 将缓冲器中的图形显示出来
 * 
 * 目前指定显示到终端中
 */  
void screen::display() 
{
    using std::cout; using std::endl;

    system("clear");

    cout << '+';
    for(int i=0; i<WIDTH*2; i++)
        cout << '-';
    cout << "+" << endl;

    for(int i=0; i<HEIGHT; i++) {
        cout << '|';
        for(int j=0; j<WIDTH; j++)
            buffer[i*WIDTH+j] ? cout << "O " : cout << "  ";
        cout << "|" << endl;
    }

    cout << '+';
    for(int i=0; i<WIDTH*2; i++)
        cout << '-';
    cout << '+' << endl;
}


