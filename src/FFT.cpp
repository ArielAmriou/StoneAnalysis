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
            = getAmplitudes(std::move(evenPart));
        std::vector<std::complex<double>> oddComputed
            = getAmplitudes(std::move(oddPart));

        std::complex<double> base(cos((2 * M_PI) / N), -sin((2 * M_PI) / N));
        std::complex<double> w(1.0, 0.0);
        std::vector<std::complex<double>> amplitudes(N);
        for (std::size_t k = 0; k < M; ++k) {
            std::complex<double> C = w * oddComputed[k];
            amplitudes[k] = evenComputed[k] + C;
            amplitudes[k + M] = evenComputed[k] - C;
            w *= base;
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
