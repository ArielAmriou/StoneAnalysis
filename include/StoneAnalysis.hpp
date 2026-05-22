/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** StoneAnalysis
*/

#ifndef STONEANALYSIS_HPP_
#define STONEANALYSIS_HPP_

#define SWAP(x) (x = (x >> 24) | ((x << 8) & 0x00ff0000) \
        | ((x >> 8) & 0x0000ff00) | (x << 24))

namespace StoneAnalysis {

    using b2 = short int;
    using b4 = int;
    using desc = char[4];
}

#endif /* !STONEANALYSIS_HPP_ */
