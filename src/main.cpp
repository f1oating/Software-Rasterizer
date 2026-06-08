#include <iostream>
#include "TGAImage.h"
#include <cmath>
#include <chrono>
#include <random>
#include "Model.h"

constexpr int WIDTH = 128;
constexpr int HEIGHT = 128;

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
    
    int y = ay;
    int iError = 0;
    
    for (float x = ax; x < bx; x++)
    {
        if (steep)
        {
            framebuffer.Set(y, x, color);
        } else
        {
            framebuffer.Set(x, y, color);
        }

        iError += 2 * std::abs(by - ay);
        y += (by > ay ? 1 : -1) * (iError > bx - ax);
        iError -= 2 * (bx - ax) * (iError > bx - ax);
    }
}

void triangle(int ax, int ay, int bx, int by,
    int cx, int cy, TGAImage& framebuffer, Color color)
{
    line(ax, ay, bx, by, framebuffer, color);
    line(bx, by, cx, cy, framebuffer, color);
    line(cx, cy, ax, ay, framebuffer, color);
}

std::tuple<int, int> project(vec3 vec)
{
    return {
        (vec.x + 1.0f) * WIDTH / 2,
        (vec.y + 1.0f) * HEIGHT / 2,
    };
}

int main()
{
    TGAImage framebuffer(WIDTH, WIDTH, TGAImage::RGB);

    Model model("res/diablo3_pose.obj");

    triangle(7, 45, 35, 100, 45, 60, framebuffer, RED);
    triangle(120, 35, 90, 5, 45, 110, framebuffer, WHITE);
    triangle(115, 83, 80, 90, 85, 120, framebuffer, GREEN);

    framebuffer.WriteFile("test.tga");

    std::cout << "Done!" << std::endl;
}