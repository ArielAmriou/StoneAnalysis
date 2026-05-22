/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Fmt
*/

#ifndef FMT_HPP_
#define FMT_HPP_

#include <fstream>

#include "StoneAnalysis.hpp"

namespace StoneAnalysis {
    struct fmtSubChunkData {
        desc subChunkID;
        b4 subChunkSize;
        b2 audioFormat;
        b2 numChannel;
        b4 sampleRate;
        b4 byteRate;
        b2 blockAlign;
        b2 bitsPerSample;
    };

    class fmtSubChunk {
        public:
            fmtSubChunk() = default;
            fmtSubChunk(std::ifstream &file);

            fmtSubChunkData _data;
    };

    std::ostream& operator<<(std::ostream& os, fmtSubChunk& obj);
}

#endif /* !FMT_HPP_ */
