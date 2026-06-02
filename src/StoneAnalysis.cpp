/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** StoneAnalysis
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <iomanip>
#include <algorithm>
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
        std::transform(_msg.begin(), _msg.end(), _msg.begin(),
            [](unsigned char c) {return std::toupper(c);});
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
        auto a = _in->analize();
        std::size_t usable = (a.size() / 2.0) + 1.0;
        std::map<double, std::size_t> dists;
        for (std::size_t i = 1; i < usable; i++) {
            auto dist = std::sqrt(std::pow(a[i].imag(), 2.0) + std::pow(a[i].real(), 2.0));
            dists.insert({dist, i});
        }
        std::cout << "Top " << _n << " frequencies:\n" << std::fixed << std::setprecision(1);
        auto iter = --dists.end();
        for (std::size_t i = 0; i < _n; i++) {
            auto value = iter->second * RATE / a.size();
            std::cout << value << " Hz\n";
            if (iter == dists.begin())
                break;
            iter--;
        }
    }

    void StoneAnalysis::cypher()
    {
        if (!_in)
            throw NotInitializeException();
        std::string msg = _msg + '\0';
        std::vector<int> bits;
        for (unsigned char c : msg)
            for (int i = NB_BITS - 1; i >= 0; --i)
                bits.push_back((c >> i) & 1);
        if (bits.size() > _in->_waves._data.size())
            throw MsgTooLongException();
        for (std::size_t i = 0; i < bits.size(); ++i)
            _in->_waves._data[i] = (_in->_waves._data[i] & ~1) | bits[i];
        _in->save(_out);
    }

    void StoneAnalysis::decypher()
    {
        if (!_in)
            throw NotInitializeException();
        std::string msg;
        std::size_t i = 0;
        while (i + NB_BITS <= _in->_waves._data.size()) {
            unsigned char c = 0;
            for (int b = NB_BITS - 1; b >= 0; --b)
                c |= (_in->_waves._data[i++] & 1) << b;
            if (c == '\0')
                break;
            msg += c;
        }
        std::cout << msg << "\n";
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