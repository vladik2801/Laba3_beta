#ifndef LABWORK_3_ELIZABETINKA_PARSING_H
#define LABWORK_3_ELIZABETINKA_PARSING_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdint>

enum Options {
    Input = 0, Output = 1, Max_iter = 2, Freq = 3
};

struct getInfo {
    char* input;
    char* output;
    size_t max_iter;
    size_t freq;
    // проверяет, какие введены параметры (True-вводились, False-нет)
    bool flag[4];
};

void Parsing(int argc, char** argv, getInfo& arguments);

#endif //LABWORK_3_ELIZABETINKA_PARSING_H
