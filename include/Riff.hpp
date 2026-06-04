/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Riff
*/

#ifndef RIFF_HPP_
#define RIFF_HPP_

#include <fstream>
#include <filesystem>

#include "Utils.hpp"

namespace StoneAnalysis {

    struct RIFF_data {
        desc chunkID;
        b4 chunkSize;
        desc format;
    };

    class RIFF {
        public:
            RIFF() = default;
            RIFF(std::ifstream &file, uintmax_t size);

            RIFF_data _data;
    };

    std::ostream& operator<<(std::ostream& os, RIFF& obj);
}

#endif /* !RIFF_HPP_ */
