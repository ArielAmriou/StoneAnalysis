/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** StoneAnalysis
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include "StoneAnalysis.hpp"
#include "Exception.hpp"
#include "Wav.hpp"

namespace StoneAnalysis {
    StoneAnalysis::StoneAnalysis()
    {
        _modes[Mode::Analyze] = [this](std::queue<std::string> args)
            {analize(args);};
        _modes[Mode::Cypher] = [this](std::queue<std::string> args)
            {cypher(args);};
        _modes[Mode::Decypher] = [this](std::queue<std::string> args)
            {decypher(args);};
    }

    void StoneAnalysis::run(std::queue<std::string> args)
    {
        if (args.empty()) {
            help();
            throw WrongArgsException();
        }
        if (args.front() == FLAG_HELP)
            return help();
        try {
            auto find = _modes.find(getMode(args.front()));
            if (find == _modes.end())
                throw WrongArgsException();
            args.pop();
            find->second(args);
        } catch (StoneAnalysisException &e) {
            throw e;
        }
    }

    void StoneAnalysis::analize(std::queue<std::string> args)
    {
        if (args.size() != NB_ARGS_A)
            throw WrongArgsException();
        Wav wav(args.front());
        args.pop();
        std::size_t n;
        std::istringstream stream(args.front());
        stream >> n;
        if (stream.fail() || !stream.eof())
            throw WrongArgsException();
        std::cout << wav << std::endl;
        auto a = wav.analize();
        auto size = a.size();
        int i = 440 * size / 48000;
        std::cout << a[i].imag() << " : " <<  a[i].real() << std::endl;
    }

    void StoneAnalysis::cypher(std::queue<std::string> args)
    {
        if (args.size() != NB_ARGS_C)
            throw WrongArgsException();
        Wav wav(args.front());
        args.pop();
        std::string output = args.front();
        args.pop();
        std::string msg = args.front();
    }

    void StoneAnalysis::decypher(std::queue<std::string> args)
    {
        if (args.size() != NB_ARGS_D)
            throw WrongArgsException();
        Wav wav(args.front());
    }

    void StoneAnalysis::help()
    {
        std::ifstream file({std::string(HELP)});

        if (file.is_open())
            std::cout << file.rdbuf();
    }

    StoneAnalysis::Mode StoneAnalysis::getMode(std::string str)
    {
        for (auto iter = _modesStr.begin(); iter != _modesStr.end(); iter++) {
            if (iter->second.first == str || iter->second.second == str)
                return iter->first;
        }
        throw WrongArgsException();
    }

    const std::unordered_map<StoneAnalysis::Mode,
        std::pair<std::string, std::string>>StoneAnalysis::_modesStr = {
        {
            Mode::Analyze,
            {"--analyze", "-a"}
        },
        {
            Mode::Cypher,
            {"--cypher", "-c"}
        },
        {
            Mode::Decypher,
            {"--decypher", "-d"}
        },
    };
}