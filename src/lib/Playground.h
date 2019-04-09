#ifndef SRC_PLAYGROUND_H
#define SRC_PLAYGROUND_H


class Playground;
#include "Artifact.h"
#include "State.h"
#include "PriorityQueue.h"
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
    Playground(const std::string& inputFile, int width, int height, const std::string& artifact);
    ~Playground();
    std::string printField(const std::string& delimField, const std::string& delimLine, char bitmask = 0xff);
    void calculatePath(int x, int y);
    int getEstimate(int x, int y, char artifacts) const;
    char getArtifactOnField(int x, int y) const;
    char getLandOnField(int x, int y) const;
private:
    void fillPathCache();
    char * field = nullptr;
    int width;
    int height;
    std::vector<Artifact> artifacts = std::vector<Artifact>();
};


#endif //SRC_PLAYGROUND_H
