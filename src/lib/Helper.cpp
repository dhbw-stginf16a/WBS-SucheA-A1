#include "Helper.h"

char Helper::countBits(char x) {
    char count = 0;
    for(char bytemask = 1; bytemask; bytemask <<= 1) {
        if(bytemask & x) count++;
    }
    return count;
}

unsigned int Helper::manhattanDistance(int x1, int y1, int x2, int y2) {
    return static_cast<unsigned int>(abs(x1 - x2) + abs(y1 - y2));
}
