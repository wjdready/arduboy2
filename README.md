# arduboy2 使用说明

这是一个支持移植到任意平台的 arduboy2 迷你像素游戏引擎，你只需提供 `./src/hardware` 文件夹里面的 screen 类和 button 类的实现并提供 public 接口，这个引擎就能正常工作，这个和硬件平台有关，现在工程提供的 hardware 是跑在类 unix 操作系统下的，它以终端作为显示屏，尽可能的不引用第三方库来实现 button 类和 srceen 类。实际上你完全可以移植到其他机器中或者用的图形界面来美化它。

你可以用任何手段任何第三方库实现以下两个类接口，只要它能正常工作，那么我们的 arduboy2 就能正常工作了

## 对于 screen 类
你需要提供默认构造函数 `screen::screen()` ，且默认的 arduboy2 掌机是 128*64 像素的，所以你需要在默认构造函数里面就设置好。
接着你只需要提供如下三个函数接口：
```cpp
// 在屏幕上绘制一个点
void drawPixel(unsigned x, unsigned y, uint8_t color);
// 清空缓冲区
void clear(uint8_t color);
// 刷新屏幕显示
void display();
```
如果你发现你的屏幕刷新不够快，那么可能是你的 display() 实现得不够高效，你可能需要新建一个缓冲区，然后在缓冲区显示的时候将缓冲区一并写入到实际的屏幕中去。

## 对于 button 类
这是用来提供输入的，同样你需要提供默认构造函数 button::button() 并在该构造函数中就初始化好你的 button 硬件。

接着你需要在 public 部分提供如下两个函数，为 arduboy2 应用提供按键是否按下。
```C
bool pressed(uint8_t buttons);
bool notPressed(uint8_t buttons);
```

