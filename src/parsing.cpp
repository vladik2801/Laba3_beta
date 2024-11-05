#include "../include/parsing.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

void Parsing(int argc, char** argv, getInfo& arguments) {
    for (int i = 0; i < 4; i++) {
        arguments.flag[i] = false;  
    }

    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc) { 
                i++;
                arguments.input = strdup(argv[i]);  
                arguments.flag[Input] = true;
            } else {
                std::cerr << "Error: Missing value for input flag" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                i++;
                arguments.output = strdup(argv[i]);  
                arguments.flag[Output] = true;
            } else {
                std::cerr << "Error: Missing value for output flag" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--max-iter") == 0) {
            if (i + 1 < argc) {
                i++;
                arguments.max_iter = atoi(argv[i]);
                arguments.flag[Max_iter] = true;
            } else {
                std::cerr << "Error: Missing value for max-iter flag" << std::endl;
                exit(1);
            }
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--freq") == 0) {
            if (i + 1 < argc) {
                i++;
                arguments.freq = atoi(argv[i]);
                arguments.flag[Freq] = true;
            } else {
                std::cerr << "Error: Missing value for freq flag" << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "unknown option: " << argv[i] << std::endl;
        }
    }

    
    for (int i = 0; i < 4; i++) {
        if (!arguments.flag[i]) {
            std::cerr << "Required parameters were not entered" << std::endl;
            exit(1);
        }
    }
}