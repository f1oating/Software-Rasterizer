#include <iostream>
#include "TGAImage.h"

int main()
{
    TGAImage image(800, 600, 4, { 122, 123, 32, 255 });

    Color color = image.Get(0, 1);

    image.WriteFile("test.tga");

    std::cout << "Hello, World!" << std::endl;
}