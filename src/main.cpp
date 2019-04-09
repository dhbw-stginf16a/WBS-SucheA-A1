// #define NDEBUG // Disable all assert calls
#include "lib/Playground.h"
#include <iostream>

int main(int argc, char *argv[]) {
    if(argc < 6) throw std::runtime_error("Need at least three arguments width, height, dataFile, ArtifactFile, startX, startY");
    int length = std::stoul(argv[2], nullptr, 10);
    int height = std::stoul(argv[1], nullptr, 10);
    int x = std::stoul(argv[5], nullptr, 10);
    int y = std::stoul(argv[6], nullptr, 10);
    bool color = (argc > 6) && argv[7] != nullptr && std::string("color") == (std::string(argv[7]));

    Playground playground(argv[3], length, height, argv[4]);
    std::string test = playground.printField(";", "\n");
    std::cout << "Here is the read playing field:\n";
    std::cout << playground.printFieldFancy(";", "\n", color);
    if(color) {
        std::cout << Helper::getColorForLand(4); //Reset Color to black
    }
    std::cout << "Start calculating shortest path.\n\n\n" << std::endl;
    playground.calculatePath(x, y);
    int a = 0;
}