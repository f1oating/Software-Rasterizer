#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

#pragma pack(push,1)
struct TGAHeader 
{
    uint8_t IDLength = 0;
    uint8_t ColorMapType = 0;
    uint8_t DataTypeCode = 0;
    uint16_t ColorMapOrigin = 0;
    uint16_t ColorMapLength = 0;
    uint8_t ColorMapDepth = 0;
    uint16_t XOrigin = 0;
    uint16_t YOrigin = 0;
    uint16_t Width = 0;
    uint16_t Height = 0;
    uint8_t BitsPerPixel = 0;
    uint8_t ImageDescriptor = 0;
};
#pragma pack(pop)

struct Color
{
    uint8_t BGRA[4] = { 0, 0, 0, 0 };
    uint8_t BPP = 4;
};

struct TGAImage
{
enum Format
{
    Grayscale = 1,
    RGB = 3,
    RGBA = 4
};

public:
    TGAImage(int width, int height, int bpp, Color color = {});

    bool ReadFile(std::string path);
    bool WriteFile(std::string path, bool vFlip = true, bool rle = true);

    void FlipHorizontally();
    void FlipVertically();

    Color Get(int x, int y);
    void Set(int x, int y, Color& color);

    int GetWidth() { return m_Width; }
    int GetHeight() { return m_Height; }

private:
    void LoadRLEData(std::ifstream& in);
    void UnloadRLEData(std::ofstream& out);

private:
    int m_Width = 0;
    int m_Height = 0;
    uint8_t m_BPP = 0;
    std::vector<uint8_t> m_Data;

};