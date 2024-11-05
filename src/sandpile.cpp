#include "../include/sandpile.h"
#include "../include/create_bmp.h"
#include <limits>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>

Sandpile::Sandpile() : grid(nullptr), width(0), height(0), minX(0), minY(0), maxX(0), maxY(0) {}

Sandpile::~Sandpile() {
    if (grid) {
        for (int i = 0; i < height; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }
}

void Sandpile::initialize(const char* filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    
    int x, y;
    uint64_t sand;
    minX = minY = std::numeric_limits<int>::max();
    maxX = maxY = std::numeric_limits<int>::min();

    while (inputFile >> x >> y >> sand) {
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }
    inputFile.close();

    width = maxX - minX + 1;
    height = maxY - minY + 1;

    
    grid = new uint64_t*[height];
    for (int i = 0; i < height; ++i) {
        grid[i] = new uint64_t[width]{0};
    }

    
    inputFile.open(filename);
    while (inputFile >> x >> y >> sand) {
        grid[y - minY][x - minX] = sand;
    }
    std::cout << "Grid after initialization:\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool Sandpile::update() {
    bool stable = true;
    topple();
    return stable;
}

void Sandpile::topple() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            while (grid[y][x] > 3) {
                grid[y][x] -= 4;
                if (y > 0) grid[y - 1][x]++;
                if (y < height - 1) grid[y + 1][x]++;
                if (x > 0) grid[y][x - 1]++;
                if (x < width - 1) grid[y][x + 1]++;
            }
        }
    }
    std::cout << "Grid after toppling:\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Sandpile::saveToBMP(const char* filename) const {
    uint8_t** tempGrid = new uint8_t*[height];
    for (int i = 0; i < height; ++i) {
        tempGrid[i] = new uint8_t[width];
        for (int j = 0; j < width; ++j) {
            tempGrid[i][j] = (grid[i][j] > 3) ? 3 : static_cast<uint8_t>(grid[i][j]);
        }
    }

    saveBMP(filename, tempGrid, width, height);

    for (int i = 0; i < height; ++i) {
        delete[] tempGrid[i];
    }
    delete[] tempGrid;
}