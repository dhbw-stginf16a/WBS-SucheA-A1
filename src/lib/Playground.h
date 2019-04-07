#ifndef SRC_PLAYGROUND_H
#define SRC_PLAYGROUND_H

class Playground;
#include "Artefact.h"
#include <sstream>
#include <fstream>
#include <assert.h>
#include <vector>

#define LAND_BYTE_MASK 0x3
#define ARTEFACT_BYTE_MASK_A (0x1 << 3)
#define ARTEFACT_BYTE_MASK_B (0x1 << 4)
#define ARTEFACT_BYTE_MASK_C (0x1 << 5)
#define getArtefact(x) ((x >> 2) & 7)
#define shiftArtefact(x) ((x << 2))
#define getLand(x) (x & 3)
// Transforms two-dimensional coordinates to one dimensional data
#define tdtod(x, y, len) ((y * len) + x)


class Playground {
public:
    Playground(const Playground& obj) = delete; // copy constructor
    Playground(Playground&& obj) noexcept = delete; // move constructor
    Playground& operator=(const Playground& obj) = delete; //copy assignment
    Playground& operator=(Playground&& obj) noexcept = delete; // move assignment constructor
    Playground(const std::string& inputFile, unsigned int length, unsigned int height, const std::string& artefacts);
    ~Playground();
    std::string printField(const std::string& delimField, const std::string& delimLine, char bitmask = 0xff);
private:
    char * field = nullptr;
    unsigned int length;
    unsigned int height;
    std::vector<Artefact> artefacts = std::vector<Artefact>();
};


#endif //SRC_PLAYGROUND_H
