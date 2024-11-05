#include <cstdlib>
#include "../include/create_bmp.h"

#include "../include/sandpile.h"
#include "../include/parsing.h"


int main(int argc, char** argv) {
    getInfo arguments;
    Parsing(argc, argv, arguments);

    
    Sandpile sandpile;
    sandpile.initialize(arguments.input);

    for (size_t iteration = 0; iteration < arguments.max_iter; ++iteration) {
        bool isStable = sandpile.update(); 
        if (iteration % arguments.freq == 0 || isStable) {
            std::string filename = arguments.output + std::to_string(iteration) + ".bmp";
            sandpile.saveToBMP(filename.c_str());
        }
        if (isStable) {
            break; 
        }
    }
    return 0;
}