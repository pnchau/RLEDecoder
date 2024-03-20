#include <iostream>
#include "RLEDecoder.h"


int main()
{
    int size;
    std::cin >> size;
    RLEDecoder myDecoder(size);
    std::string filename;
    std::cin >> filename;
    if(myDecoder.readFromFile(filename) == true)
    {
        myDecoder.decode();
        myDecoder.printInfo();
        myDecoder.printDecodedMessages();
    }
    
    return 0;
}