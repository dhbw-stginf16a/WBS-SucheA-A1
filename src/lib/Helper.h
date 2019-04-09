#ifndef WBS_SUCHEA_A1_HELPER_H
#define WBS_SUCHEA_A1_HELPER_H

#define LAND_BYTE_MASK 0x3
#define ARTIFACT_BYTE_MASK 0x7
#define ARTIFACT_SHIFT_AMOUNT 2
#define getArtifact(x) (static_cast<char>((x >> ARTIFACT_SHIFT_AMOUNT) & 7))
#define shiftArtifact(x) ((x << ARTIFACT_SHIFT_AMOUNT))
#define getLand(x) (static_cast<char>(x & LAND_BYTE_MASK))
#define hasB(x) ((x & 2) == 2)
// Transforms two-dimensional coordinates to one dimensional data
#define tdtod(x, y, len) ((y * len) + x)
#include <cmath>
#include <string>

namespace Helper {
    char countBits(char x);
    std::string printString(char x, char numberOfBits);
    int manhattanDistance(int x1, int y1, int x2, int y2);
};


#endif //WBS_SUCHEA_A1_HELPER_H
