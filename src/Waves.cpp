/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Waves
*/

#include <cstring>

#include "Waves.hpp"
#include "Exception.hpp"

namespace StoneAnalysis {
    Waves::Waves(std::ifstream &file, uintmax_t size)
    {
        file.read((char *)(&_header), sizeof(_header));
        if (file.fail())
            throw DataParsingError("Unexpected end of file");
        if (std::strncmp(_header.subChunkID, "data", 4) != 0)
            throw DataParsingError("Invalid SubChunk ID");
        if (static_cast<uintmax_t>(_header.subChunkSize + 8 + 36) != size)
            throw DataParsingError("Invalid SubChunk Size (" + std::to_string(_header.subChunkSize) + ")");
        std::size_t numSamples = _header.subChunkSize / sizeof(b2);
        _data.reserve(numSamples);
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