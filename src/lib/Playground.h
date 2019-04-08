#ifndef SRC_PLAYGROUND_H
#define SRC_PLAYGROUND_H

#define LAND_BYTE_MASK 0x3
#define ARTEFACT_BYTE_MASK 0x7
#define ARTEFACT_SHIFT_AMOUNT 2
#define getArtefact(x) ((x >> ARTEFACT_SHIFT_AMOUNT) & 7)
#define shiftArtefact(x) ((x << ARTEFACT_SHIFT_AMOUNT))
#define getLand(x) (x & LAND_BYTE_MASK)
// Transforms two-dimensional coordinates to one dimensional data
#define tdtod(x, y, len) ((y * len) + x)

class Playground;
#include "Artefact.h"
#include <sstream>
#include <fstream>
#include <assert.h>
#include <vector>

class Playground {
public:
    Playground() = delete; // Default constructor
    Playground(const Playground& obj) = delete; // copy constructor
    Playground(Playground&& obj) noexcept = delete; // move constructor
    Playground& operator=(const Playground& obj) = delete; //copy assignment
    Playground& operator=(Playground&& obj) noexcept = delete; // move assignment constructor
    Playground(const std::string& inputFile, unsigned int length, unsigned int height, const std::string& artefacts);
    ~Playground();
    std::string printField(const std::string& delimField, const std::string& delimLine, char bitmask = 0xff);
    void calculatePath(unsigned int x, unsigned int y);
    unsigned int getEstimate(unsigned int x, unsigned int y, char artifacts) const;
private:
    void fillPathCache();
    char * field = nullptr;
    unsigned int length;
    unsigned int height;
    std::vector<Artefact> artefacts = std::vector<Artefact>();
};


#endif //SRC_PLAYGROUND_H
