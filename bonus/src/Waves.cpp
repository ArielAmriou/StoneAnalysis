/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Waves
*/

#include <cstring>
#include <iostream>

#include "Waves.hpp"
#include "Exception.hpp"

namespace StoneAnalysis {
    Waves::Waves(std::ifstream &file)
    {
        desc subChunkID;
        b4 subChunkSize;
        file.read((char *)(&subChunkID), sizeof(subChunkID));
        if (std::strncmp(subChunkID, "LIST", 4) == 0) {
            b4 jmpSize;
            char tmp;
            file.read((char *)(&jmpSize), sizeof(jmpSize));
            for (b4 i = 0; i < jmpSize; ++i)
                file.read((char *)(&tmp), sizeof(tmp));
            file.read((char *)(&subChunkID), sizeof(subChunkID));
        }
        if (std::strncmp(subChunkID, "data", 4) != 0)
            throw DataParsingError("Invalid SubChunk ID");
        file.read((char *)(&subChunkSize), sizeof(subChunkSize));
        std::strncpy(_header.subChunkID, subChunkID, 4);
        _header.subChunkSize = subChunkSize;
        std::size_t numSamples = _header.subChunkSize / sizeof(b2);
        for (std::size_t i = 0; i < numSamples; ++i) {
            b2 sample;
            file.read((char *)(&sample), sizeof(sample));
            _data.push_back(sample);
        }
    }

    std::ostream& operator<<(std::ostream& os, Waves& obj)
    {
        os << "data {\n";
        os << "    ID: \"";
        os << std::string(obj._header.subChunkID, 4) << "\";\n";
        os << "    Size: ";
        os << obj._header.subChunkSize << ";\n";
        os << "    Waves: ";
        auto size = obj._data.size();
        if (size <= 10) {
            for (std::size_t i = 0; i < size; ++i)
                os << obj._data[i] << ", ";
        } else {
            for (std::size_t i = 0; i < 5; ++i)
                os << obj._data[i] << ", ";
            os << "..., ";
            for (std::size_t i = size - 1; i > size - 6; --i)
                os << obj._data[i] << (i == size - 5 ? ";": ", ");
        }
        os << "\n}";
        return os;
    }

}