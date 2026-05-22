/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Riff
*/

#include <fstream>

#include "Riff.hpp"

namespace StoneAnalysis {

    RIFF::RIFF(std::ifstream &file)
    {
        file.read((char *)(&_data), sizeof(_data));
        SWAP(_data.chunkSize);
    }
    
    std::ostream& operator<<(std::ostream& os, RIFF& obj)
    {
        os << "RIFF {\n";
        os << "    ID: \"";
        os << std::string(obj._data.chunkID, 4) << "\";\n";
        os << "    Size: ";
        os << obj._data.chunkSize << ";\n";
        os << "    Format: \"";
        os << std::string(obj._data.format, 4) << "\";\n}";
        return os;
    }
}

