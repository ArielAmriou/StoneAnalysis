/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Fmt
*/

#include <fstream>
#include <cstring>

#include "Fmt.hpp"
#include "Exception.hpp"
#include "Utils.hpp"

namespace StoneAnalysis {

    fmtSubChunk::fmtSubChunk(std::ifstream &file)
    {
        file.read((char *)(&_data), sizeof(_data));
        if (std::strncmp(_data.subChunkID, "fmt ", 4) != 0)
            throw FmtParsingError("Invalid SubChunk ID");
        if (_data.subChunkSize != 16)
            throw FmtParsingError("SubChunk size of " + std::to_string(_data.subChunkSize) + " is not handled");
        if (_data.audioFormat != 1)
            throw FmtParsingError("Only PCM is handled");
        if (_data.numChannel != 1)
            throw FmtParsingError("Only on channel is handled");
        if (_data.sampleRate != RATE)
            throw FmtParsingError("Sample Rate of " + std::to_string(_data.sampleRate) + " is not handled");
        if (_data.byteRate != RATE * 2)
            throw FmtParsingError("Byte Rate of " + std::to_string(_data.byteRate) + " is not handled");
        if (_data.bitsPerSample != 16)
            throw FmtParsingError("Byte per Sample of " + std::to_string(_data.bitsPerSample) + " is not handled");
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
