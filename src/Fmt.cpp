/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Fmt
*/

#include <fstream>

#include "Fmt.hpp"

namespace StoneAnalysis {

    fmtSubChunk::fmtSubChunk(std::ifstream &file)
    {
        file.read((char *)(&_data), sizeof(_data));
    }

    std::ostream& operator<<(std::ostream& os, fmtSubChunk& obj)
    {
        os << "fmt {\n";
        os << "    ID: \"";
        os << std::string(obj._data.subChunkID, 4) << "\";\n";
        os << "    Size: ";
        os << obj._data.subChunkSize << ";\n";
        os << "    Format: ";
        os << obj._data.audioFormat << ";\n";
        os << "    Number of channel: ";
        os << obj._data.numChannel << ";\n";
        os << "    Sample rate: ";
        os << obj._data.sampleRate << ";\n";
        os << "    Byte rate: ";
        os << obj._data.byteRate << ";\n";
        os << "    Block align: ";
        os << obj._data.blockAlign << ";\n";
        os << "    Bits per sample: ";
        os << obj._data.bitsPerSample << ";\n}";
        return os;
    }
}
