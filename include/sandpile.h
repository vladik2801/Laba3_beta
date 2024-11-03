#ifndef LABWORK_3_ELIZABETINKA_SANDPILE_H
#define LABWORK_3_ELIZABETINKA_SANDPILE_H

#include "parsing.h"
#include <cstdint>
#include <deque>
#include <fstream>
#include <set>

enum KeysOfAdd {
    up = 0, left = 1, down = 2, right = 3
};
struct Sandpile{
    int width;
    int height;
    int count_iter;
    Deque<Deque<uint64_t>> grid;
};
// считываем данные из tsv файла
Sandpile ReadingInput(const char* path,Deque<Deque<uint64_t>>& basic);

void AddPlace(Deque<Deque<uint64_t>>& basic, Sandpile& sandpile, KeysOfAdd key);

void Iteration(Deque<Deque<uint64_t>>& basic, Sandpile& sandpile, int& count_cells_more4);

#endif //LABWORK_3_ELIZABETINKA_SANDPILE_H