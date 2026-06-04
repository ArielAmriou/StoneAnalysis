/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Riff
*/

#include <fstream>
#include <cstring>
#include <iostream>

#include "Riff.hpp"
#include "Exception.hpp"

namespace StoneAnalysis {

    RIFF::RIFF(std::ifstream &file, uintmax_t size)
    {
        file.read((char *)(&_data), sizeof(_data));
        if (std::strncmp(_data.chunkID, "RIFF", 4) != 0)
            throw RiffParsingError("Invalid Chunk ID");
        if (static_cast<uintmax_t>(_data.chunkSize + 8) != size)
            throw RiffParsingError("Invalid Chunk Size (" + std::to_string(_data.chunkSize) + ")");
        if (std::strncmp(_data.format, "WAVE", 4) != 0)
            throw RiffParsingError("Invalid Chunk Format");
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

