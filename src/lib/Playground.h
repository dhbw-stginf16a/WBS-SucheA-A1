#ifndef SRC_PLAYGROUND_H
#define SRC_PLAYGROUND_H


class Playground;
#include "Component.h"
#include "State.h"
#include "PriorityQueue.h"
#include <sstream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <iostream>

class Playground {
public:
    Playground() = delete; // Default constructor
    Playground(const Playground& obj) = delete; // copy constructor
    Playground(Playground&& obj) noexcept = delete; // move constructor
    Playground& operator=(const Playground& obj) = delete; //copy assignment
    Playground& operator=(Playground&& obj) noexcept = delete; // move assignment constructor
    Playground(const std::string& inputFile, int width, int height, const std::string& component);
    ~Playground();
    std::string printField(const std::string& delimField, const std::string& delimLine, char bitmask = 0xff);
    std::string printFieldFancy(const std::string& delimField, const std::string& delimLine, bool color = false);
    void calculatePath(int x, int y);
    int getEstimate(int x, int y, char components) const;
    char getComponentOnField(int x, int y) const;
    char getLandOnField(int x, int y) const;
    bool inField(int x, int y) const;
    bool isWater(int x, int y) const;
    bool isMoveAble(int xFrom, int yFrom, int xTo, int yTo, char component) const;
private:
    void fillPathCache();
    char * field = nullptr;
    int width;
    int height;
    std::vector<Component> components = std::vector<Component>();
};


#endif //SRC_PLAYGROUND_H
