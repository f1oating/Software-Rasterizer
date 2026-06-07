#include <iostream>
#include "TGAImage.h"

constexpr Color WHITE = { 255, 255, 255, 255 };
constexpr Color GREEN = { 0, 255, 0, 255 };
constexpr Color RED = { 0, 0, 255, 255 };
constexpr Color BLUE = { 255, 128, 64, 255 };
constexpr Color YELLOW = { 0, 200, 255, 255 };

int main()
{
    TGAImage framebuffer(64, 64, TGAImage::RGB);

    int ax = 7, ay = 3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.Set(ax, ay, WHITE);
    framebuffer.Set(bx, by, WHITE);
    framebuffer.Set(cx, cy, WHITE);

    framebuffer.WriteFile("test.tga");

    std::cout << "Done!" << std::endl;
}