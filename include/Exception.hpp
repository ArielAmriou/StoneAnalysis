/*
** EPITECH PROJECT, 2026
** 
** File description:
** Exception
*/

#ifndef STONEANALYSISEXCEPTION_HPP
    #define STONEANALYSISEXCEPTION_HPP

#include <exception>
#include <string>

namespace StoneAnalysis {
    class StoneAnalysisException : public std::exception {
        public:
            StoneAnalysisException(std::string str) : _str("Stone Analysis Error: " + str) {};

            virtual const char *what() const noexcept override
                    { return _str.c_str(); };
        private:
            std::string _str;
    };

    class WrongArgsException : public StoneAnalysisException {
        public:
            WrongArgsException() : StoneAnalysisException("Wrongs Args.") {};
    };

    class NoSuchFileException : public StoneAnalysisException {
        public:
            NoSuchFileException(std::string str) : StoneAnalysisException("No Such file: " + str + ".") {};
    };

    class NotInitializeException : public StoneAnalysisException {
        public:
            NotInitializeException() : StoneAnalysisException("Not Initialize") {};
    };
};

#endif