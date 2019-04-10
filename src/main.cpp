// #define NDEBUG // Disable all assert calls
#include "lib/Playground.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Hello to the WBS_SucheA_A1 solution." << std::endl;
    if(argc < 6) {
        std::cerr << "Need at least six arguments height, width, dataFile, ComponentFile, startX, startY";
        return 1;
    }
    std::cout << "Start reading in parameters:\n";
    int height = std::stoul(argv[1], nullptr, 10);
    std::cout << "height=" << height << "\n";
    int width = std::stoul(argv[2], nullptr, 10);
    std::cout << "width=" << width << "\n";
    int x = std::stoul(argv[5], nullptr, 10);
    std::cout << "xStart=" << x << "\n";
    int y = std::stoul(argv[6], nullptr, 10);
    std::cout << "yStart=" << y << "\n";
    bool color = (argc > 6) && argv[7] != nullptr && std::string("color") == (std::string(argv[7]));
    std::cout << "Printing field " << (color?"":"not ") << "in color.\n";

    Playground playground(argv[3], width, height, argv[4]);
    std::string test = playground.printField(";", "\n");
    std::cout << "Here is the read playing field:\n";
    std::cout << playground.printFieldFancy(";", "\n", color);
    if(color) {
        char buffer[] = {'\033', '[', '0', 'm'};
        std::cout << "\033[0m"; //Reset Color to default
    }
    std::cout << "Start calculating shortest path.\n\n\n" << std::endl;
    playground.calculatePath(x, y);
    int a = 0;
}