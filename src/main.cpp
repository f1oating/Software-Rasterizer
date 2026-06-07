#include <iostream>
#include "TGAImage.h"

int main()
{
    TGAImage image(800, 600, 4, { 111, 231, 32, 255 });

    image.WriteFile("test.tga");

    std::cout << "Hello, World!" << std::endl;
}