#ifndef LABWORK_3_ELIZABETINKA_CREATE_BMP_H
#define LABWORK_3_ELIZABETINKA_CREATE_BMP_H
#include <cstdint>
#include "parsing.h"
#include "sandpile.h" 
#include <iostream>
#include <cstring>

#include <fstream>

std::string GetPath(const char* path);

// переводим число в представление little-endian, для этого переводим в систему счисления с осн 256
void ToNumbers4(int32_t x, uint8_t numbers_4[]); // Изменено на int32_t

void CreateBmp(const char* path, Deque<Deque<uint64_t>>& basic, const Sandpile& arguments);

#endif // LABWORK_3_ELIZABETINKA_CREATE_BMP_H
