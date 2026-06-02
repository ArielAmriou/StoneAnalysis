/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** DFT
*/

#include "DFT.hpp"

namespace StoneAnalysis {

    std::vector<std::complex<double>> DFT::analize(std::vector<b2> waves) {
        auto N = waves.size();
        auto K = N;

        std::vector<std::complex<double>> f;
        f.reserve(N);

        for (std::size_t k = 0; k < K; ++k) {
            std::complex<double> correlation(0.0, 0.0);
            for (std::size_t n = 0; n < N; ++n) {
                double realPart = cos(((2 * M_PI) / N) * k * n);
                double imagPart = sin(((2 * M_PI) / N) * k * n);
                std::complex<double> tmpCor(realPart, -imagPart);
                correlation += tmpCor * std::complex<double>(waves[n], 0.0);
            }
            f.push_back(correlation);
        }
        return f;
    };
}
