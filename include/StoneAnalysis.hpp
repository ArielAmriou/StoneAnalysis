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

    #define SWAP(x) (x = (x >> 24) | ((x << 8) & 0x00ff0000) \
        | ((x >> 8) & 0x0000ff00) | (x << 24))

namespace StoneAnalysis {

    using b2 = short int;
    using b4 = int;
    using desc = char[4];

    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr std::string_view HELP = "public/help.txt";
    constexpr std::string_view FLAG_HELP = "--help";
    constexpr std::size_t NB_ARGS_A = 2;
    constexpr std::size_t NB_ARGS_C = 3;
    constexpr std::size_t NB_ARGS_D = 1;

    class StoneAnalysis {
        public:

        enum class Mode {
            Analyze,
            Cypher,
            Decypher,
        };

        StoneAnalysis();

        void run(std::queue<std::string> args);

        void help();

        private:
            Mode getMode(std::string);
            void analize(std::queue<std::string>);
            void cypher(std::queue<std::string>);
            void decypher(std::queue<std::string>);

            std::unordered_map<Mode, std::function<void (std::queue<std::string>)>> _modes;
            static const std::unordered_map<
                Mode, std::pair<std::string, std::string>> _modesStr;
    };
}

#endif /* !STONEANALYSIS_HPP_ */
