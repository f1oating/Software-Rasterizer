#include "TGAImage.h"

#include <cstring>
#include <iostream>

TGAImage::TGAImage(int width, int height, int bpp, Color color) : 
    m_Width(width), m_Height(height), m_BPP(bpp), m_Data((width * height) * bpp)
{
    for (int y = 0; y < m_Height; y++)
    {
        for (int x = 0; x < m_Width; x++)
        {
            Set(x, y, color);
        }
    }
}

bool TGAImage::ReadFile(std::string path)
{

}

bool TGAImage::WriteFile(std::string path, bool vFlip, bool rle)
{
    uint8_t developer_area_ref[4] = { 0, 0, 0, 0 };
    uint8_t extension_area_ref[4] = { 0, 0, 0, 0 };
    uint8_t footer[18] = { 'T','R','U','E','V','I','S','I','O','N','-','X','F','I','L','E','.','\0' };

    std::ofstream out;
    out.open(path, std::ios::binary);
    if (!out.is_open())
    {
        std::cerr << "Can not open file " << path << std::endl;
        return false;
    }

    TGAHeader header = {};
    header.BitsPerPixel = m_BPP << 3;
    header.Width = m_Width;
    header.Height = m_Height;
    header.DataTypeCode = m_BPP == Grayscale ? 3 : 2;
    header.ImageDescriptor = vFlip ? 0x00 : 0x20;

    out.write(reinterpret_cast<const char*>(&header), sizeof(header));

    if (!out.good()) goto err;

    out.write(reinterpret_cast<const char*>(m_Data.data()), m_Width * m_Height * m_BPP);
    if (!out.good()) goto err;
    out.write(reinterpret_cast<const char *>(developer_area_ref), sizeof(developer_area_ref));
    if (!out.good()) goto err;
    out.write(reinterpret_cast<const char *>(extension_area_ref), sizeof(extension_area_ref));
    if (!out.good()) goto err;
    out.write(reinterpret_cast<const char *>(footer), sizeof(footer));

    if (!out.good()) goto err;
    return true;

err:
    std::cerr << "Can not dump TGA file" << std::endl;
    return false;
}

void TGAImage::FlipHorizontally()
{
    for (int y = 0; y < m_Height; y++)
    {
        for (int x = 0; x < m_Width / 2; x++)
        {
            for (int b = 0; b < m_BPP; b++)
            {
                std::swap(m_Data[(x + y * m_Width) * m_BPP + b], m_Data[(m_Width - 1 - x + y * m_Width) * m_BPP + b]);
            }
        }
    }
}

void TGAImage::FlipVertically()
{
    for (int x = 0; x < m_Width; x++)
    {
        for (int y = 0; y < m_Height / 2; y++)
        {
            for (int b = 0; b < m_BPP; b++)
            {
                std::swap(m_Data[(x + y * m_Width) * m_BPP + b], m_Data[(x + (m_Height - 1 - y) * m_Width) * m_BPP + b]);
            }
        }
    }
}

Color TGAImage::Get(int x, int y)
{
    if (!m_Data.size() || x < 0 || y < 0 || x > m_Width || y > m_Height) {};

    Color color;

    const uint8_t* pixelData = m_Data.data() + (x + y * m_Width) * m_BPP;
    mempcpy(color.BGRA, pixelData, m_BPP);

    return color;
}

void TGAImage::Set(int x, int y, Color& color)
{
    if (!m_Data.size() || x < 0 || y < 0 || x > m_Width || y > m_Height) return;
    memcpy(m_Data.data() + (x + y * m_Width) * m_BPP, color.BGRA, m_BPP);
}

void LoadRLEData(std::ifstream& in)
{

}

void UnloadRLEData(std::ofstream& out)
{

}