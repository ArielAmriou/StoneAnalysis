/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Utils
*/

#ifndef UTILS_HPP
    #define UTILS_HPP

namespace StoneAnalysis {
    using b2 = short int;
    using b4 = int;
    using desc = char[4];

    constexpr double RATE = 48000.0;

    #define SWAP(x) (x = (x >> 24) | ((x << 8) & 0x00ff0000) \
        | ((x >> 8) & 0x0000ff00) | (x << 24))
}

#endif
