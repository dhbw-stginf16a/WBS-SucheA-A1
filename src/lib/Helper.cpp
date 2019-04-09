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
    return static_cast<int>(abs(x1 - x2) + abs(y1 - y2));
}

/**
 * Prints the Artifacts in human readable
 * @param x the
 * @param numberOfBits the number of bits to print
 * @return string with 0 and 1 representing the number
 */
std::string Helper::printArtifactString(char x, char numberOfBits) {
    char buffer[numberOfBits];
    for(char i = 0; i < numberOfBits; i++) {
        buffer[i] = ((1 << i) & x)? 'A' + i: '_';
    }
    int a = 0;
    return std::string(buffer, static_cast<unsigned int>(numberOfBits));
}

/**
 * Prints the artifact as A, B, C or ' ' if no artifact is present
 * @param x the bitmask of the artifact
 * @return a character to represent the artifact
 */
char Helper::printArtifact(char x) {
    if(!(x & ARTIFACT_BYTE_MASK)) return ' ';
    for(char i = 0; i < 8; i++) {
        if((1 << i) & x) return 'A' + i;
    }
    return ' ';
}
