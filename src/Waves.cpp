/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Waves
*/

#include "Waves.hpp"

namespace StoneAnalysis {
    Waves::Waves(std::ifstream &file)
    {
        file.read((char *)(&_header), sizeof(_header));
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