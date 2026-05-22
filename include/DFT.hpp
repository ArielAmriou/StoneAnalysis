/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** DFT
*/

#ifndef DFT_HPP_
#define DFT_HPP_

#include "IAnalyser.hpp"

namespace StoneAnalysis {
    class DFT: public IAnalyser {
        public:
            ~DFT() = default;
            std::vector<std::complex<double>> analize(std::vector<b2> waves);
    };
}

#endif /* !DFT_HPP_ */
