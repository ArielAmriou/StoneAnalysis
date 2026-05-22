/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Waves
*/

#ifndef WAVES_HPP_
#define WAVES_HPP_

#include <fstream>
#include <vector>

#include "StoneAnalysis.hpp"

namespace StoneAnalysis {

    struct wavesData {
        desc subChunkID;
        b4 subChunkSize;
    };

    class Waves {
        public:
            Waves() = default;
            Waves(std::ifstream &file);

            wavesData _header;
            std::vector<b2> _data;
    };

    std::ostream& operator<<(std::ostream& os, Waves& obj);
}

#endif /* !WAVES_HPP_ */
