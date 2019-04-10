#ifndef WBS_SUCHEA_A1_HELPER_H
#define WBS_SUCHEA_A1_HELPER_H

#define LAND_BYTE_MASK 0x3
#define COMPONENT_BYTE_MASK 0x7
#define COMPONENT_SHIFT_AMOUNT 2
#define getComponent(x) (static_cast<char>((x >> COMPONENT_SHIFT_AMOUNT) & 7))
#define shiftComponent(x) ((x << COMPONENT_SHIFT_AMOUNT))
#define getLand(x) (static_cast<char>(x & LAND_BYTE_MASK))
#define hasB(x) ((x & 2) == 2)
// Transforms two-dimensional coordinates to one dimensional data
#define tdtod(x, y, len) ((y * len) + x)
#include <cmath>
#include <string>

namespace Helper {
    char countBits(char x);
    std::string printComponentString(char x, char numberOfBits);
    int manhattanDistance(int x1, int y1, int x2, int y2);
    char printComponent(char x);
    std::string getColorForLand(char x);
};


#endif //WBS_SUCHEA_A1_HELPER_H
