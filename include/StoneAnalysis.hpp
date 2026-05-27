/*
** EPITECH PROJECT, 2026
** StoneAnalysis
** File description:
** StoneAnalysis
*/

#ifndef STONEANALYSIS_HPP_
    #define STONEANALYSIS_HPP_

    #include <unordered_map>
    #include <functional>
    #include <string>
    #include <string_view>
    #include <queue>
    #include <optional>
    #include "Wav.hpp"

namespace StoneAnalysis {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr std::string_view HELP = "public/help.txt";
    constexpr std::string_view FLAG_HELP = "--help";
    constexpr std::size_t NB_ARGS_A = 2;
    constexpr std::size_t NB_ARGS_C = 3;
    constexpr std::size_t NB_ARGS_D = 1;
    constexpr std::size_t NB_BITS = 8;

    class StoneAnalysis {
        public:

        struct Func {
            std::function<void (std::queue<std::string>)> parser;
            std::function<void ()> methode;
        };

        enum class Mode {
            Analyze,
            Cypher,
            Decypher,
        };

        StoneAnalysis(std::queue<std::string> args);

        void run();

        void help();

        private:
            Mode getMode(std::string);
            void initModes();
            void analizeParser(std::queue<std::string>);
            void cypherParser(std::queue<std::string>);
            void decypherParser(std::queue<std::string>);

            void analize();
            void cypher();
            void decypher();

            Mode _mode;
            std::optional<Wav> _in;
            std::string _out;
            std::string _msg;
            std::size_t _n;

            std::unordered_map<Mode, Func> _modes;
            static const std::unordered_map<
                Mode, std::pair<std::string, std::string>> _modesStr;
    };
}

#endif /* !STONEANALYSIS_HPP_ */
