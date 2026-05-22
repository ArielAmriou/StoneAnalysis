/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Main
*/

#include <iostream>

#include "Wav.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;

    StoneAnalysis::Wav wav(av[1]);
    std::cout << wav << std::endl;
    auto a = wav.analize();
    auto size = a.size();
    int i = 440 * size / 48000;
    std::cout << a[i].imag() << " : " <<  a[i].real() << std::endl;
    return 0;
}