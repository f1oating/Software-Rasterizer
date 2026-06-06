#include "Image.h"

#include <cstring>

Image::Image(int width, int height, int bpp, Color color) : 
    Width(width), Height(height), BPP(bpp), Data((width * height) * bpp)
{
    for (int y = 0; y < Height; y++)
    {
        for (int x = 0; x < Width; x++)
        {
            Set(x, y, color);
        }
    }
}

void Image::Set(int x, int y, Color& color)
{
    if (!Data.size() || x < 0 || y < 0 || x > Width || y > Height) return;
    memcpy(Data.data() + (x + y * Width) * BPP, color.BGRA, BPP);
}