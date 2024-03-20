#include "RLEDecoder.h"
#include "RLEInfo.h"
#include <fstream>

RLEDecoder::RLEDecoder(int size) {
    this->size = size; // take from STDIN
    data = new RLEInfo[size]; // Initialize array
    originalMessages = new std::string[size]; // Initialize array
}
RLEDecoder::RLEDecoder(const RLEDecoder& copy) { // copy constructor
    size = copy.size;
    data = new RLEInfo[size];
    for (int i = 0; i < size; i++) {
        data[i] = copy.data[i];
    }
    originalMessages = new std::string[size];
    for (int i = 0; i < size; i++) {
        originalMessages[i] = copy.originalMessages[i];
    }
}
RLEDecoder& RLEDecoder::operator=(const RLEDecoder& copy) { // copy assignment constructor
    if (this != &copy) { // 1. Don't self-assign
        delete[] data; // 2. Delete old data
        data = new RLEInfo[size]; // 3. Allocate new data
        *data = *(copy.data); // 4. Copy data
    }
    if (this != &copy) { // 1. Don't self-assign
        delete[] originalMessages; // 2. Delete old data
        originalMessages = new std::string[size]; // 3. Allocate new data
        *originalMessages = *(copy.originalMessages); // 4. Copy data
    }
    return *this;
}
RLEDecoder::~RLEDecoder() {
    // Release memory for dynamic arrays
    delete[] data;
    delete[] originalMessages;
}
bool RLEDecoder::readFromFile(const std::string& filename) {
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        return false; // if file fails to open we will return false so no output happens
    }
    int nMessages = 0;
    std::string line;

    while (std::getline(file, line)) { // using getters and setters to assign the lines to data array
        data[nMessages].setRLEString(line);

        std::getline(file, line); // This begins storing the Frequencies in the array.

        std::vector<int> frequencies;
        std::string frequencyStr;
        bool firstValueSkipped = false; // intialized since we do not need the first number as it only tells us how many runs we have

        for (char ch : line) {
            if (ch == ' ') {
                if (!frequencyStr.empty()) {
                    if (firstValueSkipped) {
                        int frequency = std::stoi(frequencyStr); // stoi() function is used to change string to int
                        frequencies.push_back(frequency); // we now can add integer into the vector <int>
                    } else {
                        firstValueSkipped = true;
                    }
                    frequencyStr.clear();
                }
            } else {
                frequencyStr += ch;
            }
        }

        if (!frequencyStr.empty()) {
            if (firstValueSkipped) {
                int frequency = std::stoi(frequencyStr);
                frequencies.push_back(frequency);
            }
        }

        data[nMessages].setRLEFrequencies(frequencies);
        nMessages++;
    }
    file.close(); // close file at the end 
    return true;
}

void RLEDecoder::printInfo() {
    for (int j = 0; j < size; j++) { // for loop to output the info using getters and setters method
        std::cout << "RLE String: " << data[j].getRLEString() << std::endl; 
        std::cout << "RLE Frequencies: ";
        std::vector<int> frequencies = data[j].getRLEFrequencies();
        for (int i = 0; i < frequencies.size(); i++) {
            std::cout << frequencies[i] << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

void RLEDecoder::decode() {
    for (int i = 0; i < size; i++) { // decode function using getters from RLEInfo
        const std::string& rleString = data[i].getRLEString();
        const std::vector<int>& frequencies = data[i].getRLEFrequencies();
        std::string decodedMessage;

        decodedMessage = "";

        int rleLength = rleString.length();
        int freqIndex = 0;
        int freqSize = frequencies.size();

        for (int j = 0; j < rleLength; j++) {
            char ch = rleString[j];

            if (j + 1 < rleLength && rleString[j] == rleString[j + 1]) {
                int frequency = frequencies[freqIndex];
                for (int k = 0; k < frequency; k++) {
                    decodedMessage += ch;
                }
                j++;
                freqIndex++;
            } else {
                decodedMessage += ch;
            }

            if (freqIndex >= freqSize) {
                freqIndex = 0;
            }
        }

        originalMessages[i] = decodedMessage; // Stores decoded message in the original messages array.
    }
}

void RLEDecoder::printDecodedMessages() { //print of decoded messages with proper formatting for moodle
    for (int i = 0; i < size; i++) {
        std::cout << "Decoded Message" << i + 1 << ": " << originalMessages[i];
        if (i < size -1) {
            std::cout << std::endl << std::endl;
        }
    }
}