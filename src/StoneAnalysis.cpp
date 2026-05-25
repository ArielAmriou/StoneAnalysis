/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** StoneAnalysis
*/

#include "StoneAnalysis.hpp"
#include "Exception.hpp"

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
        if (args.empty())
            throw WrongArgsException();
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

    void StoneAnalysis::analize(std::queue<std::string>)
    {

    }

    void StoneAnalysis::cypher(std::queue<std::string>)
    {

    }

    void StoneAnalysis::decypher(std::queue<std::string>)
    {

    }

    void StoneAnalysis::help()
    {

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