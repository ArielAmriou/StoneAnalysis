/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Wav
*/

#include "Wav.hpp"
#include "FFT.hpp"
#include "Exception.hpp"

#include <filesystem>

namespace StoneAnalysis {

    Wav::Wav(std::string path): _file(path, std::ios::binary)
    {
        if (_file.fail())
            throw NoSuchFileException(path);
        if (!std::filesystem::file_size(path))
            throw EmptyFile();
        _RIFF = RIFF(_file);
        _fmt = fmtSubChunk(_file);
        _waves = Waves(_file);
        _file.close();
    };

    std::vector<std::complex<double>> Wav::analize()
    {
        return std::make_unique<FFT>()->analize(_waves._data);
    };

    void Wav::save(std::string path)
    {
        std::ofstream out(path, std::ios::binary);
        if (out.fail())
            throw NoSuchFileException(path);
        SWAP(_RIFF._data.chunkSize);
        out.write((char *)(&_RIFF._data), sizeof(_RIFF._data));
        out.write((char *)(&_fmt._data), sizeof(_fmt._data));
        out.write((char *)(&_waves._header), sizeof(_waves._header));
        for (auto &sample : _waves._data)
            out.write((char *)(&sample), sizeof(sample));
    }
    
    std::ostream& operator<<(std::ostream& os, Wav& obj)
    {
        os << obj._RIFF;
        os << "\n";
        os << obj._fmt;
        os << "\n";
        os << obj._waves;
        return os;
    }
}

