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
    StoneAnalysis::StoneAnalysis(std::queue<std::string> args)
    {
        initModes();
        if (args.empty()) {
            help();
            throw WrongArgsException();
        }
        if (args.front() == FLAG_HELP)
            help();
        else {
            try {
                _mode = getMode(args.front());
                auto find = _modes.find(_mode);
                if (find == _modes.end())
                    throw WrongArgsException();
                args.pop();
                find->second.parser(args);
            } catch (StoneAnalysisException &e) {
                throw e;
            }
        }
    }

    void StoneAnalysis::initModes()
    {
        _modes[Mode::Analyze] = {
            [this](std::queue<std::string> args) {analizeParser(args);},
            [this]() {analize();}
        };
        _modes[Mode::Cypher] = {
            [this](std::queue<std::string> args) {cypherParser(args);},
            [this]() {cypher();}
        };
        _modes[Mode::Decypher] = {
            [this](std::queue<std::string> args) {decypherParser(args);},
            [this]() {decypher();}
        };
    }

    void StoneAnalysis::run()
    {
        auto find = _modes.find(_mode);
        if (find != _modes.end())
            find->second.methode();
    }

    void StoneAnalysis::analizeParser(std::queue<std::string> args)
    {
        if (args.size() != NB_ARGS_A)
            throw WrongArgsException();
        _in = Wav(args.front());
        args.pop();
        std::istringstream stream(args.front());
        stream >> _n;
        if (stream.fail() || !stream.eof())
            throw WrongArgsException();
    }

    void StoneAnalysis::cypherParser(std::queue<std::string> args)
    {
        if (args.size() != NB_ARGS_C)
            throw WrongArgsException();
        _in = Wav(args.front());
        args.pop();
        _out = args.front();
        args.pop();
        _msg = args.front();
    }

    void StoneAnalysis::decypherParser(std::queue<std::string> args)
    {
        if (args.size() != NB_ARGS_D)
            throw WrongArgsException();
        _in = Wav(args.front());
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

    void StoneAnalysis::analize()
    {
        if (!_in)
            throw NotInitializeException();
        std::cout << *_in << std::endl;
        auto a = _in->analize();
        auto size = a.size();
        int i = 440 * size / 48000;
        std::cout << a[i].imag() << " : " <<  a[i].real() << std::endl;
    }

    void StoneAnalysis::cypher()
    {
        if (!_in)
            throw NotInitializeException();
    }

    void StoneAnalysis::decypher()
    {
        if (!_in)
            throw NotInitializeException();
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