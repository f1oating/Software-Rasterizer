#include <iostream>
#include "TGAImage.h"
#include <cmath>
#include <chrono>
#include <random>
#include "Model.h"

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

std::tuple<int, int> project(vec3 vec)
{
    return {
        (vec.x + 1.0f) * 800 / 2,
        (vec.y + 1.0f) * 800 / 2,
    };
}

int main()
{
    TGAImage framebuffer(800, 800, TGAImage::RGB);

    Model model("res/diablo3_pose.obj");

    for (int i=0; i<model.NumFaces(); i++) 
    {
        auto [ax, ay] = project(model.Vertex(i, 0));
        auto [bx, by] = project(model.Vertex(i, 1));
        auto [cx, cy] = project(model.Vertex(i, 2));
        line(ax, ay, bx, by, framebuffer, RED);
        line(bx, by, cx, cy, framebuffer, RED);
        line(cx, cy, ax, ay, framebuffer, RED);
    }

    for (int i=0; i < model.NumVerts(); i++) 
    {
        vec3 v = model.Vertex(i);
        auto [x, y] = project(v);
        framebuffer.Set(x, y, WHITE);
    }

    framebuffer.WriteFile("test.tga");

    std::cout << "Done!" << std::endl;
}