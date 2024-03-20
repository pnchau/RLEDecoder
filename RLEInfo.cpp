#include "RLEInfo.h"
#include <iostream>
#include <string>
#include <vector>

RLEInfo::RLEInfo() { // default constructor
    RLEString = ""; 
    RLEFrequencies = {};
}

std::string RLEInfo::getRLEString() const{ // getter for RLEString
    return RLEString;
}

std::vector<int> RLEInfo::getRLEFrequencies() const { // getter for RLEFrequencies
    return RLEFrequencies;
}
void RLEInfo::setRLEString(const std::string& rleString) { // setter for RLEString
    RLEString = rleString;
}
void RLEInfo::setRLEFrequencies(const std::vector<int> rleFrequencies) { // setter for RLEFrequencies
    RLEFrequencies = rleFrequencies;
}

std::istream& operator>>(std::istream& input, RLEInfo& RLE) { //overloaded operator>>
    // Read RLEString from input stream
    std::getline(input, RLE.RLEString);

    // Read RLEFrequencies from input stream
    RLE.RLEFrequencies.clear();
    int freq;
    while (input >> freq) {
        RLE.RLEFrequencies.push_back(freq);
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const RLEInfo& RLE) { //overloaded operator<<
    // Write RLEString to output stream
    output << RLE.RLEString << std::endl;

    // Write RLEFrequencies to output stream
    for (int freq : RLE.RLEFrequencies) {
        output << freq << " ";
    }
    output << std::endl;

    return output;
}
