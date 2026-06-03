/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** FFT
*/

#include <bit>
#include <iostream>

#include "FFT.hpp"

namespace StoneAnalysis {

    std::vector<std::complex<double>>
        FFT::getAmplitudes(std::vector<std::complex<double>> waves)
    {
        std::size_t N = waves.size();
        std::size_t M = N / 2;

        if (N <= 1)
            return waves;
    
        std::vector<std::complex<double>> evenPart; 
        evenPart.reserve(M);
        std::vector<std::complex<double>> oddPart;
        oddPart.reserve(M);
        for (std::size_t k = 0; k < M; ++k) {
            evenPart.emplace_back(waves[k * 2]);
            oddPart.emplace_back(waves[(k * 2) + 1]);
        }

        std::vector<std::complex<double>> evenComputed
            = getAmplitudes(evenPart);
        std::vector<std::complex<double>> oddComputed
            = getAmplitudes(oddPart);

        std::vector<std::complex<double>> amplitudes(N, 0);
        for (std::size_t k = 0; k < M; ++k) {
            double realPart = cos(((2 * M_PI) / N) * k);
            double imagPart = sin(((2 * M_PI) / N) * k);
            std::complex<double> C(realPart, -imagPart);
            amplitudes[k] = evenComputed[k] + (C * oddComputed[k]);
            amplitudes[k + M] = evenComputed[k] - (C * oddComputed[k]);
        }
        return amplitudes;
    }

    std::vector<std::complex<double>> FFT::analize(std::vector<b2> waves)
    {
        std::vector<std::complex<double>> complexWaves;
        std::size_t N = waves.size();
        std::size_t next = std::__bit_ceil(N);
        complexWaves.reserve(next);

        for (std::size_t i = 0; i < N; ++i)
            complexWaves.emplace_back(waves[i], 0);
        for (std::size_t i = N; i < next; ++i)
            complexWaves.emplace_back(0, 0);
        return getAmplitudes(complexWaves);
    };
}
