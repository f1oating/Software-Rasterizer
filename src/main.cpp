#include <iostream>
#include "TGAImage.h"
#include <cmath>
#include <chrono>
#include <random>

constexpr Color WHITE = { 255, 255, 255, 255 };
constexpr Color GREEN = { 0, 255, 0, 255 };
constexpr Color RED = { 0, 0, 255, 255 };
constexpr Color BLUE = { 255, 128, 64, 255 };
constexpr Color YELLOW = { 0, 200, 255, 255 };

void line(int ax, int ay, int bx, int by, TGAImage& framebuffer, Color color)
{
    bool steep = std::abs(ax - bx) < std::abs(ay - by);
    if (steep)
    {
        std::swap(ax, ay);
        std::swap(bx, by);
    }
    if (ax > bx)
    {
        std::swap(ax, bx);
        std::swap(ay, by);
    }
    for (float x = ax; x < bx; x++)
    {
        float t = (x - ax) / static_cast<float>(bx - ax);
        int y = std::round(ay + (by - ay) * t);
        if (steep)
        {
            framebuffer.Set(y, x, color);
        } else
        {
            framebuffer.Set(x, y, color);
        }
    }
}

int main()
{
    TGAImage framebuffer(64, 64, TGAImage::RGB);

    std::srand(std::time({}));
    for (int i = 0; i < (1 << 24); i++) 
    {
        int ax = rand() % 64, ay = rand() % 64;
        int bx = rand() % 64, by = rand() % 64;
        line(ax, ay, bx, by, framebuffer, { 
            static_cast<uint8_t>(rand() % 255), 
            static_cast<uint8_t>(rand() % 255), 
            static_cast<uint8_t>(rand() % 255), 
            static_cast<uint8_t>(rand() % 255) 
        });
    }

    framebuffer.WriteFile("test.tga");

    std::cout << "Done!" << std::endl;
}