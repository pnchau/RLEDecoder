#ifndef RLEINFO_H
#define RLEINFO_H

#include <iostream>
#include <string>
#include <vector>

class RLEInfo {
    private:
        std::string RLEString;
        std::vector<int> RLEFrequencies;
    public:
        RLEInfo();
        void setRLEString(const std::string& rleString);
        void setRLEFrequencies(const std::vector<int> rleFrequencies);
        std::string getRLEString() const;
        std::vector<int> getRLEFrequencies() const;
        friend std::istream& operator>>(std::istream& input, RLEInfo& RLE);
        friend std::ostream& operator<<(std::ostream& output, const RLEInfo& RLE);
};

#endif