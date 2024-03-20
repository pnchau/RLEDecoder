#ifndef RLEDECODER_H
#define RLEDECODER_H

#include <iostream>
#include <string>
#include <vector>
#include "RLEInfo.h"

class RLEDecoder {
    private:
        int size;
        RLEInfo* data;
        std::string* originalMessages; 
    public:
        RLEDecoder(int size);
        RLEDecoder(const RLEDecoder& copy);
        RLEDecoder& operator=(const RLEDecoder& copy);
        ~RLEDecoder();
        bool readFromFile(const std::string& filename);
        void printInfo();
        void printDecodedMessages();
        void decode();
};

#endif