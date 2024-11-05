#include "../include/create_bmp.h"
#include "../include/deq.h" 
#include "../include/sandpile.h" 
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>  

void saveBMP(const char* filename, uint8_t** data, int width, int height) {
    uint32_t fileSize = 54 + width * height;
    
    
    uint8_t header[54] = {
        0x42, 0x4D,
        static_cast<uint8_t>(fileSize & 0xFF),
        static_cast<uint8_t>((fileSize >> 8) & 0xFF),
        static_cast<uint8_t>((fileSize >> 16) & 0xFF),
        static_cast<uint8_t>((fileSize >> 24) & 0xFF),
        0, 0, 0, 0,
        54, 0, 0, 0,
        40, 0, 0, 0,
        static_cast<uint8_t>(width & 0xFF),
        static_cast<uint8_t>((width >> 8) & 0xFF),
        0, 0,
        static_cast<uint8_t>(height & 0xFF),
        static_cast<uint8_t>((height >> 8) & 0xFF),
        0, 0,
        1, 0, 8, 0,  
        0, 0, 0, 0,
        static_cast<uint8_t>(width * height & 0xFF),
        static_cast<uint8_t>((width * height >> 8) & 0xFF),
        static_cast<uint8_t>((width * height >> 16) & 0xFF),
        static_cast<uint8_t>((width * height >> 24) & 0xFF),
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    
    uint8_t palette[1024] = {};
   
    palette[0] = 255;   palette[1] = 255;   palette[2] = 255; 
    palette[4] = 0;     palette[5] = 255;   palette[6] = 0;   
    palette[8] = 255;   palette[9] = 0;     palette[10] = 255; 
    palette[12] = 255;  palette[13] = 255;  palette[14] = 0;  

    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<char*>(header), sizeof(header));
        outFile.write(reinterpret_cast<char*>(palette), sizeof(palette));

        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                uint8_t colorIndex = (data[y][x] > 3) ? 3 : data[y][x]; 
                outFile.put(static_cast<char>(colorIndex));
            }
        }
        outFile.close();
    } else {
        std::cerr << "Unable to open file " << filename << " for writing.\n";
    }
}