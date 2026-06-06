#pragma once

#include <vector>
#include <cstdint>

struct Color
{
    uint8_t BGRA[4] = { 0, 0, 0, 0 };
    uint8_t BPP = 4;
};

struct Image
{
    Image(int width, int height, int bpp, Color color = {});

    void Set(int x, int y, Color& color);

    int Width = 0;
    int Height = 0;
    uint8_t BPP = 0;
    std::vector<uint8_t> Data;
};