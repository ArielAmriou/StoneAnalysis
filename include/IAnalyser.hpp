/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** IAnalyser
*/

#ifndef IANALYSER_HPP_
#define IANALYSER_HPP_

#include <vector>
#include <complex>

#include "Utils.hpp"

namespace StoneAnalysis {

    class IAnalyser {
        public:
            IAnalyser() = default;
            virtual ~IAnalyser() = default;

            virtual std::vector<std::complex<double>> analize(std::vector<b2>) = 0;
    };
}

#endif /* !IANALYSER_HPP_ */
