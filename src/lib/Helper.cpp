#include "Helper.h"
/**
 * Count the amount of set bits in a given number
 * @param x the number to count bits in
 * @return amount of bits counted (Should be <=8)
 */
char Helper::countBits(char x) {
    char count = 0;
    for(char bytemask = 1; bytemask; bytemask <<= 1) {
        if(bytemask & x) count++;
    }
    return count;
}

/**
 * Calculate the Manhatten distance between two points
 * @param x1 x-Cord of first point
 * @param y1 y-Cord of first point
 * @param x2 x-Cord of second point
 * @param y2 y-Cord of second point
 * @return The distance between these points in moves
 */
int Helper::manhattanDistance(int x1, int y1, int x2, int y2) {
    const int i = static_cast<int>(abs(x1 - x2) + abs(y1 - y2));
    return i;
}

/**
 * Prints the Components in human readable
 * @param x the
 * @param numberOfBits the number of bits to print
 * @return string with 0 and 1 representing the number
 */
std::string Helper::printComponentString(char x, char numberOfBits) {
    char buffer[numberOfBits];
    for(char i = 0; i < numberOfBits; i++) {
        buffer[i] = ((1 << i) & x)? 'A' + i: '_';
    }
    int a = 0;
    return std::string(buffer, static_cast<unsigned int>(numberOfBits));
}

/**
 * Prints the component as A, B, C or ' ' if no component is present
 * @param x the bitmask of the component
 * @return a character to represent the component
 */
char Helper::printComponent(char x) {
    if(!(x & COMPONENT_BYTE_MASK)) return ' ';
    for(char i = 0; i < 8; i++) {
        if((1 << i) & x) return 'A' + i;
    }
    return ' ';
}

/**
 * REturns the terminalcomand code to switch to this color
 * @param x 0, 1, 2, 3 (land) or 4 for turning it black again
 * @return
 */
std::string Helper::getColorForLand(char x) {
    char buffer[] = {'\033', '[', '3', static_cast<char>('4' - x), 'm'};
    return std::string(buffer, 5);
}
