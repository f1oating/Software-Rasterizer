#include <iostream>
#include "Image.h"

int main()
{
    Image image(2, 2, 4, { 1, 1, 1, 0 });

    Color color = image.Get(0, 1);
    for (int i = 0; i < 4; i++) printf("%d", color.BGRA[i]);
    printf("\n");

    std::cout << "Hello, World!" << std::endl;
}