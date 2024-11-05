#ifndef SANDPILE_H
#define SANDPILE_H

#include <cstdint>

class Sandpile {
public:
    Sandpile();
    ~Sandpile();
    
    void initialize(const char* filename);
    bool update();
    void saveToBMP(const char* filename) const;

private:
    uint64_t** grid;
    int width, height;
    int minX, minY, maxX, maxY;
    
    void topple();
    void resizeGrid();
};

#endif 