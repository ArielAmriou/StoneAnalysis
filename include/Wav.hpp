/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Wav
*/

#ifndef WAV_HPP_
#define WAV_HPP_

#include <string>
#include <fstream>
#include <complex>
#include <memory>
#include <vector>

#include "Riff.hpp"
#include "Fmt.hpp"
#include "Waves.hpp"

namespace StoneAnalysis {
    class Wav {
        public:
            Wav(std::string path);
            std::vector<std::complex<double>> analize();

            RIFF _RIFF;
            fmtSubChunk _fmt;
            Waves _waves;
        private:
            std::ifstream _file;
    };

    std::ostream& operator<<(std::ostream& os, Wav& obj);
}

#endif /* !WAV_HPP_ */
