/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Wav
*/

#include "Wav.hpp"
#include "DFT.hpp"
#include "Exception.hpp"

namespace StoneAnalysis {

    Wav::Wav(std::string path): _file(path, std::ios::binary)
    {
        if (_file.fail())
            throw NoSuchFileException(path);
        _RIFF = RIFF(_file);
        _fmt = fmtSubChunk(_file);
        _waves = Waves(_file);
        _file.close();
    };

    std::vector<std::complex<double>> Wav::analize()
    {
        return std::make_unique<DFT>()->analize(_waves._data);
    };
    
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

