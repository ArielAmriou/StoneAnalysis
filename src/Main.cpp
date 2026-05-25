/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** Main
*/

#include <iostream>
#include "Exception.hpp"
#include "StoneAnalysis.hpp"
#include "Wav.hpp"

int main(int ac, char **av)
{
    std::queue<std::string> args(std::deque<std::string>(av + 1, av + ac));
    try {
        StoneAnalysis::StoneAnalysis func;
        func.run(args);
    } catch (StoneAnalysis::StoneAnalysisException &e) {
        std::cerr << e.what() << std::endl;
        return StoneAnalysis::EPIERROR;
    }
    return StoneAnalysis::EPISUCCESS;
}