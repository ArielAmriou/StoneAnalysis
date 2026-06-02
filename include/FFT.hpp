/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** FFT
*/

#ifndef FFT_HPP_
#define FFT_HPP_

#include "IAnalyser.hpp"

namespace StoneAnalysis {
    class FFT: public IAnalyser {
        public:
            ~FFT() = default;
            std::vector<std::complex<double>> analize(std::vector<b2> waves);
        private:
            std::vector<std::complex<double>>
                getAmplitudes(std::vector<std::complex<double>> waves);
    };
}

#endif /* !FFT_HPP_ */
