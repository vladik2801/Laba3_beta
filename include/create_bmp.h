#ifndef LABWORK_3_CREATE_BMP_H
#define LABWORK_3_CREATE_BMP_H
#include <cstdint>
#include "parsing.h"
#include "sandpile.h" 
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "deq.h"


void saveBMP(const char* filename, uint8_t** data, int width, int height);

#endif 